#include "NeutronRunAction.hpp"

#ifdef G4MPI
#include <G4MPImanager.hh>
#endif

#include <G4Run.hh>
#include <G4RunManager.hh>
#include <G4SystemOfUnits.hh>

#include "G4AnalysisManager.hh"
#include "NeutronAnalysis.hpp"

NeutronRunAction::NeutronRunAction(bool fFileOutRoot)
    : G4UserRunAction(), fFileOutRoot(fFileOutRoot) {
  // Create analysis manager
  // The choice of the output format is done via the specified
  // file extension.
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetHistoDirectoryName("histograms");
  analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetNtupleMerging(true);
  analysisManager->SetFileName("spallation.root");

  double start = 1;
  double stop = 6;
  auto num = 200;
  std::vector<double> vals;
  std::generate_n(std::back_inserter(vals), num, Logspace<>(start, stop, num));

  analysisManager->CreateH1("neutronE", "Energy neutron", num, 1e-2, 1e2, "MeV",
                            "none", "log");
  analysisManager->CreateH1("GammaE", "Energy gamma", num, 1e-4, 1e2, "MeV",
                            "none", "log");

  analysisManager->CreateNtuple("TupleOut1", "Particle output tuple");
  analysisManager->CreateNtupleSColumn("PDGcodeS");
  analysisManager->CreateNtupleIColumn("PDGcode");
  analysisManager->FinishNtuple();
}

NeutronRunAction::~NeutronRunAction() {}

void NeutronRunAction::BeginOfRunAction(const G4Run *run) {
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Reset();
  analysisManager->OpenFile();
}

void NeutronRunAction::EndOfRunAction(const G4Run *run) {
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetH1XAxisIsLog(0, true);
  analysisManager->SetH1YAxisIsLog(0, true);
  analysisManager->Write();
  analysisManager->CloseFile();
}