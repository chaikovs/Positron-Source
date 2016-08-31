#ifndef PhysListOpt4_h
#define PhysListOpt4_h 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"


class PhysListOpt4 : public G4VPhysicsConstructor
{
public:
    PhysListOpt4(const G4String& name = "opt4");
    ~PhysListOpt4();
    virtual void ConstructParticle();
    virtual void ConstructProcess();
};
#endif
