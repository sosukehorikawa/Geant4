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
// $Id: AClass.hh 86749 2014-11-17 15:03:05Z gcosmo $
// ====================================================================
//   AClass.hh
//
//                                         2005 Q
// ====================================================================
#ifndef ACLASS_H
#define ACLASS_H

// ====================================================================
//
// class definition
//
// ====================================================================

class AClass {
private:
  int ival;
  double dval;
  
public:
  AClass();
  AClass(int i, double d=0.);

  ~AClass();

  inline void SetIVal(int i);
  inline int GetIVal() const;

  inline void SetDVal(double d);
  inline double GetDVal() const;

  void AMethod();

};

// ====================================================================
// inline functions
// ====================================================================

inline void AClass::SetIVal(int i) { ival= i; }
inline int AClass::GetIVal() const { return ival; }

inline void AClass::SetDVal(double d) { dval= d; }
inline double AClass::GetDVal() const { return dval; }

#endif
