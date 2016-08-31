#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "SensitiveDetector.hh"

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
//-----FIELD-----
#include "Field.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4Mag_UsualEqRhs.hh"

#include "G4ClassicalRK4.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4ChordFinder.hh"
#include "G4PropagatorInField.hh"

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
    if(fField)
        delete fField;
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

//---------------------------------- Target ----------------------------
    if(fTargetThickness > 0.)
    {
        fSolidTarget=0; fLogicTarget=0; fPhysiTarget=0;
  	
        fSolidTarget = new G4Tubs("Target", 0., 35.*mm, fTargetThickness, 0., 360.*deg);
	
        fLogicTarget = new G4LogicalVolume(fSolidTarget, W, "LTarget");

        fPhysiTarget = new G4PVPlacement(0, G4ThreeVector(0., 0., 100.*mm), fLogicTarget, "PTarget", fLogicWorld, false, 0);

//------------------------ Sensetive Detector After --------------------
        fSolidSD = new G4Tubs("SD", 0., 35.*mm, 1.*mm, 0., 360.*deg);

        fLogicSD = new G4LogicalVolume(fSolidSD, Galactic, "LSD");

        fPhysiSD = new G4PVPlacement(0, G4ThreeVector(0., 0., 301*mm + fTargetThickness), fLogicSD, "PSD", fLogicWorld, false, 0);
        
//------------------------ Volume with magnetic field ------------------
        fSolidMF = new G4Tubs("MF", 0., 20.*mm, 100.*mm, 0., 360.*deg);
        
        fLogicMF = new G4LogicalVolume(fSolidMF, Galactic, "LMF");
        
        fPhysiMF = new G4PVPlacement(0, G4ThreeVector(0., 0., 200*mm + fTargetThickness), fLogicMF, "PMF", fLogicWorld, false, 0);
    }
    else
        G4cout << "\n------------------------------------------------------------"
        << "\n---> Target Thickness ERROR, check your TT value"
        << "\n------------------------------------------------------------\n";

    SensitiveDetector *detector = new SensitiveDetector("Sensetive Detector");

    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    SDman->AddNewDetector(detector);
    fLogicSD->SetSensitiveDetector(detector);

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

G4ThreadLocal Field* DetectorConstruction::fField = 0;
void DetectorConstruction::ConstructSDandField()
{
    if(!fField)
    {
        fField = new Field();
        G4Mag_UsualEqRhs* equation = new G4Mag_UsualEqRhs((G4MagneticField*)fField);
        fieldManager = G4TransportationManager::GetTransportationManager()->GetFieldManager();
        fieldManager->SetDetectorField(fField);
        G4MagIntegratorStepper* stepper = new G4ClassicalRK4(equation);
        G4double minStep = 0.25*mm;
        G4ChordFinder* chordFinder = new G4ChordFinder((G4MagneticField*)fField,minStep,stepper);
        G4double deltaChord = 0.25*mm;
        chordFinder->SetDeltaChord(deltaChord);
        /*
        G4double deltaOneStep      = 0.01*mm;
        fieldManager->SetAccuraciesWithDeltaOneStep(deltaOneStep);
        
        G4double deltaIntersection = 0.1*mm;
        fieldManager->SetDeltaIntersection(deltaIntersection);
        
        G4TransportationManager* transportManager =
        G4TransportationManager::GetTransportationManager();
        
        G4PropagatorInField* fieldPropagator =
        transportManager->GetPropagatorInField();
        
        G4double epsMin            = 2.5e-7*mm;
        G4double epsMax            = 0.05*mm;
        
        fieldPropagator->SetMinimumEpsilonStep(epsMin);
        fieldPropagator->SetMaximumEpsilonStep(epsMax);
         */
        fieldManager->SetChordFinder(chordFinder);
    }
    
    G4bool allLocal = true;
    fLogicMF->SetFieldManager(fieldManager, allLocal);
}
