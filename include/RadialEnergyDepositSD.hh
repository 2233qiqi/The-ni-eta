#ifndef RADIAL_ENERGY_DEPOSIT_SD_HH
#define RADIAL_ENERGY_DEPOSIT_SD_HH

#include "G4VSensitiveDetector.hh"
#include <vector>

class G4Step;
class G4HCofThisEvent;

class RadialEnergyDepositSD : public G4VSensitiveDetector
{
public:
    RadialEnergyDepositSD(const G4String &name, G4int nbins, G4double rmax);
    virtual ~RadialEnergyDepositSD();

    virtual void Initialize(G4HCofThisEvent *hce) override;
    virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *history) override;
    virtual void EndOfEvent(G4HCofThisEvent *hce) override;

    // 归一化方法
    void NormalizePerEvent(G4int tAotalEvents);
    void NormalizePerPrimaryEnergy(G4double primaryEnergy);

    // ROOT输出方法
    void SaveToROOT(const G4String &filename);

private:
    G4int fNbins;
    G4double fRmax;
    G4double fBinWidth;
    std::vector<G4double> fEnergyDeposit;  // 累计能量沉积
    std::vector<G4double> fNormalizedEdep; // 归一化后的结果
};

#endif