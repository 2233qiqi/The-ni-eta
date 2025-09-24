#include "DetectorConstruction.hh"
#include "SingleParticleSD.hh"
#include "NiSelfAbsorbSD.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4PVReplica.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"

DetectorConstruction::DetectorConstruction()
    : fScoringVolume(nullptr)
{
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
    G4bool checkOverlaps = true;
    // NI材料定义
    G4Isotope *isoNi63 = new G4Isotope("Ni63", 28, 63, 62.9296 * g / mole);
    G4Isotope *isoNi64 = new G4Isotope("Ni64", 28, 64, 63.92797 * g / mole);
    G4Element *iso_elNi = new G4Element("CustomNickel", "Ni", 2);
    iso_elNi->AddIsotope(isoNi63, 20. * perCent);
    iso_elNi->AddIsotope(isoNi64, 80. * perCent);
    G4Material *MixNi = new G4Material("Ni", 8.9 * g / cm3, 1);
    MixNi->AddElement(iso_elNi, 100. * perCent);

    // SIC材料定义
    G4Element *elSi = new G4Element("Silicon", "Si", 14, 28.09 * g / mole);
    G4Element *elC = new G4Element("Carbon", "C", 6, 12.01 * g / mole);
    G4Material *SiC = new G4Material("SiliconCarbide", 3.21 * g / cm3, 2);
    SiC->AddElement(elSi, 1);
    SiC->AddElement(elC, 1);

    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldmat = nist->FindOrBuildMaterial("G4_Galactic");

    // World
    G4double worldX = 2 * cm, worldY = 2 * cm, worldZ = 2 * cm;
    auto *solidWorld = new G4Box("SoildWorld", worldX, worldY, worldZ);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldmat, "LogicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "PhysWorld", 0, false, 0, checkOverlaps);

    // World 可视化
    G4VisAttributes *worldVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.1));
    worldVisAtt->SetVisibility(true);
    logicWorld->SetVisAttributes(worldVisAtt);

    // Ni
    G4double Ni63X = 0.5 * cm, Ni63Y = 0.5 * cm, Ni63Z = 0.25 * um; 
    auto *solidNi63 = new G4Box("SolidNi63", Ni63X, Ni63Y, Ni63Z);
    auto *logicalNi63 = new G4LogicalVolume(solidNi63, MixNi, "LogicNi63");

    new G4PVPlacement(0, G4ThreeVector(0., 0., -0.25* um), logicalNi63, "PhysNi63", logicWorld, false, 0, checkOverlaps);

    
    // Ni可视化
    auto *niVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.7));
    niVisAtt->SetVisibility(true);
    logicalNi63->SetVisAttributes(niVisAtt);

    // 设置计分体积，如果需要的话
    
    fScoringVolume = logicalNi63;

    return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
    auto sdManager = G4SDManager::GetSDMpointer();


    G4String niSDName = "NiSelfAbsorbSD";
    if (!sdManager->FindSensitiveDetector(niSDName, false))
    {
        auto *sd_ni = new NiSelfAbsorbSD(niSDName);
        sdManager->AddNewDetector(sd_ni);
        SetSensitiveDetector("LogicNi63", sd_ni, true);
    }

   
    G4String spSDName = "SingleParticleSD";
    if (!sdManager->FindSensitiveDetector(spSDName, false))
    {
        auto *sd_sp = new SingleParticleSD(spSDName);
        sdManager->AddNewDetector(sd_sp);
        SetSensitiveDetector("LogicNi63", sd_sp, true);
    }
}
