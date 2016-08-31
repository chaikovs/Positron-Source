#ifndef Field_h
#define Field_h 1

#include "globals.hh"
#include "G4ElectroMagneticField.hh"

class Field : public G4ElectroMagneticField
{
public:
    Field();
    virtual ~Field();
    /// DoesFieldChangeEnergy() returns true.
    virtual G4bool DoesFieldChangeEnergy() const { return true; };
    /// GetFieldValue() returns the field value at a given point[].
    /// field is really field[6]: Bx,By,Bz,Ex,Ey,Ez.
    /// point[] is in global coordinates: x,y,z,t.
    virtual void GetFieldValue(const G4double Point[4], G4double* Bfield) const;
};
#endif
