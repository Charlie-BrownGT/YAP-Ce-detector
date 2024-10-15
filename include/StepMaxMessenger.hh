#ifndef StepMaxMessenger_h
#define StepMaxMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class StepMax;
class G4UIcmdWithADoubleAndUnit;

class StepMaxMessenger: public G4UImessenger
{
  public:
    StepMaxMessenger(StepMax*);
   ~StepMaxMessenger() override;
    
    void SetNewValue(G4UIcommand*, G4String) override;
    
  private:
    StepMax* fStepMax = nullptr;
    G4UIcmdWithADoubleAndUnit* fStepMaxCmd = nullptr;
};
#endif