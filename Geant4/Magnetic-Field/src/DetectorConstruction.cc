#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "SensitiveDetector.hh"
#include "SensitiveDetectorBefore.hh"
#include "SensitiveDetectorAfter.hh"
//----------- MAGNETIC FIELD -----------
#include "MagneticField.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4VSensitiveDetector.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4SDParticleFilter.hh"
#include "G4VSDFilter.hh"

DetectorConstruction::DetectorConstruction():
G4VUserDetectorConstruction(),
fDetectorMessenger(0)
{
    fTargetThickness = 7.*mm;
    DefineMaterials();
    G4NistManager* nistManager = G4NistManager::Instance();
    nistManager->SetVerbose(1);
    fDetectorMessenger = new DetectorMessenger(this);
}

DetectorConstruction::~DetectorConstruction()
{
    delete fDetectorMessenger;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    return ConstructCalorimeter();
}

void DetectorConstruction::DefineMaterials()
{ 
    G4NistManager* nistManager = G4NistManager::Instance();
    Galactic = nistManager->FindOrBuildMaterial("G4_Galactic");
    W = nistManager->FindOrBuildMaterial("G4_W");
    Cu = nistManager->FindOrBuildMaterial("G4_Cu");
}

G4VPhysicalVolume* DetectorConstruction::ConstructCalorimeter()
{
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

//------------------------------------- World ------------------------------------
    fSolidWorld=0; fLogicWorld=0; fPhysiWorld=0;

    fSolidWorld = new G4Box("World", 5.*m, 5.*m, 5.*m);
                         
    fLogicWorld = new G4LogicalVolume(fSolidWorld, Galactic, "LWorld");

    fPhysiWorld = new G4PVPlacement(0, G4ThreeVector(), fLogicWorld, "PWorld", 0, false, 0);

    if(fTargetThickness > 0.)
    {
//----------------------- Sensetive Detector Before Target -----------------------
        fSolidSDB = new G4Tubs("SDB", 0., 100.*mm, 1.*nm, 0., 360.*deg);
        
        fLogicSDB = new G4LogicalVolume(fSolidSDB, Galactic, "LSDB");
        
        fPhysiSDB = new G4PVPlacement(0, G4ThreeVector(0., 0., 100.*mm - fTargetThickness - 1.*nm), fLogicSDB, "PSDB", fLogicWorld, false, 0);
        
//------------------------------------ Target ------------------------------------
        fSolidTarget = new G4Tubs("Target", 0., 35.*mm, fTargetThickness, 0., 360.*deg);
	
        fLogicTarget = new G4LogicalVolume(fSolidTarget, W, "LTarget");

        fPhysiTarget = new G4PVPlacement(0, G4ThreeVector(0., 0., 100.*mm), fLogicTarget, "PTarget", fLogicWorld, false, 0);

//------------------------ Sensetive Detector After Target -----------------------
        fSolidSDA = new G4Tubs("SDA", 0., 15.*mm, 1.*nm, 0., 360.*deg);

        fLogicSDA = new G4LogicalVolume(fSolidSDA, Galactic, "LSDA");

        fPhysiSDA = new G4PVPlacement(0, G4ThreeVector(0., 0., 100.*mm + fTargetThickness + 1.*nm), fLogicSDA, "PSDA", fLogicWorld, false, 0);
        
//------------------------------------ Magnet ------------------------------------
        fSolidM = new G4Cons("Magnet", 0., 17.*mm, 0., 22.*mm, 100.*mm, 0., 360.*deg);
        
        fLogicM = new G4LogicalVolume(fSolidM, Cu, "LMagnet");
        
        fPhysiM = new G4PVPlacement(0, G4ThreeVector(0., 0., 200.*mm + fTargetThickness + 2.*nm), fLogicM, "PMagnet", fLogicWorld, false, 0);
        
//-------------------------- Volume With Magnetic Field --------------------------
        fSolidMF = new G4Cons("MF", 0., 15.*mm, 0., 20.*mm, 100.*mm, 0., 360.*deg);
        
        fLogicMF = new G4LogicalVolume(fSolidMF, Galactic, "LMF");
        
        fPhysiMF = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), fLogicMF, "PMF", fLogicM, false, 0);
        
//------------------------ Sensetive Detector After Magnet ------------------------
        fSolidSD = new G4Tubs("SD", 0., 20.*mm, 1.*nm, 0., 360.*deg);
        
        fLogicSD = new G4LogicalVolume(fSolidSD, Galactic, "LSD");
        
        fPhysiSD = new G4PVPlacement(0, G4ThreeVector(0., 0., 300.*mm + fTargetThickness + 3.*nm), fLogicSD, "PSD", fLogicWorld, false, 0);
    }
    else
        G4cout << "\n------------------------------------------------------------"
        << "\n---> Target Thickness ERROR, check your TT value"
        << "\n------------------------------------------------------------\n";

    return fPhysiWorld;
}

void DetectorConstruction::SetTargetThickness(G4double val)
{
    fTargetThickness = val;
    G4RunManager::GetRunManager()->ReinitializeGeometry();
}

double DetectorConstruction::GetTargetThickness() const
{
    return fTargetThickness;
}

G4ThreadLocal MagneticField* DetectorConstruction::magField = 0;
void DetectorConstruction::ConstructSDandField()
{
    static G4ThreadLocal G4bool initialized = false;
    if(!initialized)
    {
        SensitiveDetector *detector = new SensitiveDetector("Sensetive Detector After Magnet");
        (G4SDManager::GetSDMpointer())->AddNewDetector(detector);
        fLogicSD->SetSensitiveDetector(detector);
        SensitiveDetectorBefore *detectorBefore = new SensitiveDetectorBefore("Sensetive Detector Before Target");
        (G4SDManager::GetSDMpointer())->AddNewDetector(detectorBefore);
        fLogicSDB->SetSensitiveDetector(detectorBefore);
        SensitiveDetectorAfter *detectorAfter = new SensitiveDetectorAfter("Sensetive Detector After Target");
        (G4SDManager::GetSDMpointer())->AddNewDetector(detectorAfter);
        fLogicSDA->SetSensitiveDetector(detectorAfter);
        initialized = false;
    }
    
    if(!magField)
    {
        magField = new MagneticField();
    }
}

