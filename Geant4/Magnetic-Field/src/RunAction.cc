#include "RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include <iomanip>
#include <fstream>

RunAction::RunAction():
G4UserRunAction(){}

RunAction::~RunAction(){}

void RunAction::BeginOfRunAction(const G4Run*)
{
    fSumEAbs = fSum2EAbs = 0.;
}

void RunAction::fillPerEvent(G4double EAbs)
{
    fSumEAbs += EAbs;
    fSum2EAbs += EAbs*EAbs;

    std::ofstream file("EDEP.dat", std::ios::app);
    file << std::setw(10) << EAbs << " " << std::endl;
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{
    G4int NbOfEvents = aRun->GetNumberOfEvent();
    if(NbOfEvents == 0)
        return;

    fSumEAbs /= NbOfEvents;
    fSum2EAbs /= NbOfEvents;
    G4double rmsEAbs = fSum2EAbs - fSumEAbs*fSumEAbs;
    if(rmsEAbs >0.)
        rmsEAbs = std::sqrt(rmsEAbs);
    else
        rmsEAbs = 0.;
}
