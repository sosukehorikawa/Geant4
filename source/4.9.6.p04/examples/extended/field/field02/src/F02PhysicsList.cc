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
/// \file field/field02/src/F02PhysicsList.cc
/// \brief Implementation of the F02PhysicsList class
//
//
// $Id$
// 

#include "G4Timer.hh"
   
#include "F02PhysicsList.hh"
#include "F02DetectorConstruction.hh"
#include "F02PhysicsListMessenger.hh"

#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4Material.hh"
#include "G4EnergyLossTables.hh"
#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include <iomanip>




/////////////////////////////////////////////////////////////
//
//

F02PhysicsList::F02PhysicsList(F02DetectorConstruction* p)
:  G4VUserPhysicsList(), MaxChargedStep(DBL_MAX),
   thePhotoElectricEffect(0), theComptonScattering(0),
   theGammaConversion(0), theeminusIonisation(0),
   theeminusBremsstrahlung(0), theeplusIonisation(0),
   theeplusBremsstrahlung(0), theeplusAnnihilation(0),
   theeminusStepCut(0), theeplusStepCut(0)
{
  pDet = p;

  defaultCutValue = 1.000*mm ;

  cutForGamma = defaultCutValue ;
  cutForElectron = defaultCutValue ;

  SetVerboseLevel(1);
  physicsListMessenger = new F02PhysicsListMessenger(this);
}

/////////////////////////////////////////////////////////////////////////
//
//

F02PhysicsList::~F02PhysicsList()
{
  delete physicsListMessenger; 
}

///////////////////////////////////////////////////////////////////////////
//
//

void F02PhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program. 

  ConstructBosons();
  ConstructLeptons();
  ConstructMesons();
  ConstructBarions();
}

////////////////////////////////////////////////////////////////////////////
//
//

void F02PhysicsList::ConstructBosons()
{
  // gamma

  G4Gamma::GammaDefinition();

  // charged geantino

  G4ChargedGeantino::ChargedGeantinoDefinition();


}

void F02PhysicsList::ConstructLeptons()
{
  // leptons

  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();

  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  G4NeutrinoMu::NeutrinoMuDefinition();
  G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
}

void F02PhysicsList::ConstructMesons()
{
 //  mesons

  G4PionPlus::PionPlusDefinition();
  G4PionMinus::PionMinusDefinition();
  G4PionZero::PionZeroDefinition();
  G4KaonPlus::KaonPlusDefinition();
  G4KaonMinus::KaonMinusDefinition();
}


void F02PhysicsList::ConstructBarions()
{
//  barions

  G4Proton::ProtonDefinition();
  G4AntiProton::AntiProtonDefinition();
}


///////////////////////////////////////////////////////////////////////
//
//

void F02PhysicsList::ConstructProcess()
{
  AddTransportation();
  // AddParameterisation();

  ConstructEM();
  ConstructGeneral();
}

/////////////////////////////////////////////////////////////////////////////
//
//

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4hMultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"

#include "F02StepCut.hh"

