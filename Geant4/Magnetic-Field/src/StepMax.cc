#include "StepMax.hh"

StepMax::StepMax(const G4String& processName, G4ProcessType type):
G4VDiscreteProcess(processName,type)
{
    fMaxStep1 = fMaxStep2 = DBL_MAX;
    fApplyMaxStep2 = true;
}

StepMax::~StepMax(){}

G4bool StepMax::IsApplicable(const G4ParticleDefinition& particle)
{
    return (particle.GetPDGCharge() != 0. && !particle.IsShortLived());
}

void StepMax::SetMaxStep1(G4double step)
{
    fMaxStep1 = step;
}

void StepMax::SetMaxStep2(G4double step)
{
    fMaxStep2 = step;
}

void StepMax::ApplyMaxStep2(G4bool value)
{
    fApplyMaxStep2 = value;
}

G4double StepMax::PostStepGetPhysicalInteractionLength( const G4Track&, G4double, G4ForceCondition* condition)
{
    *condition = NotForced;
    if(fApplyMaxStep2)
        return fMaxStep2;
    else
        return fMaxStep1;
}

G4VParticleChange* StepMax::PostStepDoIt(const G4Track& aTrack, const G4Step&)
{
    aParticleChange.Initialize(aTrack);
    return &aParticleChange;
}

