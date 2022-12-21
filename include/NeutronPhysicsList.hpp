#ifndef PhysicsList_hpp
#define PhysicsList_hpp

#include "globals.hh"
#include <G4VModularPhysicsList.hh>

class NeutronPhysicsList : public G4VModularPhysicsList {
public:
  NeutronPhysicsList();
  ~NeutronPhysicsList();

public:
  virtual void ConstructParticle();
  virtual void SetCuts();
};

#endif