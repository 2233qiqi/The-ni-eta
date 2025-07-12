#include "SingleParticleSD.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4Threading.hh"
#include "G4UnitsTable.hh"

SingleParticleSD::SingleParticleSD(const G4String &name)
    : G4VSensitiveDetector(name),
      fEnergyOut(0.0), fEnergyIn(0.0), fEscapedParticles(0),
      fEdepTotal(0.0)
{
}

SingleParticleSD::~SingleParticleSD()
{
    if (G4Threading::IsMasterThread())
    {
        G4cout << "\n======================== Boundary & Absorption Summary (from SD) ========================"
               << "\n Total Particles Escaping the Source: " << fEscapedParticles
               << "\n Total Energy Leaving the Source:   " << G4BestUnit(fEnergyOut, "Energy")
               << "\n Total Energy Returning to Source:  " << G4BestUnit(fEnergyIn, "Energy")
               << "\n Total Energy Deposited in Source:  " << G4BestUnit(fEdepTotal, "Energy")
               << "\n========================================================================================="
               << G4endl;
    }
}

G4bool SingleParticleSD::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{
    std::lock_guard<std::mutex> lock(fMutex);

    auto preStepPoint = aStep->GetPreStepPoint();
    auto postStepPoint = aStep->GetPostStepPoint();
    auto preVolume = preStepPoint->GetPhysicalVolume();
    auto postVolume = postStepPoint->GetPhysicalVolume();

    // 检查step是否穿过了边界
    if (preVolume != postVolume)
    { // 如果穿过了边界
        auto sensitiveVolume = preStepPoint->GetTouchableHandle()->GetVolume();
        G4double kineticEnergy = preStepPoint->GetKineticEnergy();

        if (preVolume == sensitiveVolume && postVolume != sensitiveVolume)
        { // 出去
            fEnergyOut += kineticEnergy;
            fEscapedParticles++;
        }
        if (preVolume != sensitiveVolume && postVolume == sensitiveVolume)
        { // 回来
            fEnergyIn += kineticEnergy;
        }
    }
    else
    { // 如果step完全在体积内部，才算作能量沉积
        G4double edep = aStep->GetTotalEnergyDeposit();
        if (edep > 0.)
        {
            fEdepTotal += edep;
        }
    }

    return true;
}
