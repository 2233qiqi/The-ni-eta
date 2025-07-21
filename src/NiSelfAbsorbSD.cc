#include "NiSelfAbsorbSD.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Threading.hh"
#include "G4Step.hh"

NiSelfAbsorbSD::NiSelfAbsorbSD(const G4String &name)
    : G4VSensitiveDetector(name), fEdepNi(0.0)
{
}

NiSelfAbsorbSD::~NiSelfAbsorbSD()
{
    if (G4Threading::IsMasterThread())
    {
        G4cout << "\n Total Energy Deposited in Ni (Self-Absorption): "
               << G4BestUnit(fEdepNi, "Energy") << G4endl;
    }
}

G4bool NiSelfAbsorbSD::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{
    G4double edep = aStep->GetTotalEnergyDeposit();
    if (edep <= 0.)
        return false;

    std::lock_guard<std::mutex> lock(fMutex);
    fEdepNi += edep;

    return true;
}
