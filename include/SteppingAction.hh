#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include <mutex>

class EventAction;
class G4LogicalVolume; // <--- 修正：加回这一行前向声明

class SteppingAction : public G4UserSteppingAction
{
public:
  SteppingAction(EventAction *eventAction);
  ~SteppingAction() override;

  void UserSteppingAction(const G4Step *) override;

private:
  // Original variables
  EventAction *fEventAction;
  G4LogicalVolume *fScoringVolume;

  // New variables for self-absorption study
  G4double fInitialEnergy;
  G4int fGeneratedParticles;
  std::mutex fMutex;
};

#endif