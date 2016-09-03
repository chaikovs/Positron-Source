#include "SensitiveDetectorBefore.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <iomanip>
#include <fstream>

SensitiveDetectorBefore::SensitiveDetectorBefore(G4String name):
G4VSensitiveDetector(name){}

G4bool SensitiveDetectorBefore::ProcessHits(G4Step *step, G4TouchableHistory*)
{
    nameOfParticle = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();
    X = step->GetPreStepPoint()->GetPosition().x();
    Y = step->GetPreStepPoint()->GetPosition().y();
    energy = step->GetTrack()->GetDynamicParticle()->GetKineticEnergy();

    if(step->IsFirstStepInVolume())
    {
        std::ofstream filePX("BEFORE_TARGET/P_X.dat", std::ios::app);
        std::ofstream filePY("BEFORE_TARGET/P_Y.dat", std::ios::app);
        std::ofstream filePE("BEFORE_TARGET/P_E.dat", std::ios::app);
        if(nameOfParticle == "e+")
        {
            filePX << std::setw(20) << X << std::endl;
            filePY << std::setw(20) << Y << std::endl;
            filePE << std::setw(20) << energy << std::endl;
        }
    
        ID = step->GetTrack()->GetTrackID();
        std::ofstream fileIEX("BEFORE_TARGET/IE_X.dat", std::ios::app);
        std::ofstream fileIEY("BEFORE_TARGET/IE_Y.dat", std::ios::app);
        std::ofstream fileEX("BEFORE_TARGET/E_X.dat", std::ios::app);
        std::ofstream fileEY("BEFORE_TARGET/E_Y.dat", std::ios::app);
        std::ofstream fileEE("BEFORE_TARGET/E_E.dat", std::ios::app);
        if(nameOfParticle == "e-")
        {
            if(ID != 1)
            {
                fileEX << std::setw(20) << X << std::endl;
                fileEY << std::setw(20) << Y << std::endl;
                fileEE << std::setw(20) << energy << std::endl;
            }
            else
                if(ID == 1 && energy == 6000)
                {
                    fileIEX << std::setw(20) << X << std::endl;
                    fileIEY << std::setw(20) << Y << std::endl;
                }

        }
    
        std::ofstream fileGX("BEFORE_TARGET/G_X.dat", std::ios::app);
        std::ofstream fileGY("BEFORE_TARGET/G_Y.dat", std::ios::app);
        std::ofstream fileGE("BEFORE_TARGET/G_E.dat", std::ios::app);
        if(nameOfParticle == "gamma")
        {
            fileGX << std::setw(20) << X << std::endl;
            fileGY << std::setw(20) << Y << std::endl;
            fileGE << std::setw(20) << energy << std::endl;
        }
    }
    return true;
}

SensitiveDetectorBefore::~SensitiveDetectorBefore(){}
