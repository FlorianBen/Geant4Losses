#ifndef NeutronEventAction_hpp
#define NeutronEventAction_hpp

#include <G4UserEventAction.hh>

class NeutronEventAction : public G4UserEventAction {
public:
  NeutronEventAction(bool verbose = true);
  virtual ~NeutronEventAction();

  virtual void BeginOfEventAction(const G4Event *event);
  virtual void EndOfEventAction(const G4Event *event);

private:
  bool fVerbose;
};

#endif
