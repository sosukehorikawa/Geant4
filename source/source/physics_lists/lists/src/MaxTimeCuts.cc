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
//
// --------------------------------------------------------------
//   GEANT 4
//
//      For information related to this code contact: Alex Howard
//      e-mail: a.s.howard@ic.ac.uk
// --------------------------------------------------------------
// Comments
//
//               by A. Howard and H. Araujo 
//                    (27th November 2001)
//
// MaxTimeCuts program
// --------------------------------------------------------------

#include "MaxTimeCuts.hh"

#include "G4Step.hh"
#include "G4UserLimits.hh"
#include "G4VParticleChange.hh"
#include "G4EnergyLossTables.hh"


MaxTimeCuts::MaxTimeCuts(const G4String& aName)
  : SpecialCuts(aName)
{
   if (verboseLevel>1) {
     G4cout << GetProcessName() << " is created "<< G4endl;
   }
   SetProcessType(fUserDefined);
}

MaxTimeCuts::~MaxTimeCuts()
{}

MaxTimeCuts::MaxTimeCuts(MaxTimeCuts& ) : SpecialCuts()
{}

 
G4double MaxTimeCuts::PostStepGetPhysicalInteractionLength(
                             const G4Track& aTrack,
			     G4double ,
			     G4ForceCondition* condition
			    )
{
  // condition is set to "Not Forced"
  *condition = NotForced;

   G4double     proposedStep = DBL_MAX;
   // get the pointer to UserLimits
   G4UserLimits* pUserLimits = aTrack.GetVolume()->GetLogicalVolume()->GetUserLimits();
   const G4DynamicParticle* aParticle = aTrack.GetDynamicParticle();

   // can apply cuts for specific particles - use if(particleDef):
   //   G4ParticleDefinition* aParticleDef = aTrack.GetDefinition();

   //   G4cout << " Time: " << pUserLimits->GetUserMaxTime(aTrack) << G4endl;
  
   if (pUserLimits) {
     G4double temp = DBL_MAX;
     //max time limit
     G4double dTime= (pUserLimits->GetUserMaxTime(aTrack) - aTrack.GetGlobalTime());
     if (dTime < 0. ) {
       proposedStep = 0.;
     } else {  
       G4double beta = (aParticle->GetTotalMomentum())/(aParticle->GetTotalEnergy());
       temp = beta*c_light*dTime;
       if (proposedStep > temp) proposedStep = temp;                  
     }

   }
   return proposedStep;
}
