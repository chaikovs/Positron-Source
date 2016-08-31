#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization(DetectorConstruction* detector):
G4VUserActionInitialization(),
fDetector(detector){}

ActionInitialization::~ActionInitialization(){}

void ActionInitialization::BuildForMaster() const
{
    SetUserAction(new RunAction());
}

void ActionInitialization::Build() const
{
    SetUserAction(new PrimaryGeneratorAction(fDetector));
    RunAction* runAction = new RunAction();
    SetUserAction(runAction);
    EventAction* eventAction = new EventAction(runAction);
    SetUserAction(eventAction);
    SteppingAction* steppingAction = new SteppingAction(fDetector, eventAction);
    SetUserAction(steppingAction);
}
