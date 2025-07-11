#include "PrimaryGenerator.hh"

#include "G4ParticleGun.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Geantino.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4Exception.hh"

PrimaryGenerator::PrimaryGenerator() : G4VUserPrimaryGeneratorAction()
{
    fGPS = new G4GeneralParticleSource();
}

void PrimaryGenerator::GeneratePrimaries(G4Event *event)
{
    fGPS->GeneratePrimaryVertex(event);
}
PrimaryGenerator::~PrimaryGenerator()
{
    delete fGPS;
}

/*PrimaryGenerator::PrimaryGenerator()
    : G4VUserPrimaryGeneratorAction(),
      fParticleGun(nullptr)
{
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -7. * um));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
}

PrimaryGenerator::~PrimaryGenerator()
{
    delete fParticleGun;
}

void PrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    if (fParticleGun->GetParticleDefinition() == G4Geantino::Geantino())
    {
        G4int Z = 28;
        G4int A = 63;
        G4double ionEnergy = 0. * keV;
        G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, ionEnergy);

        if (ion)
        {
            fParticleGun->SetParticleDefinition(ion);
            fParticleGun->SetParticleEnergy(0. * keV);
        }
        else
        {

            G4Exception("PrimaryGenerator::GeneratePrimaries()",
                        "MyCode002", FatalException,
                        "Could not find the Ni63 ion. Check PhysicsList.");
            ;
        }
    }
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
*/
/*PrimaryGenerator::PrimaryGenerator() : G4VUserPrimaryGeneratorAction()
{

    fGPS = new G4GeneralParticleSource();

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *electron = particleTable->FindParticle("e-");

    fGPS->GetCurrentSource()->SetParticleDefinition(electron);

    fGPS->GetCurrentSource()->GetAngDist()->SetAngDistType("planar");
    fGPS->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
    fGPS->GetCurrentSource()->GetPosDist()->SetPosDisType("Point");
    fGPS->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(0, 0, 0));
    fGPS->GetCurrentSource()->GetEneDist()->SetEnergyDisType("Mono");
}*/

/*PrimaryGenerator::PrimaryGenerator() : G4VUserPrimaryGeneratorAction()
{

    particleGun = new G4ParticleGun(1);

    G4String particle_name = "e-";
    particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle(particle_name);
    particleGun->SetParticleDefinition(particleDefinition);

    G4double particle_E = 17.63 * keV;
    particleGun->SetParticleEnergy(particle_E);

    G4ThreeVector Gunpos(0., 0., 0.);
    particleGun->SetParticlePosition(Gunpos);

    G4ThreeVector Gunp(0., 0., 1.);
    particleGun->SetParticleMomentumDirection(Gunp);
}

void PrimaryGenerator::GeneratePrimaries(G4Event *evt)
{

    particleGun->GeneratePrimaryVertex(evt);
}

PrimaryGenerator::~PrimaryGenerator()
{
    delete particleGun;
}*/