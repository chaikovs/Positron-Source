#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class RunAction;

class EventAction : public G4UserEventAction
{
public:
    EventAction(RunAction*);
    virtual ~EventAction();
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
    void AddAbs(G4double de){fEnergyAbs += de;};
private:
    RunAction*    fRunAct;
    G4double      fEnergyAbs;
    G4int         fPrintModulo;                             
};
#endif

    
