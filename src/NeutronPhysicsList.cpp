#include "NeutronPhysicsList.hpp"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronElasticPhysicsXS.hh"

#include "G4HadronInelasticQBBC.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4HadronPhysicsINCLXX.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4HadronPhysicsQGSP_BIC_AllHP.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronPhysicsShielding.hh"

#include "G4IonElasticPhysics.hh"
#include "G4IonINCLXXPhysics.hh"
#include "G4IonPhysicsPHP.hh"
#include "G4IonPhysicsXS.hh"
#include "G4IonQMDPhysics.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include <G4EmStandardPhysics_option3.hh>


// particles

#include "G4BaryonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

NeutronPhysicsList::NeutronPhysicsList() : G4VModularPhysicsList() {
  G4int verb = 0;
  SetVerboseLevel(verb);

  // add new units for cross sections
  //
  new G4UnitDefinition("mm2/g", "mm2/g", "Surface/Mass", mm2 / g);
  new G4UnitDefinition("um2/mg", "um2/mg", "Surface/Mass", um * um / mg);

  // Hadron Elastic scattering
  //
  RegisterPhysics(new G4HadronElasticPhysicsHP(verb));
  /// RegisterPhysics( new G4HadronElasticPhysicsXS(verb));

  // Hadron Inelastic physics
  //
  ////RegisterPhysics( new G4HadronPhysicsFTFP_BERT_HP(verb));
  ////RegisterPhysics( new G4HadronPhysicsQGSP_BIC_HP(verb));
  RegisterPhysics(new G4HadronPhysicsQGSP_BIC_AllHP(verb));
  ////RegisterPhysics( new G4HadronPhysicsQGSP_BIC(verb));
  ////RegisterPhysics( new G4HadronInelasticQBBC(verb));
  ////RegisterPhysics( new G4HadronPhysicsINCLXX(verb));
  ////RegisterPhysics( new G4HadronPhysicsShielding(verb));

  // Ion Elastic scattering
  //
  RegisterPhysics(new G4IonElasticPhysics(verb));

  // Ion Inelastic physics
  //
  RegisterPhysics(new G4IonPhysicsXS(verb));
  ////RegisterPhysics( new G4IonPhysicsPHP(verb));
  ////RegisterPhysics( new G4IonQMDPhysics(verb));
  ////RegisterPhysics( new G4IonINCLXXPhysics(verb));

  RegisterPhysics(new G4EmStandardPhysics_option3(verb));

  // Gamma physics
  //
  //RegisterPhysics(new GammaNuclearPhysics("gamma"));


  // Decay
  RegisterPhysics( new G4DecayPhysics());

  // Radioactive decay
  //RegisterPhysics(new G4RadioactiveDecayPhysics());
}

NeutronPhysicsList::~NeutronPhysicsList() {}

void NeutronPhysicsList::ConstructParticle() {
  G4BosonConstructor pBosonConstructor;
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

void NeutronPhysicsList::SetCuts() { SetCutValue(0.01 * nm, "proton"); }
