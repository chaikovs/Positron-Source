#include "PhysListOpt4.hh"

#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4LossTableManager.hh"
#include "G4EmParameters.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4RayleighScattering.hh"
#include "G4PEEffectFluoModel.hh"
#include "G4KleinNishinaModel.hh"
#include "G4LivermorePhotoElectricModel.hh"
#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4hMultipleScattering.hh"
#include "G4MscStepLimitType.hh"
#include "G4UrbanMscModel.hh"
#include "G4GoudsmitSaundersonMscModel.hh"
#include "G4EmProcessOptions.hh"
#include "G4DummyModel.hh"
#include "G4WentzelVIModel.hh"
#include "G4CoulombScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4Generator2BS.hh"
#include "G4SeltzerBergerModel.hh"
#include "G4eplusAnnihilation.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"
#include "G4MuBremsstrahlungModel.hh"
#include "G4MuPairProductionModel.hh"
#include "G4hBremsstrahlungModel.hh"
#include "G4hPairProductionModel.hh"
#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4NuclearStopping.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4PionPlus.hh"
#include "G4PionMinus.hh"
#include "G4KaonPlus.hh"
#include "G4KaonMinus.hh"
#include "G4Proton.hh"
#include "G4AntiProton.hh"
#include "G4Deuteron.hh"
#include "G4Triton.hh"
#include "G4He3.hh"
#include "G4Alpha.hh"
#include "G4GenericIon.hh"
#include "G4PhysicsListHelper.hh"
#include "G4BuilderType.hh"
#include "G4EmModelActivator.hh"
#include "G4PhysicsConstructorFactory.hh"
#include "G4LowEPComptonModel.hh"
#include "G4PenelopeGammaConversionModel.hh"
#include "G4eCoulombScatteringModel.hh"
#include "G4PenelopeIonisationModel.hh"
#include "G4UniversalFluctuation.hh"


PhysListOpt4::PhysListOpt4(const G4String& name):
G4VPhysicsConstructor(name)
{
    G4EmParameters* param = G4EmParameters::Instance();
    param->SetDefaults();
    param->SetMinEnergy(1*MeV);
    param->SetMaxEnergy(10*GeV);
    param->SetLowestElectronEnergy(1*MeV);
    param->ActivateAngularGeneratorForIonisation(true);
    param->SetMscRangeFactor(0.04);
    param->SetFluo(true);
    SetPhysicsType(bElectromagnetic);
}

PhysListOpt4::~PhysListOpt4(){}

void PhysListOpt4::ConstructParticle()
{
    G4Gamma::Gamma();
    G4Electron::Electron();
    G4Positron::Positron();
    G4MuonPlus::MuonPlus();
    G4MuonMinus::MuonMinus();
    G4PionPlus::PionPlusDefinition();
    G4PionMinus::PionMinusDefinition();
    G4KaonPlus::KaonPlusDefinition();
    G4KaonMinus::KaonMinusDefinition();
    G4Proton::Proton();
    G4AntiProton::AntiProton();
    G4Deuteron::Deuteron();
    G4Triton::Triton();
    G4He3::He3();
    G4Alpha::Alpha();
    G4GenericIon::GenericIonDefinition();
    G4EmModelActivator mact;
    mact.ConstructParticle();
}

