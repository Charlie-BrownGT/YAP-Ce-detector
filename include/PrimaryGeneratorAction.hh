#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4Event;
class DetectorConstruction;
class PrimaryGeneratorMessenger;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction(DetectorConstruction*);    
   ~PrimaryGeneratorAction() override;

  public:
    void SetDefaultKinematic(G4int);
    void SetRndmBeam(G4double val)  {fRndmBeam = val;}   
    void GeneratePrimaries(G4Event*) override;
    
    G4ParticleGun* GetParticleGun() {return fParticleGun;}

  private:
    G4ParticleGun*             fParticleGun  = nullptr;
    DetectorConstruction*      fDetector     = nullptr;
    G4double                   fRndmBeam     = 0.;
    PrimaryGeneratorMessenger* fGunMessenger = nullptr;
};
#endif