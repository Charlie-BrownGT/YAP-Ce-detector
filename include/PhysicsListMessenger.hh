#ifndef PhysicsListMessenger_h
#define PhysicsListMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class PhysicsList;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PhysicsListMessenger: public G4UImessenger
{
  public:
  
    PhysicsListMessenger(PhysicsList* );
   ~PhysicsListMessenger() override;
    
    void SetNewValue(G4UIcommand*, G4String) override;
    
  private:
  
    PhysicsList*               fPhysicsList = nullptr;
    
    G4UIdirectory*             fPhysDir     = nullptr;
    G4UIcmdWithADoubleAndUnit* fRCmd        = nullptr;
    G4UIcmdWithAString*        fListCmd     = nullptr;
    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

