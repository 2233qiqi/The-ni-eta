#include "PrimaryGenerator.hh"

#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

PrimaryGenerator::PrimaryGenerator()
    : G4VUserPrimaryGeneratorAction()
{

    fGPS = new G4GeneralParticleSource();


    G4ParticleDefinition* electron =
        G4ParticleTable::GetParticleTable()->FindParticle("e-");
    fGPS->GetCurrentSource()->SetParticleDefinition(electron);

    fGPS->GetCurrentSource()->GetPosDist()->SetPosDisType("Volume");
    fGPS->GetCurrentSource()->GetPosDist()->SetPosDisShape("Para");
    fGPS->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(0., 0., -1.75 *um));
    fGPS->GetCurrentSource()->GetPosDist()->SetHalfX(0.5*cm);
    fGPS->GetCurrentSource()->GetPosDist()->SetHalfY(0.5*cm);
    fGPS->GetCurrentSource()->GetPosDist()->SetHalfZ(1.75 *um);

    // 方向
    //fGPS->GetCurrentSource()->GetAngDist()->SetAngDistType("iso");

   auto angDist = fGPS->GetCurrentSource()->GetAngDist();
   angDist->SetAngDistType("planar");  
   angDist->SetParticleMomentumDirection(G4ThreeVector(0.0, 0.0, 1.0));  
    //能谱
   auto eneDist = fGPS->GetCurrentSource()->GetEneDist();
   eneDist->SetEnergyDisType("Arb");
   eneDist->ArbEnergyHistoFile("Ni_data.dat");

    eneDist->ArbInterpolate("Spline");

}

PrimaryGenerator::~PrimaryGenerator()
{
    delete fGPS;
}

void PrimaryGenerator::GeneratePrimaries(G4Event* event)
{
    fGPS->GeneratePrimaryVertex(event);
}
