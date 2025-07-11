// RunAction.hh
#ifndef RUN_ACTION_HH
#define RUN_ACTION_HH
#include "G4UserRunAction.hh"
#include "SingleParticleSD.hh"
class RunAction : public G4UserRunAction
{
public:
    RunAction();
    virtual ~RunAction();
    RunAction(SingleParticleSD *sd);
    virtual void BeginOfRunAction(const G4Run *);
    virtual void EndOfRunAction(const G4Run *);

    void SetPrimaryEnergy(G4double energy) { fPrimaryEnergy = energy; }

private:
    G4double fPrimaryEnergy;
    SingleParticleSD *fSD = nullptr;
};
#endif