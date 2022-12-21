#ifndef NeutronActionInitialization_hpp
#define NeutronActionInitialization_hpp 1

#include "G4VUserActionInitialization.hh"

class NeutronActionInitialization : public G4VUserActionInitialization {
public:
  NeutronActionInitialization();
  virtual ~NeutronActionInitialization();

  virtual void Build() const;
  virtual void BuildForMaster() const;
};

#endif