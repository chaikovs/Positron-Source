#include "SensitiveDetector.hh"

#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include <iomanip>
#include <fstream>

SensitiveDetector::SensitiveDetector(G4String name):
G4VSensitiveDetector(name){}

G4bool SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory*)
{
    nameOfParticle = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();
    energy = step->GetTrack()->GetDynamicParticle()->GetKineticEnergy();
    momentumDirectionPhi = step->GetTrack()->GetDynamicParticle()->GetMomentumDirection().phi()*180/M_PI;
    momentumDirectionTheta = step->GetTrack()->GetDynamicParticle()->GetMomentumDirection().theta()*180/M_PI;
    
    if(nameOfParticle == "e+")
    {
        std::ofstream filePX("AFTER_MAGNET/P_X.dat", std::ios::app);
        std::ofstream filePY("AFTER_MAGNET/P_Y.dat", std::ios::app);
        std::ofstream filePE("AFTER_MAGNET/P_E.dat", std::ios::app);
        std::ofstream filePMX("AFTER_MAGNET/P_MX.dat", std::ios::app);
        std::ofstream filePMY("AFTER_MAGNET/P_MY.dat", std::ios::app);
        std::ofstream filePMZ("AFTER_MAGNET/P_MZ.dat", std::ios::app);
        std::ofstream filePP("AFTER_MAGNET/P_P.dat", std::ios::app);
        std::ofstream filePT("AFTER_MAGNET/P_T.dat", std::ios::app);
        std::ofstream filePTg("AFTER_MAGNET/P_TG.dat", std::ios::app);
        std::ofstream filePTl("AFTER_MAGNET/P_TL.dat", std::ios::app);
        std::ofstream filePTp("AFTER_MAGNET/P_TP.dat", std::ios::app);
        momentumX = step->GetTrack()->GetDynamicParticle()->GetMomentum().x();
        momentumY = step->GetTrack()->GetDynamicParticle()->GetMomentum().y();
        momentumZ = step->GetTrack()->GetDynamicParticle()->GetMomentum().z();
        X = step->GetPreStepPoint()->GetPosition().x();
        Y = step->GetPreStepPoint()->GetPosition().y();
        T_proper = step->GetTrack()->GetProperTime();
        T_global = step->GetTrack()->GetGlobalTime();
        T_local = step->GetTrack()->GetLocalTime();
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
        std::ofstream fileEE("AFTER_MAGNET/E_E.dat", std::ios::app);
        std::ofstream fileEP("AFTER_MAGNET/E_P.dat", std::ios::app);
        std::ofstream fileET("AFTER_MAGNET/E_T.dat", std::ios::app);
        fileEE << std::setw(20) << energy << std::endl;
        fileEP << std::setw(20) << momentumDirectionPhi << std::endl;
        fileET << std::setw(20) << momentumDirectionTheta << std::endl;
    }
    
    if(nameOfParticle == "gamma")
    {
        std::ofstream fileGE("AFTER_MAGNET/G_E.dat", std::ios::app);
        std::ofstream fileGP("AFTER_MAGNET/G_P.dat", std::ios::app);
        std::ofstream fileGT("AFTER_MAGNET/G_T.dat", std::ios::app);
        fileGE << std::setw(20) << energy << std::endl;
        fileGP << std::setw(20) << momentumDirectionPhi << std::endl;
        fileGT << std::setw(20) << momentumDirectionTheta << std::endl;
    }

    step->GetTrack()->SetTrackStatus(fStopAndKill);
    return true;
}

SensitiveDetector::~SensitiveDetector(){}
