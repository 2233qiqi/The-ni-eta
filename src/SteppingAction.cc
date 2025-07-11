#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4VProcess.hh"
#include "G4SystemOfUnits.hh"
#include "G4Threading.hh"
#include "G4UnitsTable.hh"

SteppingAction::SteppingAction(EventAction *eventAction)
    : G4UserSteppingAction(),
      fEventAction(eventAction),
      fScoringVolume(nullptr),
      fInitialEnergy(0.0),   // Initialize new variable
      fGeneratedParticles(0) // Initialize new variable
{
}

SteppingAction::~SteppingAction()
{
  // In the end, the master thread prints the summary
  if (G4Threading::IsMasterThread())
  {
    G4cout << "\n========================== Generation Summary (from SteppingAction) =========================="
           << "\n Total Particles Generated in Source: " << fGeneratedParticles
           << "\n Total Initial Energy Generated: " << G4BestUnit(fInitialEnergy, "Energy")
           << "\n============================================================================================"
           << G4endl;
  }
}

void SteppingAction::UserSteppingAction(const G4Step *step)
{
  if (step->GetTrack()->GetCurrentStepNumber() == 1)
  {
    if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "e-")
    {
      G4double initialEnergy = step->GetTrack()->GetVertexKineticEnergy();

      std::lock_guard<std::mutex> lock(fMutex);
      fInitialEnergy += initialEnergy;
      fGeneratedParticles++;
    }
  }

  // ================== 核心逻辑结束 ==================

  // ================== 您原来的能量沉积逻辑 (保持注释状态) ==================
  /*
  if (!fScoringVolume) {
      const auto detConstruction = static_cast<const DetectorConstruction*>(
      G4RunManager::GetRunManager()->GetUserDetectorConstruction());
      fScoringVolume = detConstruction->GetScoringVolume();
  }

  G4LogicalVolume* volume =
      step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  if (volume != fScoringVolume) return;

  G4double edepStep = step->GetTotalEnergyDeposit();
  //fEventAction->AddEdep(edepStep);
  std::cout<<"edepStep:"<<edepStep<<std::endl;
  */
}
