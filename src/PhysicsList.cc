#include "PhysicsList.hh"

#include "G4EmLivermorePhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4SystemOfUnits.hh"
PhysicsList::PhysicsList() : G4VModularPhysicsList()
{
    SetVerboseLevel(1);

    RegisterPhysics(new G4EmLivermorePhysics());

    RegisterPhysics(new G4DecayPhysics());

    RegisterPhysics(new G4RadioactiveDecayPhysics());
}

PhysicsList::~PhysicsList()
{
}

void PhysicsList::SetCuts()
{

    G4double defaultCutValue = 5 * eV;
    SetCutValue(defaultCutValue, "e-");
    SetCutValue(defaultCutValue, "e+");
    SetCutValue(defaultCutValue, "gamma");
}