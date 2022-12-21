#ifndef NeutronDetectorConstruction_hpp
#define NeutronDetectorConstruction_hpp

#include <G4VSolid.hh>
#include <G4VUserDetectorConstruction.hh>

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class NeutronDetectorMessenger;
class G4Region;
class TargetSD;

/**
 * Detector construction class to define materials and geometry.
 */
class NeutronSimConstruction : public G4VUserDetectorConstruction {
public:
  NeutronSimConstruction();
  virtual ~NeutronSimConstruction();

  virtual G4VPhysicalVolume *Construct();
  virtual void ConstructSDandField();

  void SetSize(G4double);
  void SetMaterial(G4String);

protected:
  /**
   * Setup materials.
   */
  virtual void ConstructMaterials();
  /**
   * Construct the Building Tunnel solid.
   */

  G4VPhysicalVolume *ConstructVolumes();
  /**
   * Delete field.
   * 
   */
  void DeleteSDandField();

private:
  G4bool checkOverlaps;
  G4Material *mat_air;
  G4Material *mat_vacuum;
  G4Material *mat_steel;

  G4LogicalVolume *worldL;
  G4VPhysicalVolume *worldPV;
  
  G4LogicalVolume *srfL;
  G4VPhysicalVolume *srfPV;

  G4LogicalVolume *tubOuterL;
  G4VPhysicalVolume *tubOuterPV;

  G4LogicalVolume *tubInnerL;
  G4VPhysicalVolume *tubInnerPV;

  G4double fTubThickness;

  G4Region *detectorRegion;
  TargetSD *detSD;
};

#endif