#include "SteppingAction.hh"
#include "Run.hh"
#include "EventAction.hh"
#include "HistoManager.hh"

#include "G4RunManager.hh"
#include "G4SteppingManager.hh"
#include "G4VProcess.hh"
#include "G4UnitsTable.hh"
#include "G4NIELCalculator.hh"
#include "G4ICRU49NuclearStoppingModel.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* event)
  :fEventAction(event)
{
  fNIELCalculator = new G4NIELCalculator(new G4ICRU49NuclearStoppingModel(),1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

///SteppingAction::~SteppingAction()
///{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  Run* run = static_cast<Run*>(
             G4RunManager::GetRunManager()->GetNonConstCurrentRun()); 
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
   
  G4double EdepStep = aStep->GetTotalEnergyDeposit();

  if (EdepStep > 0.) {
    run->AddEdep(EdepStep);
    fEventAction->AddEdep(EdepStep);
  }
  G4double niel = fNIELCalculator->ComputeNIEL(aStep);
  if(niel > 0.) {
    run->AddNIEL(niel);
    fEventAction->AddNIEL(niel);
  }

  const G4VProcess* process = 
    aStep->GetPostStepPoint()->GetProcessDefinedStep();
  if (process) run->CountProcesses(process->GetProcessName());

  // step length of primary particle
  G4int ID         = aStep->GetTrack()->GetTrackID();
  G4double steplen = aStep->GetStepLength();
  if (ID == 1) analysisManager->FillH1(3,steplen);

/*  
  //debug: charge and mass
  //
  G4int stepNb = aStep->GetTrack()->GetCurrentStepNumber();
  G4StepPoint* postPoint = aStep->GetPostStepPoint();
  G4double charge = postPoint->GetCharge();
  G4double mass   = postPoint->GetMass();
  G4cout << "\n   step= " << stepNb << "   charge= " << charge 
         << "  mass= " << G4BestUnit(mass, "Energy");
*/      
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