void PhysListOpt4::ConstructProcess()
{
    G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

    G4MuBremsstrahlung* mub = new G4MuBremsstrahlung();
    G4MuPairProduction* mup = new G4MuPairProduction();
    G4hBremsstrahlung* pib = new G4hBremsstrahlung();
    G4hPairProduction* pip = new G4hPairProduction();
    G4hBremsstrahlung* kb = new G4hBremsstrahlung();
    G4hPairProduction* kp = new G4hPairProduction();
    G4hBremsstrahlung* pb = new G4hBremsstrahlung();
    G4hPairProduction* pp = new G4hPairProduction();

    G4MuMultipleScattering* mumsc = new G4MuMultipleScattering();
    mumsc->AddEmModel(0, new G4WentzelVIModel());
    G4CoulombScattering* muss = new G4CoulombScattering();

    G4MuMultipleScattering* pimsc = new G4MuMultipleScattering();
    pimsc->AddEmModel(0, new G4WentzelVIModel());
    G4CoulombScattering* piss = new G4CoulombScattering();

    G4MuMultipleScattering* kmsc = new G4MuMultipleScattering();
    kmsc->AddEmModel(0, new G4WentzelVIModel());
    G4CoulombScattering* kss = new G4CoulombScattering();

    G4MuMultipleScattering* pmsc = new G4MuMultipleScattering();
    pmsc->AddEmModel(0, new G4WentzelVIModel());
    G4CoulombScattering* pss = new G4CoulombScattering();

    G4hMultipleScattering* hmsc = new G4hMultipleScattering("ionmsc");
    
    G4double highEnergyLimit = 100*MeV;
    G4double penEnergyLimit = 1*MeV;

    G4NuclearStopping* pnuc = new G4NuclearStopping();
 
    aParticleIterator->reset();
    while((*aParticleIterator)())
    {
        G4ParticleDefinition* particle = aParticleIterator->value();
        G4String particleName = particle->GetParticleName();
 
        if(particleName == "gamma")
        {
            G4PhotoElectricEffect* pe = new G4PhotoElectricEffect();
            G4VEmModel* theLivermorePEModel = new G4LivermorePhotoElectricModel();
            pe->SetEmModel(theLivermorePEModel,1);
            ph->RegisterProcess(pe, particle);

            G4ComptonScattering* cs = new G4ComptonScattering;
            cs->SetEmModel(new G4KleinNishinaModel(),1);
            G4VEmModel* theLowEPComptonModel = new G4LowEPComptonModel();
            theLowEPComptonModel->SetHighEnergyLimit(20*MeV);
            cs->AddEmModel(0, theLowEPComptonModel);
            ph->RegisterProcess(cs, particle);

            G4GammaConversion* gc = new G4GammaConversion();
            G4VEmModel* thePenelopeGCModel = new G4PenelopeGammaConversionModel();
            thePenelopeGCModel->SetHighEnergyLimit(1*GeV);
            gc->SetEmModel(thePenelopeGCModel,1);
            ph->RegisterProcess(gc, particle);
            ph->RegisterProcess(new G4RayleighScattering(), particle);
        }
        else
            if(particleName == "e-")
            {
                G4eMultipleScattering* msc = new G4eMultipleScattering;
                G4GoudsmitSaundersonMscModel* msc1 = new G4GoudsmitSaundersonMscModel();
                msc1->SetOptionPWAScreening(true);

                G4WentzelVIModel* msc2 = new G4WentzelVIModel();
                msc1->SetHighEnergyLimit(highEnergyLimit);
                msc2->SetLowEnergyLimit(highEnergyLimit);
                msc->AddEmModel(0, msc1);
                msc->AddEmModel(0, msc2);

                G4eCoulombScatteringModel* ssm = new G4eCoulombScatteringModel();
                G4CoulombScattering* ss = new G4CoulombScattering();
                ss->SetEmModel(ssm, 1);
                ss->SetMinKinEnergy(highEnergyLimit);
                ssm->SetLowEnergyLimit(highEnergyLimit);
                ssm->SetActivationLowEnergyLimit(highEnergyLimit);

                G4eIonisation* eIoni = new G4eIonisation();
                eIoni->SetStepFunction(0.2, 100*um);
                G4PenelopeIonisationModel* pen = new G4PenelopeIonisationModel();
                pen->SetHighEnergyLimit(penEnergyLimit);
                eIoni->AddEmModel(0, pen, new G4UniversalFluctuation());

                G4eBremsstrahlung* brem = new G4eBremsstrahlung();
                G4SeltzerBergerModel* br1 = new G4SeltzerBergerModel();
                G4eBremsstrahlungRelModel* br2 = new G4eBremsstrahlungRelModel();
                br1->SetAngularDistribution(new G4Generator2BS());
                br2->SetAngularDistribution(new G4Generator2BS());
                brem->SetEmModel(br1,1);
                brem->SetEmModel(br2,2);
                br2->SetLowEnergyLimit(GeV);

                ph->RegisterProcess(msc, particle);
                ph->RegisterProcess(eIoni, particle);
                ph->RegisterProcess(brem, particle);
                ph->RegisterProcess(ss, particle);
            }
            else
                if(particleName == "e+")
                {
                    G4eMultipleScattering* msc = new G4eMultipleScattering;
                    G4GoudsmitSaundersonMscModel* msc1 = new G4GoudsmitSaundersonMscModel();
                    msc1->SetOptionPWAScreening(true);

                    G4WentzelVIModel* msc2 = new G4WentzelVIModel();
                    msc1->SetHighEnergyLimit(highEnergyLimit);
                    msc2->SetLowEnergyLimit(highEnergyLimit);
                    msc->AddEmModel(0, msc1);
                    msc->AddEmModel(0, msc2);

                    G4eCoulombScatteringModel* ssm = new G4eCoulombScatteringModel();
                    G4CoulombScattering* ss = new G4CoulombScattering();
                    ss->SetEmModel(ssm, 1);
                    ss->SetMinKinEnergy(highEnergyLimit);
                    ssm->SetLowEnergyLimit(highEnergyLimit);
                    ssm->SetActivationLowEnergyLimit(highEnergyLimit);

                    G4eIonisation* eIoni = new G4eIonisation();
                    eIoni->SetStepFunction(0.2, 100*um);
                    G4PenelopeIonisationModel* pen = new G4PenelopeIonisationModel();
                    pen->SetHighEnergyLimit(penEnergyLimit);
                    eIoni->AddEmModel(0, pen, new G4UniversalFluctuation());

                    G4eBremsstrahlung* brem = new G4eBremsstrahlung();
                    G4SeltzerBergerModel* br1 = new G4SeltzerBergerModel();
                    G4eBremsstrahlungRelModel* br2 = new G4eBremsstrahlungRelModel();
                    br1->SetAngularDistribution(new G4Generator2BS());
                    br2->SetAngularDistribution(new G4Generator2BS());
                    brem->SetEmModel(br1,1);
                    brem->SetEmModel(br2,2);
                    br2->SetLowEnergyLimit(GeV);
                    
                    ph->RegisterProcess(msc, particle);
                    ph->RegisterProcess(eIoni, particle);
                    ph->RegisterProcess(brem, particle);
                    ph->RegisterProcess(new G4eplusAnnihilation(), particle);
                    ph->RegisterProcess(ss, particle);
                }
                else
                    if(particleName == "mu+" || particleName == "mu-")
                    {
                        G4MuIonisation* muIoni = new G4MuIonisation();
                        muIoni->SetStepFunction(0.2, 50*um);
 
                        ph->RegisterProcess(mumsc, particle);
                        ph->RegisterProcess(muIoni, particle);
                        ph->RegisterProcess(mub, particle);
                        ph->RegisterProcess(mup, particle);
                        ph->RegisterProcess(muss, particle);
                    }
                    else
                        if(particleName == "alpha" || particleName == "He3")
                        {
                            G4hMultipleScattering* msc = new G4hMultipleScattering();
                            G4ionIonisation* ionIoni = new G4ionIonisation();
                            ionIoni->SetStepFunction(0.1, 10*um);
 
                            ph->RegisterProcess(msc, particle);
                            ph->RegisterProcess(ionIoni, particle);
                            ph->RegisterProcess(pnuc, particle);
                        }
                        else
                            if(particleName == "GenericIon")
                            {
                                G4ionIonisation* ionIoni = new G4ionIonisation();
                                ionIoni->SetEmModel(new G4IonParametrisedLossModel());
                                ionIoni->SetStepFunction(0.1, 1*um);
 
                                ph->RegisterProcess(hmsc, particle);
                                ph->RegisterProcess(ionIoni, particle);
                                ph->RegisterProcess(pnuc, particle);
                            }
                            else
                                if(particleName == "pi+" || particleName == "pi-")
                                {
                                    G4hIonisation* hIoni = new G4hIonisation();
                                    hIoni->SetStepFunction(0.2, 50*um);
 
                                    ph->RegisterProcess(pimsc, particle);
                                    ph->RegisterProcess(hIoni, particle);
                                    ph->RegisterProcess(pib, particle);
                                    ph->RegisterProcess(pip, particle);
                                    ph->RegisterProcess(piss, particle);
                                }
                                else
                                    if(particleName == "kaon+" || particleName == "kaon-")
                                    {
                                        G4hIonisation* hIoni = new G4hIonisation();
                                        hIoni->SetStepFunction(0.2, 50*um);
 
                                        ph->RegisterProcess(kmsc, particle);
                                        ph->RegisterProcess(hIoni, particle);
                                        ph->RegisterProcess(kb, particle);
                                        ph->RegisterProcess(kp, particle);
                                        ph->RegisterProcess(kss, particle);
                                    }
                                    else
                                        if(particleName == "proton" || particleName == "anti_proton")
                                        {
                                            G4hIonisation* hIoni = new G4hIonisation();
                                            hIoni->SetStepFunction(0.1, 20*um);
 
                                            ph->RegisterProcess(pmsc, particle);
                                            ph->RegisterProcess(hIoni, particle);
                                            ph->RegisterProcess(pb, particle);
                                            ph->RegisterProcess(pp, particle);
                                            ph->RegisterProcess(pss, particle);
                                            ph->RegisterProcess(pnuc, particle);
                                        }
                                        else
                                            if(particleName == "B+" ||
                                               particleName == "B-" ||
                                               particleName == "D+" ||
                                               particleName == "D-" ||
                                               particleName == "Ds+" ||
                                               particleName == "Ds-" ||
                                               particleName == "anti_He3" ||
                                               particleName == "anti_alpha" ||
                                               particleName == "anti_deuteron" ||
                                               particleName == "anti_lambda_c+" ||
                                               particleName == "anti_omega-" ||
                                               particleName == "anti_sigma_c+" ||
                                               particleName == "anti_sigma_c++" ||
                                               particleName == "anti_sigma+" ||
                                               particleName == "anti_sigma-" ||
                                               particleName == "anti_triton" ||
                                               particleName == "anti_xi_c+" ||
                                               particleName == "anti_xi-" ||
                                               particleName == "deuteron" ||
                                               particleName == "lambda_c+" ||
                                               particleName == "omega-" ||
                                               particleName == "sigma_c+" ||
                                               particleName == "sigma_c++" ||
                                               particleName == "sigma+" ||
                                               particleName == "sigma-" ||
                                               particleName == "tau+" ||
                                               particleName == "tau-" ||
                                               particleName == "triton" ||
                                               particleName == "xi_c+" ||
                                               particleName == "xi-")
                                            {
                                                ph->RegisterProcess(hmsc, particle);
                                                ph->RegisterProcess(new G4hIonisation(), particle);
                                                ph->RegisterProcess(pnuc, particle);
                                            }
    }

    pnuc->SetMaxKinEnergy(MeV);
    G4VAtomDeexcitation* de = new G4UAtomicDeexcitation();
    G4LossTableManager::Instance()->SetAtomDeexcitation(de);
    G4EmModelActivator mact;
    mact.ConstructProcess();
}

