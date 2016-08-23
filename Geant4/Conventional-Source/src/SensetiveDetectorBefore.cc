#include "SensitiveDetectorBefore.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <iomanip>
#include <fstream>

SensitiveDetectorBefore::SensitiveDetectorBefore(G4String name):
G4VSensitiveDetector(name)
{
    numberOfThePositrons = 0;
    numberOfTheElectrons = 0;
    numberOfTheInitialElectrons = 0;
    numberOfThePhotons = 0;
}

G4bool SensitiveDetectorBefore::ProcessHits(G4Step *step, G4TouchableHistory*)
{
    nameOfParticle = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();
    X = step->GetPreStepPoint()->GetPosition().x();
    Y = step->GetPreStepPoint()->GetPosition().y();
    G4double Z = step->GetPreStepPoint()->GetPosition().z();
    energy = step->GetTrack()->GetDynamicParticle()->GetKineticEnergy();

    if(step->IsFirstStepInVolume())
    {
        std::ofstream filePositron("BEFOREpositron.dat", std::ios::app);
        if(nameOfParticle == "e+")
        {
            numberOfThePositrons++;
        
            filePositron
            << std::setw(10) << X << " "
            << std::setw(10) << Y << " "
            << std::setw(20) << energy << " "
            << std::endl;
        }
    
        ID = step->GetTrack()->GetTrackID();
        std::ofstream fileInitialElectron("BEFOREinitialElectron.dat", std::ios::app);
        std::ofstream fileElectron("BEFOREelectron.dat", std::ios::app);
        if(nameOfParticle == "e-")
        {
            if(ID != 1)
            {
                numberOfTheElectrons++;
    
                fileElectron
                << std::setw(10) << X << " "
                << std::setw(10) << Y << " "
                << std::setw(10) << Z << " "
                << std::setw(20) << energy << " "
                << std::endl;
            }
            else
                if(ID == 1 && energy == 6000)
                {
                    numberOfTheInitialElectrons++;
                
                    fileInitialElectron
                    << std::setw(10) << X << " "
                    << std::setw(10) << Y << " "
                    << std::setw(10) << Z << " "
                    << std::setw(20) << energy << " "
                    << std::endl;
                }

        }
    
        std::ofstream fileGamma("BEFOREgamma.dat", std::ios::app);
        if(nameOfParticle == "gamma")
        {
            numberOfThePhotons++;
        
            fileGamma
            << std::setw(10) << X << " "
            << std::setw(10) << Y << " "
            << std::setw(20) << energy << " "
            << std::endl;
        }
    }
    return true;
}

SensitiveDetectorBefore::~SensitiveDetectorBefore()
{
    std::ofstream fileNum("BEFOREnumber.dat");
    fileNum << std::setw(10) << "Number of the initial electrons: " << numberOfTheInitialElectrons <<  std::endl;
    fileNum << std::setw(10) << "Number of the positrons: " << numberOfThePositrons <<  std::endl;
    fileNum << std::setw(10) << "Number of the electrons: " << numberOfTheElectrons <<  std::endl;
    fileNum << std::setw(10) << "Number of the gamma: " << numberOfThePhotons <<  std::endl;
}
