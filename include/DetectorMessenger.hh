#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

class DetectorMessenger: public G4UImessenger
{
  public:
  
    DetectorMessenger(DetectorConstruction* );
   ~DetectorMessenger() override;
    
    void SetNewValue(G4UIcommand*, G4String) override;
    
  private:
  
    DetectorConstruction*      fDetector  = nullptr;
    
    G4UIdirectory*             fTestemDir = nullptr;
    G4UIdirectory*             fDetDir    = nullptr;
    G4UIcmdWithAString*        fMaterCmd  = nullptr;
    G4UIcmdWithADoubleAndUnit* fSizeCmd   = nullptr;
};
#endif

