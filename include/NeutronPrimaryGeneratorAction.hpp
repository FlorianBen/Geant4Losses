#ifndef NeutronPrimaryGeneratorAction_hpp
#define NeutronPrimaryGeneratorAction_hpp

#include <G4GenericMessenger.hh>
#include <G4ParticleGun.hh>
#include <G4VUserPrimaryGeneratorAction.hh>

class G4GeneralParticleSource;
class G4Event;

class NeutronPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  NeutronPrimaryGeneratorAction();
  virtual ~NeutronPrimaryGeneratorAction();

  // method from the base class
  virtual void GeneratePrimaries(G4Event *);

private:
  G4GeneralParticleSource *fParticleGun;
};

#endif
