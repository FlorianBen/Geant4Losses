#include "NeutronDetectorConstruction.hpp"

#include <string>

#include "G4UnitsTable.hh"
#include <G4Box.hh>
#include <G4GDMLParser.hh>
#include <G4GeometryManager.hh>
#include <G4LogicalVolume.hh>
#include <G4LogicalVolumeStore.hh>
#include <G4Material.hh>
#include <G4MultiUnion.hh>
#include <G4NistManager.hh>
#include <G4PVPlacement.hh>
#include <G4PVReplica.hh>
#include <G4PhysicalVolumeStore.hh>
#include <G4Polycone.hh>
#include <G4ProductionCuts.hh>
#include <G4Region.hh>
#include <G4RunManager.hh>
#include <G4SDManager.hh>
#include <G4SolidStore.hh>
#include <G4SystemOfUnits.hh>

#include "NeutronTargetSD.hpp"

NeutronSimConstruction::NeutronSimConstruction()
    : G4VUserDetectorConstruction(), worldL(0), worldPV(0), tubOuterL(0),
      tubOuterPV(0), tubInnerL(0), tubInnerPV(0), fTubThickness(0.2 * cm) {
  checkOverlaps = true;
  ConstructMaterials();

  detectorRegion = new G4Region("VacuumTub");
  auto cuts_detectorRegion = new G4ProductionCuts;
  cuts_detectorRegion->SetProductionCut(0.0);
  detectorRegion->SetProductionCuts(cuts_detectorRegion);
  detSD = new TargetSD("VacuumTubSD", "VacuumTubCollection", 0);
  auto sdManager = G4SDManager::GetSDMpointer();
  sdManager->AddNewDetector(detSD);
}

NeutronSimConstruction::~NeutronSimConstruction() {}

G4VPhysicalVolume *NeutronSimConstruction::Construct() {
  return ConstructVolumes();
}

void NeutronSimConstruction::DeleteSDandField() {
  detectorRegion->RemoveRootLogicalVolume(tubOuterL);
}

void NeutronSimConstruction::ConstructSDandField() {
  detectorRegion->AddRootLogicalVolume(tubOuterL);
  tubOuterL->SetSensitiveDetector(detSD);
}

void NeutronSimConstruction::ConstructMaterials() {
  auto nistManager = G4NistManager::Instance();
  mat_air = nistManager->FindOrBuildMaterial("G4_AIR");
  mat_vacuum = nistManager->FindOrBuildMaterial("G4_Galactic");
  // mat_steel = nistManager->FindOrBuildMaterial("G4_Fe");

  G4int nAtoms = 9;
  auto elSi = nistManager->FindOrBuildElement("Si");
  auto elMn = nistManager->FindOrBuildElement("Mn");
  auto elCr = nistManager->FindOrBuildElement("Cr");
  auto elNi = nistManager->FindOrBuildElement("Ni");
  auto elN = nistManager->FindOrBuildElement("N");
  auto elFe = nistManager->FindOrBuildElement("Fe");

  auto density =  8000 * kg / m3;
  mat_steel = new G4Material("304L", density, 5, kStateSolid);
  mat_steel->AddElementByNumberOfAtoms(elSi, 1);
  mat_steel->AddElementByNumberOfAtoms(elMn, 2);
  mat_steel->AddElementByNumberOfAtoms(elCr, 18);
  mat_steel->AddElementByNumberOfAtoms(elNi, 9);
  mat_steel->AddElementByNumberOfAtoms(elFe, 69);
}

G4VPhysicalVolume *NeutronSimConstruction::ConstructVolumes() {
  DeleteSDandField();
  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
  // World Creation
  // World parameters
  G4double hx = 2 * m;
  G4double hy = 2 * m;
  G4double hz = 3 * m;

  // World volume
  auto worldS = new G4Box("World", hx, hy, hz);
  worldL = new G4LogicalVolume(worldS, mat_air, "WorldL");
  worldPV = new G4PVPlacement(0,               // no rotation
                              G4ThreeVector(), // at (0,0,0)
                              worldL,          // its logical volume
                              "World",         // its name
                              0,               // its mother  volume
                              false,           // no boolean operation
                              0,               // copy number
                              checkOverlaps);  // overlaps checking

  auto boxS = new G4Box("SRF", 75.5 * cm, 106 * cm, 2.5177 * m);
  srfL = new G4LogicalVolume(worldS, mat_air, "SRFL");
  srfPV = new G4PVPlacement(0,               // no rotation
                              G4ThreeVector(), // at (0,0,0)
                              srfL,          // its logical volume
                              "Srf",         // its name
                              worldL,               // its mother  volume
                              false,           // no boolean operation
                              0,               // copy number
                              checkOverlaps);  // overlaps checking

  auto tubOuterS =
      new G4Tubs("tubSoutter", 0, 200 * mm, 2. * m, 0 * deg, 360 * deg);
  tubOuterL = new G4LogicalVolume(tubOuterS, mat_steel, "tubOuterL");
  tubOuterPV = new G4PVPlacement(0,               // no rotation
                                 G4ThreeVector(), // at (0,0,0)
                                 tubOuterL,       // its logical volume
                                 "tubOuterPV",    // its name
                                 srfL,          // its mother  volume
                                 false,           // no boolean operation
                                 0,               // copy number
                                 checkOverlaps);  // overlaps checking

  auto tubInnerS = new G4Tubs("tubInner", 0, 198 * mm, 1.98 * m - fTubThickness,
                              0 * deg, 360 * deg);
  tubInnerL = new G4LogicalVolume(tubInnerS, mat_vacuum, "tubInnerL");
  tubInnerPV = new G4PVPlacement(0,               // no rotation
                                 G4ThreeVector(), // at (0,0,0)
                                 tubInnerL,       // its logical volume
                                 "tubInnerPV",    // its name
                                 tubOuterL,       // its mother  volume
                                 false,           // no boolean operation
                                 0,               // copy number
                                 checkOverlaps);  // overlaps checking

  // always return the root volume
  //
  return worldPV;
}