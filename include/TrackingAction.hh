#ifndef TrackingAction_h
#define TrackingAction_h 1

#include "G4UserTrackingAction.hh"

class PrimaryGeneratorAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TrackingAction : public G4UserTrackingAction {

  public:  
    TrackingAction(PrimaryGeneratorAction*);
   ~TrackingAction() override = default;
   
    void  PreUserTrackingAction(const G4Track*) override;
    void PostUserTrackingAction(const G4Track*) override;
    
  private:
    PrimaryGeneratorAction* fPrimary = nullptr;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
