#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4Box;
class G4Tubs;
class G4VSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class DetectorMessenger;
class Field;
class G4FieldManager;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();
    void CreateScorers();
    void UpdateGeometry();
    virtual G4VPhysicalVolume* Construct();
    const G4VPhysicalVolume* GetpWorld(){return fPhysiWorld;};
    const G4VPhysicalVolume* GetpTarget(){return fPhysiTarget;};
    const G4VPhysicalVolume* GetpSD(){return fPhysiSD;};
    void SetTargetThickness (G4double); 
    void PrintTargetThickness();    
	double GetTargetThickness() const;
    
    virtual void ConstructSDandField();
private:
    G4double fTargetThickness;
    G4Material* W;
    G4Material* Galactic;
    G4Box* fSolidWorld;
    G4LogicalVolume* fLogicWorld;
    G4VPhysicalVolume* fPhysiWorld;
    G4Tubs* fSolidTarget;
    G4LogicalVolume* fLogicTarget;
    G4VPhysicalVolume* fPhysiTarget;
    G4Tubs* fSolidSD;
    G4LogicalVolume* fLogicSD;
    G4VPhysicalVolume* fPhysiSD;
    G4Tubs* fSolidMF;
    G4LogicalVolume* fLogicMF;
    G4VPhysicalVolume* fPhysiMF;
    DetectorMessenger* fDetectorMessenger;
    void DefineMaterials();
    G4VPhysicalVolume* ConstructCalorimeter();
    static G4ThreadLocal Field* fField;
    G4FieldManager* fieldManager;
};
#endif

