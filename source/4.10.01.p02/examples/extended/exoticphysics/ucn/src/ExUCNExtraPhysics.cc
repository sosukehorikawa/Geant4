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
// $Id: ExUCNExtraPhysics.cc 69762 2013-05-14 08:08:54Z gcosmo $
//
/// \file exoticphysics/ucn/src/ExUCNExtraPhysics.cc
/// \brief Implementation of the ExUCNExtraPhysics class
//
//
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"

#include "G4Transportation.hh"
#include "G4PhysicsListHelper.hh"

#include "G4Decay.hh"
#include "G4DecayTable.hh"
#include "G4NeutronBetaDecayChannel.hh"

#include "G4UserSpecialCuts.hh"
#include "G4StepLimiter.hh"
#include "G4SystemOfUnits.hh"

#include "G4UCNLoss.hh"
#include "G4UCNAbsorption.hh"
#include "G4UCNMultiScattering.hh"
#include "G4UCNBoundaryProcess.hh"

#include "ExUCNExtraPhysics.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExUCNExtraPhysics::ExUCNExtraPhysics() 
    : G4VPhysicsConstructor("Extra") {;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExUCNExtraPhysics::~ExUCNExtraPhysics() {;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExUCNExtraPhysics::ConstructParticle() {;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExUCNExtraPhysics::ConstructProcess()
{
    aParticleIterator->reset();

    while ((*aParticleIterator)()) {
        G4ParticleDefinition* particle = aParticleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();

        if (!pmanager) {
            std::ostringstream o;
            o << "Particle " << particleName << "without a Process Manager";
            G4Exception("ExUCNExtraPhysics::ConstructProcess()","",
                         FatalException,o.str().c_str());
        }

        pmanager->AddDiscreteProcess(new G4StepLimiter());
        pmanager->AddDiscreteProcess(new G4UserSpecialCuts());
    }

    AddBetaDecay();

    ConstructUCN();

//    G4Transportation* transportation = NULL;
//    G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
//    transportation = (G4Transportation*) ph->GetTransportation();

//    if (transportation) transportation->EnableUseMagneticMoment();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExUCNExtraPhysics::AddBetaDecay()
{
    aParticleIterator->reset();

    while ((*aParticleIterator)()) {

        G4ParticleDefinition* particle = aParticleIterator->value();
        G4String particleName = particle->GetParticleName();

        if ( particleName == "neutron" ) {

           particle->SetPDGLifeTime(886.7*second);
           particle->SetPDGStable(false);

           G4DecayTable * table = new G4DecayTable();
           G4VDecayChannel* mode = 
                                new G4NeutronBetaDecayChannel("neutron",1.00);
           table->Insert(mode);
           particle->SetDecayTable(table);

           G4ProcessManager* pmanager = particle->GetProcessManager();
           if (!pmanager) {
               std::ostringstream o;
               o << "Particle " << particleName << "without a Process Manager";
               G4Exception("ExUCNExtraPhysics::ConstructProcess()","",
                            FatalException,o.str().c_str());
           }

           G4Decay* theDecayProcess = new G4Decay();
           pmanager->AddProcess(theDecayProcess);
           pmanager->SetProcessOrdering(theDecayProcess,idxPostStep);
           pmanager->SetProcessOrdering(theDecayProcess,idxAtRest);
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExUCNExtraPhysics::ConstructUCN()
{
    aParticleIterator->reset();
    G4ProcessManager* pmanager = NULL;

    while ((*aParticleIterator)()) {
        G4ParticleDefinition* particle = aParticleIterator->value();
        pmanager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();

        if (!pmanager) {
           std::ostringstream o;
           o << "Particle " << particleName << "without a Process Manager";
           G4Exception("ExUCNExtraPhysics::ConstructProcess()","",
                       FatalException,o.str().c_str());
        }

        if (particleName == "neutron") {
           pmanager->AddDiscreteProcess(new G4UCNLoss());
           pmanager->AddDiscreteProcess(new G4UCNAbsorption());
           pmanager->AddDiscreteProcess(new G4UCNMultiScattering());

           G4UCNBoundaryProcess* ucnBoundaryProcess = 
                                                   new G4UCNBoundaryProcess();
           ucnBoundaryProcess->SetMicroRoughness(true);
           ucnBoundaryProcess->SetVerboseLevel(0);

           pmanager->AddDiscreteProcess(ucnBoundaryProcess);
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
