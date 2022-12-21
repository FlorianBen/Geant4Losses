#include "NeutronPrimaryGeneratorAction.hpp"

#include <G4Event.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleTable.hh>
#include <G4PrimaryParticle.hh>
#include <G4PrimaryVertex.hh>
#include <G4RandomTools.hh>
#include <G4SystemOfUnits.hh>
#include <G4ios.hh>
#include <G4GeneralParticleSource.hh>

#include <Randomize.hh>

NeutronPrimaryGeneratorAction::NeutronPrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction() {
  G4int nofParticles = 1;
  fParticleGun = new G4GeneralParticleSource();//new G4ParticleGun(nofParticles);

  // // Define particle properties
  // G4String particleName = "proton";
  // G4ThreeVector position(.0, .0, -1.2 * m);
  // G4ThreeVector momentum(.0, .0, 1);
  // G4double time = 0;

  // // Get particle definition from G4ParticleTable
  // G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  // G4ParticleDefinition *particleDefinition =
  //     particleTable->FindParticle(particleName);
  // if (!particleDefinition) {
  //   G4cerr << "Error: " << particleName << " not found in G4ParticleTable"
  //          << G4endl;
  //   exit(1);
  // }

  // fParticleGun->SetParticleTime(time);
  // fParticleGun->SetParticleDefinition(particleDefinition);
  // fParticleGun->SetParticleEnergy(2 * GeV);
  // fParticleGun->SetParticleMomentumDirection(momentum);
  // fParticleGun->SetParticlePosition(position);
}

NeutronPrimaryGeneratorAction::~NeutronPrimaryGeneratorAction() {
  delete fParticleGun;
}

void NeutronPrimaryGeneratorAction::GeneratePrimaries(G4Event *event) {
  //fParticleGun->SetParticleMomentum(G4RandomDirection());
  fParticleGun->GeneratePrimaryVertex(event);
}