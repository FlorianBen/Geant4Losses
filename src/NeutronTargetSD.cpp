#include "NeutronTargetSD.hpp"

#include "NeutronAnalysis.hpp"

#include <G4Gamma.hh>
#include <G4HCofThisEvent.hh>
#include <G4Neutron.hh>
#include <G4SDManager.hh>
#include <G4Step.hh>
#include <G4SystemOfUnits.hh>
#include <G4VProcess.hh>
#include <G4VTouchable.hh>
#include <G4ios.hh>

TargetSD::TargetSD(const G4String &name, const G4String &hitsCollectionName,
                   const G4int idTuple)
    : G4VSensitiveDetector(name) {}

TargetSD::~TargetSD() {}

void TargetSD::Initialize(G4HCofThisEvent *hce) {}

G4bool TargetSD::ProcessHits(G4Step *step, G4TouchableHistory *) {
  auto analysisManager = G4AnalysisManager::Instance();

  G4String process_name;
  G4StepPoint *preStepPoint = step->GetPreStepPoint();
  G4StepPoint *postStepPoint = step->GetPostStepPoint();
  auto track = step->GetTrack();

  if (step->IsLastStepInVolume()) {
    if (track->GetParticleDefinition() == G4Neutron::Definition()) {
      analysisManager->FillH1(0, preStepPoint->GetKineticEnergy() / MeV);
    } else if (track->GetParticleDefinition() == G4Gamma::Definition()) {
      analysisManager->FillH1(1, preStepPoint->GetKineticEnergy() / MeV);
    }
    analysisManager->FillNtupleSColumn(
        0, 0, track->GetParticleDefinition()->GetParticleName());
    analysisManager->FillNtupleIColumn(
        0, 1, track->GetParticleDefinition()->GetPDGEncoding());
    analysisManager->AddNtupleRow(0);
  }

  return true;
}
