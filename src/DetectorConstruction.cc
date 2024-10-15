#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

DetectorConstruction::DetectorConstruction()
{
  fBoxSize = 1.*m;
  DefineMaterials();
  SetMaterial("YAPCe");  
  fDetectorMessenger = new DetectorMessenger(this);
}

DetectorConstruction::~DetectorConstruction()
{ delete fDetectorMessenger;}

void DetectorConstruction::DefineMaterials()
{
  
  G4double z,a;
  G4Element* O  = new G4Element("Oxygen"   ,"O" , z= 8., a=  16.00*g/mole);
  G4Element* Y  = new G4Element("Yttrium"  ,"Y" , z=39., a=   88.91*g/mole);  
  G4Element* Ce = new G4Element("Cerium"   ,"Ce", z=58., a=  140.12*g/mole);  
  G4Element* Al = new G4Element("Aluminium"   ,"Al", z=13., a=  26.98*g/mole);
  
 G4Material* YAPCe = new G4Material("YAPCe", 5.37*g/cm3, 4);
 YAPCe->AddElement(Y, 1);
 YAPCe->AddElement(Ce, 1);
 YAPCe->AddElement(Al, 1);
 YAPCe->AddElement(O, 1);
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  if(fPBox) { return fPBox; }
  fBox = new G4Box("Container",                         //its name
                   fBoxSize/2,fBoxSize/2,fBoxSize/2);   //its dimensions

  fLBox = new G4LogicalVolume(fBox,                     //its shape
                             fMaterial,                 //its material
                             fMaterial->GetName());     //its name

  fPBox = new G4PVPlacement(0,                          //no rotation
                           G4ThreeVector(),             //at (0,0,0)
                           fLBox,                       //its logical volume
                           fMaterial->GetName(),        //its name
                           0,                           //its mother  volume
                           false,                       //no boolean operation
                           0);                          //copy number
                           
  PrintParameters();

  return fPBox;
}

void DetectorConstruction::PrintParameters()
{
  G4cout << "\n The Box is " << G4BestUnit(fBoxSize,"Length")
         << " of " << fMaterial->GetName() << G4endl;
  G4cout << fMaterial << G4endl;
}

void DetectorConstruction::SetMaterial(const G4String& materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial = 
     G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);
  
  if (pttoMaterial) {
    fMaterial = pttoMaterial;
    if ( fLBox ) { fLBox->SetMaterial(fMaterial); }
  } else {
    G4cout << "\n--> warning from DetectorConstruction::SetMaterial : "
           << materialChoice << " not found" << G4endl;
  }
  G4RunManager::GetRunManager()->PhysicsHasBeenModified();
}

void DetectorConstruction::SetSize(G4double value)
{
  fBoxSize = value;
  if(fBox) {
    fBox->SetXHalfLength(fBoxSize/2);
    fBox->SetYHalfLength(fBoxSize/2);
    fBox->SetZHalfLength(fBoxSize/2);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
    if ( fFieldMessenger.Get() == 0 ) {
        // Create global magnetic field messenger.
        // Uniform magnetic field is then created automatically if
        // the field value is not zero.
        G4ThreeVector fieldValue = G4ThreeVector();
        G4GlobalMagFieldMessenger* msg =
        new G4GlobalMagFieldMessenger(fieldValue);
        //msg->SetVerboseLevel(1);
        G4AutoDelete::Register(msg);
        fFieldMessenger.Put( msg );
    }
}