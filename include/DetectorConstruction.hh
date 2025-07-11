#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Element.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4Box.hh"

#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4SDManager.hh"

#include "SingleParticleSD.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{

public:
    DetectorConstruction();
    ~DetectorConstruction() override;

    G4VPhysicalVolume *Construct() override;

    G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }

    void ConstructSDandField();

private:
    G4LogicalVolume *fScoringVolume = NULL;

    /* G4LogicalVolume *logicSic_mother = NULL;
     G4LogicalVolume *logicSiC_layer = NULL;

     G4LogicalVolume *logicNi63_mother = NULL;
     G4LogicalVolume *logicNi63_layer = NULL;
     */
};

#endif