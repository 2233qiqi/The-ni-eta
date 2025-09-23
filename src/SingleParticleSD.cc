#include "SingleParticleSD.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4Threading.hh"
#include "G4UnitsTable.hh"
#include "G4ThreeVector.hh"

SingleParticleSD::SingleParticleSD(const G4String &name)
    : G4VSensitiveDetector(name),
      fEdepTotal(0.0),
      fEnergyOut(0.0),
      fEscapedParticles(0),
      fBackscatteredParticles(0),
      fBackscatteredEnergy(0.0)
{
}

SingleParticleSD::~SingleParticleSD()
{
    if (G4Threading::IsMasterThread())
    {
        G4cout
            << "\n Total Energy of Escaping Particles: " << G4BestUnit(fEnergyOut, "Energy")
            <<"\n All Escaping Particles: " << fEscapedParticles 
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

    if (preVolume != postVolume)
    {
        auto sensitiveVolume = preStepPoint->GetTouchableHandle()->GetVolume();

        if (preVolume == sensitiveVolume && postVolume != sensitiveVolume)
        {

            G4double kineticEnergy = preStepPoint->GetKineticEnergy();
            fEnergyOut += kineticEnergy;
            fEscapedParticles++;

            G4ThreeVector momentumDirection = preStepPoint->GetMomentumDirection();

            if (momentumDirection.z() < 0.0)
            {
                fBackscatteredParticles++;
                fBackscatteredEnergy += kineticEnergy;
            }
        }
    }
    else
    {
        G4double edep = aStep->GetTotalEnergyDeposit();
        if (edep > 0.)
        {
            fEdepTotal += edep;
        }
    }

    return true;
}