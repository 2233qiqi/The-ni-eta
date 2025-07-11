#include "PhysicsList.hh"

#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4OpticalPhysics.hh" //光学
PhysicsList::PhysicsList() : G4VModularPhysicsList()
{
    SetVerboseLevel(1);

    //  电磁物理 (必须)
    RegisterPhysics(new G4EmStandardPhysics());

    //  通用衰变过程
    RegisterPhysics(new G4DecayPhysics());

    //  放射性衰变
    RegisterPhysics(new G4RadioactiveDecayPhysics());

    // 4. 如果您模拟闪烁体等，还需要光学物理
    // G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
    // RegisterPhysics(opticalPhysics);
}

PhysicsList::~PhysicsList()
{
}

void PhysicsList::SetCuts()
{

    G4VUserPhysicsList::SetCuts();
}