#include "SensitiveDetector.hh"

#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

SensitiveDetector::SensitiveDetector(G4String name):
G4VSensitiveDetector(name)
{
    numberOfThePositrons = 0;
}

G4bool SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory*)
{
    nameOfParticle = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();
    energy = step->GetTrack()->GetDynamicParticle()->GetKineticEnergy();
    momentumX = step->GetTrack()->GetDynamicParticle()->GetMomentum().x();
    momentumY = step->GetTrack()->GetDynamicParticle()->GetMomentum().y();
    momentumZ = step->GetTrack()->GetDynamicParticle()->GetMomentum().z();
    momentumDirectionPhi = step->GetTrack()->GetDynamicParticle()->GetMomentumDirection().phi()*180/M_PI;
    momentumDirectionTheta = step->GetTrack()->GetDynamicParticle()->GetMomentumDirection().theta()*180/M_PI;
    X = step->GetPreStepPoint()->GetPosition().x();
    Y = step->GetPreStepPoint()->GetPosition().y();

    std::ofstream filePositron("POSITRON.dat", std::ios::app);
    if(nameOfParticle == "e+")
    {
        numberOfThePositrons++;
        filePositron
        << std::setw(10) << X << " "
        << std::setw(10) << Y << " "
        << std::setw(20) << energy << " "
        << std::setw(20) << momentumX << " "
        << std::setw(10) << momentumY << " "
        << std::setw(10) << momentumZ << " "
        << std::setw(20) << momentumDirectionPhi << " "
        << std::setw(10) << momentumDirectionTheta << " "
        << std::endl;
    }

    step->GetTrack()->SetTrackStatus(fStopAndKill);
    return true;
}

SensitiveDetector::~SensitiveDetector(){}
