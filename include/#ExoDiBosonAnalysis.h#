#ifndef ExoDiBosonAnalysis_H
#define ExoDiBosonAnalysis_H

#include "core/include/SCycleBase.h"

#include "TLorentzVector.h"
#include <string>
#include "TF1.h"
#include "TRandom3.h"
#include "LHAPDF/LHAPDF.h"
// #include <algorithm>

#include "../ExoDiBosonAnalysis/include/InputData.h"
#include "../ExoDiBosonAnalysis/include/PUWeight.h"
#include "../ExoDiBosonAnalysis/include/LHEWeight.h"
#include "../ExoDiBosonAnalysis/include/HLTWeight.h"
#include "../ExoDiBosonAnalysis/include/BTagWeight.h"
#include "../ExoDiBosonAnalysis/include/LumiWeight.h"
#include "../ExoDiBosonAnalysis/include/JetCandidate.h"
#include "../ExoDiBosonAnalysis/include/LeptonCandidate.h"
#include "../ExoDiBosonAnalysis/include/METCandidate.h"
#include "../ExoDiBosonAnalysis/include/HiggsCandidate.h"
#include "../ExoDiBosonAnalysis/include/PredictedDistribution.h"
#include "../../GoodRunsLists/include/TGoodRunsListReader.h"


class HistosManager;
class NtupleManager;

class ExoDiBosonAnalysis : public SCycleBase {

public:
  ExoDiBosonAnalysis();
  ~ExoDiBosonAnalysis();

  virtual void BeginCycle()	throw( SError );
  virtual void EndCycle()		throw( SError );

  virtual void BeginInputData( const SInputData& )				throw( SError );
  virtual void EndInputData  ( const SInputData& )				throw( SError );
  virtual void BeginInputFile( const SInputData& )				throw( SError );
  virtual void ExecuteEvent	( const SInputData&, Double_t )	throw( SError );
   
  void setGenCandidates          ( void );
  bool selectChannel             ( void );
   
  void setWeight                 ( TString infile );
  void initWeight                ( void );
   
  void initData                  ( void );
  void reset                     ( void );
  InputData& getData             ( void ){ return data_; }
  void setNtupleManager          ( NtupleManager* ntupleManager ){ theNtupleManager_ = ntupleManager; }
  void printCutFlow              ( void );
  

  void fillHistos                ( std::string Channel );
       
  bool passedTTbarSelections     ( TString infile );
  bool passedDijetSelections     (  TString infile  );
  bool passedDijetSelectionsAK4  (  TString infile  );
  bool applyJSON                 ( void );
  bool passedFilters             ( TString infile );
  bool passedTrigger             ( void );
	
  bool findLeptonCandidate       ( void );     
  double getMuonScale            ( double oldpt );
  bool findMuonCandidate         ( void ); 
  bool findElectronCandidate     ( void ); 
  bool findMETCandidate          ( void );
  bool findWCandidate            ( void );
  bool findHadronicWCandidate    ( void );
  void findExoCandidate          ( void );
  
  void findAK4Jets             ( void ); 
  TLorentzVector getp4Nu         ( void );
  TLorentzVector getp4NuMethod2  ( void );


  bool findJetCandidates         ( TString infile );
  bool findJetCandidatesAK4      ( void );

  void doJetTriggerEfficiency   ( void );
  void doTriggerEfficiencyvsMass  ( void );
  void do2DTriggerEfficiency  ( void );
  
  void doGenTTReco              ( void );
  void doSubstructureStudies    ( TString infile );
  void doWTagEfficiency         ( TString infile );
  float getPUPPIweight          ( float puppipt, float puppieta );
  double getJetEnergyScale      ( int ak8JetID );
  double getJetMassScale        ( float mass, float jerSigmaPt, TLorentzVector puppijet_tlv, TLorentzVector AK8jet_tlv );
  void  InitPDFSet(int pdfset);
  std::vector<double> PDFweight( int pdfset );
  void calcPDFweight(bool all);
  bool passedTau21Selections(std::string cat);
  bool preparationOfHistosForPUreweighting();
  float getPUPPIweight_gen(float puppipt, float puppieta );
  float getPUPPIweight_rec(float puppipt, float puppieta );

