#ifndef StepMax_h
#define StepMax_h 1

#include "globals.hh"
#include "G4VDiscreteProcess.hh"
#include "G4ParticleDefinition.hh"
#include "G4Step.hh"

class StepMaxMessenger;

class StepMax : public G4VDiscreteProcess
{
  public:

   StepMax(const G4String& processName = "UserMaxStep");
  ~StepMax();

   G4bool IsApplicable(const G4ParticleDefinition&) override;

   void SetMaxStep(G4double);

   G4double GetMaxStep() {return fMaxChargedStep;};

   G4double PostStepGetPhysicalInteractionLength(const G4Track& track,
                                       G4double previousStepSize,
                                       G4ForceCondition* condition) override;

   G4VParticleChange* PostStepDoIt(const G4Track&, const G4Step&) override;

   G4double GetMeanFreePath(const G4Track&,G4double,G4ForceCondition*) override;    

  private:

   G4double fMaxChargedStep = DBL_MAX;
     
   StepMaxMessenger* fMess = nullptr;
};
#endif