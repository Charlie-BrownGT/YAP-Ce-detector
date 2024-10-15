#ifndef PrimaryGeneratorMessenger_h
#define PrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;

class PrimaryGeneratorMessenger: public G4UImessenger
{
  public:
    PrimaryGeneratorMessenger(PrimaryGeneratorAction*);
   ~PrimaryGeneratorMessenger() override;
    
    void SetNewValue(G4UIcommand*, G4String) override;
    
  private:
    PrimaryGeneratorAction* fAction     = nullptr;
    
    G4UIdirectory*          fGunDir     = nullptr;
    G4UIcmdWithAnInteger*   fDefaultCmd = nullptr;
    G4UIcmdWithADouble*     fRndmCmd    = nullptr;
};

#endif