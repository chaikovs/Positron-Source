#include "PhysicsList.hh"
#include "StepMax.hh"
#include "PhysListOpt4.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmStandardPhysicsSS.hh"
#include "G4EmStandardPhysicsGS.hh"
#include "G4EmStandardPhysicsWVI.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmLowEPPhysics.hh"
#include "G4LossTableManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"
#include "G4EmProcessOptions.hh"
#include "G4Decay.hh"
#include "G4PhysicsListHelper.hh"
#include "G4RadioactiveDecay.hh"
#include "G4GenericIon.hh"
#include "G4ProcessManager.hh"

PhysicsList::PhysicsList():
G4VModularPhysicsList(),
fEmPhysicsList(0)
{
    G4LossTableManager::Instance();

    currentDefaultCut = 10*mm;
    SetCutValue(currentDefaultCut, "gamma");
    SetParticleCuts(currentDefaultCut, "gamma");
    SetCutValue(currentDefaultCut, "e-");
    SetParticleCuts(currentDefaultCut, "e-");
    SetCutValue(currentDefaultCut, "e+");
    SetParticleCuts(currentDefaultCut, "e+");

    SetVerboseLevel(1);

    fEmName = "opt4";
    fEmPhysicsList = new PhysListOpt4();

    G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(1*MeV, 10*GeV);
}

PhysicsList::~PhysicsList()
{
    delete fEmPhysicsList;
}

void PhysicsList::ConstructParticle()
{
    G4BosonConstructor  pBosonConstructor;
    pBosonConstructor.ConstructParticle();

    G4LeptonConstructor pLeptonConstructor;
    pLeptonConstructor.ConstructParticle();

    G4MesonConstructor pMesonConstructor;
    pMesonConstructor.ConstructParticle();

    G4BaryonConstructor pBaryonConstructor;
    pBaryonConstructor.ConstructParticle();

    G4IonConstructor pIonConstructor;
    pIonConstructor.ConstructParticle();

    G4ShortLivedConstructor pShortLivedConstructor;
    pShortLivedConstructor.ConstructParticle();
}

void PhysicsList::ConstructProcess()
{
    AddTransportation();
    fEmPhysicsList->ConstructProcess();
    AddDecay();
    AddRadioactiveDecay();
    AddStepMax();
    G4EmProcessOptions emOptions;
    emOptions.SetBuildCSDARange(true);
    emOptions.SetDEDXBinningForCSDARange(8*10);
}

void PhysicsList::AddPhysicsList(const G4String& name)
{
    if(name == fEmName) return;

    if(name == "opt4")
    {
        fEmName = name;
        delete fEmPhysicsList;
        fEmPhysicsList = new PhysListOpt4();
    }
    else
        if(name == "emstandard_opt0")
        {
            fEmName = name;
            delete fEmPhysicsList;
            fEmPhysicsList = new G4EmStandardPhysics();
        }
        else
            if(name == "emstandard_opt1")
            {
                fEmName = name;
                delete fEmPhysicsList;
                fEmPhysicsList = new G4EmStandardPhysics_option1();
            }
            else
                if(name == "emstandard_opt2")
                {
                    fEmName = name;
                    delete fEmPhysicsList;
                    fEmPhysicsList = new G4EmStandardPhysics_option2();
                }
                else
                    if(name == "emstandard_opt3")
                    {
                        fEmName = name;
                        delete fEmPhysicsList;
                        fEmPhysicsList = new G4EmStandardPhysics_option3();
                    }
                    else
                        if(name == "emstandard_opt4")
                        {
                            fEmName = name;
                            delete fEmPhysicsList;
                            fEmPhysicsList = new G4EmStandardPhysics_option4();
                        }
                        else
                            if(name == "emstandardSS")
                            {
                                fEmName = name;
                                delete fEmPhysicsList;
                                fEmPhysicsList = new G4EmStandardPhysicsSS();
                            }
                            else
                                if(name == "emstandardGS")
                                {
                                    fEmName = name;
                                    delete fEmPhysicsList;
                                    fEmPhysicsList = new G4EmStandardPhysicsGS();
                                }
                                else
                                    if(name == "emstandardWVI")
                                    {
                                        fEmName = name;
                                        delete fEmPhysicsList;
                                        fEmPhysicsList = new G4EmStandardPhysicsWVI();
                                    }
                                    else
                                        if(name == "emlivermore")
                                        {
                                            fEmName = name;
                                            delete fEmPhysicsList;
                                            fEmPhysicsList = new G4EmLivermorePhysics();
                                        }
                                        else
                                            if(name == "empenelope")
                                            {
                                                fEmName = name;
                                                delete fEmPhysicsList;
                                                fEmPhysicsList = new G4EmPenelopePhysics();
                                            }
                                            else
                                                if(name == "emlowenergy")
                                                {
                                                    fEmName = name;
                                                    delete fEmPhysicsList;
                                                    fEmPhysicsList = new G4EmLowEPPhysics();
                                                }
                                                else
                                                {}
}

void PhysicsList::AddDecay()
{
    G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

    G4Decay* fDecayProcess = new G4Decay();

    theParticleIterator->reset();
    while((*theParticleIterator)())
    {
        G4ParticleDefinition* particle = theParticleIterator->value();
        
        if(fDecayProcess->IsApplicable(*particle))
            ph->RegisterProcess(fDecayProcess, particle);
    }
}

void PhysicsList::AddRadioactiveDecay()
{
    G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay();
    radioactiveDecay->SetHLThreshold(-1.*s);
    radioactiveDecay->SetARM(true);

    G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
    ph->RegisterProcess(radioactiveDecay, G4GenericIon::GenericIon());
}

void PhysicsList::AddStepMax()
{
    StepMax* stepMaxProcess = new StepMax();

    theParticleIterator->reset();
    
    while((*theParticleIterator)())
    {
        G4ParticleDefinition* particle = theParticleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        
        if (stepMaxProcess->IsApplicable(*particle))
        {
            pmanager ->AddDiscreteProcess(stepMaxProcess);
        }
    }
}
