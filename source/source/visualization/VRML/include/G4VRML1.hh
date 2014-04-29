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
// $Id: G4VRML1.hh,v 1.10 2006-06-29 21:25:23 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// G4VRML1.hh
// Yasuhide Sawada and Satoshi Tanaka

#ifndef WIN32

#if defined (G4VIS_BUILD_VRML_DRIVER) || defined (G4VIS_USE_VRML)

#ifndef G4VRML1_HH
#define G4VRML1_HH

#include "G4VGraphicsSystem.hh"
#include "FRClient.h"

class G4VSceneHandler;

//#define FR_VRML_DEFAULT_PORT	40801
//#define FR_VRML_PORT_ENV	"FR_VRML_PORT"
//#define FR_VRML_HOST_NAME_ENV	"FR_VRML_HOST_NAME"

#include "G4VRMLNetConfig.hh"

class G4VRML1: public G4VGraphicsSystem {
public:
	G4VRML1(); 
	virtual ~G4VRML1();
	G4VSceneHandler* CreateSceneHandler(const G4String& name = "");
	G4VViewer*  CreateViewer(G4VSceneHandler&, const G4String& name = "");

public:
	const G4String& getHostName() { return fHostName; }
	G4int getPort() { return fPort; }

private:
	G4String	fHostName;
	G4int		fPort;

};

#endif //G4VRML1_HH
#endif //G4VIS_BUILD_VRML_DRIVER
#endif //WIN32
