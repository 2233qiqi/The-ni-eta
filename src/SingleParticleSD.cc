#include "SingleParticleSD.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4TouchableHistory.hh"
#include "G4SystemOfUnits.hh"
#include "G4Threading.hh"
#include "G4UnitsTable.hh"

BoundarySD::BoundarySD(const G4String &name)
    : G4VSensitiveDetector(name), fEnergyOut(0.0), fEnergyIn(0.0)
{
}

BoundarySD::~BoundarySD()
{
}

G4bool BoundarySD::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{
    auto preStepPoint = aStep->GetPreStepPoint();
    auto postStepPoint = aStep->GetPostStepPoint();

    auto preVolume = preStepPoint->GetPhysicalVolume();
    auto postVolume = postStepPoint->GetPhysicalVolume();

    if (preVolume == postVolume)
    {
        return false;
    }

    auto sensitiveVolume = preStepPoint->GetTouchableHandle()->GetVolume();

    G4double kineticEnergy = preStepPoint->GetKineticEnergy();

    if (preVolume == sensitiveVolume && postVolume != sensitiveVolume)
    {
        std::lock_guard<std::mutex> lock(fMutex);
        fEnergyOut += kineticEnergy;
    }

    if (preVolume != sensitiveVolume && postVolume == sensitiveVolume)
    {
        std::lock_guard<std::mutex> lock(fMutex);
        fEnergyIn += kineticEnergy;
    }

    return true;
}
NiEnergyDepositSD::NiEnergyDepositSD(const G4String &name)
    : G4VSensitiveDetector(name), fEdepTotal(0.0)
{
}

NiEnergyDepositSD::~NiEnergyDepositSD()
{
    if (G4Threading::IsMasterThread())
    {
        G4cout << "\n======================== Source Absorption Summary ========================"
               << "\n Total Energy Deposited in Ni63: " << G4BestUnit(fEdepTotal, "Energy")
               << "\n========================================================================"
               << G4endl;
    }
}

G4bool NiEnergyDepositSD::ProcessHits(G4Step *step, G4TouchableHistory *)
{
    G4double edep = step->GetTotalEnergyDeposit();
    if (edep <= 0.)
        return false;

    std::lock_guard<std::mutex> lock(fMutex);
    fEdepTotal += edep;

    return true;
}