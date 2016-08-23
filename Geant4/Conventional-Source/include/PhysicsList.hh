#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class PhysicsListMessenger;

class PhysicsList: public G4VModularPhysicsList
{
public:
    PhysicsList();
    virtual ~PhysicsList();
    virtual void ConstructParticle();
    virtual void ConstructProcess();
    void AddPhysicsList(const G4String& name);
    void AddDecay();
    void AddRadioactiveDecay();
    void AddStepMax();
private:
    G4VPhysicsConstructor* fEmPhysicsList;
    G4String fEmName;
    G4double currentDefaultCut;
};
#endif

