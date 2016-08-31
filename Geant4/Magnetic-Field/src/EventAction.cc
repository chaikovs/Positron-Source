#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"

EventAction::EventAction(RunAction* run):
G4UserEventAction(),
fRunAct(run), fPrintModulo(0)
{
    fPrintModulo = 100;
}

EventAction::~EventAction(){}

void EventAction::BeginOfEventAction(const G4Event*)
{
    fEnergyAbs = 0.;
}

void EventAction::EndOfEventAction(const G4Event*)
{
    fRunAct->fillPerEvent(fEnergyAbs);
}
