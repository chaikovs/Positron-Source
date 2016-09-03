#ifndef SENSITIVEDETECTORBEFORE
#define SENSITIVEDETECTORBEFORE

#include <G4VSensitiveDetector.hh>

class G4Step;
class G4TouchableHistory;

class SensitiveDetectorBefore: public G4VSensitiveDetector
{
private:
    G4String nameOfParticle;
    G4double X;
    G4double Y;
    G4double energy;
    G4int ID;
public:
    SensitiveDetectorBefore(G4String name);
    ~SensitiveDetectorBefore();
    G4bool ProcessHits(G4Step *step, G4TouchableHistory*);
};
#endif
