#ifndef PRIMARYGENERATOR_HH
#define PRIMARYGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"

class PrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGenerator();
  virtual ~PrimaryGenerator();

  virtual void GeneratePrimaries(G4Event*);

private:
  G4GeneralParticleSource* fGPS;  
};

#endif