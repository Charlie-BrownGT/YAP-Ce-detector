#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction * Det)
 : fDetector(Det)
{ 
  fTestemDir = new G4UIdirectory("/testem/");
  fTestemDir->SetGuidance("commands specific to this example");
  
  fDetDir = new G4UIdirectory("/testem/det/");
  fDetDir->SetGuidance("detector construction commands");
        
  fMaterCmd = new G4UIcmdWithAString("/testem/det/setMat",this);
  fMaterCmd->SetGuidance("Select material of the box.");
  fMaterCmd->SetParameterName("choice",false);
  fMaterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fMaterCmd->SetToBeBroadcasted(false);
  
  fSizeCmd = new G4UIcmdWithADoubleAndUnit("/testem/det/setSize",this);
  fSizeCmd->SetGuidance("Set size of the box");
  fSizeCmd->SetParameterName("Size",false);
  fSizeCmd->SetRange("Size>0.");
  fSizeCmd->SetUnitCategory("Length");
  fSizeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fSizeCmd->SetToBeBroadcasted(false);
}

DetectorMessenger::~DetectorMessenger()
{
  delete fMaterCmd;
  delete fSizeCmd; 
  delete fDetDir;
  delete fTestemDir;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == fMaterCmd )
   { fDetector->SetMaterial(newValue);}
   
  if( command == fSizeCmd )
   { fDetector->SetSize(fSizeCmd->GetNewDoubleValue(newValue));}
   
}