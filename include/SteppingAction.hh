#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include <mutex>

class SteppingAction : public G4UserSteppingAction
{
public:
  SteppingAction();
  ~SteppingAction() override;

  void UserSteppingAction(const G4Step *step) override;

private:
  G4double fInitialEnergy;
  G4int fGeneratedParticles;
  std::mutex fMutex;
};

#endif