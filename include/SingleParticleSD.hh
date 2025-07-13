#ifndef SingleParticleSD_h
#define SingleParticleSD_h 1

#include "G4VSensitiveDetector.hh"
#include <mutex>

class SingleParticleSD : public G4VSensitiveDetector
{
public:
    SingleParticleSD(const G4String &name);
    ~SingleParticleSD() override;

    G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *) override;

private:
    G4double fEdepTotal;
    G4double fEnergyOut;
    G4int fEscapedParticles;
    std::mutex fMutex;
};

#endif