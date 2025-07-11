#include "DetectorConstruction.hh"
#include "SingleParticleSD.hh"

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

    G4Isotope *isoNi63 = new G4Isotope("Ni63", 28, 63, 62.9296 * g / mole);
    G4Isotope *isoNi64 = new G4Isotope("Ni64", 28, 64, 63.92797 * g / mole);
    G4Element *iso_elNi = new G4Element("CustomNickel", "Ni", 2);
    iso_elNi->AddIsotope(isoNi63, 20. * perCent);
    iso_elNi->AddIsotope(isoNi64, 80. * perCent);
    G4Material *MixNi = new G4Material("Ni", 8.9 * g / cm3, 1);
    MixNi->AddElement(iso_elNi, 100. * perCent);

    // World Material (Vacuum)
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldmat = nist->FindOrBuildMaterial("G4_Galactic");

    // World
    G4double worldX = 200 * um, worldY = 200 * um, worldZ = 200 * um;
    auto *solidWorld = new G4Box("SoildWorld", worldX, worldY, worldZ);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldmat, "LogicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "PhysWorld", 0, false, 0, checkOverlaps);

    // World
    G4VisAttributes *worldVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.1));
    worldVisAtt->SetVisibility(true);
    logicWorld->SetVisAttributes(worldVisAtt);

    // Ni

    G4double Ni63X = 10 * um, Ni63Y = 10 * um, Ni63Z = 0.25 * um; // Ni源的半尺寸
    auto *solidNi63 = new G4Box("SolidNi63", Ni63X, Ni63Y, Ni63Z);
    auto *logicalNi63 = new G4LogicalVolume(solidNi63, MixNi, "LogicNi63");

    new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicalNi63, "PhysNi63", logicWorld, false, 0, checkOverlaps);

    // Ni
    auto *niVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.7));
    niVisAtt->SetVisibility(true);
    logicalNi63->SetVisAttributes(niVisAtt);

    // 设置计分体积，如果需要的话
    fScoringVolume = logicWorld;

    return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
    auto sdManager = G4SDManager::GetSDMpointer();
    G4String BoundarySDName = "sourceBoundarySD";

    if (!sdManager->FindSensitiveDetector(BoundarySDName, false))
    {
        G4cout << "Constructing Boundary Sensitive Detector: " << BoundarySDName << G4endl;

        auto *boundarySD = new BoundarySD(BoundarySDName);

        sdManager->AddNewDetector(boundarySD);

        SetSensitiveDetector("LogicNi63", boundarySD, true);
    }

    G4String NiSDName = "Ni_source_despositsSD";

    if (!sdManager->FindSensitiveDetector(NiSDName, false))
    {
        G4cout << "Constructing Boundary Sensitive Detector: " << NiSDName << G4endl;
        auto *niSD = new NiEnergyDepositSD(NiSDName);
        sdManager->AddNewDetector(niSD);
        SetSensitiveDetector("LogicNi63", niSD, true);
    }
}
