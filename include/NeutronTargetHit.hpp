#ifndef NeutronGapHit_hpp
#define NeutronGapHit_hpp

#include <G4Allocator.hh>
#include <G4RotationMatrix.hh>
#include <G4THitsCollection.hh>
#include <G4ThreeVector.hh>
#include <G4VHit.hh>

class TargetHit : public G4VHit {
public:
  TargetHit();
  virtual ~TargetHit();
  TargetHit(const TargetHit &right);
  const TargetHit &operator=(const TargetHit &right);
  int operator==(const TargetHit &right) const;

  inline void *operator new(size_t);
  inline void operator delete(void *hit);

  virtual void Print();

  void SetTime(G4double time) { fTime = time; }
  void SetPosition(G4ThreeVector position) { fPosition = position; }
  void SetMomentum(G4ThreeVector Momentum) { fMomentum = Momentum; }
  void AddEdep(G4double edep) { fEdep += edep; }

  G4double GetTime() const { return fTime; }
  G4ThreeVector GetPosition() const { return fPosition; }
  G4ThreeVector GetMomentum() const { return fMomentum; }
  G4double GetEdep() const { return fEdep; }

private:
  G4double fTime;
  G4double fEdep;
  G4ThreeVector fPosition;
  G4ThreeVector fMomentum;
  G4RotationMatrix fRot;
};

using GapHitsCollection = G4THitsCollection<TargetHit>;

extern G4ThreadLocal G4Allocator<TargetHit> *GapHitAllocator;

inline void *TargetHit::operator new(size_t) {
  if (!GapHitAllocator)
    GapHitAllocator = new G4Allocator<TargetHit>;
  return (void *)GapHitAllocator->MallocSingle();
}

inline void TargetHit::operator delete(void *hit) {
  GapHitAllocator->FreeSingle((TargetHit *)hit);
}

#endif
