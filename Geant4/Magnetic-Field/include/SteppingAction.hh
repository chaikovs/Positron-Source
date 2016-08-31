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
    G4double x_pre;
    G4double y_pre;
    G4double z_pre;
    G4double x_post;
    G4double y_post;
    G4double z_post;
    G4double energy;
    G4double momentumX;
    G4double momentumY;
    G4double momentumZ;
    G4double momentumDirectionPhi;
    G4double momentumDirectionTheta;
    G4String nameOfParticle;
};
#endif
