#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "G4VModularPhysicsList.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

int main(int argc,char** argv)
{
    G4RunManager * runManager = new G4RunManager;

    DetectorConstruction* detector = new DetectorConstruction;
    runManager->SetUserInitialization(detector);

    PhysicsList* physics = new PhysicsList;
    runManager->SetUserInitialization(physics);

    PrimaryGeneratorAction* gen_action = new PrimaryGeneratorAction(detector);
    runManager->SetUserAction(gen_action);

    RunAction* run_action = new RunAction();
    runManager->SetUserAction(run_action);

    EventAction* event_action = new EventAction(run_action);
    runManager->SetUserAction(event_action);

    SteppingAction* stepping_action = new SteppingAction(detector, event_action);
    runManager->SetUserAction(stepping_action);

    runManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();
  
    if(argc!=1)
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }
    else
    {
#ifdef G4VIS_USE
        G4VisManager* visManager = new G4VisExecutive;
        visManager->Initialize();
#ifdef G4UI_USE
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#endif
        UImanager->ApplyCommand("/control/execute vis.mac");
#endif
#ifdef G4UI_USE
        ui->SessionStart();
        delete ui;
#endif
#ifdef G4VIS_USE
        delete visManager;
#endif
    }
    delete runManager;
    return 0;
}

