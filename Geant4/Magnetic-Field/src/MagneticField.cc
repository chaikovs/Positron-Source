#include "MagneticField.hh"

#include "G4SystemOfUnits.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4ClassicalRK4.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4ChordFinder.hh"
#include "G4UserLimits.hh"
#include <iomanip>
#include <fstream>

MagneticField::MagneticField()
{
    SetFieldValue(G4ThreeVector(0., 0., 0.));
}

MagneticField::~MagneticField(){}

void MagneticField::GetFieldValue(const double Point[4],double *Bfield) const
{
    // Point[0],Point[1],Point[2] are x-, y-, z-cordinates, Point[3] is time
    G4double posR = std::sqrt(Point[0]*Point[0] + Point[1]*Point[1]);
    G4double z = Point[2]-107.000002;
    
    if(posR <= (15. + z/40.) && z >= 0. && z <= 200.)
    {
        Bfield[0] = 0.;
        Bfield[1] = 0.;
        Bfield[2] = (6./(1.+55.*z/1000.))*tesla;
    }
    else
    {
        Bfield[0] = 0.;
        Bfield[1] = 0.;
        Bfield[2] = 0.;
    }
}

void MagneticField::SetFieldValue(G4ThreeVector fieldVal)
{
    fieldValue = fieldVal;
    G4FieldManager* fieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
    fieldMgr->SetDetectorField(this);
    G4Mag_UsualEqRhs* equation = new G4Mag_UsualEqRhs(this);
    G4MagIntegratorStepper* stepper = new G4ClassicalRK4(equation);
    G4double minStep = 0.01*mm;
    G4ChordFinder* chordFinder = new G4ChordFinder((G4MagneticField*)this,minStep,stepper);
    fieldMgr->SetAccuraciesWithDeltaOneStep(0.01*mm);
    fieldMgr->SetDeltaIntersection(0.1*mm);
    chordFinder->SetDeltaChord(1.*mm);
    fieldMgr->SetChordFinder(chordFinder);
}



