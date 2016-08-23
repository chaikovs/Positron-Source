#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include <iomanip>
#include <fstream>

EventAction::EventAction(RunAction* run):
G4UserEventAction(),
fRunAct(run), fPrintModulo(0)
{
    fPrintModulo = 100;
}

EventAction::~EventAction(){}

void EventAction::BeginOfEventAction(const G4Event* evt)
{
    fEnergyAbs = 0.;
    
    G4int x0 = evt->GetPrimaryVertex()->GetX0();
    G4int y0 = evt->GetPrimaryVertex()->GetY0();
    std::ofstream fileEvent("EVENT.dat", std::ios::app);
    fileEvent << std::setw(10) << x0 << std::setw(10) << y0 << std::endl;
}

void EventAction::EndOfEventAction(const G4Event*)
{
    fRunAct->fillPerEvent(fEnergyAbs);
}
