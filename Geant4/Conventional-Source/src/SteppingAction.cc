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
fDetector(det), fEventAction(evt), trackID(0), numberOfThePositrons(0){}

SteppingAction::~SteppingAction()
{
    std::ofstream filePositron("TARGETnumber.dat", std::ios::app);
    filePositron << std::setw(10) << "Number of the positrons: " << numberOfThePositrons <<  std::endl;
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    G4VPhysicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
    G4VPhysicalVolume* where = step->GetTrack()->GetNextVolume();
    G4double edep = step->GetTotalEnergyDeposit();
    if(volume == fDetector->GetpTarget())
        fEventAction->AddAbs(edep);
    
    nameOfParticle = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();
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
    
    std::ofstream filePositron("TARGETpositron.dat", std::ios::app);
    firstStepInVolume = step->IsFirstStepInVolume();
    
    if(nameOfParticle == "e+")
    {
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
    
    if(where == fDetector->GetpSD() && ID == trackID)
    {
        if(nameOfParticle == "e+")
        {
            numberOfThePositrons++;
            filePositron
            << std::setw(10) << x << " "
            << std::setw(10) << y << " "
            << std::setw(10) << z << " "
            << std::setw(20) << energy << " "
            << std::setw(20) << momentumX << " "
            << std::setw(10) << momentumY << " "
            << std::setw(10) << momentumZ << " "
            << std::setw(20) << momentumDirectionPhi << " "
            << std::setw(10) << momentumDirectionTheta << " "
            << std::endl;
        }
    }
}
