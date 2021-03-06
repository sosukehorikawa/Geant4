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
// $Id: G4NistMaterialBuilder.hh 67044 2013-01-30 08:50:06Z gcosmo $

#ifndef G4NistMaterialBuilder_h
#define G4NistMaterialBuilder_h 1

//---------------------------------------------------------------------------
//
// ClassName:   G4NistMaterialBuilder
//
// Description: Utility class to hold and manipulate G4Materials
//
// Author:      V.Ivanchenko 21.11.2004
//
// Modifications:
// 31.10.05 Add chemical effect and gas properties (V.Ivanchenko)
// 27.02.06 V.Ivanchneko add ConstructNewGasMaterial
// 11.05.06 V.Ivanchneko add warning flag to FindOrBuildMaterial method
// 27.07.06 V.Ivanchneko set defaul warning=true for FindOrBuildMaterial
// 27.07.07 V.Ivanchneko add matIndex vector to control built materials
// 28.07.07 V.Ivanchneko add BuildMaterial method using Nist index
// 29.04.10 V.Ivanchneko add GetMeanIonisationEnergy method using Nist index
// 09.02.12 P.Gumplinger add ConstructNewIdealGasMaterial
//
//----------------------------------------------------------------------------
//
// Class Description:
//
// Element data from the NIST DB on Atomic Weights and Isotope Compositions
// http://physics.nist.gov/PhysRefData/Compositions/index.html
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include <vector>
#include <CLHEP/Units/PhysicalConstants.h>

#include "globals.hh"
#include "G4Material.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4NistElementBuilder;

class G4NistMaterialBuilder
{
public:

  G4NistMaterialBuilder(G4NistElementBuilder*, G4int verb=0);
			
  ~G4NistMaterialBuilder();
 
  // Find or build a G4Material by name, from dataBase
  //
  G4Material* FindOrBuildMaterial (const G4String& name, 
				   G4bool isotopes=true,
				   G4bool warning =true);
					    
  // construct a G4Material from scratch by atome count
  // 
  G4Material* ConstructNewMaterial (const G4String& name,
				    const std::vector<G4String>& elm,
				    const std::vector<G4int>& nbAtoms,
				    G4double  dens, 
				    G4bool    isotopes = true,
				    G4State   state    = kStateSolid,     
				    G4double  temp     = CLHEP::STP_Temperature,  
				    G4double  pressure = CLHEP::STP_Pressure);

  // construct a G4Material from scratch by fraction mass
  //
  G4Material* ConstructNewMaterial (const G4String& name,
				    const std::vector<G4String>& elm,
				    const std::vector<G4double>& weight,
				    G4double  dens, 
				    G4bool    isotopes = true,
				    G4State   state    = kStateSolid,     
				    G4double  temp     = CLHEP::STP_Temperature,  
				    G4double  pressure = CLHEP::STP_Pressure); 


  // construct a gas G4Material from scratch by atome count
  // 
  G4Material* ConstructNewGasMaterial(const G4String& name, 
				      const G4String& nameDB,
				      G4double temp, G4double pres, 
				      G4bool isotopes = true);

  // Construct an ideal gas G4Material from scratch by atom count
  //
  G4Material* ConstructNewIdealGasMaterial(const G4String& name,
                                           const std::vector<G4String>& elm,
                                           const std::vector<G4int>& nbAtoms,
                                           G4bool    isotopes = true,
                                           G4double  temp     = CLHEP::STP_Temperature,
                                           G4double  pressure = CLHEP::STP_Pressure); 
				      
  // verbosity level defined by G4NistManager
  //
  void SetVerbose(G4int val);

  // cout predefined materials:
  // "simple" - only pure materials in basic state (Z = 1, ..., 98)
  // "compound" - NIST compounds
  // "hep" - HEP materials and compounds
  // "biochemical" - bio-chemical materials 
  // "all" - all
  //
  void ListMaterials(const G4String&);

  // cout lists of predefined materials
  //
  void ListNistSimpleMaterials();
  void ListNistCompoundMaterials();
  void ListHepMaterials();
  void ListSpaceMaterials();
  void ListBioChemicalMaterials();

  // access to the list of names of Geant4 predefined materials
  //
  const std::vector<G4String>& GetMaterialNames() const;

  // access to the NIST mean ionisation potentials
  //
  inline G4double GetMeanIonisationEnergy(G4int index) const;

private:

  void Initialise();
  void NistSimpleMaterials();
  void NistCompoundMaterials();
  void HepAndNuclearMaterials();
  void SpaceMaterials();
  void BioChemicalMaterials();

  // add parameters of material from NIST DB to internal vectors
  // density in g/cm3, mean ionisation potential in eV
  // 
  void AddMaterial(const G4String& nameMat, G4double dens, G4int Z=0,
		   G4double pot=0.0, G4int ncomp=1,
		   G4State=kStateSolid, G4bool stp = true);

  void AddGas(const G4String& nameMat, G4double t=CLHEP::STP_Temperature,
                                       G4double p=CLHEP::STP_Pressure);

  void AddElementByWeightFraction(G4int Z, G4double);
  void AddElementByAtomCount     (G4int Z, G4int);

  void AddElementByWeightFraction(const G4String& name, G4double);
  void AddElementByAtomCount     (const G4String& name, G4int);

  // build a G4Material from dataBase
  G4Material* BuildMaterial(G4int idx, G4bool isotopes);

  void DumpElm(G4int);
  void DumpMix(G4int);

private:

  G4NistElementBuilder*  elmBuilder;

  G4int                  verbose;
  G4int                  nMaterials;
  G4int                  nComponents;
  G4int                  nCurrent;
  G4int                  nElementary;
  G4int                  nNIST;
  G4int                  nHEP;
  G4int                  nSpace;

  std::vector<G4String>  names;
  std::vector<G4String>  chFormulas;

  std::vector<G4double>  densities;
  std::vector<G4double>  ionPotentials;
  std::vector<G4State>   states;
  std::vector<G4double>  fractions;
  std::vector<G4bool>    atomCount;
  std::vector<G4int>     components;
  std::vector<G4int>     indexes;
  std::vector<G4int>     elements;
  std::vector<G4int>     matIndex;
  std::vector<G4bool>    STP;

  std::vector<G4int>     idxGas;
  std::vector<G4double>  gasTemperature;
  std::vector<G4double>  gasPressure;

  G4bool                 first;

};

inline const std::vector<G4String>& 
       G4NistMaterialBuilder::GetMaterialNames() const
{
  return names;
}

inline G4double 
G4NistMaterialBuilder::GetMeanIonisationEnergy(G4int index) const
{
  G4double res = 10*index;
  if(index >= 0 && index < nMaterials) { res = ionPotentials[index]; }
  return res;
}

#endif
