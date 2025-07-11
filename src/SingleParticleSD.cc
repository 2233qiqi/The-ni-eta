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
        G4cout << "\n======================== Boundary Crossing Summary (from SingleParticleSD) ========================"
               << "\n Total Particles Escaping the Source: " << fEscapedParticles
               << "\n Total Energy Leaving the Source: " << G4BestUnit(fEnergyOut, "Energy")
               << "\n Total Energy Returning to the Source: " << G4BestUnit(fEnergyIn, "Energy")
               << G4endl;

        G4cout << "\n======================== Source Absorption Summary (from SingleParticleSD) ========================"
               << "\n Total Energy Deposited in Source: " << G4BestUnit(fEdepTotal, "Energy")
               << G4endl;
    }
}

G4bool SingleParticleSD::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{

    G4double edep = aStep->GetTotalEnergyDeposit();
    if (edep > 0.)
    {
        std::lock_guard<std::mutex> lock(fMutex);
        fEdepTotal += edep;
    }

    auto preStepPoint = aStep->GetPreStepPoint();
    auto postStepPoint = aStep->GetPostStepPoint();
    auto preVolume = preStepPoint->GetPhysicalVolume();
    auto postVolume = postStepPoint->GetPhysicalVolume();

    if (preVolume != postVolume)
    {
        auto sensitiveVolume = preStepPoint->GetTouchableHandle()->GetVolume();
        G4double kineticEnergy = preStepPoint->GetKineticEnergy();

        std::lock_guard<std::mutex> lock(fMutex);
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

    return true;
}