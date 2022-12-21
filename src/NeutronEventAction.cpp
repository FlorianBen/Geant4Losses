#include "NeutronEventAction.hpp"

#include <G4Event.hh>
#include <G4ios.hh>

NeutronEventAction::NeutronEventAction(bool verbose)
    : G4UserEventAction(), fVerbose(verbose) {}

NeutronEventAction::~NeutronEventAction() {}

void NeutronEventAction::BeginOfEventAction(const G4Event *event) {
    
}

void NeutronEventAction::EndOfEventAction(const G4Event *event) {
}