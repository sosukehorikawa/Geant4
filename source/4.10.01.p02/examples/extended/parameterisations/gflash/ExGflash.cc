//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: ExGflash.cc 72372 2013-07-16 14:30:39Z gcosmo $
//
/// \file parameterisations/gflash/ExGflash.cc
/// \brief Main program of the parameterisations/gflash example
//
// Created by Joanna Weng 26.11.2004

//std includes 
#include <algorithm>
#include <iostream>
#include "G4Timer.hh"
// G4 includes 
#include "G4ios.hh"
#include "G4GlobalFastSimulationManager.hh"
#include "G4Timer.hh"
#include "G4UImanager.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include "ExGflashActionInitialization.hh"

// my project 
#include "ExGflashDetectorConstruction.hh"
#include "ExGflashPhysicsList.hh"
#include "ExGflashPrimaryGeneratorAction.hh"
#include "ExGflashEventAction.hh"
#include "ExGflashRunAction.hh"

#include "QBBC.hh"


using namespace std;

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#ifdef G4_SOLVE_TEMPLATES
#ifdef G4VIS_USE
#define G4_SOLVE_VIS_TEMPLATES
#endif
#endif


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{   
  // Timer to see GFlash performance
  G4Timer Timer;
  Timer.Start();
  
  G4cout<<"+-------------------------------------------------------+"<<G4endl;
  G4cout<<"|                                                       |"<<G4endl;
  G4cout<<"|          This is an example of Shower                 |"<<G4endl;
  G4cout<<"|          Parameterization with GFLASH                 |"<<G4endl;
  G4cout<<"+-------------------------------------------------------+"<<G4endl;
  


#ifdef G4MULTITHREADED
  G4MTRunManager * runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(4);
  G4cout<<"+-------------------------------------------------------+"<<G4endl;
  G4cout<<"|              Constructing MT run manager              |"<<G4endl;
  G4cout<<"+-------------------------------------------------------+"<<G4endl;
#else
  G4RunManager * runManager = new G4RunManager;
  G4cout<<"+-------------------------------------------------------+"<<G4endl;
  G4cout<<"|        Constructing sequential run manager            |"<<G4endl;
  G4cout<<"+-------------------------------------------------------+"<<G4endl;
#endif
  
  // UserInitialization classes (mandatory)
  G4cout<<"# GFlash Example: Detector Construction"<<G4endl;    
  runManager->SetUserInitialization(new ExGflashDetectorConstruction);
  G4cout<<"# GFlash Example: Physics list"<<G4endl;
  runManager->SetUserInitialization(new ExGflashPhysicsList);
  // runManager->SetUserInitialization(new QBBC);
  // Action initialization:
  runManager->SetUserInitialization(new ExGflashActionInitialization);

  
#ifdef G4VIS_USE
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif
  
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  UImanager->ApplyCommand("/run/verbose 0");
  runManager->Initialize();
  UImanager->ApplyCommand("/Step/Verbose 0");
  
  if (argc==1)   // Define UI terminal for interactive mode  
  { 
#ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute vis.mac");     
#endif
    ui->SessionStart();
    delete ui;
#endif
  }
  else           // Batch mode
  { 
    G4String s=*(argv+1);
    UImanager->ApplyCommand("/control/execute "+s);
  }
  
  #ifdef G4VIS_USE
  delete visManager;
  #endif  
  delete runManager;
  
  Timer.Stop();
  G4cout << G4endl;
  G4cout << "******************************************";
  G4cout << G4endl;
  G4cout << "Total Real Elapsed Time is: "<< Timer.GetRealElapsed();
  G4cout << G4endl;
  G4cout << "Total System Elapsed Time: " << Timer.GetSystemElapsed();
  G4cout << G4endl;
  G4cout << "Total GetUserElapsed Time: " << Timer.GetUserElapsed();
  G4cout << G4endl;
  G4cout << "******************************************";
  G4cout << G4endl;
  
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



