#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class DetectorConstruction;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
public:
    SteppingAction(DetectorConstruction*, EventAction*);
    virtual ~SteppingAction();
    virtual void UserSteppingAction(const G4Step*);
private:
    DetectorConstruction* fDetector;
    EventAction* fEventAction;
    G4int trackID;
    G4double x;
    G4double y;
    G4double z;
    G4double energy;
    G4double momentumX;
    G4double momentumY;
    G4double momentumZ;
    G4double momentumDirectionPhi;
    G4double momentumDirectionTheta;
    G4double numberOfThePositrons;
    G4String nameOfParticle;
    G4double Energy;
    G4double MomentumX;
    G4double MomentumY;
    G4double MomentumZ;
    G4double MomentumDirectionPhi;
    G4double MomentumDirectionTheta;
    G4double X;
    G4double Y;
    G4double Z;
    G4int ID;
    G4bool firstStepInVolume;
};
#endif