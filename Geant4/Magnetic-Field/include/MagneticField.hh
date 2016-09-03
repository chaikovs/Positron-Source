#ifndef MagneticField_H
#define MagneticField_H 1

#include "globals.hh"
#include "G4MagneticField.hh"
#include "G4ThreeVector.hh"

class MagneticField : public G4MagneticField
{
public:
    MagneticField();
    virtual ~MagneticField();
    virtual void GetFieldValue(const  double Point[4], double *Bfield) const;
    void SetFieldValue(G4ThreeVector);
private:
    G4ThreeVector fieldValue;
};
#endif

