#ifndef NiSelfAbsorbSD_h
#define NiSelfAbsorbSD_h

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4Threading.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include <mutex>

class NiSelfAbsorbSD : public G4VSensitiveDetector
{
public:
    NiSelfAbsorbSD(const G4String &name);
    virtual ~NiSelfAbsorbSD();

    virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *history) override;

private:
    G4double fEdepNi;
    std::mutex fMutex;
};

#endif
