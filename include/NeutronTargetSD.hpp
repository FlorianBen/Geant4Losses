#ifndef NeutronGapSD_hpp
#define NeutronGapSD_hpp

#include <G4VSensitiveDetector.hh>

#include "NeutronTargetHit.hpp"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class TargetSD : public G4VSensitiveDetector {
public:
  TargetSD(const G4String &name, const G4String &hitsCollectionName,
               const G4int idTuple);
  virtual ~TargetSD();

  virtual void Initialize(G4HCofThisEvent *hce);
  virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *history);

private:

};

#endif