#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VProcess.hh"

SteppingAction::SteppingAction(DetectorConstruction* det, EventAction* evt):
G4UserSteppingAction(),
fDetector(det), fEventAction(evt){}

SteppingAction::~SteppingAction(){}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    G4VPhysicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
    G4double edep = step->GetTotalEnergyDeposit();
    if(volume == fDetector->GetpTarget())
        fEventAction->AddAbs(edep);
    
    nameOfParticle = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();
    energy = step->GetTrack()->GetDynamicParticle()->GetKineticEnergy();
    momentumX = step->GetTrack()->GetDynamicParticle()->GetMomentum().x();
    momentumY = step->GetTrack()->GetDynamicParticle()->GetMomentum().y();
    momentumZ = step->GetTrack()->GetDynamicParticle()->GetMomentum().z();
    momentumDirectionPhi = step->GetTrack()->GetDynamicParticle()->GetMomentumDirection().phi()*180/M_PI;
    momentumDirectionTheta = step->GetTrack()->GetDynamicParticle()->GetMomentumDirection().theta()*180/M_PI;
    x_pre = step->GetPreStepPoint()->GetPosition().x();
    y_pre = step->GetPreStepPoint()->GetPosition().y();
    z_pre = step->GetPreStepPoint()->GetPosition().z();
    x_post = step->GetPostStepPoint()->GetPosition().x();
    y_post = step->GetPostStepPoint()->GetPosition().y();
    z_post = step->GetPostStepPoint()->GetPosition().z();
    
    
    std::ofstream file("STEP.dat", std::ios::app);
    file
    << std::setw(15) << nameOfParticle << " "
    << std::setw(20) << x_pre << " "
    << std::setw(15) << y_pre << " "
    << std::setw(15) << z_pre << " "
    << std::setw(20) << x_post << " "
    << std::setw(15) << y_post << " "
    << std::setw(15) << z_post << " "
    << std::setw(20) << energy << " "
    << std::setw(20) << momentumX << " "
    << std::setw(10) << momentumY << " "
    << std::setw(10) << momentumZ << " "
    << std::setw(20) << momentumDirectionPhi << " "
    << std::setw(10) << momentumDirectionTheta << " "
    << std::endl;

}
