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
// $Id: RE01EventAction.hh,v 1.2 2006-06-29 17:42:46 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//


#ifndef RE01EventAction_h
#define RE01EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class G4PrimaryParticle;

class RE01EventAction : public G4UserEventAction
{
  public:
    RE01EventAction();
    ~RE01EventAction();

  public:
    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);

  private:
    G4int trackerCollID;
    G4int calorimeterCollID;
    G4int muonCollID;

    void PrintPrimary(G4PrimaryParticle* pp,G4int ind);
};

#endif

    