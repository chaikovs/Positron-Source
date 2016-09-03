#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VProcess.hh"
#include "Randomize.hh"
#include <iomanip>
#include <fstream>

SteppingAction::SteppingAction(DetectorConstruction* det, EventAction* evt):
G4UserSteppingAction(),
fDetector(det), fEventAction(evt), trackID(0)
{
    for(int i = -sx/2; i < sx/2; ++i)
    {
        for(int j = -sy/2; j < sy/2; ++j)
        {
            for(int k = 0; k < sz; ++k)
            {
                depEn[i+sx/2][j+sy/2][k] = 0;
                number[i+sx/2][j+sy/2][k] = 0;
            }
        }
    }
}

SteppingAction::~SteppingAction()
{
    std::ofstream fileBijk("TARGET/B_ijk.dat", std::ios::app);
    std::ofstream fileBN("TARGET/B_N.dat", std::ios::app);
    std::ofstream fileBDE("TARGET/B_DE.dat", std::ios::app);
    for(int i = -sx/2; i < sx/2; ++i)
    {
        for(int j = -sy/2; j < sy/2; ++j)
        {
            for(int k = 0; k < sz; ++k)
            {
                fileBijk << std::setw(20) << i << std::setw(20) << j << std::setw(20) << k << std::endl;
                fileBN << std::setw(20) << number[i+sx/2][j+sy/2][k] << std::endl;
                fileBDE << std::setw(20) << depEn[i+sx/2][j+sy/2][k] << std::endl;
            }
        }
    }
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    G4VPhysicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
    G4VPhysicalVolume* where = step->GetTrack()->GetNextVolume();
    G4double edep = step->GetTotalEnergyDeposit();
    if(volume == fDetector->GetpTarget())
    {
        fEventAction->AddAbs(edep);
    
        nameOfParticle = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();
        if(nameOfParticle == "e+")
        {
            Energy = step->GetTrack()->GetDynamicParticle()->GetKineticEnergy();
            MomentumX = step->GetTrack()->GetDynamicParticle()->GetMomentum().x();
            MomentumY = step->GetTrack()->GetDynamicParticle()->GetMomentum().y();
            MomentumZ = step->GetTrack()->GetDynamicParticle()->GetMomentum().z();
            MomentumDirectionPhi = step->GetTrack()->GetDynamicParticle()->GetMomentumDirection().phi()*180/M_PI;
            MomentumDirectionTheta = step->GetTrack()->GetDynamicParticle()->GetMomentumDirection().theta()*180/M_PI;
            X = step->GetPreStepPoint()->GetPosition().x();
            Y = step->GetPreStepPoint()->GetPosition().y();
            Z = step->GetPreStepPoint()->GetPosition().z();
            ID = step->GetTrack()->GetTrackID();
            firstStepInVolume = step->IsFirstStepInVolume();
        
            if (firstStepInVolume)
            {
                trackID = ID;
                x = X;
                y = Y;
                z = Z;
                momentumX = MomentumX;
                momentumY = MomentumY;
                momentumZ = MomentumZ;
                momentumDirectionPhi = MomentumDirectionPhi;
                momentumDirectionTheta = MomentumDirectionTheta;
                energy = Energy;
            }
        }
        
        if(where == fDetector->GetpSDA() && ID == trackID)
        {
            if(nameOfParticle == "e+")
            {
                std::ofstream filePX("TARGET/P_X.dat", std::ios::app);
                std::ofstream filePY("TARGET/P_Y.dat", std::ios::app);
                std::ofstream filePZ("TARGET/P_Z.dat", std::ios::app);
                std::ofstream filePE("TARGET/P_E.dat", std::ios::app);
                std::ofstream filePMX("TARGET/P_MX.dat", std::ios::app);
                std::ofstream filePMY("TARGET/P_MY.dat", std::ios::app);
                std::ofstream filePMZ("TARGET/P_MZ.dat", std::ios::app);
                std::ofstream filePP("TARGET/P_P.dat", std::ios::app);
                std::ofstream filePT("TARGET/P_T.dat", std::ios::app);
                filePX << std::setw(20) << x << std::endl;
                filePY << std::setw(20) << y << std::endl;
                filePZ << std::setw(20) << z << std::endl;
                filePE << std::setw(20) << energy << std::endl;
                filePMX << std::setw(20) << momentumX << std::endl;
                filePMY << std::setw(20) << momentumY << std::endl;
                filePMZ << std::setw(20) << momentumZ << std::endl;
                filePP << std::setw(20) << momentumDirectionPhi << std::endl;
                filePT << std::setw(20) << momentumDirectionTheta << std::endl;
            }
        }
        x_pre = step->GetPreStepPoint()->GetPosition().x();
        y_pre = step->GetPreStepPoint()->GetPosition().y();
        z_pre = step->GetPreStepPoint()->GetPosition().z() - 93.;
        for(int i = -sx/2; i < sx/2; ++i)
        {
            if(x_pre >= i && x_pre < i + 1)
            {
                for(int j = -sy/2; j < sy/2; ++j)
                {
                    if(y_pre >= j && y_pre < j + 1)
                    {
                        for(int k = 0; k < sz; ++k)
                        {
                            if(z_pre >= k && z_pre < k + 1)
                            {
                                depEn[i+sx/2][j+sy/2][k] += edep;
                                number[i+sx/2][j+sy/2][k]++;
                            }
                        }
                    }
                }
            }
        }
    }
}
