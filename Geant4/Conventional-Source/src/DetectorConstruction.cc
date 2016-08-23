#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "SensitiveDetector.hh"
#include "SensitiveDetectorBefore.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
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
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

DetectorConstruction::DetectorConstruction():
G4VUserDetectorConstruction(),
fSolidWorld(0), fLogicWorld(0), fPhysiWorld(0),
fSolidTarget(0), fLogicTarget(0), fPhysiTarget(0),
fSolidSD(0), fLogicSD(0), fPhysiSD(0),
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
}

G4VPhysicalVolume* DetectorConstruction::ConstructCalorimeter()
{
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

//------------------------ World ----------------------------------------
    fSolidWorld=0; fLogicWorld=0; fPhysiWorld=0;

    fSolidWorld = new G4Box("World", 5.*m, 5.*m, 5.*m);
                         
    fLogicWorld = new G4LogicalVolume(fSolidWorld, Galactic, "LWorld");

    fPhysiWorld = new G4PVPlacement(0, G4ThreeVector(), fLogicWorld, "PWorld", 0, false, 0);

//------------------------- Target -------------------------------------
    if(fTargetThickness > 0.)
    {
        fSolidTarget=0; fLogicTarget=0; fPhysiTarget=0;
  	
        fSolidTarget = new G4Tubs("Target", 0., 35.*mm, fTargetThickness, 0., 360.*deg);
	
        fLogicTarget = new G4LogicalVolume(fSolidTarget, W, "LTarget");

        fPhysiTarget = new G4PVPlacement(0, G4ThreeVector(0., 0., 100.*mm), fLogicTarget, "PTarget", fLogicWorld, false, 0);

//------------------------ Sensetive Detector After --------------------
        fSolidSD = new G4Tubs("SD", 0., 35.*mm, 1.*mm, 0., 360.*deg);

        fLogicSD = new G4LogicalVolume(fSolidSD, Galactic, "LSD");

        fPhysiSD = new G4PVPlacement(0, G4ThreeVector(0., 0., 101*mm + fTargetThickness), fLogicSD, "PSD", fLogicWorld, false, 0);

//------------------------ Sensetive Detector Before Target --------------------
    fSolidSDB = new G4Tubs("SDB", 0., 350.*mm, 1.*nm, 0., 360.*deg);

    fLogicSDB = new G4LogicalVolume(fSolidSDB, Galactic, "LSDB");

    fPhysiSDB = new G4PVPlacement(0, G4ThreeVector(0., 0., 100.*mm - fTargetThickness - 1.*nm), fLogicSDB, "PSDB", fLogicWorld, false, 0);
    }
    else
        G4cout << "\n------------------------------------------------------------"
        << "\n---> Target Thickness ERROR, check your TT value"
        << "\n------------------------------------------------------------\n";

    SensitiveDetector *detector = new SensitiveDetector("Sensetive Detector");
    SensitiveDetectorBefore *detectorBefore = new SensitiveDetectorBefore("Sensetive Detector Before Target");

    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    SDman->AddNewDetector(detector);
    fLogicSD->SetSensitiveDetector(detector);
    SDman->AddNewDetector(detectorBefore);
    fLogicSDB->SetSensitiveDetector(detectorBefore);

    return fPhysiWorld;
}

void DetectorConstruction::PrintTargetThickness()
{
    G4cout << "\n------------------------------------------------------------"
           << "\n---> Target: [ "
           << fTargetThickness/mm << " mm of Tungsten ] "
           << "\n------------------------------------------------------------\n";
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
