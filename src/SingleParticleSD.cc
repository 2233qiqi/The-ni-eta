#include "SingleParticleSD.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4Threading.hh"
#include "G4UnitsTable.hh"

SingleParticleSD::SingleParticleSD(const G4String &name)
    : G4VSensitiveDetector(name),
      fEdepTotal(0.0),
      fEnergyOut(0.0),
      fEscapedParticles(0)
{
}

SingleParticleSD::~SingleParticleSD()
{
    if (G4Threading::IsMasterThread())
    {
        G4cout << "\n======================== SD Summary ========================"
               << "\n Total Particles Escaping Source:  " << fEscapedParticles
               << "\n Total Energy of Escaping Particles: " << G4BestUnit(fEnergyOut, "Energy")
               << "\n============================================================"
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
    {
        auto sensitiveVolume = preStepPoint->GetTouchableHandle()->GetVolume();

        // 我们只关心“出去”的粒子
        if (preVolume == sensitiveVolume && postVolume != sensitiveVolume)
        {
            G4double kineticEnergy = preStepPoint->GetKineticEnergy();
            fEnergyOut += kineticEnergy;
            fEscapedParticles++;
        }
    }
    else
    { // 如果step完全在体积内部，才将其能量算作沉积能量
        G4double edep = aStep->GetTotalEnergyDeposit();
        if (edep > 0.)
        {
            fEdepTotal += edep;
        }
    }

    return true;
}