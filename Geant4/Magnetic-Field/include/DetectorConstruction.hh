#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "MagneticField.hh"
#include "DetectorMessenger.hh"
#include "globals.hh"

class G4Box;
class G4Tubs;
class G4Cons;
class G4VSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();
    const G4VPhysicalVolume* GetpWorld(){return fPhysiWorld;};
    const G4VPhysicalVolume* GetpTarget(){return fPhysiTarget;};
    const G4VPhysicalVolume* GetpSD(){return fPhysiSD;};
    const G4VPhysicalVolume* GetpSDB(){return fPhysiSDB;};
    const G4VPhysicalVolume* GetpSDA(){return fPhysiSDA;};
    void ConstructSDandField();
    void SetTargetThickness(G4double);
	double GetTargetThickness() const;
private:
    G4double fTargetThickness;
    G4Material* W;
    G4Material* Galactic;
    G4Material* Cu;
    G4Box* fSolidWorld;
    G4LogicalVolume* fLogicWorld;
    G4VPhysicalVolume* fPhysiWorld;
    G4Tubs* fSolidTarget;
    G4LogicalVolume* fLogicTarget;
    G4VPhysicalVolume* fPhysiTarget;
    G4Tubs* fSolidSD;
    G4LogicalVolume* fLogicSD;
    G4VPhysicalVolume* fPhysiSD;
    G4Tubs* fSolidSDB;
    G4LogicalVolume* fLogicSDB;
    G4VPhysicalVolume* fPhysiSDB;
    G4Tubs* fSolidSDA;
    G4LogicalVolume* fLogicSDA;
    G4VPhysicalVolume* fPhysiSDA;
    G4Cons* fSolidM;
    G4LogicalVolume* fLogicM;
    G4VPhysicalVolume* fPhysiM;
    G4Cons* fSolidMF;
    G4LogicalVolume* fLogicMF;
    G4VPhysicalVolume* fPhysiMF;
    DetectorMessenger* fDetectorMessenger;
    void DefineMaterials();
    G4VPhysicalVolume* ConstructCalorimeter();
    static G4ThreadLocal MagneticField *magField;
};
#endif

