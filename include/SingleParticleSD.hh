#ifndef BoundarySD_h
#define BoundarySD_h 1

#include "G4VSensitiveDetector.hh"
#include <mutex>

class G4Step;

class BoundarySD : public G4VSensitiveDetector
{
public:
    BoundarySD(const G4String &name);
    ~BoundarySD() override;

    G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *) override;

private:
    G4double fEnergyOut;
    G4double fEnergyIn;
    std::mutex fMutex;
};

class NiEnergyDepositSD : public G4VSensitiveDetector
{
public:
    NiEnergyDepositSD(const G4String &name);
    virtual ~NiEnergyDepositSD();

    virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *) override;

private:
    G4double fEdepTotal;
    std::mutex fMutex;
};

#endif