#include "SingleParticleSD.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4Threading.hh"
#include "G4UnitsTable.hh"

SingleParticleSD::SingleParticleSD(const G4String &name)
    : G4VSensitiveDetector(name), fEdepTotal(0.0)
{
}

SingleParticleSD::~SingleParticleSD()
{
    if (G4Threading::IsMasterThread())
    {
        G4cout << "\n======================== Source Absorption Summary ========================"
               << "\n Total Energy Deposited in Source: " << G4BestUnit(fEdepTotal, "Energy")
               << "\n========================================================================="
               << G4endl;
    }
}

G4bool SingleParticleSD::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{

    G4double edep = aStep->GetTotalEnergyDeposit();

    if (edep <= 0.)
        return false;

    std::lock_guard<std::mutex> lock(fMutex);
    fEdepTotal += edep;

    return true;
}