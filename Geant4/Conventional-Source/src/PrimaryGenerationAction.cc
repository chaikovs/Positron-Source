#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "globals.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction*):
G4VUserPrimaryGeneratorAction(),
fParticleGun(0)
{
    fParticleGun = new G4GeneralParticleSource();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
