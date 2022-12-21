#ifdef G4MULTITHREADED
#include <G4MTRunManager.hh>
#else
#include <G4RunManager.hh>
#endif

#include <G4MTRunManager.hh>

#ifdef G4MPI
#include <G4MPImanager.hh>
#include <G4MPIsession.hh>
#endif

#include <FTFP_BERT.hh>
#include <G4GDMLParser.hh>
#include <G4GenericBiasingPhysics.hh>
#include <G4PhysListFactory.hh>
#include <G4UImanager.hh>

#include <G4UIExecutive.hh>
#include <G4VisExecutive.hh>

#include <G4GDMLParser.hh>
#include <G4LogicalVolume.hh>
#include <G4TransportationManager.hh>

#include "NeutronActionInitialization.hpp"
#include "NeutronDetectorConstruction.hpp"
#include "NeutronPhysicsList.hpp"

int main(int argc, char *argv[]) {
#ifdef G4MPI
  G4MPImanager *g4MPI = new G4MPImanager(argc, argv);
  G4MPIsession *session = g4MPI->GetMPIsession();

  // LAM/MPI users can use G4tcsh.
  G4String prompt = "[";
  prompt += "\033[31mG4MPI\033[0m";
  prompt += "](\e[104m%s\e[49m)[%/]:";
  session->SetPrompt(prompt);
#else
  // Detect interactive mode (if no arguments) and define UI session
  G4UIExecutive *ui = 0;
  if (argc == 1) {
    ui = new G4UIExecutive(argc, argv);
  }
#endif

// Construct the run manager
#ifdef G4MULTITHREADED
  G4MTRunManager *runManager = new G4MTRunManager;
  //  //runManager->SetNumberOfThreads(1);
  runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());
#else
  G4RunManager *runManager = new G4RunManager;
#endif

  runManager->SetUserInitialization(new NeutronSimConstruction());

  // Physics list
  auto physicListFactory = new G4PhysListFactory();
  auto physicsList = physicListFactory->GetReferencePhysList("FTFP_INCLXX_HP");
  // NeutronPhysicsList *physicsList = new NeutronPhysicsList;
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);

  // User action initialization
  runManager->SetUserInitialization(new NeutronActionInitialization());
  runManager->Initialize();

  // Initialize visualization
  G4VisManager *visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager *UImanager = G4UImanager::GetUIpointer();
  if (!ui) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  } else {
    // interactive mode : define UI session
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    if (ui->IsGUI()) {
      UImanager->ApplyCommand("/control/execute icons.mac");
    }
    ui->SessionStart();
    delete ui;
  }
  delete visManager;
  delete runManager;

  return EXIT_SUCCESS;
}
