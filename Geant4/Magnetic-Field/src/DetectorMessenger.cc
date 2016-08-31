#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
DetectorMessenger::DetectorMessenger( DetectorConstruction* Det):
G4UImessenger(),
fDetector(Det), fTargetDir(0),
fDetDir(0), fTargetThicknessCmd(0)
{ 
    fTargetDir = new G4UIdirectory("/TT/");
    fTargetDir->SetGuidance("UI commands of positron production project");

    G4bool broadcast = false;
    fDetDir = new G4UIdirectory("/TT/det/",broadcast);
    fDetDir->SetGuidance("detector control");
    
    fTargetThicknessCmd = new G4UIcmdWithADoubleAndUnit("/TT/det/setTargetThickness",this);
    fTargetThicknessCmd->SetGuidance("Set Thickness of the Target");
    fTargetThicknessCmd->SetParameterName("Size",false);
    fTargetThicknessCmd->SetRange("Size>=0.");
    fTargetThicknessCmd->SetUnitCategory("Length");
    fTargetThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

DetectorMessenger::~DetectorMessenger()
{
    delete fTargetThicknessCmd;
    delete fDetDir;
    delete fTargetDir;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if( command == fTargetThicknessCmd )
    {
        fDetector->SetTargetThickness(fTargetThicknessCmd->GetNewDoubleValue(newValue));
    }
}
