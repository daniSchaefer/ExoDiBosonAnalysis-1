#ifndef JETCANDIDATE_H
#define JETCANDIDATE_H

#include "RecoCandidate.h"

class JetCandidate : public RecoCandidate {

public:
   JetCandidate( TLorentzVector tlv );
   ~JetCandidate( void );
   
   float csv ;
   float mass;
   float prunedMass;
   float prunedMassUnCorr;
   float softdropMass;
   float tau1;
   float tau2;
   float tau3;
   int   flavor;
   float rcn;
   
   int cm;
   int nm;
   float muf;
   float phf;
   float emf;
   float nhf;
   float chf;
   float che;
   float ne;  
   float hf_hf;
   float hf_emf;
   float hof;
   int chm ;
   int neHadMult;
   int phoMult;
   float nemf;
   float cemf;
   float charge;
   float area;

   float rho; 
   
   float jec;
   float pruned_jec; 
   float puppi_prunedMass; 
   float puppi_softdropMass; 
   float puppi_tau1;
   float puppi_tau2;
   float puppi_tau3;
   float puppi_pt;
      
private:

};

#endif // JETCANDIDATE_H



