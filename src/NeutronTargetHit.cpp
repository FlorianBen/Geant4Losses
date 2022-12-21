#include "NeutronTargetHit.hpp"

#include <G4UnitsTable.hh>

#include <iomanip>

G4ThreadLocal G4Allocator<TargetHit> *GapHitAllocator = 0;

TargetHit::TargetHit() : G4VHit(), fEdep(0.) {}

TargetHit::~TargetHit() {}

TargetHit::TargetHit(const TargetHit & /*right*/) : G4VHit() {}

const TargetHit &TargetHit::operator=(const TargetHit & /*right*/) {
  return *this;
}

int TargetHit::operator==(const TargetHit & /*right*/) const { return 0; }

void TargetHit::Print() {
  if (fEdep > 0.) {
    G4cout << "Hit in the gap Edep: " << std::setw(7)
           << G4BestUnit(fEdep, "Energy") << G4endl;
  }
}