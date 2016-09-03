#include "SensitiveDetectorAfter.hh"

#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include <iomanip>
#include <fstream>

SensitiveDetectorAfter::SensitiveDetectorAfter(G4String name):
G4VSensitiveDetector(name){}

G4bool SensitiveDetectorAfter::ProcessHits(G4Step *step, G4TouchableHistory*)
{
    G4bool firstStepInVolume = step->IsFirstStepInVolume();
    
    if(firstStepInVolume)
    {
        nameOfParticle = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();
        energy = step->GetTrack()->GetDynamicParticle()->GetKineticEnergy();
        momentumDirectionPhi = step->GetTrack()->GetDynamicParticle()->GetMomentumDirection().phi()*180/M_PI;
        momentumDirectionTheta = step->GetTrack()->GetDynamicParticle()->GetMomentumDirection().theta()*180/M_PI;

        if(nameOfParticle == "e+")
        {
            momentumX = step->GetTrack()->GetDynamicParticle()->GetMomentum().x();
            momentumY = step->GetTrack()->GetDynamicParticle()->GetMomentum().y();
            momentumZ = step->GetTrack()->GetDynamicParticle()->GetMomentum().z();
            X = step->GetPreStepPoint()->GetPosition().x();
            Y = step->GetPreStepPoint()->GetPosition().y();
            T_proper = step->GetTrack()->GetProperTime();
            T_global = step->GetTrack()->GetGlobalTime();
            T_local = step->GetTrack()->GetLocalTime();
            std::ofstream filePX("AFTER_TARGET/P_X.dat", std::ios::app);
            std::ofstream filePY("AFTER_TARGET/P_Y.dat", std::ios::app);
            std::ofstream filePE("AFTER_TARGET/P_E.dat", std::ios::app);
            std::ofstream filePMX("AFTER_TARGET/P_MX.dat", std::ios::app);
            std::ofstream filePMY("AFTER_TARGET/P_MY.dat", std::ios::app);
            std::ofstream filePMZ("AFTER_TARGET/P_MZ.dat", std::ios::app);
            std::ofstream filePP("AFTER_TARGET/P_P.dat", std::ios::app);
            std::ofstream filePT("AFTER_TARGET/P_T.dat", std::ios::app);
            std::ofstream filePTg("AFTER_TARGET/P_TG.dat", std::ios::app);
            std::ofstream filePTl("AFTER_TARGET/P_TL.dat", std::ios::app);
            std::ofstream filePTp("AFTER_TARGET/P_TP.dat", std::ios::app);
            filePX << std::setw(20) << X << std::endl;
            filePY << std::setw(20) << Y << std::endl;
            filePE << std::setw(20) << energy << std::endl;
            filePMX << std::setw(20) << momentumX << std::endl;
            filePMY << std::setw(20) << momentumY << std::endl;
            filePMZ << std::setw(20) << momentumZ << std::endl;
            filePP << std::setw(20) << momentumDirectionPhi << std::endl;
            filePT << std::setw(20) << momentumDirectionTheta << std::endl;
            filePTg << std::setw(20) << T_global << std::endl;
            filePTl << std::setw(20) << T_local << std::endl;
            filePTp << std::setw(20) << T_proper << std::endl;
        }
        
        if(nameOfParticle == "e-")
        {
            std::ofstream fileEE("AFTER_TARGET/E_E.dat", std::ios::app);
            std::ofstream fileEP("AFTER_TARGET/E_P.dat", std::ios::app);
            std::ofstream fileET("AFTER_TARGET/E_T.dat", std::ios::app);
            fileEE << std::setw(20) << energy << std::endl;
            fileEP << std::setw(20) << momentumDirectionPhi << std::endl;
            fileET << std::setw(20) << momentumDirectionTheta << std::endl;
        }
        
        if(nameOfParticle == "gamma")
        {
            std::ofstream fileGE("AFTER_TARGET/G_E.dat", std::ios::app);
            std::ofstream fileGP("AFTER_TARGET/G_P.dat", std::ios::app);
            std::ofstream fileGT("AFTER_TARGET/G_T.dat", std::ios::app);
            fileGE << std::setw(20) << energy << std::endl;
            fileGP << std::setw(20) << momentumDirectionPhi << std::endl;
            fileGT << std::setw(20) << momentumDirectionTheta << std::endl;
        }
    }
    return true;
}

SensitiveDetectorAfter::~SensitiveDetectorAfter(){}
