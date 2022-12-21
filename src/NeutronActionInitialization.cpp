#include "NeutronActionInitialization.hpp"
#include "NeutronEventAction.hpp"
#include "NeutronPrimaryGeneratorAction.hpp"
#include "NeutronRunAction.hpp"

NeutronActionInitialization::NeutronActionInitialization()
    : G4VUserActionInitialization() {}

NeutronActionInitialization::~NeutronActionInitialization() {}

void NeutronActionInitialization::Build() const {
  SetUserAction(new NeutronPrimaryGeneratorAction);
  SetUserAction(new NeutronEventAction(true));
  SetUserAction(new NeutronRunAction(true));
}

void NeutronActionInitialization::BuildForMaster() const {
  SetUserAction(new NeutronRunAction(true));
}