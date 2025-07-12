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
    // For boundary crossing
    G4double fEnergyOut;
    G4double fEnergyIn;
    G4int fEscapedParticles;

    // For internal deposition
    G4double fEdepTotal;

    std::mutex fMutex;
};

#endif