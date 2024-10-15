#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"

#include "G4AnalysisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HistoManager
{
  public:
   HistoManager();
  ~HistoManager() = default;

  private:
    void Book();

    G4String fFileName = "testem1";
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