  void setPredictedDistribution();
     
private:
  ClassDef( ExoDiBosonAnalysis, 0 );  
       
  HistosManager* theHistosManager_;
  NtupleManager* theNtupleManager_;
  InputData      data_            ;
  PUWeight       PUWeight_        ;
  HLTWeight      HLTWeight_       ;
  BTagWeight     BTagWeight_      ;
  LumiWeight     LumiWeight_      ;
  TH1F*          hPUweights_      ;
  TFile*         fMistag_         ;
  TH1D*          hMistag_         ;
  PredictedDistribution * hvv_pred; 
  Root::TGoodRunsList m_grl;

  std::map<int,TLorentzVector>	genCandidates_	;
  std::vector<LeptonCandidate>	leptonCand_		;
  std::vector<JetCandidate	>	AK4jetCand_		;
  std::vector<JetCandidate	>	AK4bjetCand_	;
  std::vector<JetCandidate	>	Vcand				;
  std::vector<JetCandidate	>	genJetCand				;
  std::vector<HiggsCandidate	>	WCand_			;
  std::vector<METCandidate	>	METCand_			;
	 
  std::vector<JetCandidate	>	Leptonicb_	;
  std::vector<JetCandidate	>	Hadronicb_	;
  std::vector<JetCandidate	>	HadronicJ_	;
  std::vector<std::vector<JetCandidate> > PrunedSubjetCand_;
  std::vector<std::vector<JetCandidate> > SoftdropSubjetCand_;
  
  int jetINDX;
  
  int            ScaleMuonUpDown_  ;

  // XML configuration //
   
  /* general settings */    
  bool           isLowMass ;     
  std::string    InputTreeName_   ;
  std::string    OutputTreeName_  ;   
  bool           isSignal_        ;
  bool           usePuppiSD_        ;
  bool           runOnMC_         ;
  bool           GenStudies_       ;
  std::string    Channel_         ; 
  std::string    MassWindow_  ; 
  bool           Trigger_         ;
  bool           applyFilters_  ;
   

  /* leptonic selections */
  int    foundAEle              ;
  int    foundAMu               ;
  double         leptPtCut_	   ;
  double         leptEtaCut_	   ;
  double         elePtCut_	   ;
  double         eleEtaCut_	   ;
  double         muPtCut_	   ;
  double         muEtaCut_	   ;
  double         AleptPtCut_	   ;
  double         AleptEtaCut_	;
  double         METCut_  	   ;
   
  /* jet selections */
  double         MjjCut_	   	;
  double         dEtaCut_	   	;
  double         JetPtCutLoose_   	;
  double         JetPtCutTight_   	;
  double         JetEtaCut_	   	; 
  bool           Tau21Cut_	   		;  
  double         Tau21Low_	   		;
  double         Tau21High_	   	;
  double         Tau21HPLow_	   		;
  double         Tau21HPHigh_	   	;      

  /* pruned mass */
  bool           VetoSR_          ;
  double         mWLow_		   ;
  double         mWHigh_	   ;
  double         mZLow_		   ;
  double         mZHigh_	   ;

  double         xSec_            ;
  double         genEvents_       ;
  double         Lumi_            ;
  std::string    PUProfileData_   ;
  std::string    JSONfile_;
  std::string    BTagEff4vetoData_  ;
  std::string    BTagEff4fatjetData_;
  std::string    BTagEff4subjetData_;
  std::string    PUPPIJEC_;
  std::string    PUPPIJMR_;
  std::string    scaleUncPar_;
  double JMS_   ;
  double JMSunc_;
  double JMR_   ;
  double JMRunc_;
  
  int PDFSET_;
  std::string wPDFname_;
  
  
  TRandom3*      tr_              ;
   

