// PhysicsList.hh
#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh" // <-- 注意基类变成了 G4VModularPhysicsList

class PhysicsList : public G4VModularPhysicsList
{
public:
    PhysicsList();
    virtual ~PhysicsList();

    virtual void SetCuts();
};

#endif