void F02PhysicsList::ConstructEM()
{
  theParticleIterator->reset();

  while( (*theParticleIterator)() )
  {
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    if (particleName == "gamma") 
    {
      // Construct processes for gamma

      thePhotoElectricEffect = new G4PhotoElectricEffect();      
      theComptonScattering   = new G4ComptonScattering();
      theGammaConversion     = new G4GammaConversion();
      
      pmanager->AddDiscreteProcess(thePhotoElectricEffect);
      pmanager->AddDiscreteProcess(theComptonScattering);

      pmanager->AddDiscreteProcess(theGammaConversion);
      
    } 
    else if (particleName == "e-") 
    {
      // Construct processes for electron 

      theeminusIonisation = new G4eIonisation();
      theeminusBremsstrahlung = new G4eBremsstrahlung();
      theeminusStepCut = new F02StepCut();

      pmanager->AddProcess(theeminusIonisation,-1,2,2);
      pmanager->AddProcess(theeminusBremsstrahlung,-1,-1,3); 
      pmanager->AddProcess(theeminusStepCut,-1,-1,4);
      theeminusStepCut->SetMaxStep(MaxChargedStep) ;

    } 
    else if (particleName == "e+") 
    {
      // Construct processes for positron 

      theeplusIonisation = new G4eIonisation();
      theeplusBremsstrahlung = new G4eBremsstrahlung();
      theeplusStepCut = new F02StepCut();
      
      pmanager->AddProcess(theeplusIonisation,-1,2,2);
      pmanager->AddProcess(theeplusBremsstrahlung,-1,-1,3);
      pmanager->AddProcess(theeplusStepCut,-1,-1,5);
      theeplusStepCut->SetMaxStep(MaxChargedStep) ;
  
    } 
    else if( particleName == "mu+" || 
             particleName == "mu-"    ) 
    {
      // Construct processes for muon+ 

      F02StepCut* muonStepCut = new F02StepCut();

      G4MuIonisation* themuIonisation = new G4MuIonisation() ;
      pmanager->AddProcess(new G4MuMultipleScattering(),-1,1,1);
      pmanager->AddProcess(themuIonisation,-1,2,2);
      pmanager->AddProcess(new G4MuBremsstrahlung(),-1,-1,3);
      pmanager->AddProcess(new G4MuPairProduction(),-1,-1,4); 
      
      pmanager->AddProcess( muonStepCut,-1,-1,3);
      muonStepCut->SetMaxStep(MaxChargedStep) ;

    } 
    else if (
                particleName == "proton"  
               || particleName == "antiproton"  
               || particleName == "pi+"  
               || particleName == "pi-"  
               || particleName == "kaon+"  
               || particleName == "kaon-"  
              )
    {
      F02StepCut* thehadronStepCut = new F02StepCut();

      G4hIonisation* thehIonisation = new G4hIonisation() ; 
      G4hMultipleScattering* thehMultipleScattering =
                     new G4hMultipleScattering() ;


      pmanager->AddProcess(thehMultipleScattering,-1,1,1);
      pmanager->AddProcess(thehIonisation,-1,2,2);

        pmanager->AddProcess( thehadronStepCut,-1,-1,3);
        thehadronStepCut->SetMaxStep(MaxChargedStep) ;
    }
  }
}

#include "G4Decay.hh"

void F02PhysicsList::ConstructGeneral()
{
  // Add Decay Process

  G4Decay* theDecayProcess = new G4Decay();
  theParticleIterator->reset();

  while( (*theParticleIterator)() )
  {
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();

    if (theDecayProcess->IsApplicable(*particle)) 
    { 
      pmanager ->AddProcess(theDecayProcess);

      // set ordering for PostStepDoIt and AtRestDoIt

      pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
      pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
    }
  }
}

/////////////////////////////////////////////////////////////////////////////

void F02PhysicsList::SetCuts()
{
  G4Timer theTimer ;
  theTimer.Start() ;
  if (verboseLevel >0)
  {
    G4cout << "F02PhysicsList::SetCuts:";
    G4cout << "CutLength : " << G4BestUnit(defaultCutValue,"Length") << G4endl;
  }  
  // set cut values for gamma at first and for e- second and next for e+,
  // because some processes for e+/e- need cut values for gamma
 
   SetCutValue(cutForGamma,"gamma");

   SetCutValue(cutForElectron,"e-");
   SetCutValue(cutForElectron,"e+");

  if (verboseLevel>1)     DumpCutValuesTable();

  theTimer.Stop();
  G4cout.precision(6);
  G4cout << G4endl ;
  G4cout << "total time(SetCuts)=" << theTimer.GetUserElapsed() << " s " <<G4endl;

}

///////////////////////////////////////////////////////////////////////////

void F02PhysicsList::SetGammaCut(G4double val)
{
  cutForGamma = val;
}

///////////////////////////////////////////////////////////////////////////

void F02PhysicsList::SetElectronCut(G4double val)
{
  cutForElectron = val;
}

////////////////////////////////////////////////////////////////////////////

void F02PhysicsList::SetMaxStep(G4double step)
{
  MaxChargedStep = step ;
  G4cout << " MaxChargedStep=" << MaxChargedStep << G4endl;
  G4cout << G4endl;
}

