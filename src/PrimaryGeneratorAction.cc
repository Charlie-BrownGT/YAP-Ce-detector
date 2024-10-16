#include "PrimaryGeneratorAction.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorMessenger.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction( DetectorConstruction* det)
 :fDetector(det)
{
  //fparticleGun = new G4GeneralParticleSource();
  
  fParticleGun  = new G4ParticleGun(1);
  SetDefaultKinematic(1);
    
  //create a messenger for this class
  fGunMessenger = new PrimaryGeneratorMessenger(this);  
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  //delete fparticleGun; 
  
  delete fParticleGun;
  delete fGunMessenger;
}

void PrimaryGeneratorAction::SetDefaultKinematic(G4int front)
{   
   G4ParticleDefinition* ion 
           = G4IonTable::GetIonTable()->GetIon(2, 4, 0.);

   //G4ParticleDefinition* ion 
   //        = G4IonTable::GetIonTable()->GetIon(11, 13, 0.);

  

  fParticleGun->SetParticleDefinition(ion);
  fParticleGun->SetParticleCharge(2.0);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
  fParticleGun->SetParticleEnergy(100.*GeV);
  G4double position = 0.*cm;
  if (front) position = -0.4999*(fDetector->GetSize());
  fParticleGun->SetParticlePosition(G4ThreeVector(position,0.*cm,0.*cm));
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fParticleGun->GeneratePrimaryVertex(anEvent); 

  //fparticleGun -> GeneratePrimaryVertex(anEvent);
}