  // END OF XML CONFIGURATION //
  
  
  TF1* puppisd_corrGEN     ;
  TF1* puppisd_corrRECO_cen;
  TF1* puppisd_corrRECO_for;
  TF1* puppisd_resolution_cen ; 
  TF1* puppisd_resolution_for ; 
  int  channel		;
  int  category		;
  int run;
  int event;
  int lumi;
   
  float		pdgMtop;
  float		pdgMw; 
  float		pdgWidthtop;
  float		pdgWidthw;   
  float		weight_			;
  float		weight			;
  float         genweight_   ;
  float		puweight_		;
  float		ptweight_		;
  float		hltweight_		;
  float  btagweight_  ;
  float  lumiweight_  ;
  std::vector<double> pdfweight_       ;
  float  btagvetow    ;
  float  htagw        ;  
  float		Mjj				;
  float  	MWW				;
  float  	MVV				;
  float  	MVV_reduced	  ;
  float  	MVVmethod2		;
  float  	Mj1				;
  float  	Mj2				;
  float 	htopmass			;
  float  	ltopmass			;
  float		ltopmassMethod2;
  float		Mj					;
  float		WMass				;
  float		WMassMethod2	;
  float		jetsDeltaEta	;
  int		nBTags			;
  
  float nSumGenWeights_;
  int    nPVs             ; 
  int    nEvents_         ;
  int    nPassedJSON_     ;  
  int    nPassedFilters_  ;  
  int    nPassedTrigger_  ;  
  int    nPassedChi2_     ;  
  
  std::vector<double> nEvents_wPDF_;
  std::vector<double> nPassed_wPDF_;
  
  int     nak4jets;

  int    nPassedTopMass_         ;    
  int    nPassedJetMass_         ;     
  int    nPassedJetPrunedMass_   ;
  int    nPassedTau21Cut_        ;
  int    nPassedWTag_				 ;
  
  int    nPassedFilter_HBHEIso_;
  int    nPassedFilter_HBHE_;
  int    nPassedFilter_CSCHalo_;
  int    nPassedFilter_CSCTightHalo2015_;
  int    nPassedFilter_HCALlaser_;
  int    nPassedFilter_ECALDeadCell_;
  int    nPassedFilter_GoodVtx_;
  int    nPassedFilter_TrkFailure_;
  int    nPassedFilter_EEBadSc_;
  int    nPassedFilter_ECALlaser_;
  int    nPassedFilter_TrkPOG_;
  int    nPassedFilter_TrkPOG_manystrip_;
  int    nPassedFilter_TrkPOG_toomanystrip_;
  int    nPassedFilter_TrkPOG_logError_;
  int    nPassedFilter_METFilters_;
  int    nPassedMETFiltersAll_;
  int    nPassedTrkFiltersAll_;
  int    nPassedGoodPVFilter_;
   
   
  //Dijet cut flow
  int    nPassedFoundJets_	 ;
  int    nPassedJetsDEta_		 ;
  int    nPassedMjj_			 ;
  int    nPassedWtagging_		 ;
	
  //TTbar W-tag SF cut flow
  int    nNopuppi_  ;
  int    nPassedFoundLept_  ;
  int    nPassedFoundMET_   ;
  int    nPassedIsoLep_     ;
  int    nPassedVetoLep_		;
  int    nPassedFoundW_			;
  int    nPassedFoundJet_   ;
  int    nPassedLepJetDR_   ;
  int    nPassed1bTag_      ;

	
  /* for tree */
  int nPV;

  float pfMET;
  float pfMETPhi;

  int nLooseEle; //number of electrons with looseID
  int nLooseMu; //number of electrons with looseID	

  //SELECTED LEPTON - the most energetic one satisfying HEEP_ID/HighPtMuon_ID :
  float l_pt; 
  float l_eta; 
  float l_phi; 
  float l_iso ;

  //FAT JET: the most energetic AK8 jet satisfying loosejetID && cleaned from the all HEEP/highPtMuon leptons in a cone dR=1.0:
  
  float jet_deta; 
  
