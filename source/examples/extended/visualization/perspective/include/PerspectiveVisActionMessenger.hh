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
// $Id: PerspectiveVisActionMessenger.hh,v 1.2 2006-06-29 17:45:45 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $

#ifndef PERSPECTIVEVISACTIONMESSENGER_HH
#define PERSPECTIVEVISACTIONMESSENGER_HH

#include "G4UImessenger.hh"

class PerspectiveVisAction;
class G4UIdirectory;
class G4UIcmdWithAString;

class PerspectiveVisActionMessenger: public G4UImessenger {
public:
  PerspectiveVisActionMessenger(PerspectiveVisAction*);
  ~PerspectiveVisActionMessenger();
  void SetNewValue (G4UIcommand*, G4String);

private:
  PerspectiveVisAction* fPVA;
  G4UIdirectory* fpDirectory;
  G4UIcmdWithAString* fpCommandOS;
  G4UIcmdWithAString* fpCommandScene;
};

#endif

