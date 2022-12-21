#ifndef NeutronRunAction_hpp
#define NeutronRunAction_hpp 1

#include <G4UserRunAction.hh>
#include <globals.hh>

class G4Run;

class NeutronRunAction : public G4UserRunAction {
public:
  NeutronRunAction(bool fFileOutRoot);
  virtual ~NeutronRunAction();

  virtual void BeginOfRunAction(const G4Run *);
  virtual void EndOfRunAction(const G4Run *);

  private:
  bool fFileOutRoot;
};

template<typename T = double>
class Logspace {
private:
    T curValue, base, step;

public:
    Logspace(T first, T last, int num, T base = 10.0) : curValue(first), base(base){
       step = (last - first)/(num-1);
    }

    T operator()() {
        T retval = pow(base, curValue);
        curValue += step;
        return retval;
    }
};


#endif