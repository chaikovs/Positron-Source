#ifndef SENSITIVEDETECTOR
#define SENSITIVEDETECTOR

#include <G4VSensitiveDetector.hh>

class G4Step;
class G4TouchableHistory;

class SensitiveDetector: public G4VSensitiveDetector
{
private:
    G4String nameOfParticle;
    G4double energy;
    G4double momentumX;
    G4double momentumY;
    G4double momentumZ;
    G4double momentumDirectionPhi;
    G4double momentumDirectionTheta;
    G4double X;
    G4double Y;
    G4double T_global;
    G4double T_local;
    G4double T_proper;
public:
    SensitiveDetector(G4String name);
    ~SensitiveDetector();
    G4bool ProcessHits(G4Step *step, G4TouchableHistory*);
};

#endif
