#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"

#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4NuclideTable.hh"

#include "QBBC.hh"
#include "PhysicsList.hh"
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

int main(int argc, char **argv)
{

  G4UIExecutive *ui = nullptr;
  if (argc == 1)
  {
    ui = new G4UIExecutive(argc, argv);
  }

  auto runManager = new G4RunManager;

  // physics process
  auto physicsList = new QBBC();

  runManager->SetUserInitialization(physicsList);
  // detector geometry
  runManager->SetUserInitialization(new DetectorConstruction());
  // primary generator
  runManager->SetUserInitialization(new ActionInitialization());

  runManager->Initialize();

  G4VisManager *visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  G4UImanager *uiManager = G4UImanager::GetUIpointer();

  // uiManager->ApplyCommand("/control/execute vis.mac");

  // ui->SessionStart();
  // delete ui;
  if (!ui)
  {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    uiManager->ApplyCommand(command + fileName);
  }
  else
  {
    // interactive mode
    uiManager->ApplyCommand("/control/execute vis.mac");
    // if (ui->IsGUI()) {
    //   UImanager->ApplyCommand("/control/execute gui.mac");
    // }
    ui->SessionStart();
    delete ui;
  }

  delete visManager;
  delete runManager;

  return 0;
}