  float jet_pt_jet1; 
  float jet_eta_jet1; 
  float jet_phi_jet1; 
  float jet_mass_jet1;
  float jet_mass_pruned_jet1;
  float jet_mass_pruned_W1;
  float jet_mass_pruned_Z1;
  float jet_mass_softdrop_jet1; 
  float jet_tau2tau1_jet1; 
  
  float jet_pt_jet2; 
  float jet_eta_jet2; 
  float jet_phi_jet2; 
  float jet_mass_jet2;
  float jet_mass_pruned_jet2;
  float jet_mass_pruned_W2;
  float jet_mass_pruned_Z2;
  float jet_mass_softdrop_jet2; 
  float jet_tau2tau1_jet2; 
  
  
  float jet1_rcn        ;
  float jet1_cm         ;
  float jet1_nm         ;
  float jet1_muf        ;
  float jet1_phf        ;
  float jet1_emf        ;
  float jet1_nhf        ;
  float jet1_chf        ;
  float jet1_che        ;
  float jet1_ne         ;
  float jet1_hf_hf      ;
  float jet1_hf_emf     ;
  float jet1_hof        ;
  float jet1_chm        ;
  float jet1_neHadMult  ;
  float jet1_phoMult    ;
  float jet1_nemf       ;
  float jet1_cemf       ;
  float jet1_charge     ;
  float jet1_area       ;
  float jet2_rcn        ;
  float jet2_cm         ;
  float jet2_nm         ;
  float jet2_muf        ;
  float jet2_phf        ;
  float jet2_emf        ;
  float jet2_nhf        ;
  float jet2_chf        ;
  float jet2_che        ;
  float jet2_ne         ;
  float jet2_hf_hf      ;
  float jet2_hf_emf     ;
  float jet2_hof        ;
  float jet2_chm        ;
  float jet2_neHadMult  ;
  float jet2_phoMult    ;
  float jet2_nemf       ;
  float jet2_cemf       ;
  float jet2_charge     ;
  float jet2_area       ;
  
  
  
  
  
  
  
  
  
  
  
  
  
  float sum_genweights; 
  float jet_rho; 

  //W boson:
  float W_pt;
  float W_eta;
  float W_phi;

  //lvj MASS:
  float m_lvj;

  int njets;  //AK4 jets
  int nbtag;  //number of AK4 jets b-tagged with iCSVM 
  

  float jet_mass_pruned ;
  float jet_mass_pruned_UnCorr;
  float jet_pt ;
  float jet_csv ;
  float jet_eta ;
  float jet_phi ;
  float jet_tau2tau1 ;
  float jet_jec ;
  float jet_pruned_jec ;
  float jet_puppi_softdrop ;
  float jet_puppi_pruned ;
  float jet_puppi_tau1;
  float jet_puppi_tau2;  
  float jet_puppi_tau3;
  float jet_puppi_pt;
  
  float jet1_puppi_softdrop ;
  float jet1_puppi_pruned ;
  float jet1_puppi_tau1;
  float jet1_puppi_tau2;  
  float jet1_puppi_tau3;
  float jet1_puppi_pt;
  float jet2_puppi_softdrop ;
  float jet2_puppi_pruned ;
  float jet2_puppi_tau1;
  float jet2_puppi_tau2;  
  float jet2_puppi_tau3;
  float jet2_puppi_pt;
  float jet_puppi_tau2tau1_jet1;
  float jet_puppi_tau2tau1_jet2;
  float jet_ddt_jet1;
  float jet_ddt_jet2;
  
  float Wlept_pt ;
  float Wlept_mt ;
  int   realW_def1 ;
  int   realW_def2 ;
  
   
  
  float wmax_  =0;
  float wmaxpu_ =0;
  float wmaxlumi_ =0;
  float wmaxpt_ =0;
  float wmaxhlt_=0;
  float wmaxbtag_=0;
  float wmaxgen_=0;
  int numEvents_=0;

  

}; // class ExoDiBosonAnalysis

#endif // ExoDiBosonAnalysis_H

