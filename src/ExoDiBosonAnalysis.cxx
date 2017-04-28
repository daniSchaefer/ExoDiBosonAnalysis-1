#include "../ExoDiBosonAnalysis/include/ExoDiBosonAnalysis.h"
#include "../ExoDiBosonAnalysis/include/Utilities.h"
#include "../ExoDiBosonAnalysis/include/HistosManager.h"
#include "../ExoDiBosonAnalysis/include/NtupleManager.h"
#include "../ExoDiBosonAnalysis/include/MatchingTools.h"
#include "../ExoDiBosonAnalysis/include/SomeTools.h"
#include "LHAPDF/LHAPDF.h"

#include <iostream>
#include <TRandom.h>
#include <fstream>
using namespace std;

//==============================================================================================
ClassImp( ExoDiBosonAnalysis );

//==============================================================================================
ExoDiBosonAnalysis::ExoDiBosonAnalysis()
  : SCycleBase()
    , weight_(1.)
    , genweight_(1.)
    , puweight_(1.)
    , hltweight_(1.)
    , btagweight_(1.)
    , lumiweight_(1.)
    , ptweight_(1.){

  SetLogName( GetName() );
  /* general settings */   
  DeclareProperty( "InputTreeName"    , InputTreeName_	);
  DeclareProperty( "OutputTreeName"   , OutputTreeName_	);
  DeclareProperty( "isSignal"         , isSignal_				);
  DeclareProperty( "runOnMC"          , runOnMC_				);
  DeclareProperty( "usePuppiSD"       , usePuppiSD_		  );
  DeclareProperty( "GenStudies"       , GenStudies_			);
  DeclareProperty( "Channel"          , Channel_				);
  DeclareProperty( "MassWindow"       , MassWindow_     );
  DeclareProperty( "Trigger"          , Trigger_				);
  DeclareProperty( "applyFilters"     , applyFilters_   );
	 
  /* leptonic selections */
  DeclareProperty( "LeptPtCut"		, leptPtCut_		);
  DeclareProperty( "LeptEtaCut"		, leptEtaCut_		);
  DeclareProperty( "elePtCut"		, elePtCut_	= 35	);
  DeclareProperty( "eleEtaCut"		, eleEtaCut_	= 2.5	);
  DeclareProperty( "muPtCut"		, muPtCut_	= 30	);
  DeclareProperty( "muEtaCut"		, muEtaCut_	= 2.4	);
  DeclareProperty( "AleptPtCut"		, AleptPtCut_		);
  DeclareProperty( "AleptEtaCut"	, AleptEtaCut_		);
  DeclareProperty( "METCut"		, METCut_		);

  /* jet selections */
  DeclareProperty( "MjjCut"		, MjjCut_					);
  DeclareProperty( "dEtaCut"		, dEtaCut_				);
  DeclareProperty( "JetPtCutLoose"	, JetPtCutLoose_	);
  DeclareProperty( "JetPtCutTight"	, JetPtCutTight_	);
  DeclareProperty( "JetEtaCut"        , JetEtaCut_			);  
  DeclareProperty( "Tau21Cut"         , Tau21Cut_				);  
  DeclareProperty( "Tau21HPLow"       , Tau21HPLow_			);
  DeclareProperty( "Tau21HPHigh"	, Tau21HPHigh_		);
  DeclareProperty( "Tau21Low"       	, Tau21Low_		  	);
  DeclareProperty( "Tau21High"     	  , Tau21High_	  	);
	        
  /* pruned mass */ 
  DeclareProperty( "mZLow"						, mZLow_			    );
  DeclareProperty( "mZHigh"					  , mZHigh_	      	);
  DeclareProperty( "mWLow"						, mWLow_		    	);
  DeclareProperty( "mWHigh"					  , mWHigh_		      );
	
  /* weights settings */
  DeclareProperty( "xSec"							, xSec_					  );
  DeclareProperty( "genEvents"				, genEvents_		  );
  DeclareProperty( "Lumi"							, Lumi_					  );
  DeclareProperty( "PUdata"						, PUProfileData_  );
  DeclareProperty( "JSONfile"         , JSONfile_       );
  DeclareProperty( "PUPPIJEC"         , PUPPIJEC_       );
  DeclareProperty( "PUPPIJMR"         , PUPPIJMR_       );
  
  DeclareProperty( "BTagEff4vetoData"  , BTagEff4vetoData_   );
  DeclareProperty( "BTagEff4fatjetData", BTagEff4fatjetData_ );
  DeclareProperty( "BTagEff4subjetData", BTagEff4subjetData_ );
  
  DeclareProperty( "scaleUncPar"      , scaleUncPar_    );
  DeclareProperty( "JMS"              , JMS_            );
  DeclareProperty( "JMSunc"           , JMSunc_         );
  DeclareProperty( "JMR"              , JMR_            );
  DeclareProperty( "JMRunc"           , JMRunc_         );
  DeclareProperty( "PDFSET",  PDFSET_ = -1 );
  DeclareProperty( "wPDFname", wPDFname_ ="none");
   
  theHistosManager_ = new HistosManager( this );
  theNtupleManager_ = new NtupleManager( this );

  pdgMtop = 171.3;
  pdgMw		= 80.4;   
  pdgWidthtop = 19.1;
  pdgWidthw    = 8.9;
  
  
  nNopuppi_           = 0;
  nSumGenWeights_           = 0; 
  sum_genweights            = 0;
  nEvents_                  = 0;
  nPassedJSON_              = 0;
  nPassedTrigger_           = 0;
  nPassedFilters_           = 0;	      
  nPassedJetPrunedMass_     = 0;
  nPassedTau21Cut_          = 0;  
  nPassedWTag_              = 0;
   
  Mjj                       = 0;
  jetsDeltaEta              = 0;
  nBTags                    = 0;
   
  nPassedFoundJets_				= 0;
  nPassedJetsDEta_				= 0;
  nPassedMjj_             = 0;
  nPassedWtagging_				= 0;
 
	
  
  nPassedChi2_          = 0;
  
  nPassedFoundLept_ = 0;
  nPassedVetoLep_   = 0;
  nPassedFoundMET_  = 0;
  nPassedFoundW_    = 0;
  nPassedFoundJet_  = 0;
  nPassedLepJetDR_  = 0;
  nPassed1bTag_     = 0;
  
  jetINDX     					= 99;
  
  nPassedFilter_HBHEIso_             = 0;
  nPassedFilter_HBHE_                = 0;
  nPassedFilter_CSCHalo_             = 0;
  nPassedFilter_CSCTightHalo2015_    = 0;
  nPassedFilter_HCALlaser_           = 0;
  nPassedFilter_ECALDeadCell_        = 0;
  nPassedFilter_GoodVtx_             = 0;
  nPassedFilter_TrkFailure_          = 0;
  nPassedFilter_EEBadSc_             = 0;
  nPassedFilter_ECALlaser_           = 0;
  nPassedFilter_TrkPOG_              = 0;
  nPassedFilter_TrkPOG_manystrip_    = 0;
  nPassedFilter_TrkPOG_toomanystrip_ = 0;
  nPassedFilter_TrkPOG_logError_     = 0;
  nPassedFilter_METFilters_          = 0;
  nPassedMETFiltersAll_              = 0;
  nPassedTrkFiltersAll_              = 0;
  nPassedGoodPVFilter_               = 0;
  
  // setPredictedDistribution();
  
  tr_ = new TRandom3(0);   
   
}

//==============================================================================================
ExoDiBosonAnalysis::~ExoDiBosonAnalysis() {

  // TFile * fout = new TFile("hvv_pred.root", "RECREATE");
  //  hvv_pred->GetPredictedHist()->Write();
  //  hvv_pred->GetTaggableHist()->Write();
  //  hvv_pred->GetObservedHist()->Write();
  //  if ( hvv_pred )
  //    delete hvv_pred;
  //  if ( fout )
  //    delete fout;
  //  if ( hMistag_ )
  //    delete hMistag_;
  //  if ( fMistag_ )
     // delete fMistag_;
	
  if( theHistosManager_ ){
    delete theHistosManager_;
    theHistosManager_ = 0;
  }
   
  if( theNtupleManager_ ){
    delete theNtupleManager_;
    theNtupleManager_ = 0;
  }
}

//==============================================================================================
void ExoDiBosonAnalysis::BeginCycle() throw( SError ) {
    
  // opton JSONfile_ = "No" for the case when we run on data, but the JSON is already applied to the reco samples!
  if( !runOnMC_ && JSONfile_ != "" && JSONfile_ != "No" ){
   m_logger << INFO << "Loading GoodRunsList from file: " << JSONfile_ << SLogger::endmsg;
   Root::TGoodRunsListReader reader( TString( JSONfile_.c_str() ) );
   if( ! reader.Interpret() ) {
     m_logger << FATAL << "Couldn't read in the GRL!" << SLogger::endmsg;
     throw SError( ( "Couldn't read in file: " + JSONfile_ ).c_str(), SError::SkipCycle );
   }
   m_grl = reader.GetMergedGoodRunsList();
   m_grl.Summary();
   m_grl.SetName( "MyGoodRunsList" );

   //
   // Add it as a configuration object, so that the worker nodes will receive it:
   //
   AddConfigObject( &m_grl );
  }
  
  InitPDFSet(PDFSET_);
  return;

}
//==============================================================================================
void ExoDiBosonAnalysis::initWeight( void ){

  TString infile = TString(this->GetHistInputFile()->GetName());
  
  // std::string scenario = "PUS25ns";
  // if( infile.Contains("16Dec2015") or infile.Contains("Fall15") ) scenario = "PUS25ns76X";
 // else
  std::string scenario = "PUS25ns80X";
  if( infile.Contains("Summer16") || infile.Contains("Run2016")) scenario = "PUS25ns80X_full2016";
  if( infile.Contains("Summer16") and infile.Contains("Flat")) scenario = "PU25ns80X_flatPU";
  if( infile.Contains("Fall15") ) scenario = "PUS25ns76X";
  // if( infile.Contains("Spring15") ) PUProfileData_ = "/mnt/t3nfs01/data01/shome/thaarres/EXOVVAnalysisRunII/ExoDiBosonAnalysis/data/biasXsec_72000.root";
  PUWeight::Scenario sc = PUWeight_.toScenario(scenario);
  PUWeight_.initPUWeights(PUProfileData_,sc);
  
  
  TFile* file = TFile::Open( PUPPIJEC_.c_str(),"READ");
  puppisd_corrGEN      = (TF1*)file->Get("puppiJECcorr_gen");
  puppisd_corrRECO_cen = (TF1*)file->Get("puppiJECcorr_reco_0eta1v3");
  puppisd_corrRECO_for = (TF1*)file->Get("puppiJECcorr_reco_1v3eta2v5");
  
  TFile* filejmr = TFile::Open( PUPPIJMR_.c_str(),"READ");
  puppisd_resolution_cen = (TF1*)filejmr->Get("massResolution_0eta1v3");
  puppisd_resolution_for = (TF1*)filejmr->Get("massResolution_1v3eta2v5");
//   HLTWeight::Channel ch = HLTWeight_.toChannel(Channel_);
//   HLTWeight_.initHLTWeights(ch);
//   BTagWeight_.initBTagWeights(BTagEff4vetoData_,BTagEff4fatjetData_,BTagEff4subjetData_);

//   TFile* fPUweights = TFile::Open(PUProfileData_.c_str(),"READ");
//   hPUweights_ = (TH1F*)fPUweights->Get("puweights");
   
}

//==============================================================================================
void ExoDiBosonAnalysis::BeginInputFile( const SInputData& ) throw( SError ) {
  
  TString infile = TString(this->GetHistInputFile()->GetName());

  theNtupleManager_->ConnectVariables( InputTreeName_, infile, runOnMC_ , usePuppiSD_ );
  
  // Initialize weights
  initWeight(); 
         
  return;
}

//==============================================================================================
void ExoDiBosonAnalysis::BeginInputData( const SInputData& ) throw( SError ) {
  
  if( !runOnMC_ && JSONfile_!="No") {
   TObject* grl;
   if( ! ( grl = GetConfigObject( "MyGoodRunsList" ) ) ) {
     m_logger << FATAL << "Can't access the GRL!" << SLogger::endmsg;
     throw SError( "Can't access the GRL!", SError::SkipCycle );
   }
   m_grl = *( dynamic_cast< Root::TGoodRunsList* >( grl ) );
  }
	
      
  theHistosManager_->bookHistos(Channel_); 
  
  DeclareVariable( puweight_     , "puweight"         , OutputTreeName_.c_str() );
  DeclareVariable( lumiweight_   , "lumiweight"        , OutputTreeName_.c_str() );
  DeclareVariable( genweight_    , "genweight"         , OutputTreeName_.c_str() );
  DeclareVariable( btagweight_ 	 , "btagweight"        , OutputTreeName_.c_str() );
  DeclareVariable( ptweight_ 	   , "ptweight"        , OutputTreeName_.c_str() );
  DeclareVariable( pdfweight_ 	   , "pdfweight"        , OutputTreeName_.c_str() );
  DeclareVariable( weight	  , "weight"	       , OutputTreeName_.c_str() );
  DeclareVariable( run     	     , "run"	       , OutputTreeName_.c_str() );
  DeclareVariable( event     	   , "event"	       , OutputTreeName_.c_str() );
  DeclareVariable( lumi     	   , "lumi"	       , OutputTreeName_.c_str() );
  DeclareVariable( nPVs          , "nPV"        , OutputTreeName_.c_str() );
  
  
  if( Channel_.find("WtagSF") != std::string::npos ){
    DeclareVariable( hltweight_         , "hltweight"   , OutputTreeName_.c_str() );
    DeclareVariable( MWW                , "MWW"         , OutputTreeName_.c_str() );
    DeclareVariable( jet_mass_pruned    , "Whadr_pruned", OutputTreeName_.c_str() );
    DeclareVariable( jet_mass_pruned_UnCorr, "Whadr_pruned_UnCorr", OutputTreeName_.c_str() );
    DeclareVariable( jet_csv            , "Whadr_csv"   , OutputTreeName_.c_str() );
    DeclareVariable( jet_pt             , "Whadr_pt"    , OutputTreeName_.c_str() );
    DeclareVariable( jet_eta            , "Whadr_eta"   , OutputTreeName_.c_str() );
    DeclareVariable( jet_phi            , "Whadr_phi"   , OutputTreeName_.c_str() );
    DeclareVariable( realW_def1         , "Whadr_isW_def1"   , OutputTreeName_.c_str() );
    DeclareVariable( realW_def2         , "Whadr_isW_def2"   , OutputTreeName_.c_str() );
    DeclareVariable( jet_tau2tau1       , "Whadr_tau21" , OutputTreeName_.c_str() );
    DeclareVariable( jet_jec            , "Whadr_jec"   , OutputTreeName_.c_str() );
    DeclareVariable( jet_pruned_jec     , "Whadr_pruned_jec"      , OutputTreeName_.c_str() );
    DeclareVariable( jet_puppi_softdrop , "Whadr_puppi_softdrop"  , OutputTreeName_.c_str() );
    DeclareVariable( jet_puppi_pruned   , "Whadr_puppi_pruned"    , OutputTreeName_.c_str() );
    DeclareVariable( jet_puppi_tau1     , "Whadr_puppi_tau1"      , OutputTreeName_.c_str() );
    DeclareVariable( jet_puppi_tau2     , "Whadr_puppi_tau2"      , OutputTreeName_.c_str() );
    DeclareVariable( jet_puppi_tau3     , "Whadr_puppi_tau3"      , OutputTreeName_.c_str() );
    DeclareVariable( jet_puppi_tau2tau1_jet1, "Whadr_puppi_tau2tau1"  , OutputTreeName_.c_str() );
    DeclareVariable( jet_puppi_pt       , "Whadr_puppi_pt"        , OutputTreeName_.c_str() );
    DeclareVariable( jet_ddt_jet1       , "Whadr_ddt"             , OutputTreeName_.c_str() );
    DeclareVariable( l_pt               , "lept_pt"     , OutputTreeName_.c_str() );
    DeclareVariable( l_eta              , "lept_eta"    , OutputTreeName_.c_str() );
    DeclareVariable( l_phi              , "lept_phi"    , OutputTreeName_.c_str() );
    DeclareVariable( l_iso              , "lept_iso"    , OutputTreeName_.c_str() );
    DeclareVariable( Wlept_pt           , "Wlept_pt"    , OutputTreeName_.c_str() ); 
    DeclareVariable( Wlept_mt           , "Wlept_mt"    , OutputTreeName_.c_str() );
    DeclareVariable( WMass              , "Wlept_mass"  , OutputTreeName_.c_str() );
    DeclareVariable( pfMET              , "pfMET"       , OutputTreeName_.c_str() ); 
    DeclareVariable( pfMETPhi           , "pfMETPhi"    , OutputTreeName_.c_str() );
    DeclareVariable( nak4jets           , "nak4jets"    , OutputTreeName_.c_str() );
  }
  if( Channel_.find("dijet") != std::string::npos ){
  DeclareVariable( channel                 	 , "channel"	         , OutputTreeName_.c_str() );
  DeclareVariable( category     	           , "category"	         , OutputTreeName_.c_str() );
  DeclareVariable( jet_deta                  , "jet_deta"          , OutputTreeName_.c_str() );
  DeclareVariable( MVV                       , "MVV"               , OutputTreeName_.c_str() );
  DeclareVariable( MVV_reduced               , "MVV_reduced"       , OutputTreeName_.c_str() );
  
  DeclareVariable( jet_mass_jet1             , "jet_mass_jet1"	       , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_jet2             , "jet_mass_jet2"	       , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_pruned_jet1      , "jet_mass_pruned_jet1"   , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_pruned_jet2      , "jet_mass_pruned_jet2"   , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_pruned_W1        , "jet_mass_pruned_W1"   , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_pruned_W2        , "jet_mass_pruned_W2"   , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_pruned_Z1        , "jet_mass_pruned_Z1"   , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_pruned_Z2        , "jet_mass_pruned_Z2"   , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_softdrop_jet1    , "jet_mass_softdrop_jet1" , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_softdrop_jet2    , "jet_mass_softdrop_jet2" , OutputTreeName_.c_str() );
  DeclareVariable( jet_pt_jet1               , "jet_pt_jet1"            , OutputTreeName_.c_str() );
  DeclareVariable( jet_pt_jet2               , "jet_pt_jet2"            , OutputTreeName_.c_str() );
  DeclareVariable( jet_eta_jet1              , "jet_eta_jet1"           , OutputTreeName_.c_str() );
  DeclareVariable( jet_eta_jet2              , "jet_eta_jet2"           , OutputTreeName_.c_str() );
  DeclareVariable( jet_phi_jet1              , "jet_phi_jet1"			    	, OutputTreeName_.c_str() );
  DeclareVariable( jet_phi_jet2              , "jet_phi_jet2"			    	, OutputTreeName_.c_str() );
  DeclareVariable( jet_tau2tau1_jet1         , "jet_tau2tau1_jet1"		  , OutputTreeName_.c_str() );
  DeclareVariable( jet_tau2tau1_jet2         , "jet_tau2tau1_jet2"		  , OutputTreeName_.c_str() );
  DeclareVariable( jet1_puppi_softdrop       , "jet_puppi_softdrop_jet1"  , OutputTreeName_.c_str() );
  DeclareVariable( jet1_puppi_pruned         , "jet_puppi_pruned_jet1"    , OutputTreeName_.c_str() );
  DeclareVariable( jet1_puppi_tau1           , "jet_puppi_tau1_jet1"      , OutputTreeName_.c_str() );
  DeclareVariable( jet1_puppi_tau2           , "jet_puppi_tau2_jet1"      , OutputTreeName_.c_str() );
  DeclareVariable( jet1_puppi_tau3           , "jet_puppi_tau3_jet1"      , OutputTreeName_.c_str() );
  DeclareVariable( jet1_puppi_pt             , "jet_puppi_pt_jet1"        , OutputTreeName_.c_str() );
  DeclareVariable( jet2_puppi_softdrop       , "jet_puppi_softdrop_jet2"  , OutputTreeName_.c_str() );
  DeclareVariable( jet2_puppi_pruned         , "jet_puppi_pruned_jet2"    , OutputTreeName_.c_str() );
  DeclareVariable( jet2_puppi_tau1           , "jet_puppi_tau1_jet2"      , OutputTreeName_.c_str() );
  DeclareVariable( jet2_puppi_tau2           , "jet_puppi_tau2_jet2"      , OutputTreeName_.c_str() );
  DeclareVariable( jet2_puppi_tau3           , "jet_puppi_tau3_jet2"      , OutputTreeName_.c_str() );
  DeclareVariable( jet_puppi_tau2tau1_jet1   , "jet_puppi_tau2tau1_jet1"  , OutputTreeName_.c_str() );
  DeclareVariable( jet_puppi_tau2tau1_jet2   , "jet_puppi_tau2tau1_jet2"  , OutputTreeName_.c_str() );
  DeclareVariable( jet_ddt_jet1              , "jet_ddt_jet1"             , OutputTreeName_.c_str() );
  DeclareVariable( jet_ddt_jet2              , "jet_ddt_jet2"             , OutputTreeName_.c_str() );
  
  DeclareVariable( jet1_rcn       , "jet1_rcn"       , OutputTreeName_.c_str() );
  DeclareVariable( jet1_cm        , "jet1_cm"        , OutputTreeName_.c_str() );
  DeclareVariable( jet1_nm        , "jet1_nm"        , OutputTreeName_.c_str() );
  DeclareVariable( jet1_muf       , "jet1_muf"       , OutputTreeName_.c_str() );
  DeclareVariable( jet1_phf       , "jet1_phf"       , OutputTreeName_.c_str() );
  DeclareVariable( jet1_emf       , "jet1_emf"       , OutputTreeName_.c_str() );
  DeclareVariable( jet1_nhf       , "jet1_nhf"       , OutputTreeName_.c_str() );
  DeclareVariable( jet1_chf       , "jet1_chf"       , OutputTreeName_.c_str() );
  DeclareVariable( jet1_che       , "jet1_che"       , OutputTreeName_.c_str() );
  DeclareVariable( jet1_ne        , "jet1_ne"        , OutputTreeName_.c_str() );
  DeclareVariable( jet1_hf_hf     , "jet1_hf_hf"     , OutputTreeName_.c_str() );
  DeclareVariable( jet1_hf_emf    , "jet1_hf_emf"    , OutputTreeName_.c_str() );
  DeclareVariable( jet1_hof       , "jet1_hof"       , OutputTreeName_.c_str() );
  DeclareVariable( jet1_chm       , "jet1_chm"       , OutputTreeName_.c_str() );
  DeclareVariable( jet1_neHadMult , "jet1_neHadMult" , OutputTreeName_.c_str() );
  DeclareVariable( jet1_phoMult   , "jet1_phoMult"   , OutputTreeName_.c_str() );
  DeclareVariable( jet1_nemf      , "jet1_nemf"      , OutputTreeName_.c_str() );
  DeclareVariable( jet1_cemf      , "jet1_cemf"      , OutputTreeName_.c_str() );
  DeclareVariable( jet1_charge    , "jet1_charge"    , OutputTreeName_.c_str() );
  DeclareVariable( jet1_area      , "jet1_area"      , OutputTreeName_.c_str() );
  
  DeclareVariable( jet2_rcn       , "jet2_rcn"       , OutputTreeName_.c_str() );
  DeclareVariable( jet2_cm        , "jet2_cm"        , OutputTreeName_.c_str() );
  DeclareVariable( jet2_nm        , "jet2_nm"        , OutputTreeName_.c_str() );
  DeclareVariable( jet2_muf       , "jet2_muf"       , OutputTreeName_.c_str() );
  DeclareVariable( jet2_phf       , "jet2_phf"       , OutputTreeName_.c_str() );
  DeclareVariable( jet2_emf       , "jet2_emf"       , OutputTreeName_.c_str() );
  DeclareVariable( jet2_nhf       , "jet2_nhf"       , OutputTreeName_.c_str() );
  DeclareVariable( jet2_chf       , "jet2_chf"       , OutputTreeName_.c_str() );
  DeclareVariable( jet2_che       , "jet2_che"       , OutputTreeName_.c_str() );
  DeclareVariable( jet2_ne        , "jet2_ne"        , OutputTreeName_.c_str() );
  DeclareVariable( jet2_hf_hf     , "jet2_hf_hf"     , OutputTreeName_.c_str() );
  DeclareVariable( jet2_hf_emf    , "jet2_hf_emf"    , OutputTreeName_.c_str() );
  DeclareVariable( jet2_hof       , "jet2_hof"       , OutputTreeName_.c_str() );
  DeclareVariable( jet2_chm       , "jet2_chm"       , OutputTreeName_.c_str() );
  DeclareVariable( jet2_neHadMult , "jet2_neHadMult" , OutputTreeName_.c_str() );
  DeclareVariable( jet2_phoMult   , "jet2_phoMult"   , OutputTreeName_.c_str() );
  DeclareVariable( jet2_nemf      , "jet2_nemf"      , OutputTreeName_.c_str() );
  DeclareVariable( jet2_cemf      , "jet2_cemf"      , OutputTreeName_.c_str() );
  DeclareVariable( jet2_charge    , "jet2_charge"    , OutputTreeName_.c_str() );
  DeclareVariable( jet2_area      , "jet2_area"      , OutputTreeName_.c_str() );
  

  // DeclareVariable( sum_genweights       , "sum_genweights"        , OutputTreeName_.c_str() );
  // DeclareVariable( jet_rho              , "jet_rho"            , OutputTreeName_.c_str() );
  
}

     
  return;

}

//==============================================================================================
void ExoDiBosonAnalysis::initData( void ){

  data_ = theNtupleManager_->getData();
      
}

//==============================================================================================
void ExoDiBosonAnalysis::reset( void ){

  genCandidates_	.clear();
  leptonCand_			.clear();
  AK4jetCand_			.clear();
  AK4bjetCand_		.clear();
  Vcand						.clear();
  METCand_				.clear();
  WCand_					.clear();
  genJetCand      .clear();
  Leptonicb_			.clear();
  Hadronicb_			.clear();
  HadronicJ_			.clear();
  PrunedSubjetCand_  .clear();
  SoftdropSubjetCand_.clear(); 
}

//==============================================================================================
void ExoDiBosonAnalysis::setGenCandidates( void ) {
  std::cout << "setGenCandidates " <<std::endl;
  if( !runOnMC_ ) return;
  if( !isSignal_ && !GenStudies_ ) return;

  TLorentzVector genP;   
  double genptV = -99;
  //std::cout << (data_.genParticle_pdgId)->size() << std::endl;
  for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
    if( (*data_.genParticle_pt).at(p) < 0.1) continue;
    if( (*data_.genParticle_status).at(p) != 4 && (*data_.genParticle_status).at(p) != 22 && (*data_.genParticle_status).at(p) != 23) continue;
    genP.SetPtEtaPhiE( (*data_.genParticle_pt).at(p), (*data_.genParticle_eta).at(p), (*data_.genParticle_phi).at(p), (*data_.genParticle_e).at(p) );
    genCandidates_[ (*data_.genParticle_pdgId).at(p) ] = genP;
  }
                    
  return;
}

//==============================================================================================
bool ExoDiBosonAnalysis::selectChannel( void ) {
  
  if( !isSignal_ ) return false;
  
  bool isSignal = false;
  int nVs = 0;
  
  for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
    bool isHad = false;
    if( (*data_.genParticle_pt).at(p) < 0.01) continue;
    if( fabs((*data_.genParticle_pdgId).at(p)) != 24 and fabs((*data_.genParticle_pdgId).at(p)) != 23  and fabs((*data_.genParticle_pdgId).at(p)) != 25) continue;
    if ((*data_.genParticle_dau)[p].size() < 2) continue;
    for( unsigned int d = 0; d < (*data_.genParticle_dau)[p].size(); ++d ) {
      if( fabs((*data_.genParticle_dau)[p][d]) > 9) continue;
      isHad = true;
    }
    if (!isHad) continue;
    nVs ++;
  }
  
   if( Channel_.find("VVdijet")!=std::string::npos && nVs > 1) isSignal = true;
   else if (Channel_.find("qVdijet")!=std::string::npos && nVs > 0) isSignal = true;
   else isSignal = false;
   
  return isSignal;
}

//==============================================================================================
void ExoDiBosonAnalysis::setWeight( TString infile ){
  if( !runOnMC_ ) return;
    
  std::vector<int>* TruePU = data_.nPUTrue;
  if(TruePU->size()==0)
  {
   TruePU = data_.nPuVtxTrue;   
  }
  
  for( unsigned int v = 0; v < TruePU->size(); ++v ){
    if( (*data_.bX)[v] == 0 ) puweight_ = PUWeight_.getPUWeight( (*TruePU)[v] );
  }
  // if( data_.nPVs <= 52 ){
  //   int bin = hPUweights_->GetXaxis()->FindBin(data_.nPVs);
  //   puweight_ = hPUweights_->GetBinContent(bin);
  // }
  
  btagvetow = 1.; 
  htagw = 1.;
  
  if( Channel_.find("WtagSF") != std::string::npos && infile.Contains( "TT" ) ){ 
    
    float pt_top     = 0;
    float pt_antitop = 0;
    
    float a =  0.156   ;
    float b = -0.00137 ;
    
    for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
      if( (*data_.genParticle_pt).at(p) < 0.1) continue;
      if( fabs((*data_.genParticle_pdgId).at(p)) != 6) continue;
      bool isT = false;
      for( unsigned int d = 0; d < (*data_.genParticle_dau)[p].size(); ++d ) {
        if( fabs((*data_.genParticle_dau)[p][d]) != 24) continue;
        isT = true;
      }
      if( !isT) continue;
      if((*data_.genParticle_pdgId).at(p) == 6) pt_top = (*data_.genParticle_pt).at(p);
      if((*data_.genParticle_pdgId).at(p) == -6) pt_top = (*data_.genParticle_pt).at(p);
    }
    ptweight_ = std::sqrt( std::exp( a+b*pt_top )*std::exp( a+b* pt_antitop ) ); 
  } 
  
  // if( Channel_.find("WtagSF_mu") != std::string::npos ) hltweight_ = HLTWeight_.getHLTWeight( leptonCand_[0].p4.Pt(), leptonCand_[0].p4.Eta() );
  if( Channel_.find("WtagSF")    != std::string::npos ) btagvetow = BTagWeight_.getBTagWeight( AK4jetCand_, "veto" );
  btagweight_ =  btagvetow*htagw;
    
  double lumiw = xSec_/genEvents_;     
  lumiweight_ = lumiw*LumiWeight_.getLumiWeight( infile )*Lumi_; 
  if( Channel_.find("WtagSF") != std::string::npos) genweight_ = data_.genWeight < 0 ? -1 : 1;
  else  if( Channel_.find("dijet") != std::string::npos) genweight_ = data_.genWeight; //
  
 
  // // weight_ = puweight_*lumiweight_*genweight_*hltweight_;
  // if( Channel_.find("WtagSF") != std::string::npos ){
  //   weight_ = puweight_*lumiweight_*genweight_*ptweight_;
  // }
  
  weight_ = puweight_*lumiweight_*genweight_*hltweight_*btagvetow;
  if(weight_ != weight_){
  std::cout << "Weight is Inf/NAN. Please check if any of the below weights are wrong:"<<std::endl;
  std::cout << "Total weight = " << weight_ << std::endl    ; std::cout << "PU weight  = " << puweight_  << std::endl;
  std::cout << "Lumiweight   = " << lumiweight_ << std::endl; std::cout << "Gen weight = " << genweight_ << std::endl;
  std::cout << "Skipping this event..."<<std::endl;
  throw SError( SError::SkipEvent );
  }
  //std::cout << lumiweight_ << std::endl;
  //std::cout << lumiw << std::endl;
}

//==============================================================================================
void ExoDiBosonAnalysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {
  numEvents_+=1;
  // Connect branches in tree
  initData();
  // Reset vectors
  reset();

//   preparationOfHistosForPUreweighting();
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  //// Dijet analysis begins HERE/////////////////////////////////////////////////////////////////////////
  calcPDFweight(1);
  
 
  if( Channel_ == "VVdijet" || Channel_ == "qVdijet" ){
     //m_logger << INFO << "Channel : VVdijet of qVdijet "<< SLogger::endmsg; 
    
    TString infile = TString(this->GetHistInputFile()->GetName());
    setWeight(infile);
    //PrintPdgIDs(data_);
    double cos_theta1 = CalculateCOSTheta1(data_, 1);
    Hist("gen_COS_Theta1")->Fill(cos_theta1);
    
    
    if(isHadronicEvent(data_))
    {
        double M_graviton = getGravitonGenMass(data_);
        Hist("Mjj_allHadGen")->Fill(M_graviton,weight_ );
    }
    
//     if(wmax_     <= weight_){ wmax_ = weight_;}
//     if(wmaxpu_   <= puweight_  ){wmaxpu_   = puweight_  ;}
//     if(wmaxlumi_ <= lumiweight_){wmaxlumi_ = lumiweight_;}
//     if(wmaxpt_   <= ptweight_  ){wmaxpt_   = ptweight_  ;}
//     if(wmaxhlt_  <= hltweight_ ){wmaxhlt_  = hltweight_ ;}
//     if(wmaxbtag_ <= btagweight_){wmaxbtag_ = btagweight_;}
//     if(wmaxgen_  <= genweight_ ){wmaxgen_  = genweight_ ;}
    
    
  
    
    // int gW = data_.genWeight < 0 ? -1 : 1;  //Does not work for pt flat samples!
    float gW = data_.genWeight;
    nSumGenWeights_ += gW;

    if( isSignal_ and !selectChannel() ) throw SError( SError::SkipEvent );
    
    Hist( "runNumber" )->Fill(data_.EVENT_run);
    
    if( isSignal_ && runOnMC_ && GenStudies_){
      TLorentzVector genP;
      std::vector<TLorentzVector> daus;
      std::vector<TLorentzVector> myJets;
      
      for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
        if( (*data_.genParticle_pt).at(p) < 0.1) continue;
        bool isDaughter = false;
        for( unsigned int d = 0; d < (*data_.genParticle_mother)[p].size(); ++d ) {
          if(Channel_ == "qVdijet" && fabs((*data_.genParticle_mother)[p][d]) != 4000002 and fabs((*data_.genParticle_mother)[p][d]) != 4000001  ) continue;
          if(Channel_ == "VVdijet" && fabs((*data_.genParticle_mother)[p][d]) != 32 and fabs((*data_.genParticle_mother)[p][d]) != 34 and fabs((*data_.genParticle_mother)[p][d]) != 39 and fabs((*data_.genParticle_mother)[p][d]) != 9000001 and fabs((*data_.genParticle_mother)[p][d]) != 9000002) continue;
          isDaughter = true ;
        }
        if(!isDaughter) continue;
        genP.SetPtEtaPhiE( (*data_.genParticle_pt).at(p), (*data_.genParticle_eta).at(p), (*data_.genParticle_phi).at(p), (*data_.genParticle_e).at(p) );
        daus.push_back(genP);
      }
      for( int j = 0; j < data_.njetsAK8 ; ++j ){
        TLorentzVector myJet;
        if( (*data_.jetAK8_pt).at(j) <= 200.      )continue;
        if( fabs((*data_.jetAK8_eta).at(j)) >= 2.4)continue;
        if( (*data_.jetAK8_IDTight).at(j) != 1    )continue;
        myJet.SetPtEtaPhiE( (*data_.jetAK8_pt).at(j), (*data_.jetAK8_eta).at(j), (*data_.jetAK8_phi).at(j), (*data_.jetAK8_e).at(j) );
        for( unsigned int p = 0; p < daus.size(); ++p ){
          float dR = daus.at(p).DeltaR(myJet);
          if (dR > 0.8 ) continue;
          myJets.push_back(myJet);
        }
      }
      if (myJets.size() > 1) Hist( "Mjj_genMatched" ) -> Fill( ( myJets.at(0) + myJets.at(1) ).M() );	
    }

    nEvents_++;
    if( !applyJSON() ) throw SError( SError::SkipEvent );  
    nPassedJSON_++;

    if( !passedTrigger() ) throw SError( SError::SkipEvent );
    nPassedTrigger_++;
    
    if( !passedFilters( infile ) ) throw SError( SError::SkipEvent );
    nPassedFilters_++; 
    
    preparationOfHistosForPUreweighting();

    if( Channel_ == "VVdijet"){
      if(GenStudies_){
           //std::cout << "doWTagEfficiency"<<std::endl;
          doWTagEfficiency( infile );
        if( isSignal_ ) { doSubstructureStudies( infile ); }
      }
    }

    // // If doing Wtag efficiency plots with data
  //   if(data_.njetsAK8 > 1) {
  //     TLorentzVector myJet1;
  //     TLorentzVector myJet2;
  //     myJet1.SetPtEtaPhiE( (*data_.jetAK8_pt).at(0), (*data_.jetAK8_eta).at(0), (*data_.jetAK8_phi).at(0), (*data_.jetAK8_e).at(0) );
  //     myJet2.SetPtEtaPhiE( (*data_.jetAK8_pt).at(1), (*data_.jetAK8_eta).at(1), (*data_.jetAK8_phi).at(1), (*data_.jetAK8_e).at(1) );
  //     float Mjj = (myJet1 + myJet2).M();
  //     if(Mjj > 1200. && (*data_.jetAK8_pt).at(0) > 200 && (*data_.jetAK8_pt).at(1) > 200 && fabs(myJet1.Eta()  - myJet2.Eta())<=1.3 ) doWTagEfficiency( infile );
  //   }


    if( passedDijetSelections(infile) ) {
      int jetINDX1 = -99;
      int jetINDX2 = -99;

      Hist( "Mjj_final" ) -> Fill( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() , weight_ );

      bool passedTau21Cut        = false;

      float groomedMass_jet1 = Vcand.at(0).prunedMass;
      float groomedMass_jet2 = Vcand.at(1).prunedMass;

      float nsub_jet1 = Vcand.at(0).tau2/Vcand.at(0).tau1;
      float nsub_jet2 = Vcand.at(1).tau2/Vcand.at(1).tau1;

      if( usePuppiSD_ ){
         groomedMass_jet1 = Vcand.at(0).puppi_softdropMass;
         groomedMass_jet2 = Vcand.at(1).puppi_softdropMass;

         nsub_jet1 = Vcand.at(0).puppi_tau2/Vcand.at(0).puppi_tau1;
         nsub_jet2 = Vcand.at(1).puppi_tau2/Vcand.at(1).puppi_tau1;
      }
      if( Channel_ == "VVdijet"){
        channel = -1;

    

        
        if ( nsub_jet1 > Tau21HPLow_ && nsub_jet1 <= Tau21HPHigh_ && nsub_jet2 > Tau21HPLow_ && nsub_jet2 <= Tau21HPHigh_  ){
          // std::cout<<"Passed Tau21? jet 1 tau21 = " << nsub_jet1 << "  jet 2 tau21 = " << nsub_jet2 << std::endl;
          passedTau21Cut = true ;

          if( (groomedMass_jet1 > mWLow_ && groomedMass_jet1 <= mZHigh_ && groomedMass_jet2 > mWLow_ && groomedMass_jet2 <= mZHigh_) ){
            nPassedTau21Cut_ ++;
             calcPDFweight(0);
            m_logger << DEBUG << "puppi+softdrop mass VV window : "<< groomedMass_jet1 << " " << groomedMass_jet2 << SLogger::endmsg;
            category = 0; //VVHP
                 if( (groomedMass_jet1 > mWLow_ && groomedMass_jet1 <= mWHigh_) && (groomedMass_jet2 > mWLow_   && groomedMass_jet2 <= mWHigh_)){ channel = 2;} //WWHP
            else if( (groomedMass_jet1 > mWLow_ && groomedMass_jet1 <= mWHigh_) && (groomedMass_jet2 > mZLow_   && groomedMass_jet2 <= mZHigh_))  channel = 4; //WZHP
            else if( (groomedMass_jet2 > mWLow_ && groomedMass_jet2 <= mWHigh_) && (groomedMass_jet1 > mZLow_   && groomedMass_jet1 <= mZHigh_))  channel = 4; //ZWHP
            else if( (groomedMass_jet1 > mZLow_ && groomedMass_jet1 <= mZHigh_) && (groomedMass_jet2 > mZLow_   && groomedMass_jet2 <= mZHigh_))  channel = 6; //ZZHP
          }
        }

        //LP category
        else if( ( nsub_jet1 > Tau21HPLow_ && nsub_jet1 <= Tau21HPHigh_ && nsub_jet2 > Tau21Low_ && nsub_jet2 <= Tau21High_  ) ||
                  (nsub_jet2 > Tau21HPLow_ && nsub_jet2 <= Tau21HPHigh_ && nsub_jet1 > Tau21Low_ && nsub_jet1 <= Tau21High_) ) {

          if( (groomedMass_jet1 > mWLow_ && groomedMass_jet1 <= mZHigh_) && (groomedMass_jet2 > mWLow_   && groomedMass_jet2 <= mZHigh_))  {
            category = 1;  //VVLP

            if(      (groomedMass_jet1 > mWLow_ && groomedMass_jet1 <= mWHigh_) && (groomedMass_jet2 > mWLow_   && groomedMass_jet2 <= mWHigh_))  channel = 3; //WWLP
            else if( (groomedMass_jet1 > mWLow_ && groomedMass_jet1 <= mWHigh_) && (groomedMass_jet2 > mZLow_   && groomedMass_jet2 <= mZHigh_))  channel = 5; //WZLP
            else if( (groomedMass_jet2 > mWLow_ && groomedMass_jet2 <= mWHigh_) && (groomedMass_jet1 > mZLow_   && groomedMass_jet1 <= mZHigh_))  channel = 5; //ZWLP
            else if( (groomedMass_jet1 > mZLow_ && groomedMass_jet1 <= mZHigh_) && (groomedMass_jet2 > mZLow_   && groomedMass_jet2 <= mZHigh_))  channel = 7; //ZZLP
          }
        }
        // NP category
        else{
          if( (groomedMass_jet1 > mWLow_ && groomedMass_jet1 <= mZHigh_) && (groomedMass_jet2 > mWLow_   && groomedMass_jet2 <= mZHigh_))  {
            category = 4;  //VVNP

                 if( groomedMass_jet1 > mWLow_ && groomedMass_jet1 <= mWHigh_ && groomedMass_jet2 > mWLow_   && groomedMass_jet2 <= mWHigh_)  channel = 14; //WWNP
            else if( groomedMass_jet1 > mWLow_ && groomedMass_jet1 <= mWHigh_ && groomedMass_jet2 > mZLow_   && groomedMass_jet2 <= mZHigh_)  channel = 15; //WZNP
            else if( groomedMass_jet2 > mWLow_ && groomedMass_jet2 <= mWHigh_ && groomedMass_jet1 > mZLow_   && groomedMass_jet1 <= mZHigh_)  channel = 15; //ZWNP
            else if( groomedMass_jet1 > mZLow_ && groomedMass_jet1 <= mZHigh_ && groomedMass_jet2 > mZLow_   && groomedMass_jet2 <= mZHigh_)  channel = 16; //ZZNP
          }
        }
      }

      else if( Channel_ == "qVdijet"){
        channel = -1;
        for( int i = 0; i < abs(Vcand.size()) ; i++){

          float groomedMass_jet1 = Vcand.at(i).prunedMass;
          float nsub_jet1 = Vcand.at(i).tau2/Vcand.at(i).tau1;


          if( usePuppiSD_ ){
             groomedMass_jet1 = Vcand.at(i).puppi_softdropMass;
             nsub_jet1 = Vcand.at(i).puppi_tau2/Vcand.at(i).puppi_tau1;
          }

          if(! (groomedMass_jet1 > mWLow_ && groomedMass_jet1 <= mZHigh_)) continue;
          //HP
          if( nsub_jet1 > Tau21HPLow_ && nsub_jet1 <= Tau21HPHigh_ ){
            passedTau21Cut = true;
            nPassedTau21Cut_ ++;
            calcPDFweight(0);
            category = 2; //qVHP
            jetINDX1=i;
            if (groomedMass_jet1 > mWLow_ && groomedMass_jet1 <= mWHigh_) {
              channel = 10; //qWHP
            }
            else if (groomedMass_jet1 > mZLow_ && groomedMass_jet1 <= mZHigh_) {
              channel = 12; //qZHP
            }
          }
          //LP
          else if( nsub_jet1 > Tau21Low_ && nsub_jet1 <= Tau21High_ ){
            if( !(groomedMass_jet1 > mWLow_ && groomedMass_jet1 <= mZHigh_) ) continue;
            category = 3; //qVLP
            jetINDX1=i;
            if (groomedMass_jet1 > mWLow_ && groomedMass_jet1 <= mWHigh_) {
              channel = 11; //qWLP
            }
            else if (groomedMass_jet1 > mZLow_ && groomedMass_jet1 <= mZHigh_) {
              channel = 13; //qZLP
          }
        }
          else{
            if(! (groomedMass_jet1 > mWLow_ && groomedMass_jet1 <= mZHigh_))continue;
            category = 5; //qVNP
            jetINDX1=i;
            if (groomedMass_jet1 > mWLow_ && groomedMass_jet1 <= mWHigh_) channel = 17; //qWNP
            else if (groomedMass_jet1 > mZLow_ && groomedMass_jet1 <= mZHigh_) channel = 18; //qZNP
          }
        }
      }
      if( Channel_ == "qVdijet"){
        if(jetINDX1 == 0) jetINDX2 = 1;
        else if (jetINDX1 == 1) jetINDX2 = 0;
      }
      else if( Channel_ == "VVdijet"){
        jetINDX1 = 0;
        jetINDX2 = 1;
      }

      weight = weight_;
      run = data_.EVENT_run;
      event = data_.EVENT_event;
      lumi = data_.EVENT_lumi;
      MVV = (Vcand.at(jetINDX1).p4 + Vcand.at(jetINDX2).p4).M();
      MVV_reduced = ( Vcand.at(jetINDX1).p4 + Vcand.at(jetINDX2).p4 ).M() - ( Vcand.at(jetINDX1).p4.M()-pdgMw ) - ( Vcand.at(jetINDX2).p4.M()-pdgMw );
      jet_deta = fabs( Vcand.at(jetINDX1).p4.Eta()  - Vcand.at(jetINDX2).p4.Eta());
      jet_mass_jet1 = Vcand.at(jetINDX1).p4.M();
      jet_mass_softdrop_jet1 = Vcand.at(jetINDX1).softdropMass;
      jet_mass_pruned_jet1 = Vcand.at(jetINDX1).prunedMass;
      jet_pt_jet1 = Vcand.at(jetINDX1).p4.Pt();
      jet_eta_jet1 = Vcand.at(jetINDX1).p4.Eta();
      jet_phi_jet1 = Vcand.at(jetINDX1).p4.Phi();
      jet_tau2tau1_jet1 = Vcand.at(jetINDX1).tau2/Vcand.at(jetINDX1).tau1;
      jet_mass_jet2 = Vcand.at(jetINDX2).p4.M();
      jet_mass_softdrop_jet2 = Vcand.at(jetINDX2).softdropMass;
      jet_mass_pruned_jet2 = Vcand.at(jetINDX2).prunedMass;
      jet_pt_jet2 = Vcand.at(jetINDX2).p4.Pt();
      jet_eta_jet2 = Vcand.at(jetINDX2).p4.Eta();
      jet_phi_jet2 = Vcand.at(jetINDX2).p4.Phi();
      jet_tau2tau1_jet2 = Vcand.at(jetINDX2).tau2/Vcand.at(jetINDX2).tau1;
      nPVs = data_.nPVs;

      jet1_puppi_softdrop = Vcand.at(jetINDX1).puppi_softdropMass;
      jet1_puppi_tau1 = Vcand.at(jetINDX1).puppi_tau1;
      jet1_puppi_tau2 = Vcand.at(jetINDX1).puppi_tau2;
      jet1_puppi_tau3 = Vcand.at(jetINDX1).puppi_tau3;
      jet1_puppi_pt   = Vcand.at(jetINDX1).puppi_pt;
      jet2_puppi_softdrop = Vcand.at(jetINDX2).puppi_softdropMass;
      jet2_puppi_tau1 = Vcand.at(jetINDX2).puppi_tau1;
      jet2_puppi_tau2 = Vcand.at(jetINDX2).puppi_tau2;
      jet2_puppi_tau3 = Vcand.at(jetINDX2).puppi_tau3;
      jet2_puppi_pt   = Vcand.at(jetINDX2).puppi_pt;
      jet_puppi_tau2tau1_jet1 = Vcand.at(jetINDX1).puppi_tau2/Vcand.at(jetINDX1).puppi_tau1;
      jet_puppi_tau2tau1_jet2 = Vcand.at(jetINDX2).puppi_tau2/Vcand.at(jetINDX2).puppi_tau1;

      float DDT_jet1 = Vcand.at(jetINDX1).puppi_tau2/Vcand.at(jetINDX1).puppi_tau1 + ( 0.063 * log( (Vcand.at(jetINDX1).puppi_softdropMass*Vcand.at(jetINDX1).puppi_softdropMass)/Vcand.at(jetINDX1).puppi_pt) );
      float DDT_jet2 = Vcand.at(jetINDX2).puppi_tau2/Vcand.at(jetINDX2).puppi_tau1 + ( 0.063 * log( (Vcand.at(jetINDX2).puppi_softdropMass*Vcand.at(jetINDX2).puppi_softdropMass)/Vcand.at(jetINDX2).puppi_pt) );

      jet_ddt_jet1 = DDT_jet1;
      jet_ddt_jet2 = DDT_jet2;
                       ;
    jet1_rcn       = Vcand.at(jetINDX1).rcn      ;
    jet1_cm        = Vcand.at(jetINDX1).cm       ;
    jet1_nm        = Vcand.at(jetINDX1).nm       ;
    jet1_muf       = Vcand.at(jetINDX1).muf      ;
    jet1_phf       = Vcand.at(jetINDX1).phf      ;
    jet1_emf       = Vcand.at(jetINDX1).emf      ;
    jet1_nhf       = Vcand.at(jetINDX1).nhf      ;
    jet1_chf       = Vcand.at(jetINDX1).chf      ;
    jet1_che       = Vcand.at(jetINDX1).che      ;
    jet1_ne        = Vcand.at(jetINDX1).ne       ;
    jet1_hf_hf     = Vcand.at(jetINDX1).hf_hf    ;
    jet1_hf_emf    = Vcand.at(jetINDX1).hf_emf   ;
    jet1_hof       = Vcand.at(jetINDX1).hof      ;
    jet1_chm       = Vcand.at(jetINDX1).chm      ;
    jet1_neHadMult = Vcand.at(jetINDX1).neHadMult;
    jet1_phoMult   = Vcand.at(jetINDX1).phoMult  ;
    jet1_nemf      = Vcand.at(jetINDX1).nemf     ;
    jet1_cemf      = Vcand.at(jetINDX1).cemf     ;
    jet1_charge    = Vcand.at(jetINDX1).charge   ;
    jet1_area      = Vcand.at(jetINDX1).area     ;
    
    jet2_rcn       = Vcand.at(jetINDX2).rcn      ;
    jet2_cm        = Vcand.at(jetINDX2).cm       ;
    jet2_nm        = Vcand.at(jetINDX2).nm       ;
    jet2_muf       = Vcand.at(jetINDX2).muf      ;
    jet2_phf       = Vcand.at(jetINDX2).phf      ;
    jet2_emf       = Vcand.at(jetINDX2).emf      ;
    jet2_nhf       = Vcand.at(jetINDX2).nhf      ;
    jet2_chf       = Vcand.at(jetINDX2).chf      ;
    jet2_che       = Vcand.at(jetINDX2).che      ;
    jet2_ne        = Vcand.at(jetINDX2).ne       ;
    jet2_hf_hf     = Vcand.at(jetINDX2).hf_hf    ;
    jet2_hf_emf    = Vcand.at(jetINDX2).hf_emf   ;
    jet2_hof       = Vcand.at(jetINDX2).hof      ;
    jet2_chm       = Vcand.at(jetINDX2).chm      ;
    jet2_neHadMult = Vcand.at(jetINDX2).neHadMult;
    jet2_phoMult   = Vcand.at(jetINDX2).phoMult  ;
    jet2_nemf      = Vcand.at(jetINDX2).nemf     ;
    jet2_cemf      = Vcand.at(jetINDX2).cemf     ;
    jet2_charge    = Vcand.at(jetINDX2).charge   ;
    jet2_area      = Vcand.at(jetINDX2).area     ;
    
    
    
    

      fillHistos(Channel_);

    }

    else
      throw SError( SError::SkipEvent );
  }
   else if(Channel_.find("Sideband")!=std::string::npos)
  {
         
    TString infile = TString(this->GetHistInputFile()->GetName());
    setWeight(infile);
    
    // int gW = data_.genWeight < 0 ? -1 : 1;  //Does not work for pt flat samples!
    float gW = data_.genWeight;
    nSumGenWeights_ += gW;
    //std::cout<< " finds channel "<<std::endl;

    if( isSignal_ and !selectChannel() ) throw SError( SError::SkipEvent );
    
    //std::cout << " whatever  " << std::endl;
    Hist( "runNumber" )->Fill(data_.EVENT_run);
    

    nEvents_++;
    if( !applyJSON() ) throw SError( SError::SkipEvent );  
    nPassedJSON_++;

    if( !passedTrigger() ) throw SError( SError::SkipEvent );
    nPassedTrigger_++;
    
    if( !passedFilters( infile ) ) throw SError( SError::SkipEvent );
    nPassedFilters_++; 

    //std::cout << " passed filters triggers json " << std::endl;
    if(! passedDijetSelections(infile) ) throw SError(SError::SkipEvent);
    nPassedJetsDEta_+=1;
    //std::cout<< " passed dijet selection " << std::endl;
    std::string cat = "NP";
    if(Channel_.find("HP")!=std::string::npos)
        cat = "HP";
    if(Channel_.find("LP")!=std::string::npos)
        cat = "LP";
      if(!passedTau21Selections(cat)) throw SError(SError::SkipEvent);
      nPassedTau21Cut_+=1;
      
      //std::cout << " events pass my selections " << std::endl;
      int jetINDX1 =0;
      int jetINDX2 =1;
      weight = weight_;
      run = data_.EVENT_run;
      event = data_.EVENT_event;
      lumi = data_.EVENT_lumi;
      MVV = (Vcand.at(jetINDX1).p4 + Vcand.at(jetINDX2).p4).M();
      MVV_reduced = ( Vcand.at(jetINDX1).p4 + Vcand.at(jetINDX2).p4 ).M() - ( Vcand.at(jetINDX1).p4.M()-pdgMw ) - ( Vcand.at(jetINDX2).p4.M()-pdgMw );
      jet_deta = fabs( Vcand.at(jetINDX1).p4.Eta()  - Vcand.at(jetINDX2).p4.Eta());
      jet_mass_jet1 = Vcand.at(jetINDX1).p4.M();
      jet_mass_softdrop_jet1 = Vcand.at(jetINDX1).softdropMass;
      jet_mass_pruned_jet1 = Vcand.at(jetINDX1).prunedMass;
      jet_pt_jet1 = Vcand.at(jetINDX1).p4.Pt();
      jet_eta_jet1 = Vcand.at(jetINDX1).p4.Eta();
      jet_phi_jet1 = Vcand.at(jetINDX1).p4.Phi();
      jet_tau2tau1_jet1 = Vcand.at(jetINDX1).tau2/Vcand.at(jetINDX1).tau1;
      jet_mass_jet2 = Vcand.at(jetINDX2).p4.M();
      jet_mass_softdrop_jet2 = Vcand.at(jetINDX2).softdropMass;
      jet_mass_pruned_jet2 = Vcand.at(jetINDX2).prunedMass;
      jet_pt_jet2 = Vcand.at(jetINDX2).p4.Pt();
      jet_eta_jet2 = Vcand.at(jetINDX2).p4.Eta();
      jet_phi_jet2 = Vcand.at(jetINDX2).p4.Phi();
      jet_tau2tau1_jet2 = Vcand.at(jetINDX2).tau2/Vcand.at(jetINDX2).tau1;
      nPVs = data_.nPVs;

      jet1_puppi_softdrop = Vcand.at(jetINDX1).puppi_softdropMass;
      jet1_puppi_tau1 = Vcand.at(jetINDX1).puppi_tau1;
      jet1_puppi_tau2 = Vcand.at(jetINDX1).puppi_tau2;
      jet1_puppi_tau3 = Vcand.at(jetINDX1).puppi_tau3;
      jet1_puppi_pt   = Vcand.at(jetINDX1).puppi_pt;
      jet2_puppi_softdrop = Vcand.at(jetINDX2).puppi_softdropMass;
      jet2_puppi_tau1 = Vcand.at(jetINDX2).puppi_tau1;
      jet2_puppi_tau2 = Vcand.at(jetINDX2).puppi_tau2;
      jet2_puppi_tau3 = Vcand.at(jetINDX2).puppi_tau3;
      jet2_puppi_pt   = Vcand.at(jetINDX2).puppi_pt;
      jet_puppi_tau2tau1_jet1 = Vcand.at(jetINDX1).puppi_tau2/Vcand.at(jetINDX1).puppi_tau1;
      jet_puppi_tau2tau1_jet2 = Vcand.at(jetINDX2).puppi_tau2/Vcand.at(jetINDX2).puppi_tau1;

      float DDT_jet1 = Vcand.at(jetINDX1).puppi_tau2/Vcand.at(jetINDX1).puppi_tau1 + ( 0.063 * log( (Vcand.at(jetINDX1).puppi_softdropMass*Vcand.at(jetINDX1).puppi_softdropMass)/Vcand.at(jetINDX1).puppi_pt) );
      float DDT_jet2 = Vcand.at(jetINDX2).puppi_tau2/Vcand.at(jetINDX2).puppi_tau1 + ( 0.063 * log( (Vcand.at(jetINDX2).puppi_softdropMass*Vcand.at(jetINDX2).puppi_softdropMass)/Vcand.at(jetINDX2).puppi_pt) );

      jet_ddt_jet1 = DDT_jet1;
      jet_ddt_jet2 = DDT_jet2;
                       ;
    jet1_rcn       = Vcand.at(jetINDX1).rcn      ;
    jet1_cm        = Vcand.at(jetINDX1).cm       ;
    jet1_nm        = Vcand.at(jetINDX1).nm       ;
    jet1_muf       = Vcand.at(jetINDX1).muf      ;
    jet1_phf       = Vcand.at(jetINDX1).phf      ;
    jet1_emf       = Vcand.at(jetINDX1).emf      ;
    jet1_nhf       = Vcand.at(jetINDX1).nhf      ;
    jet1_chf       = Vcand.at(jetINDX1).chf      ;
    jet1_che       = Vcand.at(jetINDX1).che      ;
    jet1_ne        = Vcand.at(jetINDX1).ne       ;
    jet1_hf_hf     = Vcand.at(jetINDX1).hf_hf    ;
    jet1_hf_emf    = Vcand.at(jetINDX1).hf_emf   ;
    jet1_hof       = Vcand.at(jetINDX1).hof      ;
    jet1_chm       = Vcand.at(jetINDX1).chm      ;
    jet1_neHadMult = Vcand.at(jetINDX1).neHadMult;
    jet1_phoMult   = Vcand.at(jetINDX1).phoMult  ;
    jet1_nemf      = Vcand.at(jetINDX1).nemf     ;
    jet1_cemf      = Vcand.at(jetINDX1).cemf     ;
    jet1_charge    = Vcand.at(jetINDX1).charge   ;
    jet1_area      = Vcand.at(jetINDX1).area     ;
    
    jet2_rcn       = Vcand.at(jetINDX2).rcn      ;
    jet2_cm        = Vcand.at(jetINDX2).cm       ;
    jet2_nm        = Vcand.at(jetINDX2).nm       ;
    jet2_muf       = Vcand.at(jetINDX2).muf      ;
    jet2_phf       = Vcand.at(jetINDX2).phf      ;
    jet2_emf       = Vcand.at(jetINDX2).emf      ;
    jet2_nhf       = Vcand.at(jetINDX2).nhf      ;
    jet2_chf       = Vcand.at(jetINDX2).chf      ;
    jet2_che       = Vcand.at(jetINDX2).che      ;
    jet2_ne        = Vcand.at(jetINDX2).ne       ;
    jet2_hf_hf     = Vcand.at(jetINDX2).hf_hf    ;
    jet2_hf_emf    = Vcand.at(jetINDX2).hf_emf   ;
    jet2_hof       = Vcand.at(jetINDX2).hof      ;
    jet2_chm       = Vcand.at(jetINDX2).chm      ;
    jet2_neHadMult = Vcand.at(jetINDX2).neHadMult;
    jet2_phoMult   = Vcand.at(jetINDX2).phoMult  ;
    jet2_nemf      = Vcand.at(jetINDX2).nemf     ;
    jet2_cemf      = Vcand.at(jetINDX2).cemf     ;
    jet2_charge    = Vcand.at(jetINDX2).charge   ;
    jet2_area      = Vcand.at(jetINDX2).area     ;
  
       fillHistos(Channel_);
      
  }
  
  else if( Channel_ == "SFmuJets"){
    
    TString infile = TString(this->GetHistInputFile()->GetName());
    setWeight(infile);
    //Hist( "runNumber" )->Fill(data_.EVENT_run);
  
    nEvents_++;
    if( !passedTrigger() ) throw SError( SError::SkipEvent );
    nPassedTrigger_++;
        
    if( !passedFilters( infile ) ) throw SError( SError::SkipEvent );
    nPassedFilters_++;
    
    Hist( "nVertices" )->Fill(data_.nPVs, weight_);
    if( !passedTTbarSelections( infile ) ) return;
    if(GenStudies_){
      doGenTTReco();
    }

    // findWCandidate();
    TLorentzVector p4nu          = getp4Nu();
    // TLorentzVector p4nuMethod2   = getp4NuMethod2();

    Double_t deltaTmassMin = 999.;
    float chi2Min = 999999.;
    float Tmass = 0;
    float Wmass = 0;

    //Reconstruct hadronic top
    for(int i=0; i < 4; i++ ){
      // Hadronicb_.push_back(AK4jetCand_.at(i));
      for(int j=0; j < 4; j++ ){
        if( i==j) continue;
        float deltaWmass = ((AK4jetCand_.at(i).p4 + AK4jetCand_.at(j).p4).M())-pdgMw;
        for(int k=0; k < 4; k++ ){
          // Hadronicb_.push_back(AK4jetCand_.at(k));
          if( i==j || i==k || j==k) continue;
          float deltaTmass = ((AK4jetCand_.at(i).p4 + AK4jetCand_.at(j).p4 + AK4jetCand_.at(k).p4).M())-pdgMtop;

          float chi2 = pow((deltaTmass/pdgWidthtop),2)+pow((deltaWmass/pdgWidthw),2);
          if(chi2 > chi2Min ) continue;
          Hadronicb_.clear();
          chi2Min = chi2;
          Tmass = (AK4jetCand_.at(i).p4 + AK4jetCand_.at(j).p4 + AK4jetCand_.at(k).p4).M();
          Wmass = (AK4jetCand_.at(i).p4 + AK4jetCand_.at(j).p4).M();
          Hadronicb_.push_back(AK4jetCand_.at(i));
          Hadronicb_.push_back(AK4jetCand_.at(j));
          Hadronicb_.push_back(AK4jetCand_.at(k));
        }
      }
    }

    Hist( "tmass"             )->Fill ( Tmass, weight_ );
    Hist( "wmass"             )->Fill ( Wmass, weight_ );
    Hist( "Chi2"              )->Fill ( chi2Min, weight_ );
    Hist( "Chi2vsTMass"        )->Fill ( chi2Min,Tmass);
    Hist( "Chi2vsWMass"        )->Fill ( chi2Min,Wmass);

    if( chi2Min > 100. ) throw SError( SError::SkipEvent );
    nPassedChi2_++;
    fillHistos(Channel_);

    //Reconstruct leptonic top
    for(int i=0; i < 4; i++ ){
      if (AK4jetCand_.at(i).p4.Pt() == Hadronicb_.at(0).p4.Pt() || AK4jetCand_.at(i).p4.Pt() == Hadronicb_.at(1).p4.Pt()  || AK4jetCand_.at(i).p4.Pt() == Hadronicb_.at(2).p4.Pt()) continue;
      Leptonicb_.push_back(AK4jetCand_.at(i));
    }

    Double_t mlj = (leptonCand_.at(0).p4 + Leptonicb_.at(0).p4).M();
    Double_t TmassHad    = (Hadronicb_.at(0).p4 + Hadronicb_.at(1).p4 + Hadronicb_.at(2).p4).M();
    Double_t WmassHad    = (Hadronicb_.at(0).p4 + Hadronicb_.at(1).p4).M();
    Double_t TmassLep    = (p4nu + leptonCand_.at(0).p4 + Leptonicb_.at(0).p4).M();
    Double_t WmassLep    = TMath::Sqrt( 2*METCand_.at(0).p4.Pt()*leptonCand_.at(0).p4.Pt()*(1-cos(leptonCand_.at(0).p4.DeltaPhi(METCand_.at(0).p4))));

    Hist( "Mlj" )->Fill ( mlj, weight_  );

    if(runOnMC_){
      Hist( "LeptonicbFlavor" )->Fill ( Leptonicb_.at(0).flavor, weight_);
      Hist( "HadronicbFlavor" )->Fill ( Hadronicb_.at(2).flavor, weight_);
      Hist( "Chi2vsbCandFlav" )->Fill ( chi2Min,abs(Leptonicb_.at(0).flavor));

      if( fabs(Leptonicb_.at(0).flavor)==5 ) {
        Hist( "MljbEnriched")->Fill ( mlj, weight_);
        if( mlj > 40 && mlj < 170) Hist( "CSV_enriched_trueB")->Fill( Leptonicb_.at(0).csv, weight_    );
        if(TmassLep > 140 && TmassLep < 210) Hist( "Method2_CSV_enriched_trueB")->Fill( Leptonicb_.at(0).csv, weight_);
        Hist( "LeptonicbCSV_B")   ->Fill ( Leptonicb_.at(0).csv, weight_    );
        Hist( "LeptonicbFlavor_B")->Fill ( Leptonicb_.at(0).flavor, weight_    );
        Hist( "LeptonicTopMass_B")->Fill ( TmassLep, weight_    );
      }
      else
      if( fabs(Leptonicb_.at(0).flavor)!=5 ) {
        if( mlj > 40 && mlj < 170) Hist( "CSV_enriched_nonB")->Fill( Leptonicb_.at(0).csv, weight_    );
        if(TmassLep > 140 && TmassLep < 210) Hist( "Method2_CSV_enriched_nonB")->Fill( Leptonicb_.at(0).csv, weight_);
        Hist( "MljbDepleted")->Fill ( mlj, weight_  );
        Hist( "LeptonicbCSV_nonB" )->Fill ( Leptonicb_.at(0).csv, weight_    );
        Hist( "LeptonicbFlavor_nonB" )->Fill ( Leptonicb_.at(0).flavor, weight_    );
        Hist( "LeptonicTopMass_nonB" )->Fill ( TmassLep, weight_    );
      }
    }

    if(mlj > 40 && mlj < 170)  Hist( "CSV_enriched")->Fill( Leptonicb_.at(0).csv, weight_    );
    if(mlj > 170 && mlj < 300) Hist( "CSV_depleted")->Fill( Leptonicb_.at(0).csv, weight_    );
    if(TmassLep > 140 && TmassLep < 210) Hist( "Method2_CSV_enriched")->Fill( Leptonicb_.at(0).csv, weight_);
    if(TmassLep > 260 && TmassLep < 400) Hist( "Method2_CSV_depleted")->Fill( Leptonicb_.at(0).csv, weight_);

    Hist( "LeptonicbCSV" )->Fill ( Leptonicb_.at(0).csv, weight_);
    Hist( "HadronicbCSV" )->Fill ( Hadronicb_.at(2).csv, weight_);
    Hist( "HadronicTopMass" )->Fill ( TmassHad, weight_);
    Hist( "HadronicWMass" )->Fill ( WmassHad , weight_);
    Hist( "LeptonicWMass" )->Fill ( WmassLep , weight_);
    Hist( "LeptonicTopMass" )->Fill ( TmassLep, weight_);
  }
   
  else if( Channel_.find("WtagSF") != std::string::npos ){

    int gW = data_.genWeight < 0 ? -1 : 1;
    nSumGenWeights_+=gW;
    
    isLowMass = false;
    if (leptPtCut_ < 50) isLowMass = true ; 
    TString infile = TString(this->GetHistInputFile()->GetName());
    setWeight(infile);
    
    Hist( "runNumber" )->Fill(data_.EVENT_run);
    nEvents_++;
    
    if( !applyJSON() ) throw SError( SError::SkipEvent );
    nPassedJSON_++;
    
    
    if( !passedTrigger() ) throw SError( SError::SkipEvent );
    nPassedTrigger_++;

    if( !passedFilters( infile ) ) throw SError( SError::SkipEvent );
    nPassedFilters_++;
    if( passedTTbarSelections( infile) ){
      
      
      int isW_def1 = 0;
      int isW_def2 = 0;
      
      if( runOnMC_ ){
        TLorentzVector genP; 
        std::vector<TLorentzVector> daus;    
        TLorentzVector hadW; 

        for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
          bool isHad = false;
          if( (*data_.genParticle_pt).at(p) < 0.1) continue;
          if( fabs((*data_.genParticle_pdgId).at(p)) > 9) continue; 
          for( unsigned int d = 0; d < (*data_.genParticle_mother)[p].size(); ++d ) {
            if( fabs((*data_.genParticle_mother)[p][d]) != 24 ) continue;
            isHad = true;
          }
          if (!isHad) continue; 
          genP.SetPtEtaPhiE( (*data_.genParticle_pt).at(p), (*data_.genParticle_eta).at(p), (*data_.genParticle_phi).at(p), (*data_.genParticle_e).at(p) );
          daus.push_back(genP);
        }
        if( daus.size() > 1){  
             
          for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
            bool isHad = false;
            if( (*data_.genParticle_pt).at(p) < 0.1) continue;
            if( fabs((*data_.genParticle_pdgId).at(p)) != 24) continue;
            // if( not infile.Contains( "herwig" ) && (*data_.genParticle_status).at(p) != 4 && (*data_.genParticle_status).at(p) != 22 && (*data_.genParticle_status).at(p) != 23) continue;
            // if( infile.Contains( "herwig" ) && (*data_.genParticle_status).at(p) != 11 ) continue;
            if ((*data_.genParticle_dau)[p].size() < 2) continue;
            for( unsigned int d = 0; d < (*data_.genParticle_dau)[p].size(); ++d ) {
              if( fabs((*data_.genParticle_dau)[p][d]) > 9) continue;
              isHad = true;
            }
            if (isHad){
              hadW.SetPtEtaPhiE( (*data_.genParticle_pt).at(p), (*data_.genParticle_eta).at(p), (*data_.genParticle_phi).at(p), (*data_.genParticle_e).at(p) );
            }
          }
      
          int isMatch = 0;
          for( unsigned int p = 0; p < daus.size(); ++p ){
            float dR = daus.at(p).DeltaR(Vcand.at(0).p4);
            if (dR < 0.8 ) isMatch +=1;
          }
          if (isMatch > 1) isW_def1 = 1;
          if( (Vcand.at(0).p4).DeltaR(hadW) < 0.4  && daus.at(0).DeltaR(daus.at(1)) < 0.8 ) isW_def2 = 1;
        }
      }
    
      realW_def1 = isW_def1; 
      realW_def2 = isW_def2;   
      weight = weight_;
      run = data_.EVENT_run;
      event = data_.EVENT_event;
      lumi = data_.EVENT_lumi;
      nPVs = data_.nPVs;
      jet_mass_pruned = Vcand.at(0).prunedMass;
      jet_mass_pruned_UnCorr = Vcand.at(0).prunedMassUnCorr;
      jet_csv = Vcand.at(0).csv;
      jet_pt = Vcand.at(0).p4.Pt();
      jet_eta = Vcand.at(0).p4.Eta();
      jet_phi = Vcand.at(0).p4.Phi();
      jet_tau2tau1 = Vcand.at(0).tau2/Vcand.at(0).tau1;
      l_pt  = leptonCand_[0].p4.Pt();
      l_eta = leptonCand_[0].p4.Eta();
      l_phi = leptonCand_[0].p4.Phi();
      l_iso = leptonCand_[0].iso;
      Wlept_pt = WCand_[0].p4.Pt();
      Wlept_mt = TMath::Sqrt( 2*METCand_[0].p4.Pt()*leptonCand_[0].p4.Pt()*(1-cos(leptonCand_[0].p4.DeltaPhi(METCand_[0].p4))) );
      pfMET = METCand_[0].p4.Pt();
      pfMETPhi = METCand_[0].p4.Phi();	
      nak4jets = AK4jetCand_.size();
      jet_jec            = Vcand.at(0).jec;
      jet_pruned_jec     = Vcand.at(0).pruned_jec;
      jet_puppi_softdrop = Vcand.at(0).puppi_softdropMass;
      jet_puppi_tau1 = Vcand.at(0).puppi_tau1;
      jet_puppi_tau2 = Vcand.at(0).puppi_tau2;  
      jet_puppi_tau3 = Vcand.at(0).puppi_tau3;
      jet_puppi_pt   = Vcand.at(0).puppi_pt;
   
      jet_puppi_tau2tau1_jet1 = Vcand.at(0).puppi_tau2/Vcand.at(0).puppi_tau1;       
      float DDT_jet1 = Vcand.at(0).puppi_tau2/Vcand.at(0).puppi_tau1 + ( 0.063 * log(Vcand.at(0).puppi_softdropMass*Vcand.at(0).puppi_softdropMass/Vcand.at(0).puppi_pt) );      
      jet_ddt_jet1 = DDT_jet1;  
      
      
    }
    else
      throw SError( SError::SkipEvent );
  }
  else
    return;
}

//==============================================================================================
bool ExoDiBosonAnalysis::applyJSON( void ){

   if( runOnMC_ || JSONfile_ == "" ) return true;
   // if run on data but JSON information is already applied to samples!f
   if( JSONfile_ == "No") return true;
   return m_grl.HasRunLumiBlock( data_.EVENT_run, data_.EVENT_lumi );

   bool isGood = m_grl.HasRunLumiBlock( data_.EVENT_run, data_.EVENT_lumi );
   if( !isGood ) m_logger << DEBUG << "Bad event! Run: " << data_.EVENT_run <<  " - Lumi Section: " << data_.EVENT_lumi << SLogger::endmsg;
   else m_logger << DEBUG << "Good event! Run: " << data_.EVENT_run <<  " - Lumi Section: " << data_.EVENT_lumi << SLogger::endmsg;

}

//Passed filters
//==============================================================================================
bool ExoDiBosonAnalysis::passedFilters( TString infile ){
  
  if( data_.PV_filter ) nPassedGoodPVFilter_++;
  else return false;
  
  if( !applyFilters_ ) return true;

  //if( data_.PV_filter                       ) nPassedGoodPVFilter_++;       
  if( data_.passFilter_HBHELoose_           ) nPassedFilter_HBHE_++;
  if( data_.passFilter_HBHEIso_             ) nPassedFilter_HBHEIso_++;
  if( data_.passFilter_CSCHalo_             ) nPassedFilter_CSCHalo_++;
  if(( infile.Contains("16Dec2015") or infile.Contains("Fall15")  ) and data_.passFilter_CSCTightHalo2015_    ) nPassedFilter_CSCTightHalo2015_++; 
  if( data_.passFilter_HCALlaser_	          ) nPassedFilter_HCALlaser_++;
  if( data_.passFilter_ECALDeadCell_        ) nPassedFilter_ECALDeadCell_++;
  if( data_.passFilter_GoodVtx_	            ) nPassedFilter_GoodVtx_++;
  if( data_.passFilter_TrkFailure_	        ) nPassedFilter_TrkFailure_++;
  if( data_.passFilter_EEBadSc_	            ) nPassedFilter_EEBadSc_++;
  if( data_.passFilter_ECALlaser_           ) nPassedFilter_ECALlaser_++;
  if( data_.passFilter_TrkPOG_              ) nPassedFilter_TrkPOG_++;
  if( data_.passFilter_TrkPOG_manystrip_    ) nPassedFilter_TrkPOG_manystrip_++;
  if( data_.passFilter_TrkPOG_toomanystrip_ ) nPassedFilter_TrkPOG_toomanystrip_++;
  if( data_.passFilter_TrkPOG_logError_     ) nPassedFilter_TrkPOG_logError_++;
  if( data_.passFilter_METFilters_	        ) nPassedFilter_METFilters_++;
  //if( isGood ) nPassedFilter_EventList_++;          
  
  //bool passMETFiltersAll = data_.passFilter_HBHE_ && data_.passFilter_CSCHalo_ && data_.passFilter_HCALlaser_;
  bool passMETFiltersAll = data_.passFilter_CSCHalo_ && data_.passFilter_HCALlaser_;
  // passMETFiltersAll = passMETFiltersAll && data_.passFilter_ECALDeadCell_ && data_.passFilter_GoodVtx_ && data_.passFilter_TrkFailure_;
//   passMETFiltersAll = passMETFiltersAll && data_.passFilter_EEBadSc_ && data_.passFilter_ECALlaser_ && data_.passFilter_TrkPOG_;
  passMETFiltersAll =   data_.passFilter_HBHELoose_ && data_.passFilter_HBHEIso_ && data_.passFilter_ECALDeadCell_ && data_.PV_filter && data_.passFilter_EEBadSc_ && data_.passFilter_globalTightHalo2016_ && data_.passFilter_muonBadTrack_ && data_.passFilter_chargedHadronTrackResolution_; 
  bool passTrkFiltersAll = data_.passFilter_TrkPOG_manystrip_ && data_.passFilter_TrkPOG_toomanystrip_ && data_.passFilter_TrkPOG_logError_;
     
  if( passMETFiltersAll ) nPassedMETFiltersAll_++;
  if( passTrkFiltersAll ) nPassedTrkFiltersAll_++;
  
 // bool passAllfilters =   data_.passFilter_HBHELoose_ && data_.passFilter_HBHEIso_ && data_.passFilter_CSCTightHalo2015_ && data_.passFilter_ECALDeadCell_ && data_.PV_filter && data_.passFilter_EEBadSc_;  //Fall 15!
  bool passAllfilters =   data_.passFilter_HBHELoose_ && data_.passFilter_HBHEIso_ && data_.passFilter_ECALDeadCell_ && data_.PV_filter && data_.passFilter_EEBadSc_ && data_.passFilter_globalTightHalo2016_ && data_.passFilter_muonBadTrack_ && data_.passFilter_chargedHadronTrackResolution_;
  if( passAllfilters ) return true;
  
  return false;    

}

//==============================================================================================
bool ExoDiBosonAnalysis::passedTrigger( void ){
 
  //Make sure event is triggered
  if( !Trigger_ ) return true;
  TString infile = TString(this->GetHistInputFile()->GetName());
  
  std::vector<std::string> trignames;
	
  if( Channel_.find("VVdijet")!=std::string::npos || Channel_.find("qVdijet")!=std::string::npos ){
    //Dijet triggers
    trignames.push_back("AK8PFJet360_TrimMass30") ;
    trignames.push_back("AK8PFHT700_TrimR0p1PT0p03Mass50") ;
    // trignames.push_back("AK8DiPFJet280_200_TrimMass30_BTagCSV0p45") ;
    trignames.push_back("PFHT650_WideJetMJJ950DEtaJJ1p5") ;
    trignames.push_back("PFHT650_WideJetMJJ900DEtaJJ1p5") ;
    trignames.push_back("PFHT800_v") ;
    trignames.push_back("PFHT900");
    trignames.push_back("PFJet450");
    if( infile.Contains("Run2016H")!=std::string::npos )
    {
    trignames.push_back("HLT_PFHT500"); 
    trignames.push_back("HLT_AK8PFJet450"); 
    trignames.push_back("HLT_AK8PFJet500");
    trignames.push_back("HLT_PFJet450");
      
    }
    
  }
  
  
  else if( Channel_ == "SFmuJets"){
    trignames.push_back("Mu45_eta2p1_") ;
  }
  else if( Channel_ == "SFeleJets"){
    trignames.push_back("Ele27_eta2p1_WPLoose_Gsf") ;
  }
  
  else if( Channel_.find("WtagSF_mu") != std::string::npos){
     if (isLowMass) trignames.push_back("HLT_IsoMu27_v");
     else{
       trignames.push_back("HLT_Mu45_eta2p1");
       trignames.push_back("HLT_Mu50");
     }
  }
  
  else if( Channel_.find("WtagSF_el") != std::string::npos ){
    if (isLowMass){
      trignames.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v"); //DATA
      trignames.push_back("HLT_Ele27_eta2p1_WP75_Gsf_"); //MC
  }
  else{
    // trignames.push_back("HLT_Ele45_WPLoose_Gsf_v"); //NEW! In correspondence with low-mass VW!
    trignames.push_back("HLT_Ele105_CaloIdVT_GsfTrkIdT"); 
    trignames.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT");
  }
}
	
  bool isfired = false;
  for( std::map<std::string,bool>::iterator it = (data_.HLT_isFired)->begin(); it != (data_.HLT_isFired)->end(); ++it){
    for( unsigned int t = 0; t < trignames.size(); ++t ){
      // std::cout << (it->first) << std::endl;
      if( (it->first).find(trignames[t]) != std::string::npos && it->second ) isfired = true;
    }
  }

  return isfired;
    
}

//==============================================================================================
//Methods for VVdijet analysis====================================================================
//==============================================================================================

bool ExoDiBosonAnalysis::passedDijetSelectionsAK4(  TString infile  ){
  bool foundTwoJets			= false;
  bool passedDeltaEtaCut		= false;
  bool passedMjjCut			= false;
	
  //Make sure events contains two AK8 jets passing loose requirements
  if( findJetCandidatesAK4() ) foundTwoJets = true;
  if( !foundTwoJets) return false;
  nPassedFoundJets_++;
  
  //Only select jets separated by |DeltaEta| < cut
  jetsDeltaEta = fabs( AK4jetCand_.at(0).p4.Eta()  - AK4jetCand_.at(1).p4.Eta() ) ; 
  if (jetsDeltaEta <= dEtaCut_) passedDeltaEtaCut = true;	
  
  if ( ( AK4jetCand_.at(0).p4 + AK4jetCand_.at(1).p4 ).M() >= MjjCut_ ){
    // jet_deta = fabs( AK4jetCand_.at(0).p4.Eta()  - AK4jetCand_.at(1).p4.Eta());
    passedMjjCut = true;
  }
  
  if( !passedDeltaEtaCut) return false;  
  nPassedJetsDEta_++;
  
  if( !passedMjjCut) return false;   
  nPassedMjj_++; 
  
  // //Apply selection
  if ( foundTwoJets && passedDeltaEtaCut && passedMjjCut ) return true;
  else
    return false;
  
}

//==============================================================================================  

  
  
bool ExoDiBosonAnalysis::passedDijetSelections(  TString infile  ){
  bool foundTwoJets					= false;
  bool passedDeltaEtaCut	= false;
  bool passedMjjCut					= false;
  bool passedGroomedMassCut	= false;
  bool passedWTag						= false;
  
//     if(weight_ >= 3.)
//     {
//     std::cout << "================== event : "<< numEvents_ << " ======================"<<std::endl;
//     std::cout <<"weight : " <<weight_ << std::endl;
//     std::cout <<"lumiweight : " << lumiweight_ << std::endl;
//     std::cout <<"PU weight  : " << puweight_ << std::endl;
//     std::cout <<"HLT weight : "<<  hltweight_ << std::endl;
//     std::cout <<"btagveto w : "<< btagweight_ << std::endl;
//     std::cout <<"gen weight : "<< genweight_ << std::endl;
//     }
  
  //Make sure events contains two AK8 jets passing loose requirements
  if( findJetCandidates( infile ) ) foundTwoJets = true;
  if( !foundTwoJets) return false;
  nPassedFoundJets_++;
 
  //Only select jets separated by |DeltaEta| < cut
  jetsDeltaEta = fabs( Vcand.at(0).p4.Eta()  - Vcand.at(1).p4.Eta() ) ; 
  if (jetsDeltaEta <= dEtaCut_) passedDeltaEtaCut = true;	
  if( !passedDeltaEtaCut) return false;  
  nPassedJetsDEta_++;
  
  if( !Trigger_ && !runOnMC_ ){
    doJetTriggerEfficiency();
    do2DTriggerEfficiency();
    if(Vcand.at(0).p4.Pt() > 600) doTriggerEfficiencyvsMass();
  }
  
  //Only select jets with Mjj > cut
  
  if ( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() >= MjjCut_ ) passedMjjCut = true;
  if( !passedMjjCut) return false;
  nPassedMjj_++;
    
  Hist( "DeltaEta")	->Fill( fabs( Vcand.at(0).p4.Eta()  - Vcand.at(1).p4.Eta() ) , weight_ ); 	
  Hist( "DeltaR")	  ->Fill( (Vcand.at(0).p4).DeltaR(Vcand.at(1).p4) , weight_ ); 
  
  Hist( "nVertices"       )->Fill( data_.nPVs, weight_ );
  Hist( "Rho"              )->Fill( data_.rho, weight_ );
  for( unsigned int j = 0; j < (data_.PV_rho)->size() ; ++j )  Hist( "PV_rho"              )->Fill( (*data_.PV_rho).at(j), weight_ );
  
  Hist( "Pt_jet1"         )->Fill( Vcand.at(0).p4.Pt(), weight_ );
  Hist( "Pt_jet2"         )->Fill( Vcand.at(1).p4.Pt(), weight_ );
  
   if(weight_ >= 10){
  std::cout << numEvents_ << std::endl;
  std::cout <<"weight : " <<weight_ << std::endl;
  std::cout <<"lumiweight : " << lumiweight_ << std::endl;
  std::cout <<"PU weight  : " << puweight_ << std::endl;
  std::cout <<"HLT weight : "<<  hltweight_ << std::endl;
  std::cout <<"btagveto w : "<< btagweight_ << std::endl;
  std::cout <<"gen weight : "<< genweight_ << std::endl;
   }
  
    if(wmax_     <= weight_){ wmax_ = weight_;}
    if(wmaxpu_   <= puweight_  ){wmaxpu_   = puweight_  ;}
    if(wmaxlumi_ <= lumiweight_){wmaxlumi_ = lumiweight_;}
    if(wmaxpt_   <= ptweight_  ){wmaxpt_   = ptweight_  ;}
    if(wmaxhlt_  <= hltweight_ ){wmaxhlt_  = hltweight_ ;}
    if(wmaxbtag_ <= btagweight_){wmaxbtag_ = btagweight_;}
    if(wmaxgen_  <= genweight_ ){wmaxgen_  = genweight_ ;}
    
//       if( numEvents_ == 107804)
//     {
//     std::cout << "================== event : "<< numEvents_ << " ======================"<<std::endl;
//     std::cout <<"weight : " <<weight_ << std::endl;
//     std::cout <<"lumiweight : " << lumiweight_ << std::endl;
//     std::cout <<"PU weight  : " << puweight_ << std::endl;
//     std::cout <<"HLT weight : "<<  hltweight_ << std::endl;
//     std::cout <<"btagveto w : "<< btagweight_ << std::endl;
//     std::cout <<"gen weight : "<< genweight_ << std::endl;
//      for( int i = 0; i < abs(Vcand.size()) ; i++){
//     std::cout <<  "Mass    "                    <<   Vcand.at(i).p4.M()             << std::endl;
//     std::cout << "PrunedMass   "               <<  Vcand.at(i).prunedMass          << std::endl;
//     std::cout << "PuppiSoftdropMass   "        <<  Vcand.at(i).puppi_softdropMass  << std::endl;
//     std::cout << "Tau21  "                    <<  Vcand.at(i).tau2/Vcand.at(i).tau1<< std::endl;
//     std::cout << "Pt   "                       <<  Vcand.at(i).p4.Pt()             << std::endl;
//     std::cout << "Eta  "                      <<  Vcand.at(i).p4.Eta()            << std::endl;
//     std::cout << "Phi  "                      <<  Vcand.at(i).p4.Phi()            << std::endl;
//     std::cout << "Mass  "                     <<  Vcand.at(i).p4.M()              << std::endl;  
//     std::cout << "cm  "                       <<  Vcand.at(i).cm	                 << std::endl;
//     std::cout << "nm  "                       <<  Vcand.at(i).nm	                 << std::endl;
//     std::cout << "muf  "                      <<  Vcand.at(i).muf                  << std::endl;
//     std::cout << "phf  "                      <<  Vcand.at(i).phf  << std::endl;
//     std::cout << "emf  "                      <<  Vcand.at(i).emf  << std::endl;
//     std::cout << "nhf  "                      <<  Vcand.at(i).nhf  << std::endl;
//     std::cout << "chf  "                      <<  Vcand.at(i).chf  << std::endl;
//     std::cout << "area  "                     <<  Vcand.at(i).area << std::endl;
//     std::cout << "tau1  "                     <<  Vcand.at(i).tau1 << std::endl;
//     std::cout << "tau2  "                     <<  Vcand.at(i).tau2 << std::endl;
//     std::cout << "tau3tau2  "                 <<  Vcand.at(i).tau3/Vcand.at(i).tau2  << std::endl;
//     std::cout << "tau3tau1  "                 <<  Vcand.at(i).tau3/Vcand.at(i).tau1  << std::endl;
//     std::cout << "tau2tau1  "                 <<  Vcand.at(i).tau2/Vcand.at(i).tau1  << std::endl;
//     std::cout << "puppi_tau3tau2  "           <<  Vcand.at(i).puppi_tau3/Vcand.at(i).puppi_tau2 << std::endl;
//     std::cout << "puppi_tau3tau1  "           <<  Vcand.at(i).puppi_tau3/Vcand.at(i).puppi_tau1 << std::endl;
//     std::cout << "puppi_tau2tau1  "           <<  Vcand.at(i).puppi_tau2/Vcand.at(i).puppi_tau1 << std::endl;
//     std::cout << "puppi_tau1  "               <<  Vcand.at(i).puppi_tau1 << std::endl;
//     std::cout << "puppi_tau2  "               <<  Vcand.at(i).puppi_tau2 << std::endl;
//     std::cout << "tau3  "                     <<  Vcand.at(i).tau3 << std::endl;
//     std::cout << "che  "                      <<  Vcand.at(i).che  << std::endl;
//     std::cout << "ne  "                       <<  Vcand.at(i).ne   << std::endl;
//     std::cout << "HFHadronEnergyFraction  "   <<  Vcand.at(i).hf_hf  <<std::endl;
//     std::cout << "HFEMEnergyFraction  "       <<  Vcand.at(i).hf_emf <<std::endl;
//     std::cout << "hoEnergyFraction  "         <<  Vcand.at(i).hof    <<std::endl;
//     std::cout << "chargedHadronMultiplicity  "<<  Vcand.at(i).chm    <<std::endl;
//     //std::cout << "neutralHadronMultiplicity"<<  Vcand.at(i).neHadM <<std::endl;
//     std::cout << "photonMultiplicity  "       <<  Vcand.at(i).phoMult << std::endl;
//     std::cout << "neutralEmEnergyFraction  "  <<  Vcand.at(i).nemf    << std::endl;
//     std::cout << "chargedEmEnergyFraction  "  <<  Vcand.at(i).cemf    << std::endl;
//      }
//     }
    
  
    Hist( "Weight"      )->Fill( weight_ );
    Hist( "PUWeight"    )->Fill(puweight_);
    Hist( "LumiWeight"  )->Fill(lumiweight_);
    Hist( "GenWeight"   )->Fill(genweight_);
    Hist( "PtWeight"    )->Fill(ptweight_);
    Hist( "BtagWeight"  )->Fill(btagweight_);
    Hist( "HLTWeight"   )->Fill(hltweight_);
   if( numEvents_ != 107804){ 
  for( int i = 0; i < abs(Vcand.size()) ; i++){

    
    Hist( "Mass"                          )  ->Fill( Vcand.at(i).p4.M(), weight_ );
    Hist( "PrunedMass"                    )  ->Fill( Vcand.at(i).prunedMass, weight_ );
    Hist( "PuppiSoftdropMass"             )  ->Fill( Vcand.at(i).puppi_softdropMass, weight_ );
    Hist( "Tau21"                         )  ->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1, weight_ );
    Hist( "Pt"                            )  ->Fill( Vcand.at(i).p4.Pt(), weight_ );
    Hist( "Eta"                           )  ->Fill( Vcand.at(i).p4.Eta(), weight_ );
    Hist( "Phi"                           )  ->Fill( Vcand.at(i).p4.Phi(), weight_ );
    Hist( "Mass"                          )  ->Fill( Vcand.at(i).p4.M(), weight_ );      
    Hist( "cm"                            )  ->Fill( Vcand.at(i).cm	   , weight_ );
    Hist( "nm"                            )  ->Fill( Vcand.at(i).nm	   , weight_ );
    Hist( "muf"                           )  ->Fill( Vcand.at(i).muf  , weight_ );
    Hist( "phf"                           )  ->Fill( Vcand.at(i).phf  , weight_ );
    Hist( "emf"                           )  ->Fill( Vcand.at(i).emf  , weight_ );
    Hist( "nhf"                           )  ->Fill( Vcand.at(i).nhf  , weight_ );
    Hist( "chf"                           )  ->Fill( Vcand.at(i).chf  , weight_ );
    Hist( "area"                          )  ->Fill( Vcand.at(i).area  , weight_ );
    Hist( "tau1"                          )  ->Fill( Vcand.at(i).tau1  , weight_ );
    Hist( "tau2"                          )  ->Fill( Vcand.at(i).tau2  , weight_ );
    Hist( "tau3tau2"                      )  ->Fill( Vcand.at(i).tau3/Vcand.at(i).tau2  , weight_ );
    Hist( "tau3tau1"                      )  ->Fill( Vcand.at(i).tau3/Vcand.at(i).tau1  , weight_ );
    Hist( "tau2tau1"                      )  ->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1  , weight_ );
    Hist( "puppi_tau3tau2"                )  ->Fill( Vcand.at(i).puppi_tau3/Vcand.at(i).puppi_tau2  , weight_ );
    Hist( "puppi_tau3tau1"                )  ->Fill( Vcand.at(i).puppi_tau3/Vcand.at(i).puppi_tau1  , weight_ );
    Hist( "puppi_tau2tau1"                )  ->Fill( Vcand.at(i).puppi_tau2/Vcand.at(i).puppi_tau1  , weight_ );
    Hist( "puppi_tau1"                    )  ->Fill( Vcand.at(i).puppi_tau1  , weight_ );
    Hist( "puppi_tau2"                    )  ->Fill( Vcand.at(i).puppi_tau2  , weight_ );
    Hist( "tau3"                          )  ->Fill( Vcand.at(i).tau3  , weight_ );
    Hist( "che"                           )  ->Fill( Vcand.at(i).che  , weight_ );
    Hist( "ne"                            )  ->Fill( Vcand.at(i).ne  , weight_ );
    Hist( "HFHadronEnergyFraction"        )  ->Fill( Vcand.at(i).hf_hf , weight_ ); //HFHadronEnergyFraction());
    Hist( "HFEMEnergyFraction"            )  ->Fill( Vcand.at(i).hf_emf , weight_ ); //HFEMEnergyFraction());
    Hist( "hoEnergyFraction"              )  ->Fill( Vcand.at(i).hof , weight_ ); //hoEnergyFraction());
    Hist( "chargedHadronMultiplicity"     )  ->Fill( Vcand.at(i).chm , weight_ ); //chargedHadronMultiplicity());
    Hist( "neutralHadronMultiplicity"     )  ->Fill( Vcand.at(i).neHadMult  , weight_ ); //neutralHadronMultiplicity());
    Hist( "photonMultiplicity"            )  ->Fill( Vcand.at(i).phoMult , weight_ ); //photonMultiplicity());
    Hist( "neutralEmEnergyFraction"       )  ->Fill( Vcand.at(i).nemf , weight_ ); //neutralEmEnergyFraction());
    Hist( "chargedEmEnergyFraction"       )  ->Fill( Vcand.at(i).cemf  , weight_ ); //chargedEmEnergyFraction());
    Hist( "charge"     )  ->Fill( Vcand.at(i).charge , weight_ ); //charge());
    if( Vcand.at(i).tau2/Vcand.at(i).tau1 >= Tau21HPLow_ && Vcand.at(i).tau2/Vcand.at(i).tau1 <= Tau21HPHigh_ ) Hist( "PrunedMass_afterTau21"    )  ->Fill( Vcand.at(i).prunedMass, weight_ );
    if( Vcand.at(i).puppi_tau2/Vcand.at(i).puppi_tau1 >= Tau21HPLow_ && Vcand.at(i).puppi_tau2/Vcand.at(i).puppi_tau1 <= Tau21HPHigh_ ) Hist( "PuppiSoftdropMass_afterTau21")  ->Fill( Vcand.at(i).puppi_softdropMass, weight_ );
    if( Vcand.at(i).prunedMass > 65. && Vcand.at(i).prunedMass <= 105. ) Hist( "Tau21_afterPrunedMass" )  ->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1, weight_ );
    if( Vcand.at(i).puppi_softdropMass > 65. && Vcand.at(i).puppi_softdropMass <= 105. ) Hist( "PUPPITau21_afterPUPPISoftdropMass" )  ->Fill( Vcand.at(i).puppi_tau2/Vcand.at(i).puppi_tau1, weight_ );
  }
   }
    
  
  if( Vcand.at(0).prunedMass > mWLow_ || Vcand.at(1).prunedMass > mWLow_ )Hist( "Mjj_afterPrunedMass" ) -> Fill( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() , weight_ );	
  Hist( "Mjj" ) -> Fill( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() , weight_ );	

  
  int jetINDXPunzi = 99;
  float MET   = (*data_.MET_et).at(0);
  float SumEt = (*data_.MET_sumEt).at(0);
  if( MET > 0. ) Hist( "METsumET" )->Fill(MET/SumEt, weight_ );
  if( MET > 0. ) Hist( "MET" )->Fill(MET, weight_ );
  
  if(!usePuppiSD_){
    if( Channel_ == "VVdijet"){

      if( Vcand.at(0).prunedMass > mWLow_ && Vcand.at(0).prunedMass <= mZHigh_ && Vcand.at(1).prunedMass > mWLow_ && Vcand.at(1).prunedMass <= mZHigh_){

        passedGroomedMassCut = true;
        Hist( "Tau21_punzi1"  )->Fill( Vcand.at(0).tau2/Vcand.at(0).tau1,weight_ );
        Hist( "Tau21_punzi2"  )->Fill( Vcand.at(1).tau2/Vcand.at(1).tau1,weight_ );

        float MJJ =  (Vcand.at(0).p4 + Vcand.at(1).p4).M();
        for( int i = 0; i < abs(Vcand.size()) ; i++){
          Hist( "Tau21_punzi"  )->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1,weight_ );
          if(MJJ > 0.8*1000 && MJJ < 1.2*1000)Hist( "Tau21_punzi1TeV"  )->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1,weight_ );
          if(MJJ > 0.8*1200 && MJJ < 1.2*1200)Hist( "Tau21_punzi1v2TeV")->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1,weight_ );
          if(MJJ > 0.8*1600 && MJJ < 1.2*1600)Hist( "Tau21_punzi1v6TeV")->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1,weight_ );
          if(MJJ > 0.8*1800 && MJJ < 1.2*1800)Hist( "Tau21_punzi1v8TeV")->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1,weight_ );
          if(MJJ > 0.8*2000 && MJJ < 1.2*2000)Hist( "Tau21_punzi2TeV"  )->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1,weight_ );
          if(MJJ > 0.8*2500 && MJJ < 1.2*2500)Hist( "Tau21_punzi2v5TeV")->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1,weight_ );
          if(MJJ > 0.8*3000 && MJJ < 1.2*3000)Hist( "Tau21_punzi3TeV"  )->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1,weight_ );
          if(MJJ > 0.8*4000 && MJJ < 1.2*4000)Hist( "Tau21_punzi4TeV"  )->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1,weight_ );
        }
      }
    }

    if (Channel_ == "qVdijet"){
      for( int i = 0; i < abs(Vcand.size()) ; i++){
        if(!(Vcand.at(i).prunedMass > mWLow_ && Vcand.at(i).prunedMass <= mZHigh_) ) continue;
        passedGroomedMassCut = true;
        jetINDXPunzi=i;
        Hist( "Tau21_punzi"  )->Fill( Vcand.at(jetINDXPunzi).tau2/Vcand.at(jetINDXPunzi).tau1,weight_ );
      }
    }
  }

  else if(usePuppiSD_){
    if(Channel_ == "VVdijet" && Vcand.at(0).puppi_softdropMass > mWLow_ && Vcand.at(0).puppi_softdropMass <= mZHigh_ && Vcand.at(1).puppi_softdropMass > mWLow_ && Vcand.at(1).puppi_softdropMass <= mZHigh_ ){
      passedGroomedMassCut = true;
      Hist( "Tau21_punzi1"  )->Fill( Vcand.at(0).puppi_tau2/Vcand.at(0).puppi_tau1,weight_ );
      Hist( "Tau21_punzi2"  )->Fill( Vcand.at(1).puppi_tau2/Vcand.at(1).puppi_tau1,weight_ );

      float MJJ =  (Vcand.at(0).p4 + Vcand.at(1).p4).M();
      for( int i = 0; i < abs(Vcand.size()) ; i++){
        Hist( "Tau21_punzi"  )->Fill( Vcand.at(0).tau2/Vcand.at(0).tau1,weight_ );
        if(MJJ > 0.8*1000 && MJJ < 1.2*1000)Hist( "Tau21_punzi1TeV"  )->Fill( Vcand.at(i).puppi_tau2/Vcand.at(i).puppi_tau1,weight_ );
        if(MJJ > 0.8*1200 && MJJ < 1.2*1200)Hist( "Tau21_punzi1v2TeV")->Fill( Vcand.at(i).puppi_tau2/Vcand.at(i).puppi_tau1,weight_ );
        if(MJJ > 0.8*1600 && MJJ < 1.2*1600)Hist( "Tau21_punzi1v6TeV")->Fill( Vcand.at(i).puppi_tau2/Vcand.at(i).puppi_tau1,weight_ );
        if(MJJ > 0.8*1800 && MJJ < 1.2*1800)Hist( "Tau21_punzi1v8TeV")->Fill( Vcand.at(i).puppi_tau2/Vcand.at(i).puppi_tau1,weight_ );
        if(MJJ > 0.8*2000 && MJJ < 1.2*2000)Hist( "Tau21_punzi2TeV"  )->Fill( Vcand.at(i).puppi_tau2/Vcand.at(i).puppi_tau1,weight_ );
        if(MJJ > 0.8*2500 && MJJ < 1.2*2500)Hist( "Tau21_punzi2v5TeV")->Fill( Vcand.at(i).puppi_tau2/Vcand.at(i).puppi_tau1,weight_ );
        if(MJJ > 0.8*3000 && MJJ < 1.2*3000)Hist( "Tau21_punzi3TeV"  )->Fill( Vcand.at(i).puppi_tau2/Vcand.at(i).puppi_tau1,weight_ );
        if(MJJ > 0.8*4000 && MJJ < 1.2*4000)Hist( "Tau21_punzi4TeV"  )->Fill( Vcand.at(i).puppi_tau2/Vcand.at(i).puppi_tau1,weight_ );
      }
    }

      if (Channel_ == "qVdijet"){
        for( int i = 0; i < abs(Vcand.size()) ; i++){
          if(!(Vcand.at(i).puppi_softdropMass > mWLow_ && Vcand.at(i).puppi_softdropMass <= mZHigh_) ) continue;
          passedGroomedMassCut = true;
          jetINDXPunzi=i;
          Hist( "Tau21_punzi"  )->Fill( Vcand.at(jetINDXPunzi).puppi_tau1/Vcand.at(jetINDXPunzi).puppi_tau1,weight_ );
        }
      }
    }

    if(Channel_.find("jetmassSideband")!=std::string::npos)
    {
      if(Channel_.find("VV")!=std::string::npos)
      {
       if((Vcand.at(0).puppi_softdropMass > 20 && Vcand.at(0).puppi_softdropMass < mWLow_ && Vcand.at(1).puppi_softdropMass > mWLow_ && Vcand.at(1).puppi_softdropMass <= mZHigh_ ) or (Vcand.at(1).puppi_softdropMass > 20 && Vcand.at(1).puppi_softdropMass < mWLow_ && Vcand.at(0).puppi_softdropMass > mWLow_ && Vcand.at(0).puppi_softdropMass <= mZHigh_ ) )
       {
           passedGroomedMassCut = true;
       //std::cout << " v1 : " << Vcand.at(0).puppi_softdropMass << "  v2 : "<< Vcand.at(1).puppi_softdropMass << std::endl;
       }
      }
      if(Channel_.find("qV")!=std::string::npos)
      {
        //========== original sideband definition =========================================  
//         if((Vcand.at(0).puppi_softdropMass > 20 && Vcand.at(0).puppi_softdropMass < mWLow_ && Vcand.at(1).puppi_softdropMass > 105 && Vcand.at(1).puppi_softdropMass < 200 ) or (Vcand.at(1).puppi_softdropMass > 20 && Vcand.at(1).puppi_softdropMass < mWLow_ && Vcand.at(0).puppi_softdropMass > 105 && Vcand.at(0).puppi_softdropMass < 200 ) )
//             passedGroomedMassCut = true;
//         //=================================================================================
//         if( ((20 < Vcand.at(0).puppi_softdropMass) && (Vcand.at(0).puppi_softdropMass < mWLow_) ) && ((20 < Vcand.at(1).puppi_softdropMass) && (Vcand.at(1).puppi_softdropMass < mWLow_) ))  
//            passedGroomedMassCut = true; 
//         if( ( (mZHigh_ < Vcand.at(0).puppi_softdropMass) && ( Vcand.at(0).puppi_softdropMass< 200) ) && ((mZHigh_ < Vcand.at(1).puppi_softdropMass) && (Vcand.at(1).puppi_softdropMass < 200 )))
//             passedGroomedMassCut = true;
           if ( (45 < Vcand.at(0).puppi_softdropMass and Vcand.at(0).puppi_softdropMass <= 65. and 105 < Vcand.at(1).puppi_softdropMass and Vcand.at(1).puppi_softdropMass < 200) or ( 45 < Vcand.at(1).puppi_softdropMass and Vcand.at(1).puppi_softdropMass <= 65. and 105 < Vcand.at(0).puppi_softdropMass and Vcand.at(1).puppi_softdropMass < 200))
           {
               passedGroomedMassCut = true;
           }
          
      }
    }

  //Cut flow
  if( !passedGroomedMassCut)  return false;
  nPassedJetPrunedMass_++;
  
  //Apply selection
  if ( foundTwoJets && passedDeltaEtaCut && passedMjjCut && passedGroomedMassCut) return true;
  // if ( foundTwoJets && passedDeltaEtaCut && passedMjjCut) return true;
  else
    return false;
	
}

//==============================================================================================
bool ExoDiBosonAnalysis::findJetCandidatesAK4( void ){
  
  TLorentzVector			TLV;
  std::vector<float>	jetPt;
  bool foundJets = false;
  float csv         = -9999;
		
  jetPt.clear();
  //Make sure jets passes loose ID, pT and eta cuts
  for( int j = 0; j < data_.njetsAK4 ; ++j ){
    if( j < 2 && (*data_.jetAK4_IDTight).at(j) != 1         )break;
    if( (*data_.jetAK4_IDTight).at(j)		!= 1				  			)continue;
    if( (*data_.jetAK4_pt).at(j)					<= JetPtCutTight_	)continue;
    if( fabs((*data_.jetAK4_eta).at(j)) 	>= JetEtaCut_ 		)continue;		
    jetPt.push_back((*data_.jetAK4_pt).at(j));
  }
	
  if( jetPt.size() > 1 ) foundJets = true;
  if( !foundJets) return false;
		
  //Find two highest pT jets in event
  if( foundJets ){
    std::sort  (jetPt.begin(),jetPt.end());
    std::reverse(jetPt.begin(),jetPt.end());
    for( int jj = 0; jj < 2; ++jj ){
      bool foundOverlap = false;
      if( (*data_.jetAK4_pt)[jj] == jetPt.at(0) ){
        TLV.SetPtEtaPhiE( (*data_.jetAK4_pt).at(jj), (*data_.jetAK4_eta).at(jj), (*data_.jetAK4_phi).at(jj), (*data_.jetAK4_e).at(jj) );
        if ( findMuonCandidate() || findElectronCandidate() ){
          for(int i = 0; i < abs(leptonCand_.size()); i++){
            if( TLV.DeltaR(leptonCand_.at(i).p4) < 0.4 ){
              foundOverlap = true;
            }
          }
        }    
        if( foundOverlap ) break;
        JetCandidate jet(TLV);                               ;
        jet.flavor				= -99                               ;
        AK4jetCand_.push_back( jet );
        
      }
      else
      if( (*data_.jetAK4_pt).at(jj) == jetPt.at(1) ){
        TLV.SetPtEtaPhiE( (*data_.jetAK4_pt).at(jj), (*data_.jetAK4_eta).at(jj), (*data_.jetAK4_phi).at(jj), (*data_.jetAK4_e).at(jj) );
        if ( findMuonCandidate() || findElectronCandidate() ){
          for(int i = 0; i < abs(leptonCand_.size()); i++){
            if( TLV.DeltaR(leptonCand_.at(i).p4) < 0.4 ){
              foundOverlap = true;
            }
          }
        }
        if( foundOverlap ) break;
        JetCandidate secondJet(TLV);
        AK4jetCand_.push_back( secondJet );
      }
      else
        continue;
    }
  }
  
  if (AK4jetCand_.size() < 2) return false;
  return foundJets;
}
//==============================================================================================
bool ExoDiBosonAnalysis::findJetCandidates( TString infile ){
  
  bool foundJet = false;
  bool foundJet2 = false;
  bool foundJets = false;

  TLorentzVector bestjet_tlv;
  TLorentzVector bestjet2_tlv;
  int    jetIndex = 999;
  int    jetIndex2 = 999;
  float  jetmass1  = -999;
  float  jetmass2  = -999;

  int    PUPPIjetIndex1 = 999;
  int    PUPPIjetIndex2 = 999;
  
  //Make sure jet1 passes loose ID, pT and eta cuts
  TLorentzVector			TLV;
  for( int j = 0; j < data_.njetsAK8 ; ++j ){
    
    float jetPT = getJetEnergyScale( j );  
    if( Channel_.find("dijet")!= std::string::npos && jetPT <= JetPtCutTight_    )continue;   
    if( Channel_.find("WtagSF") != std::string::npos && jetPT <= 80.             )continue; //before used 80 here!!!
    TLV.SetPtEtaPhiE( jetPT , (*data_.jetAK8_eta).at(j), (*data_.jetAK8_phi).at(j), (jetPT/(*data_.jetAK8_pt).at(j))*(*data_.jetAK8_e).at(j) );
    if( Channel_.find("dijet")!= std::string::npos && j < 1 && (*data_.jetAK8_IDTight).at(j) != 1   )break;
    if( Channel_.find("dijet")!= std::string::npos && (*data_.jetAK8_IDTight).at(j)    != 1         )continue;
    if( Channel_.find("WtagSF") != std::string::npos && (*data_.jetAK8_IDLoose).at(j) != 1          )continue;
    if( Channel_.find("WtagSF") != std::string::npos && leptonCand_[0].p4.DeltaR(TLV) <= 1.0        )continue;   
    if( fabs(TLV.Eta()) >= JetEtaCut_ 	                                                            )continue;	
    //Find PUPPI match
    int PUPPIjetMatchIndex = 999;
    float dRmin  = 999;
    TLorentzVector puppijet_tlv1;
    for( unsigned int jj = 0; jj < (data_.jetAK8_puppi_softdrop_massUnCorr)->size() ; ++jj ){  
      if ((*data_.jetAK8_puppi_pt).at(jj) < 0.001 || (*data_.jetAK8_puppi_pt).at(jj) > 9999) continue;
      TLorentzVector puppiJet;
      puppiJet.SetPtEtaPhiE( (*data_.jetAK8_puppi_pt).at(jj), (*data_.jetAK8_puppi_eta).at(jj), (*data_.jetAK8_puppi_phi).at(jj), (*data_.jetAK8_puppi_e).at(jj) );
      float dR = puppiJet.DeltaR(TLV);
      if(dR > dRmin) continue;
      dRmin = dR;
      PUPPIjetMatchIndex = jj;
      puppijet_tlv1 = puppiJet;
    }
    
    if( !usePuppiSD_){
      if ( (*data_.jetAK8_prunedmass)[j] < jetmass1 ) continue;
      jetmass1 = (*data_.jetAK8_prunedmass)[j];
      bestjet_tlv.SetPtEtaPhiE( jetPT, (*data_.jetAK8_eta).at(j), (*data_.jetAK8_phi).at(j), (jetPT/(*data_.jetAK8_pt).at(j))*(*data_.jetAK8_e).at(j) );
      foundJet = true;
      jetIndex = j;
      PUPPIjetIndex1 = PUPPIjetMatchIndex;
    }
    else if( usePuppiSD_ and PUPPIjetMatchIndex == 999) continue;
    else{
      float puppiCorr = getPUPPIweight( puppijet_tlv1.Pt(), puppijet_tlv1.Eta() );
      float corrMass = (*data_.jetAK8_puppi_softdrop_massUnCorr)[PUPPIjetMatchIndex]*puppiCorr;
      if( isSignal_) corrMass = getJetMassScale(corrMass, (*data_.jetAK8_jer_sigma_pt).at(j), puppijet_tlv1, TLV);
      if ( corrMass < jetmass1 ) continue;
      jetmass1 = corrMass;
      bestjet_tlv.SetPtEtaPhiE( jetPT , (*data_.jetAK8_eta).at(j), (*data_.jetAK8_phi).at(j), (jetPT/(*data_.jetAK8_pt).at(j))*(*data_.jetAK8_e).at(j) );
      foundJet = true;
      jetIndex = j;
      PUPPIjetIndex1 = PUPPIjetMatchIndex;
    }
  } 
  
  if ( Channel_.find("dijet")!= std::string::npos && !foundJet) return false;

  //Make sure jet2 passes loose ID, pT and eta cuts
 for( int j = 0; j < data_.njetsAK8 ; ++j ){
    if( j == jetIndex ) continue;
    float jetPT = getJetEnergyScale( j );
    if( Channel_.find("dijet")!= std::string::npos && jetPT <= JetPtCutTight_ )continue;    
    TLV.SetPtEtaPhiE( jetPT , (*data_.jetAK8_eta).at(j), (*data_.jetAK8_phi).at(j), (jetPT/(*data_.jetAK8_pt).at(j))*(*data_.jetAK8_e).at(j) );
    if( Channel_.find("dijet")!= std::string::npos && (*data_.jetAK8_IDTight).at(j)    != 1         )continue;
    if( fabs( TLV.Eta())  >= JetEtaCut_ )continue;
    
    //Find PUPPI match
    int PUPPIjetMatchIndex = 999;
    float dRmin  = 999;
    TLorentzVector puppijet_tlv1;
    for( unsigned int jj = 0; jj < (data_.jetAK8_puppi_softdrop_massUnCorr)->size() ; ++jj ){  
      if ((*data_.jetAK8_puppi_pt).at(jj) < 0.001 || (*data_.jetAK8_puppi_pt).at(jj) > 9999 || jj == PUPPIjetIndex1 ) continue;
      TLorentzVector puppiJet;
      puppiJet.SetPtEtaPhiE( (*data_.jetAK8_puppi_pt).at(jj), (*data_.jetAK8_puppi_eta).at(jj), (*data_.jetAK8_puppi_phi).at(jj), (*data_.jetAK8_puppi_e).at(jj) );
      float dR = puppiJet.DeltaR(TLV);
      if(dR > dRmin) continue;
      dRmin = dR;
      PUPPIjetMatchIndex = jj;
      puppijet_tlv1 = puppiJet;
    }
    
    if( usePuppiSD_ and PUPPIjetMatchIndex == 999) continue;
    else if( !usePuppiSD_){
      if ( (*data_.jetAK8_prunedmass)[j] < jetmass2 or j == jetIndex) continue;
      jetmass2 = (*data_.jetAK8_prunedmass)[j];
      bestjet2_tlv.SetPtEtaPhiE(jetPT, (*data_.jetAK8_eta).at(j), (*data_.jetAK8_phi).at(j), (jetPT/(*data_.jetAK8_pt).at(j))*(*data_.jetAK8_e).at(j) );
      foundJet2 = true;
      jetIndex2 = j;
      PUPPIjetIndex2 = PUPPIjetMatchIndex;
    }
    else if( usePuppiSD_){
      float puppiCorr = getPUPPIweight(puppijet_tlv1.Pt(), puppijet_tlv1.Eta() );
      float corrMass = (*data_.jetAK8_puppi_softdrop_massUnCorr)[PUPPIjetMatchIndex]*puppiCorr;
      if( isSignal_) corrMass = getJetMassScale(corrMass, (*data_.jetAK8_jer_sigma_pt).at(j),puppijet_tlv1,TLV);
      if ( corrMass < jetmass2  or PUPPIjetMatchIndex == PUPPIjetIndex1 ) continue;
      jetmass2 = corrMass;
      bestjet2_tlv.SetPtEtaPhiE( jetPT, (*data_.jetAK8_eta).at(j), (*data_.jetAK8_phi).at(j), (jetPT/(*data_.jetAK8_pt).at(j))*(*data_.jetAK8_e).at(j) );
      foundJet2 = true;
      jetIndex2 = j;
      PUPPIjetIndex2 = PUPPIjetMatchIndex;
    }
  }
  
  if ( Channel_.find("dijet")!= std::string::npos && !foundJet2) return false;
  
  else if( Channel_.find("dijet")!= std::string::npos && foundJet && foundJet2) foundJets = true;
  else if( Channel_.find("WtagSF")!= std::string::npos && foundJet) foundJets = true;
  
  if( !foundJets) return false;
    

  bool foundOverlap = false;
  if ( Channel_.find("dijet")!= std::string::npos && (findMuonCandidate() || findElectronCandidate()) ){
    for( int i = 0; i < abs(leptonCand_.size()); i++){
      if( bestjet_tlv.DeltaR(leptonCand_.at(i).p4) < 0.8 ) foundOverlap = true;
    }
  }
  if( Channel_.find("dijet")!= std::string::npos && foundOverlap ) {std::cout << "rejected due to overlap" << std::endl; return false;}
  
  
  if (usePuppiSD_ && foundJet && PUPPIjetIndex1 == 999){
    nNopuppi_++;
    foundJet = false;
  }
  JetCandidate jet(bestjet_tlv);
  jet.csv					= (*data_.jetAK8_csv).at(jetIndex)           ;
  jet.tau1					= (*data_.jetAK8_tau1).at(jetIndex)          ;
  jet.tau2					= (*data_.jetAK8_tau2).at(jetIndex)          ;
  jet.tau3					= (*data_.jetAK8_tau3).at(jetIndex)          ;
  jet.prunedMass		= (*data_.jetAK8_prunedmass).at(jetIndex)    ;
  jet.prunedMassUnCorr = (*data_.jetAK8_prunedmass_unCorr).at(jetIndex)    ;
  jet.softdropMass	= (*data_.jetAK8_softdropmass).at(jetIndex)	;
  jet.mass					= (*data_.jetAK8_mass).at(jetIndex)         ;
  jet.flavor				        = -99;
  jet.rcn					= (*data_.jetAK8_che).at(jetIndex)/(*data_.jetAK8_ne).at(jetIndex);
  jet.cm = (*data_.jetAK8_cm).at(jetIndex);
  jet.nm = (*data_.jetAK8_nm).at(jetIndex);
  jet.muf = (*data_.jetAK8_muf).at(jetIndex);
  jet.phf = (*data_.jetAK8_phf).at(jetIndex);
  jet.emf = (*data_.jetAK8_emf).at(jetIndex);
  jet.nhf = (*data_.jetAK8_nhf).at(jetIndex);
  jet.chf = (*data_.jetAK8_chf).at(jetIndex);
  jet.che = (*data_.jetAK8_che).at(jetIndex);
  jet.ne = (*data_.jetAK8_ne).at(jetIndex);  
  jet.hf_hf = (*data_.jetAK8_hf_hf).at(jetIndex);
  jet.hf_emf = (*data_.jetAK8_hf_emf).at(jetIndex);
  jet.hof = (*data_.jetAK8_hof).at(jetIndex);
  jet.chm  = (*data_.jetAK8_chm).at(jetIndex);
  jet.neHadMult = (*data_.jetAK8_neHadMult).at(jetIndex);
  jet.phoMult = (*data_.jetAK8_phoMult).at(jetIndex);
  jet.nemf = (*data_.jetAK8_nemf).at(jetIndex);
  jet.cemf = (*data_.jetAK8_cemf).at(jetIndex);
  jet.charge = (*data_.jetAK8_charge).at(jetIndex);
  jet.area = (*data_.jetAK8_area).at(jetIndex);
  jet.jec = (*data_.jetAK8_jec).at(jetIndex);
  jet.pruned_jec = (*data_.jetAK8_pruned_jec).at(jetIndex);
  // float puppiCorr = getPUPPIweight( (*data_.jetAK8_puppi_pt).at(PUPPIjetIndex1) , (*data_.jetAK8_puppi_eta).at(PUPPIjetIndex1) );
  // jet.puppi_softdropMass = (*data_.jetAK8_puppi_softdrop_massUnCorr).at(PUPPIjetIndex1)*puppiCorr;
  jet.puppi_softdropMass = jetmass1;
  jet.puppi_tau1 = (*data_.jetAK8_puppi_tau1).at(PUPPIjetIndex1);
  jet.puppi_tau2 = (*data_.jetAK8_puppi_tau2).at(PUPPIjetIndex1);
  jet.puppi_tau3 = (*data_.jetAK8_puppi_tau3).at(PUPPIjetIndex1);
  jet.puppi_pt   = (*data_.jetAK8_puppi_pt).at(PUPPIjetIndex1);


  Vcand.push_back( jet );
        
  if( Channel_.find("dijet")!= std::string::npos){
    bool foundOverlap = false;
      
    if ( findMuonCandidate() || findElectronCandidate() ){
      for(int i = 0; i < abs(leptonCand_.size()); i++){
        if( bestjet2_tlv.DeltaR(leptonCand_.at(i).p4) < 0.8 ) foundOverlap = true;
      }
    }
      
    if( foundOverlap ) return false;
  
    JetCandidate secondJet(bestjet2_tlv);
    secondJet.csv					  = (*data_.jetAK8_csv).at(jetIndex)    ;
    secondJet.tau1          = (*data_.jetAK8_tau1).at(jetIndex2)  ;
    secondJet.tau2          = (*data_.jetAK8_tau2).at(jetIndex2)  ;
    secondJet.tau3          = (*data_.jetAK8_tau3).at(jetIndex2)  ;
    secondJet.prunedMass    = (*data_.jetAK8_prunedmass).at(jetIndex2)    ;
    secondJet.softdropMass  = (*data_.jetAK8_softdropmass).at(jetIndex2)  ;
    secondJet.mass          = (*data_.jetAK8_mass).at(jetIndex2)          ;
    secondJet.flavor        = -99                                         ;
    secondJet.rcn           = (*data_.jetAK8_che).at(jetIndex2)/(*data_.jetAK8_ne).at(jetIndex2);
    secondJet.cm            = (*data_.jetAK8_cm).at(jetIndex2);
    secondJet.nm            = (*data_.jetAK8_nm).at(jetIndex2);
    secondJet.muf           = (*data_.jetAK8_muf).at(jetIndex2);
    secondJet.phf           = (*data_.jetAK8_phf).at(jetIndex2);
    secondJet.emf           = (*data_.jetAK8_emf).at(jetIndex2);
    secondJet.nhf           = (*data_.jetAK8_nhf).at(jetIndex2);
    secondJet.chf           = (*data_.jetAK8_chf).at(jetIndex2);
    secondJet.che           = (*data_.jetAK8_che).at(jetIndex2);
    secondJet.ne            = (*data_.jetAK8_ne).at(jetIndex2);  
    secondJet.hf_hf         = (*data_.jetAK8_hf_hf).at(jetIndex2);
    secondJet.hf_emf        = (*data_.jetAK8_hf_emf).at(jetIndex2);
    secondJet.hof           = (*data_.jetAK8_hof).at(jetIndex2);
    secondJet.chm           = (*data_.jetAK8_chm).at(jetIndex2);
    secondJet.neHadMult     = (*data_.jetAK8_neHadMult).at(jetIndex2);
    secondJet.phoMult       = (*data_.jetAK8_phoMult).at(jetIndex2);
    secondJet.nemf          = (*data_.jetAK8_nemf).at(jetIndex2);
    secondJet.cemf          = (*data_.jetAK8_cemf).at(jetIndex2);
    secondJet.charge        = (*data_.jetAK8_charge).at(jetIndex2);
    secondJet.area          = (*data_.jetAK8_area).at(jetIndex2);
    if( PUPPIjetIndex2 != 999 ){
      // float puppiCorr = getPUPPIweight( (*data_.jetAK8_puppi_pt).at(PUPPIjetIndex2) , (*data_.jetAK8_puppi_eta).at(PUPPIjetIndex2) );
//       secondJet.puppi_softdropMass = (*data_.jetAK8_puppi_softdrop_massUnCorr).at(PUPPIjetIndex2)*puppiCorr;
      secondJet.puppi_softdropMass = jetmass2;
      secondJet.puppi_tau1 = (*data_.jetAK8_puppi_tau1).at(PUPPIjetIndex2);
      secondJet.puppi_tau2 = (*data_.jetAK8_puppi_tau2).at(PUPPIjetIndex2);
      secondJet.puppi_tau3 = (*data_.jetAK8_puppi_tau3).at(PUPPIjetIndex2);
      secondJet.puppi_pt   = (*data_.jetAK8_puppi_pt).at(PUPPIjetIndex2);
    }
    std::vector<JetCandidate> tmp;
    
    Vcand.push_back( secondJet );
  } 
  if ( (Channel_.find("dijet")!= std::string::npos && Vcand.size() < 2) || ((Channel_.find("WtagSF")!= std::string::npos && Vcand.size() < 1)) ) return false;
  else
    return true;
}
//==============================================================================================
bool ExoDiBosonAnalysis::passedTTbarSelections( TString infile ){

  bool foundLept    = false;
  bool passVeto     = false;
  bool foundMET     = false;
  bool foundW       = false;
  bool foundAK8     = false;
  bool passAK8LepDR = false;
  bool passAK8PrunedMass = false;
  bool found1b      = false;
  
  foundAMu  = 0;
  foundAEle = 0;
  
  // Find lepton (muon/electron depending on channel)
  if( findLeptonCandidate() ) foundLept = true; 
  if( !foundLept ) return false;
  nPassedFoundLept_++;
  
  Hist( "leptonPT"    )->Fill( leptonCand_.at(0).p4.Pt()	, weight_ );
  Hist( "leptonPhi"   )->Fill( leptonCand_.at(0).p4.Phi(), weight_ );
  Hist( "leptonEta"   )->Fill( leptonCand_.at(0).p4.Eta(), weight_ );
  
  
  // Veto additional loose leptons (both muons/electrons )
  if ( (foundAMu+foundAEle) > 0) return false;
  else 
    passVeto = true;
  
  nPassedVetoLep_++;
  
  // Find MET
  if( findMETCandidate() ) {
    Hist( "MET"         )->Fill(  METCand_.at(0).sumEt, weight_ );
     if( METCand_[0].p4.Pt() > METCut_ ) foundMET = true;
   }
  if( !foundMET ) return false;
  nPassedFoundMET_++;

  // reconstruct W
  if( foundLept && foundMET && findWCandidate() ){
    Hist( "Wcand_pt")->Fill(  WCand_[0].p4.Pt() );
     if( WCand_[0].p4.Pt() > 200.0 ) foundW = true;
  } 

  if( !foundW ) return false;   
  nPassedFoundW_++;
  // Find AK8 W-jet candidate
  if(findJetCandidates( infile )){
    foundAK8 = true;
    // if( leptonCand_[0].p4.DeltaR(Vcand.at(0).p4) > 1.0 ) passAK8LepDR = true;
    if( Vcand.at(0).p4.Pt() >= JetPtCutTight_	) passAK8LepDR = true;
    float groomedMass = Vcand.at(0).prunedMass;
    if(usePuppiSD_) groomedMass = Vcand.at(0).puppi_softdropMass;
    if( groomedMass >= mWLow_ && groomedMass <= mZHigh_ ) passAK8PrunedMass = true;
  }
  
  if( !foundAK8 ) return false;
  nPassedFoundJet_++;
 
  if( !passAK8LepDR ) return false;   
  nPassedLepJetDR_++;
  
  if( !passAK8PrunedMass ) return false;   
  nPassedJetPrunedMass_++;
  

  // Find b-tagged AK4 jet
  findAK4Jets();
  bool najetCut = false; 
  int najet = 0;
  for( unsigned int j = 0; j < abs(AK4jetCand_.size()); j++ ){
     if( AK4jetCand_[j].csv > 0.800 ) najet++;
  }
  
  if( najet  > 0 ) found1b = true;
  if( !found1b ) return false;   
  nPassed1bTag_++;
  
  if(foundLept && passVeto && foundMET && foundW && foundAK8 && passAK8LepDR && passAK8PrunedMass && found1b) return true;
 
  else
    return false;
}

//==============================================================================================
bool ExoDiBosonAnalysis::findLeptonCandidate( void ){

  if( Channel_.find("el") != std::string::npos ) return findElectronCandidate();
  else if( Channel_.find("mu") != std::string::npos ) return findMuonCandidate();
  else return false;
   
}

//==============================================================================================
bool ExoDiBosonAnalysis::findMuonCandidate( void ){
  
  foundAEle = 0;
  foundAMu = 0;
   
  TLorentzVector TLV;
  bool foundLept = false;
  double ptMu = -999;
  int muIndex = 999;
  double scale = 0.;
  double newpt = 0.;
  double scale_ = 0.;
  for( int l = 0; l < data_.mu_N; ++l ){
    // if( !isLowMass && (*data_.mu_isHighPtMuon)[l] != 1 ) continue;
    // if(  isLowMass && (*data_.mu_isTightMuon)[l] != 1 ) continue;
    if( (*data_.mu_isTightMuon)[l] != 1 ) continue;
    //if( (*data_.mu_isPFMuon)[l] != 1 ) continue;
    scale = getMuonScale((*data_.mu_pt)[l]);
    newpt = (*data_.mu_pt)[l]+scale;
    if( (*data_.mu_trackIso)[l]/newpt >= 0.1 ) continue;
    if( newpt <= muPtCut_ ) continue;
    if( fabs((*data_.mu_eta)[l]) >= muEtaCut_ ) continue;
    //if( fabs((*data_.mu_eta)[l]) > 1.2 && newpt > 500 ) continue;
    foundLept = true;
    if( newpt > ptMu ){  
      ptMu = newpt;
      TLV.SetPtEtaPhiE( newpt, (*data_.mu_eta)[l], (*data_.mu_phi)[l], (*data_.mu_e)[l]+scale );  
      muIndex = l;
      scale_ = scale;
    }      
  }
   
   if( foundLept ){
     LeptonCandidate muCand(TLV);
     muCand.iso = (*data_.mu_trackIso)[muIndex]/ptMu;
     // muCand.scale = scale_;
 //     muCand.isGlobalMuon = (*data_.mu_isGlobalMuon)[muIndex];
 //     muCand.globalHits = (*data_.mu_globalHits)[muIndex];
 //     muCand.matchedStations = (*data_.mu_matchedStations)[muIndex];
 //     muCand.bestTrack_ptErrRel = (*data_.mu_bestTrack_ptErr)[muIndex]/(*data_.mu_bestTrack_pt)[muIndex];
 //     muCand.d0 = (*data_.mu_d0)[muIndex];
 //     //muCand.dz = (*data_.mu_dz)[muIndex];
 //     muCand.pixelHits = (*data_.mu_pixelHits)[muIndex];
 //     muCand.trackerHits = (*data_.mu_trackerHits)[muIndex];
     leptonCand_.push_back( muCand );
   }
   
   scale = 0.;
   for( int l = 0; l < data_.mu_N; ++l ){
      if( muIndex == 999 || l == muIndex ) continue;
      // if( !isLowMass && (*data_.mu_isHighPtMuon)[l] != 1 ) continue;
      // if(  isLowMass && (*data_.mu_isLooseMuon)[l] != 1 ) continue;
      if( (*data_.mu_isLooseMuon)[l] != 1 ) continue;
      scale = getMuonScale((*data_.mu_pt)[l]);
      newpt = (*data_.mu_pt)[l]+scale;
      if( (*data_.mu_trackIso)[l]/newpt >= 0.1 ) continue;
      if( newpt <= AleptPtCut_ ) continue;
      if( fabs((*data_.mu_eta)[l]) >= AleptEtaCut_ ) continue;
      foundAMu++;
   }
   
   for( int l = 0; l < data_.el_N; ++l ){
      // if( !isLowMass && (*data_.el_isHEEP)[l] != 1 ) continue;
      // if( isLowMass && (*data_.el_isVetoElectron)[l] != 1 ) continue;
      if( (*data_.el_isVetoElectron)[l] != 1 ) continue;
      if( (*data_.el_pt)[l] <= 30. ) continue;
      if( fabs((*data_.el_eta)[l]) >= 1.4442 && fabs((*data_.el_eta)[l]) <= 1.566 ) continue;
      if( fabs((*data_.el_eta)[l]) >= 2.5 ) continue;
      foundAEle++;
   }
   
   return foundLept;

   //if( (foundAMu+foundAEle)<1 && foundLept ) return true;
   //else return false;
   
}
//==============================================================================================
double ExoDiBosonAnalysis::getMuonScale( double oldpt ){
  int ScaleMuonUpDown_ = 0;

   double scale = 0.;
   
   if( oldpt < 200. ) scale = (ScaleMuonUpDown_)*0.2*oldpt/100.;
   else if( oldpt >= 200. ) scale = (ScaleMuonUpDown_)*5.*oldpt/100.;	
   
   return scale;
      
}
//==============================================================================================
bool ExoDiBosonAnalysis::findElectronCandidate( void ){

   foundAMu = 0;
   foundAEle = 0;

   TLorentzVector TLV;
   bool foundEle = false;
   double ptEle = -999;
   int eleIndex = 999;
   for( int l = 0; l < data_.el_N; ++l ){
      if( (*data_.el_pt)[l] <= elePtCut_ ) continue;
      if( fabs((*data_.el_eta)[l]) >= 1.4442 && fabs((*data_.el_eta)[l]) <= 1.566 ) continue;
      if( fabs((*data_.el_eta)[l]) >= eleEtaCut_ ) continue;
      if( (*data_.el_isHEEP)[l] != 1 ) continue;
      // if(  isLowMass && (*data_.el_isTightElectron)[l] != 1 ) continue;
      
      foundEle = true;
      if( (*data_.el_pt)[l] > ptEle ){   
         ptEle = (*data_.el_pt)[l];
         TLV.SetPtEtaPhiE( (*data_.el_pt)[l], (*data_.el_eta)[l], (*data_.el_phi)[l], (*data_.el_e)[l] );         
         eleIndex = l;
      }
   }

   if( foundEle )
    leptonCand_.push_back( LeptonCandidate( TLV ) );
   
   for( int l = 0; l < data_.el_N; ++l ){
      if( eleIndex == 999 || l == eleIndex ) continue;
      // if( !isLowMass && (*data_.el_isHEEP)[l] != 1 ) continue;
      if( (*data_.el_isVetoElectron)[l] != 1 ) continue;
      if( (*data_.el_pt)[l] <= 30. ) continue;
      if( fabs((*data_.el_eta)[l]) >= 1.4442 && fabs((*data_.el_eta)[l]) <= 1.566 ) continue;
      if( fabs((*data_.el_eta)[l]) >= 2.5 ) continue;
      foundAEle++;
   }   
   for( int l = 0; l < data_.mu_N; ++l ){
     // if( !isLowMass && (*data_.mu_isHighPtMuon)[l] != 1 ) continue;
     if(  (*data_.mu_isLooseMuon)[l] != 1 ) continue;
      if( (*data_.mu_trackIso)[l]/(*data_.mu_pt)[l] >= 0.1 ) continue;
      if( (*data_.mu_pt)[l] <= 20. ) continue;
      if( fabs((*data_.mu_eta)[l]) >= 2.4 ) continue;
      foundAMu++;
   }
   return foundEle;
 }

//==============================================================================================
void ExoDiBosonAnalysis::findAK4Jets( void ){
  TLorentzVector jet;
  for( int j = 0; j < data_.njetsAK4; ++j ){ 
     jet.SetPtEtaPhiE( (*data_.jetAK4_pt)[j], (*data_.jetAK4_eta)[j], (*data_.jetAK4_phi)[j], (*data_.jetAK4_e)[j] );
     if( jet.DeltaR(Vcand[0].p4) < 0.8 ) continue;
     if( (*data_.jetAK4_IDLoose)[j] != 1 ) continue;
     if( (*data_.jetAK4_pt)[j] <= JetPtCutLoose_ ) continue;
     if( fabs((*data_.jetAK4_eta)[j]) >= JetEtaCut_ ) continue;
     if( jet.DeltaR(leptonCand_[0].p4) < 0.3 ) continue;
     JetCandidate Ajet(jet);
     Ajet.csv = (*data_.jetAK4_csv)[j];
     // Ajet.flavor = 0;
     // if( runOnMC_ ) Ajet.flavor = abs((*data_.jetAK4_flavor)[j]);
     AK4jetCand_.push_back(Ajet);
  }
}

//==============================================================================================
bool ExoDiBosonAnalysis::findMETCandidate( void ){
  
  TLorentzVector TLV;
  bool foundMET = false;
  if( (*data_.MET_et)[0] > 0. ){
  
     TLV.SetPtEtaPhiE( (*data_.MET_et)[0], 0., (*data_.MET_phi)[0], 0. );
                
     METCandidate metC(TLV);
     metC.sumEt = (*data_.MET_sumEt)[0];
     METCand_.push_back( METCandidate( TLV ) );
     foundMET = true;
     
  }
  
  return foundMET;
   
}

//==============================================================================================
bool ExoDiBosonAnalysis::findWCandidate( void ){

  TLorentzVector TLV;
  bool foundW = false;
  if( (METCand_[0].p4+leptonCand_[0].p4).Pt() > 0. ){
     foundW = true;
     TLV = METCand_[0].p4+leptonCand_[0].p4;
     WCand_.push_back( TLV );
  }
  
  return foundW;
}
//==============================================================================================
bool ExoDiBosonAnalysis::findHadronicWCandidate( void ){

  TLorentzVector TLV,TLV1, TLV2;
  bool foundW = false;
  Double_t deltaWmassMin = 999.;

  for(int i=0; i < abs(AK4jetCand_.size()); i++ ){
    if (AK4jetCand_.at(i).p4.Pt() == Leptonicb_.at(0).p4.Pt() || AK4jetCand_.at(i).p4.Pt() <= 0. ) continue;
    for(int j=0; j != i && j < abs(AK4jetCand_.size()); j++ ){
      Double_t deltaWmass = fabs(pdgMw - ((AK4jetCand_.at(i).p4+ AK4jetCand_.at(j).p4).M()));
      if( deltaWmass < deltaWmassMin ){
        deltaWmassMin = deltaWmass;
        foundW = true;
        TLV = AK4jetCand_.at(i).p4+AK4jetCand_.at(j).p4;
        TLV1 = AK4jetCand_.at(i).p4;
        TLV2 = AK4jetCand_.at(j).p4;
      }
    }
  }
  HadronicJ_.push_back( TLV1 );
  HadronicJ_.push_back( TLV2 );
  Hist( "DeltaRJJ")->Fill ( HadronicJ_.at(1).p4.DeltaR(HadronicJ_.at(0).p4) , weight_	);
	
  WCand_.push_back( TLV );
  return foundW;

}
//==============================================================================================
void ExoDiBosonAnalysis::findExoCandidate( void ){

   TLorentzVector p4nu = getp4Nu();      
   MWW = (p4nu + leptonCand_[0].p4 + Vcand[0].p4).M();
   WMass = (p4nu + leptonCand_[0].p4).M();
   
   // TLorentzVector p4nu2 = getp4NuMethod2();
//    //Hist( "pzNu" )->Fill(p4nu2.Pz());
//
//    //Hist( "NuLeptInvMass"  )->Fill( (p4nu2 + leptonCand_[0].p4).M() );
//    MWWmethod2 = (p4nu2 + leptonCand_[0].p4 + fatJetCand_[0].p4).M();
//    WMassMethod2 = (p4nu2 + leptonCand_[0].p4).M();

   return;
            
}
//==============================================================================================
TLorentzVector ExoDiBosonAnalysis::getp4Nu( void ){

  return Utilities::NuMomentum( leptonCand_.at(0).p4.Px(), leptonCand_.at(0).p4.Py(), leptonCand_.at(0).p4.Pz(), leptonCand_.at(0).p4.Pt(), leptonCand_.at(0).p4.E(), METCand_.at(0).p4.Px(), METCand_.at(0).p4.Py() );   
   
}

//==============================================================================================
TLorentzVector ExoDiBosonAnalysis::getp4NuMethod2( void ){

  double E_l  = leptonCand_.at(0).p4.E();
  double m_l  = leptonCand_.at(0).p4.M();
  double px_l = leptonCand_.at(0).p4.Px();
  double py_l = leptonCand_.at(0).p4.Py();
  double pz_l = leptonCand_.at(0).p4.Pz();

  //std::cout << "lep: px = " << px_l << " - py = " << py_l << " - pz = " << pz_l << " - pt = " << TMath::Sqrt(px_l*px_l + py_l*py_l);
  //std::cout << " - pt LTV = " << leptonCand_.at(0).p4.Pt() << " - mass = " << m_l << std::endl;
      
  double px_v = METCand_.at(0).p4.Px();
  double py_v = METCand_.at(0).p4.Py();
   
  //std::cout << "MET: metx = " << px_v << " - mety = " << py_v << " - et = " << TMath::Sqrt(px_v*px_v + py_v*py_v);
  //std::cout << " - et TLV = " << METCand_.at(0).p4.Pt() << std::endl;
   
  double m_W = 80.4;
   
  double a = m_W*m_W - m_l*m_l + 2*px_l*px_v + 2*py_l*py_v;
  double A = 4*(E_l*E_l - pz_l*pz_l);
  double B = (-4)*a*pz_l;
  double C = 4*E_l*E_l*(px_v*px_v + py_v*py_v) - a*a;
  double Delta = B*B - 4*A*C;
   
  /*Hist( "Discriminant")->Fill(Delta/1e15);
  Hist( "A"           )->Fill(A/1e+05);
  Hist( "B"           )->Fill(B/1e+07);
  Hist( "C"           )->Fill(C/1e+09);
  Hist( "a"           )->Fill(a/1e+04);*/
   
  double pz_v_1 = -9999;
  double pz_v_2 = -9999;
  double pz_v   = -9999;
      
  if( Delta > 0 ){
    pz_v_1 = ( -B + TMath::Sqrt(Delta) )/( 2*A );
    pz_v_2 = ( -B - TMath::Sqrt(Delta) )/( 2*A ); 
    if( fabs(pz_v_1) <= fabs(pz_v_2) ) pz_v = pz_v_1;
    else pz_v = pz_v_2;     
  }
  else if ( Delta <= 0 )
    pz_v = -B/(2*A);

  TLorentzVector v; v.SetPxPyPzE(px_v,py_v,pz_v,fabs(TMath::Sqrt(pz_v*pz_v + py_v*py_v + px_v*px_v)));
  v.SetPz(pz_v);
  v.SetPx(px_v);
  v.SetPy(py_v);
  v.SetE(fabs(TMath::Sqrt(pz_v*pz_v + py_v*py_v + px_v*px_v)));  

  /*if( Delta > 0){
  Hist( "NuLeptInvMassDeltap"  )->Fill( (v + leptonCand_.at(0).p4).M() );
  Hist( "DiBosonInvMassDeltap" )->Fill( (v + leptonCand_.at(0).p4 + WCand_.at(0).p4).M() );
  }
  else if( Delta <= 0 ){
  Hist( "NuLeptInvMassDeltam"  )->Fill( (v + leptonCand_.at(0).p4).M() );
  Hist( "DiBosonInvMassDeltam" )->Fill( (v + leptonCand_.at(0).p4 + WCand_.at(0).p4).M() );   
  }*/
   
  //std::cout << "Method 2: " << Delta << std::endl;
   
  return v;
      
}


//==============================================================================================
void ExoDiBosonAnalysis::fillHistos( std::string Channel ){
  
  std::string Channel_ = Channel;
  
  if( Channel_.find("VVdijet")!=std::string::npos || Channel_.find("qVdijet")!=std::string::npos ){
    if ( Vcand.size() < 2 ) return;
    Hist( "VVdeltaEta"        )-> Fill( fabs( Vcand.at(0).p4.Eta()  - Vcand.at(1).p4.Eta() ) , weight_ ); 
    Hist( "DiBosonInvMass"    )->Fill( (Vcand.at(0).p4 + Vcand.at(1).p4).M(), weight_ );
    
    for(int i = 0; i < abs(Vcand.size());i++){
      if( Channel_ == "qVdijet" && i != jetINDX) continue;
      Hist( "VcandTau21"        )->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1,weight_ );
      Hist( "VcandPrunedMass"   )->Fill( Vcand.at(i).prunedMass, weight_ );
      Hist( "VcandSoftdropMass" )->Fill( Vcand.at(i).softdropMass, weight_ );
      Hist( "VcandPt"           )->Fill( Vcand.at(i).p4.Pt() , weight_ );
      Hist( "VcandEta"          )->Fill( Vcand.at(i).p4.Eta(), weight_ );
      Hist( "VcandPhi"          )->Fill( Vcand.at(i).p4.Phi(), weight_ );
      Hist( "VcandMass"         )->Fill( Vcand.at(i).mass , weight_ );
    }
    

    // if ( Vcand.size() >= 2 ) {
    //       unsigned int tag = gRandom->Integer(1);
    //       unsigned int probe = 1;
    //       if ( tag == 1 ) probe = 0;
    //
    //       bool tagged = Vcand.at(tag).tau2/Vcand.at(tag).tau1 < 0.6 && Vcand.at(tag).softdropMass > 65. && Vcand.at(tag).softdropMass < 105.;
    //       hvv_pred->Accumulate( (Vcand.at(0).p4 + Vcand.at(1).p4).M(), Vcand.at(probe).rho, tagged, weight_);
    //       // std::cout<<"Using SoftdropSubjetCand_[probe][0] with rho == "<<SoftdropSubjetCand_[probe][0].rho<<std::endl;
    //       // hvv_pred->Accumulate( (SoftdropSubjetCand_[probe][0].p4 + SoftdropSubjetCand_[probe][1].p4).M(),SoftdropSubjetCand_[probe][0].rho, tagged, weight_);
    //     }

}
        
  else if(Channel_ == "SFmuJets"){
    
    float MET = (*data_.MET_et).at(0);
    Hist( "leptonPT"    )->Fill( leptonCand_.at(0).p4.Pt()	, weight_ );
    Hist( "leptonPhi"   )->Fill( leptonCand_.at(0).p4.Phi(), weight_ );
    Hist( "leptonEta"   )->Fill( leptonCand_.at(0).p4.Eta(), weight_ );
    Hist( "MET"         )->Fill(MET, weight_ );
    Hist( "nbTagAK4"    )->Fill ( nBTags );
    Hist( "AK4jetPt"    )->Fill( AK4jetCand_.at(0).p4.Pt(), weight_ );
    Hist( "AK4jetCSV"   )->Fill( AK4jetCand_.at(0).csv		, weight_ );
    Hist( "AK4jetMass"  )->Fill( AK4jetCand_.at(0).p4.M()	, weight_ );
  }
   
}


       			        
//==============================================================================================
void ExoDiBosonAnalysis::EndInputData( const SInputData& ) throw( SError ) {
		
  if( Channel_.find("VVdijet")!=std::string::npos || Channel_.find("qVdijet")!=std::string::npos ){

    printCutFlow();
    theHistosManager_->formatHistos(Channel_);

    //   Hist( "genEvents"               )->SetBinContent(1,genEvents_              );
    Hist( "sumGenWeight" )->SetBinContent(1,nSumGenWeights_);
    Hist( "nEvents"               )->SetBinContent(1,nEvents_*weight_               );
    Hist( "nPassedJSON"           )->SetBinContent(1,nPassedJSON_*weight_           );
    Hist( "nPassedFilter"         )->SetBinContent(1,nPassedFilters_*weight_        );
    Hist( "nPassedTrigger"        )->SetBinContent(1,nPassedTrigger_*weight_        );
    Hist( "nPassedFoundJets"      )->SetBinContent(1,nPassedFoundJets_*weight_      );
    Hist( "nPassedJetsDEta"       )->SetBinContent(1,nPassedJetsDEta_*weight_       );
    Hist( "nPassedMjj"            )->SetBinContent(1,nPassedMjj_*weight_            );
    Hist( "nPassedTau21Cut"       )->SetBinContent(1,nPassedTau21Cut_*weight_       );
    Hist( "nPassedPrunedJetMass"  )->SetBinContent(1,nPassedJetPrunedMass_*weight_  );
  }
  else if ( Channel_.find("WtagSF") != std::string::npos ){

    printCutFlow();
    theHistosManager_->formatHistos(Channel_);
    Hist( "nNopuppi")->SetBinContent(1,nNopuppi_*weight_);
    Hist( "sumGenWeight" )->SetBinContent(1,nSumGenWeights_);
    Hist( "nEvents" )->SetBinContent(1,nEvents_*weight_        );
    Hist( "nPassedJSON"     )->SetBinContent(1,nPassedJSON_*weight_           );
    Hist( "nPassedFilter"   )->SetBinContent(1,nPassedFilters_*weight_      );
    Hist( "nPassedTrigger"  )->SetBinContent(1,nPassedTrigger_*weight_    );
    Hist( "nPassedFoundLept")->SetBinContent(1,nPassedFoundLept_*weight_  );
    Hist( "nPassedVetoLep"  )->SetBinContent(1,nPassedVetoLep_*weight_    );
    Hist( "nPassedFoundMET" )->SetBinContent(1,nPassedFoundMET_*weight_   );
    Hist( "nPassedFoundW"   )->SetBinContent(1,nPassedFoundW_*weight_    );
    Hist( "nPassedFoundJet" )->SetBinContent(1,nPassedFoundJet_*weight_  );
    Hist( "nPassedLepJetDR" )->SetBinContent(1,nPassedLepJetDR_*weight_  );
    Hist( "nPassedPrunedJetMass"  )->SetBinContent(1,nPassedJetPrunedMass_*weight_  );
    Hist( "nPassed1bTag"    )->SetBinContent(1,nPassed1bTag_*weight_     );

  }
  // hvv_pred->SetCalculatedErrors();
  
  return;

}

//==============================================================================================
void ExoDiBosonAnalysis::EndCycle() throw( SError ) {

  return;

}

//==============================================================================================
void ExoDiBosonAnalysis::printCutFlow( void ) {
	
  if( Channel_.find("VVdijet")!=std::string::npos || Channel_.find("qVdijet")!=std::string::npos ){
    std::cout << std::endl;
    
    
    
    double eff = (double)nPassedTau21Cut_/nEvents_;
    double eff_wpdf;
    std::cout << "############ Cut flow: ############" << std::endl;	
    std::cout << "number of events                                " << nEvents_ << std::endl;
    std::cout << "passed JSON                                     " << nPassedJSON_       << " --- eff = " << (double)nPassedJSON_/nEvents_ << std::endl; 
    std::cout << "passed filter                                   " << nPassedFilters_    << " --- eff = " << (double)nPassedFilters_/nEvents_ << std::endl; 
    std::cout << "passed trigger                                  " << nPassedTrigger_    << " --- eff = " << (double)nPassedTrigger_/nEvents_ << std::endl; 
    std::cout << "found at least 2 jets with pT > 200/ eta < 2.4  " << nPassedFoundJets_  << " --- eff = " << (double)nPassedFoundJets_/nEvents_ << std::endl;
    
    std::cout << "Passed dEta(j,j) < 1.3                          " << nPassedJetsDEta_   << " --- eff = " << (double)nPassedJetsDEta_/nEvents_ << std::endl;
    std::cout << "Passed M(j,j) cut                               " << nPassedMjj_        << " --- eff = " << (double)nPassedMjj_/nEvents_ << std::endl;
    std::cout << "Passed jet pruned mass cut                      " << nPassedJetPrunedMass_ << " --- eff = " << (double)nPassedJetPrunedMass_/nEvents_ << std::endl;
    std::cout << "Passed tau 21 cut                               " << nPassedTau21Cut_ << " --- eff = " << eff << std::endl;
    std::cout << std::endl;
    std::cout << "largest weights for this sample : "<<std::endl;
    std::cout << " wmax_     : "<< wmax_      << std::endl;
    std::cout << " wmaxpu_   : "<< wmaxpu_    << std::endl;
    std::cout << " wmaxlumi_ : "<< wmaxlumi_  << std::endl;
    std::cout << " wmaxpt_   : "<< wmaxpt_    << std::endl;
    std::cout << " wmaxhlt_  : "<< wmaxhlt_   << std::endl;
    std::cout << " wmaxbtag_ : "<< wmaxbtag_  << std::endl;
    std::cout << " wmaxgen_  : "<< wmaxgen_   << std::endl;
    std::cout << " sum of gen weights : "<< nSumGenWeights_ << std::endl;
    
    std::cout << "############ PDF reweighting #############" << std::endl;
    std::cout << "reweighted to PDFSET : " << PDFSET_ << std::endl;
    for(unsigned int i=0; i< nEvents_wPDF_.size(); i++)
    {
        eff_wpdf = (double)nPassed_wPDF_.at(i)/nEvents_wPDF_.at(i);
    std::cout << "number of events : " << nEvents_wPDF_.at(i) << std::endl;
    std::cout << "passed all cuts  : " << nPassed_wPDF_.at(i) << std::endl;
    std::cout << "efficiency       : " << eff_wpdf << std::endl;
    std::cout << "rel. diff.       : " << (eff -  eff_wpdf)/eff*100 << std::endl;
    }
    
    if(wPDFname_.find("none")==std::string::npos)
    {
    ofstream myfile;
    myfile.open (wPDFname_+".txt");
    myfile << "############ PDF reweighting #############" << std::endl;
    for(unsigned int i=0;i<nEvents_wPDF_.size();i++)
    {
      myfile << "nset : " << i << std::endl;
      myfile << "N : " << nEvents_wPDF_.at(i) << std::endl;
      myfile << "N passed : " << nPassed_wPDF_.at(i) << std::endl;
    }
    
    }
  //   std::cout << "Passed jet pruned mass cut NOMINAL (after dEta and Mjj)" << nPassedJetPrunedMass_ << " --- eff = " << (double)nPassedJetPrunedMass_/(double)nPassedJetsDEta_ << std::endl;
  //   std::cout << "Passed tau 21 cut(after dEta and Mjj)                   " << nPassedTau21Cut_ << " --- eff = " << (double)nPassedTau21Cut_/(double)nPassedJetsDEta_ << std::endl;
  //   std::cout << "Passed jet pruned mass cut NOMINAL (after Mjj)" << nPassedJetPrunedMass_ << " --- eff = " << (double)nPassedJetPrunedMass_/(double)nPassedMjj_ << std::endl;
  //   std::cout << "Passed tau 21 cut(after  Mjj)                   " << nPassedTau21Cut_ << " --- eff = " << (double)nPassedTau21Cut_/(double)nPassedMjj_ << std::endl;
  }
  
  else if (Channel_.find("WtagSF") != std::string::npos){
    
    std::cout << "number of events		                            " << nEvents_ << std::endl;
    std::cout << "passed JSON                                     " << nPassedJSON_       << " --- eff = " << (double)nPassedJSON_/nEvents_ << std::endl; 
    std::cout << "passed trigger        " << nPassedTrigger_        << " --- eff = " << (double)nPassedTrigger_/nEvents_ << std::endl; 
    std::cout << "passed filter HBHE    " << nPassedFilter_HBHE_    << " --- eff = " << (double)nPassedFilter_HBHE_/nPassedTrigger_ << std::endl; 
    // std::cout << "passed filter CSCHalo2015 " << nPassedFilter_CSCHalo_ << " --- eff = " << (double)nPassedFilter_CSCTightHalo2015_/nPassedTrigger_ << std::endl;
    std::cout << "passed filter EEBadSc " << nPassedFilter_EEBadSc_ << " --- eff = " << (double)nPassedFilter_EEBadSc_/nPassedTrigger_ << std::endl; 
    std::cout << "passed filter GoodPV  " << nPassedGoodPVFilter_   << " --- eff = " << (double)nPassedGoodPVFilter_/nPassedTrigger_ << std::endl; 
    std::cout << "passed filter         " << nPassedFilters_        << " --- eff = " << (double)nPassedFilters_/nPassedTrigger_ << std::endl; 
    
    std::cout << "Passed found lep      " << nPassedFoundLept_      << " --- eff (relative, after pass filter)  = " << (double)nPassedFoundLept_/nEvents_     << " (" <<(double)nPassedFoundLept_/nPassedFilters_     <<") "<< std::endl;
    std::cout << "Passed VETO lep       " << nPassedVetoLep_        << " --- eff (relative, after pass filter)  = " << (double)nPassedVetoLep_/nEvents_       << " (" <<(double)nPassedVetoLep_/nPassedFilters_       <<") "<< std::endl;
    std::cout << "Passed found MET      " << nPassedFoundMET_       << " --- eff (relative, after pass filter)  = " << (double)nPassedFoundMET_/nEvents_      << " (" <<(double)nPassedFoundMET_/nPassedFilters_      <<") "<< std::endl;
    std::cout << "Passed found W        " << nPassedFoundW_         << " --- eff (relative, after pass filter)  = " << (double)nPassedFoundW_/nEvents_        << " (" <<(double)nPassedFoundW_/nPassedFilters_        <<") "<< std::endl;
    std::cout << "Passed found AK8      " << nPassedFoundJet_       << " --- eff (relative, after pass filter)  = " << (double)nPassedFoundJet_/nEvents_      << " (" <<(double)nPassedFoundJet_/nPassedFilters_      <<") "<< std::endl;
    std::cout << "Passed tight pT cut   " << nPassedLepJetDR_       << " --- eff (relative, after pass filter)  = " << (double)nPassedLepJetDR_/nEvents_      << " (" <<(double)nPassedLepJetDR_/nPassedFilters_      <<") "<< std::endl;
    std::cout << "Passed pruned M cut   " << nPassedJetPrunedMass_  << " --- eff (relative, after pass filter)  = " << (double)nPassedJetPrunedMass_/nEvents_ << " (" <<(double)nPassedJetPrunedMass_/nPassedFilters_ <<") "<< std::endl;
    std::cout << "Passed found b-tag    " << nPassed1bTag_          << " --- eff (relative, after pass filter)  = " << (double)nPassed1bTag_/nEvents_         << " (" <<(double)nPassed1bTag_/nPassedFilters_         <<") "<< std::endl;

  }
  
  
   
  std::cout << std::endl; 
   
}	
//==============================================================================================
//Efficiency studies============================================================================
//==============================================================================================


void ExoDiBosonAnalysis::doJetTriggerEfficiency( void ){
  
  float groomedMass_jet1 = Vcand.at(0).prunedMass;
  float groomedMass_jet2 = Vcand.at(1).prunedMass;

  
  if( usePuppiSD_ ){
    groomedMass_jet1 = Vcand.at(0).puppi_softdropMass;
    groomedMass_jet2 = Vcand.at(1).puppi_softdropMass;
  }
  Mjj = ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M();
  
  int fill =0;
  bool recoverL1 =false;

  
  for( std::map<std::string,bool>::iterator it2 = (data_.HLT_isFired)->begin(); it2 != (data_.HLT_isFired)->end(); it2++){
      std::string iter = it2->first;
      bool value = it2->second;
  if( ((iter).find("HLT_PFHT500")!= std::string::npos && value) 
          || ((iter).find("HLT_AK8PFJet450")!= std::string::npos && value) 
          || ((iter).find("HLT_AK8PFJet500")!= std::string::npos && value)
           || ((iter).find("HLT_PFJet450")!=std::string::npos && value) ){ recoverL1= true;}
        
  }
   //recoverL1=false;
   //std::cout << "passed L1 " << recoverL1 << std::endl;

  for( std::map<std::string,bool>::iterator it = (data_.HLT_isFired)->begin(); it != (data_.HLT_isFired)->end(); it++){
    
    std::string trigName = it->first;
    bool decision = it->second;
    //std::cout << trigName <<std::endl;
    // ============== for testing of the triggers in a single muon dataset: no baseline triggers sould be applied ===========================================
    //  for simplicity we still want to reuse the same histos (since the names are needen in the plotting script)
    //if( !((trigName).find("HLT_Mu50") != std::string::npos && decision) ) continue;
    if( !(((trigName).find("PFHT650_v") != std::string::npos && decision) or ((trigName).find("HLT_PFJet320_v") != std::string::npos && decision)) ) continue;
    // Start no tag
    fill+=1;
    if(fill==1)
    {
    Hist( "PFHT650_noTag" )->Fill( Mjj);

    
    bool passedHT = false;
    bool passedSubstructure = false;
    bool passedALL = false;
    bool passedHT800 =false;
    bool passedHT650MJJ900=false;
    bool passedHT650MJJ950=false;
    bool passedHT700Trim =false;
        
    for( std::map<std::string,bool>::iterator it2 = (data_.HLT_isFired)->begin(); it2 != (data_.HLT_isFired)->end(); it2++){
      std::string iter = it2->first;
      bool value = it2->second;
    
      
      if( ((iter).find("PFHT800")!= std::string::npos && value) 
          || ((iter).find("PFHT900")!= std::string::npos && value) 
          || ((iter).find("PFJet450")!= std::string::npos && value)){passedHT800 = true;}
      if( (iter).find("PFHT650_WideJetMJJ950DEtaJJ1p5") != std::string::npos && value ) passedHT650MJJ950 =true; 
      if( (iter).find("PFHT650_WideJetMJJ900DEtaJJ1p5") != std::string::npos && value ) passedHT650MJJ900 = true; 
      if( ((iter).find("PFHT800")                       != std::string::npos && value)
          || ((iter).find("PFHT900")                    != std::string::npos && value) 
          || ((iter).find("PFJet450")                   != std::string::npos && value)
        ||((iter).find("PFHT650_WideJetMJJ900DEtaJJ1p5")!= std::string::npos && value)
        ||((iter).find("PFHT650_WideJetMJJ950DEtaJJ1p5")!= std::string::npos && value)) passedHT = true;
          
      if( ((iter).find("PFHT800")                       != std::string::npos && value)
          || ((iter).find("PFHT900")                      != std::string::npos && value) 
          || ((iter).find("PFJet450")                   != std::string::npos && value)
          ||((iter).find("PFHT650_WideJetMJJ900DEtaJJ1p5")!= std::string::npos && value)
          ||((iter).find("PFHT650_WideJetMJJ950DEtaJJ1p5")!= std::string::npos && value)
          ||((iter).find("AK8PFJet360_TrimMass30")        != std::string::npos && value)
          ||((iter).find("AK8PFHT700_TrimR0p1PT0p03Mass50")!= std::string::npos && value)) passedALL = true;

      //SUBSTRUCTURE TRIGGERS
      if( (iter).find("AK8PFJet360_TrimMass30")                    != std::string::npos && value ) Hist( "PFJet360_Trim_noTag" ) ->Fill( Mjj);
      if( (iter).find("AK8PFHT700_TrimR0p1PT0p03Mass50")           != std::string::npos && value ) passedHT700Trim = true; 
      if( (iter).find("AK8DiPFJet280_200_TrimMass30_BTagCSV0p45")  != std::string::npos && value ) Hist( "DiPFJet280_200_TrimMass30_noTag" )->Fill( Mjj);
      if( ((iter).find("AK8PFJet360_TrimMass30")                   != std::string::npos && value)
        || ((iter).find("AK8PFHT700_TrimR0p1PT0p03Mass50")         != std::string::npos && value) ) passedSubstructure = true;
    }
//     if( passedHT )          Hist( "HT_noTag" )->Fill( Mjj);
//     if( passedSubstructure )Hist( "Substructure_noTag" )->Fill( Mjj);
//     if( passedALL )         Hist( "ALL_noTag" )->Fill( Mjj);
//     if(passedHT800) {Hist( "HT800_noTag" )->Fill( Mjj);}
//     if(passedHT650MJJ950) Hist( "HT650_MJJ950_noTag" )->Fill( Mjj);
//     if(passedHT650MJJ900) Hist( "HT650_MJJ900_noTag" )->Fill( Mjj);


      //================== test for run H to get rid of L1 inefficiency ========================================================
      // do OR with: HLT_PFJet450 (or PFJet500) HLT_AK8PFJet450 (or AK8PFJet500) HLT_CaloJet500_NoJetID
        
    if( passedHT || recoverL1 )          Hist( "HT_noTag" )->Fill( Mjj);
    if( passedSubstructure ||recoverL1 )Hist( "Substructure_noTag" )->Fill( Mjj);
    if( passedALL || recoverL1)         Hist( "ALL_noTag" )->Fill( Mjj);
    if(passedHT800 || recoverL1) {Hist( "HT800_noTag" )->Fill( Mjj);}
    if(passedHT650MJJ950 || recoverL1) Hist( "HT650_MJJ950_noTag" )->Fill( Mjj);
    if(passedHT650MJJ900 || recoverL1) Hist( "HT650_MJJ900_noTag" )->Fill( Mjj);
    if(passedHT700Trim || recoverL1) Hist( "HT700_Trim_noTag" )    ->Fill( Mjj);
      //=========================================================================================================================
    
    //End no tag

    // Start single tag
    if( (groomedMass_jet1 > mWLow_ && groomedMass_jet1 <= mZHigh_) ||
    (groomedMass_jet2 > mWLow_ && groomedMass_jet2 <= mZHigh_ )){
          
      Hist( "PFHT650" )->Fill( Mjj);

      bool passedHT = false;
      bool passedSubstructure = false;
      bool passedALL = false;
      bool passedHT800 =false;
      bool passedHT650MJJ900=false;
      bool passedHT650MJJ950=false;
      bool passedHT700Trim =false;
        
      for( std::map<std::string,bool>::iterator it2 = (data_.HLT_isFired)->begin(); it2 != (data_.HLT_isFired)->end(); it2++){
        std::string iter = it2->first;
        bool value = it2->second;
        

        if( ((iter).find("PFHT800")                        != std::string::npos && value)
            || ((iter).find("HT900")                      != std::string::npos && value) 
            || ((iter).find("PFJet450")                   != std::string::npos && value)
            ){passedHT800 = true;}
        if( (iter).find("PFHT650_WideJetMJJ950DEtaJJ1p5") != std::string::npos && value ) passedHT650MJJ950 = true;
        if( (iter).find("PFHT650_WideJetMJJ900DEtaJJ1p5") != std::string::npos && value ) passedHT650MJJ900 = true;
        if( ((iter).find("PFHT800")                       != std::string::npos && value)
            || ((iter).find("PFHT900")                    != std::string::npos && value) 
          || ((iter).find("PFJet450")                     != std::string::npos && value)
          ||((iter).find("PFHT650_WideJetMJJ900DEtaJJ1p5")!= std::string::npos && value)
          ||((iter).find("PFHT650_WideJetMJJ950DEtaJJ1p5")!= std::string::npos && value)) passedHT = true;
          
        if( ((iter).find("PFHT800")                       != std::string::npos && value)
            || ((iter).find("PFHT900")                    != std::string::npos && value) 
          || ((iter).find("PFJet450")                     != std::string::npos && value)
          ||((iter).find("PFHT650_WideJetMJJ900DEtaJJ1p5")!= std::string::npos && value)
          ||((iter).find("PFHT650_WideJetMJJ950DEtaJJ1p5")!= std::string::npos && value)
          ||((iter).find("AK8PFJet360_TrimMass30")        != std::string::npos && value)
          ||((iter).find("AK8PFHT700_TrimR0p1PT0p03Mass50")!= std::string::npos && value)) passedALL = true;

        //SUBSTRUCTURE TRIGGERS
        if( (iter).find("AK8PFJet360_TrimMass30")                    != std::string::npos && value ) Hist( "PFJet360_Trim" ) ->Fill( Mjj);
        if( (iter).find("AK8PFHT700_TrimR0p1PT0p03Mass50")           != std::string::npos && value ) passedHT700Trim = true; 
        if( (iter).find("AK8DiPFJet280_200_TrimMass30_BTagCSV0p45")  != std::string::npos && value ) Hist( "DiPFJet280_200_TrimMass30" )->Fill( Mjj);
        if( ((iter).find("AK8PFJet360_TrimMass30")                   != std::string::npos && value)
          || ((iter).find("AK8PFHT700_TrimR0p1PT0p03Mass50")         != std::string::npos && value) ) passedSubstructure = true;
      }
//       if( passedHT )            Hist( "HT" )->Fill( Mjj);
//       if( passedSubstructure )  Hist( "Substructure" )->Fill( Mjj);
//       if( passedALL )           Hist( "ALL" )->Fill( Mjj);
//       if(passedHT800)           {Hist( "HT800" )->Fill( Mjj);}
//       if(passedHT650MJJ950)     Hist( "HT650_MJJ950" )->Fill( Mjj);
//       if(passedHT650MJJ900)     Hist( "HT650_MJJ900" )->Fill( Mjj);
//       
            //================== test for run H to get rid of L1 inefficiency ========================================================
      // do OR with: HLT_PFJet450 (or PFJet500) HLT_AK8PFJet450 (or AK8PFJet500) HLT_CaloJet500_NoJetID
        
    if( passedHT || recoverL1 )       Hist( "HT" )->Fill( Mjj);
    if( passedSubstructure || recoverL1)          Hist( "Substructure" )->Fill( Mjj);
    if( passedALL || recoverL1)       Hist( "ALL" )->Fill( Mjj);
    if(passedHT800 || recoverL1)      {Hist( "HT800" )->Fill( Mjj);}
    if(passedHT650MJJ950 || recoverL1)Hist( "HT650_MJJ950" )->Fill( Mjj);
    if(passedHT650MJJ900 || recoverL1)Hist( "HT650_MJJ900" )->Fill( Mjj);
    if(passedHT700Trim || recoverL1)  Hist( "HT700_Trim" )    ->Fill( Mjj);
      //=========================================================================================================================
    
      
      
      
    } //End single tag
    
    //Start double tag
    if( (groomedMass_jet1 > mWLow_ && groomedMass_jet1 <= mZHigh_) && 
    (groomedMass_jet2 > mWLow_ && groomedMass_jet2 <= mZHigh_ )){
      Hist( "PFHT650_VV" )->Fill( Mjj);

      //Pass double tag
      bool passedHT = false;
      bool passedSubstructure = false;
      bool passedALL = false;
      bool passedHT800 =false;
      bool passedHT650MJJ900=false;
      bool passedHT650MJJ950=false;
      bool passedHT700Trim =false;

        
      for( std::map<std::string,bool>::iterator it2 = (data_.HLT_isFired)->begin(); it2 != (data_.HLT_isFired)->end(); it2++){
        std::string iter = it2->first;
        bool value = it2->second;

        if( ((iter).find("PFHT800")                       != std::string::npos && value) 
            || ((iter).find("PFHT900")                    != std::string::npos && value) 
            || ((iter).find("PFJet450")                   != std::string::npos && value)
        ){passedHT800 = true;}
        if( (iter).find("PFHT650_WideJetMJJ950DEtaJJ1p5") != std::string::npos && value ) passedHT650MJJ950 = true;
        if( (iter).find("PFHT650_WideJetMJJ900DEtaJJ1p5") != std::string::npos && value ) passedHT650MJJ900 = true;
        if( ((iter).find("PFHT800")                       != std::string::npos && value)
            || ((iter).find("PFHT900")                    != std::string::npos && value) 
          || ((iter).find("PFJet450")                     != std::string::npos && value)
          ||((iter).find("PFHT650_WideJetMJJ900DEtaJJ1p5")!= std::string::npos && value)
            ||((iter).find("PFHT650_WideJetMJJ950DEtaJJ1p5")!= std::string::npos && value)) passedHT = true;
          
        if( ((iter).find("PFHT800")                       != std::string::npos && value)
            || ((iter).find("PFHT900")                    != std::string::npos && value) 
          || ((iter).find("PFJet450")                     != std::string::npos && value)
          ||((iter).find("PFHT650_WideJetMJJ900DEtaJJ1p5")!= std::string::npos && value)
          ||((iter).find("PFHT650_WideJetMJJ950DEtaJJ1p5")!= std::string::npos && value)
          ||((iter).find("AK8PFJet360_TrimMass30")        != std::string::npos && value)
          ||((iter).find("AK8PFHT700_TrimR0p1PT0p03Mass50")!= std::string::npos && value)) passedALL = true;

        //SUBSTRUCTURE TRIGGERS
        if( (iter).find("AK8PFJet360_TrimMass30")                    != std::string::npos && value ) Hist( "PFJet360_Trim_VV" ) ->Fill( Mjj);
        if( (iter).find("AK8PFHT700_TrimR0p1PT0p03Mass50")           != std::string::npos && value ) passedHT700Trim = true;
        if( (iter).find("AK8DiPFJet280_200_TrimMass30_BTagCSV0p45")  != std::string::npos && value ) Hist( "DiPFJet280_200_TrimMass30_VV" )->Fill( Mjj);
        if( ((iter).find("AK8PFJet360_TrimMass30")                   != std::string::npos && value)
          || ((iter).find("AK8PFHT700_TrimR0p1PT0p03Mass50")         != std::string::npos && value) ) passedSubstructure = true;
      }
        
//       if( passedHT )          Hist( "HT_VV" )->Fill( Mjj);
//       if( passedSubstructure )Hist( "Substructure_VV" )->Fill( Mjj);
//       if( passedALL )         Hist( "ALL_VV" )->Fill( Mjj);
//       if(passedHT800)         {Hist( "HT800_VV" )->Fill( Mjj);}
//       if(passedHT650MJJ950)   Hist( "HT650_MJJ950_VV" )->Fill( Mjj);
//       if(passedHT650MJJ900)   Hist( "HT650_MJJ900_VV" )->Fill( Mjj);
//       
      
                 //================== test for run H to get rid of L1 inefficiency ========================================================
     // do OR with: HLT_PFJet450 (or PFJet500) HLT_AK8PFJet450 (or AK8PFJet500) HLT_CaloJet500_NoJetID
       
   if( passedHT || recoverL1 )       Hist( "HT_VV" )->Fill( Mjj);
   if( passedSubstructure || recoverL1 )          Hist( "Substructure_VV" )->Fill( Mjj);
   if( passedALL || recoverL1)       Hist( "ALL_VV" )->Fill( Mjj);
   if(passedHT800 || recoverL1)      {Hist( "HT800_VV" )->Fill( Mjj);}
   if(passedHT650MJJ950 || recoverL1)Hist( "HT650_MJJ950_VV" )->Fill( Mjj);
   if(passedHT650MJJ900 || recoverL1)Hist( "HT650_MJJ900_VV" )->Fill( Mjj);
   if(passedHT700Trim || recoverL1) Hist( "HT700_Trim_VV" )    ->Fill( Mjj);
     //=========================================================================================================================
   
        
    } //End double tag
  }
  }
  return;
}


//==============================================================================================
void ExoDiBosonAnalysis::doTriggerEfficiencyvsMass( void ){
  int fill=0;
  for( std::map<std::string,bool>::iterator it = (data_.HLT_isFired)->begin(); it != (data_.HLT_isFired)->end(); it++){ //map1 loop
    std::string trigName = it->first;
    bool decision = it->second;
    //HLT_IsoMu24_eta2p1_v2 or PFJet320
    if( !(((trigName).find("PFHT650_v") != std::string::npos && decision) or ((trigName).find("PFJet320") != std::string::npos && decision)) ) continue;
    if( !(trigName.find("PFJet320") != std::string::npos && decision) )
    {
        Hist( "PFJet320_SD")->Fill( Vcand.at(0).puppi_softdropMass);
        Hist( "PFJet320_P" )->Fill( Vcand.at(0).prunedMass);
    }
    if( !(trigName.find("PFHT650") != std::string::npos && decision) )
    {
        Hist( "PFHT650_SD")->Fill( Vcand.at(0).puppi_softdropMass);
    }
    fill+=1;
    if(fill==1)
    {
        Hist( "Base_SD")->Fill(Vcand.at(0).puppi_softdropMass);
    bool passedSub = false;
    for( std::map<std::string,bool>::iterator it2 = (data_.HLT_isFired)->begin(); it2 != (data_.HLT_isFired)->end(); it2++){
      std::string iter = it2->first;
      bool value = it2->second;

      if( iter.find("AK8PFJet360_TrimMass30")!= std::string::npos && value ){
        Hist( "PFJet360_Trim_SD" ) ->Fill( Vcand.at(0).puppi_softdropMass);
        Hist( "PFJet360_Trim_P"  ) ->Fill( Vcand.at(0).prunedMass);
      }
      if( iter.find("AK8PFHT700_TrimR0p1PT0p03Mass50")            != std::string::npos && value ){
        Hist( "HT700_Trim_SD"    ) ->Fill( Vcand.at(0).puppi_softdropMass);
        Hist( "HT700_Trim_P"    ) ->Fill( Vcand.at(0).prunedMass);
      }
      if( iter.find("AK8DiPFJet280_200_TrimMass30_BTagCSV0p45")   != std::string::npos && value ){
        Hist( "DiPFJet280_200_TrimMass30_SD" ) ->Fill( Vcand.at(0).puppi_softdropMass);
        Hist( "DiPFJet280_200_TrimMass30_P" ) ->Fill( Vcand.at(0).prunedMass);
      }
      if( (iter.find("AK8PFJet360_TrimMass30")                    != std::string::npos && value)
        || (iter.find("AK8PFHT700_TrimR0p1PT0p03Mass50")          != std::string::npos && value)
          || (iter.find("AK8DiPFJet280_200_TrimMass30_BTagCSV0p45") != std::string::npos && value )) passedSub = true;
    }
    if(passedSub){
      Hist( "Substructure_SD" ) ->Fill(Vcand.at(0).puppi_softdropMass);
      Hist( "Substructure_P" )  ->Fill(Vcand.at(0).prunedMass);
    }
    }
  }
  return;
}

//==============================================================================================
void ExoDiBosonAnalysis::do2DTriggerEfficiency( void ){
  
  for( std::map<std::string,bool>::iterator it = (data_.HLT_isFired)->begin(); it != (data_.HLT_isFired)->end(); it++){ //map1 loop
    std::string trigName = it->first;
    bool decision = it->second;
    if( !(trigName.find("PFJet320") != std::string::npos && decision) ) continue;
      
    Hist( "PtvsMSD_den" )->Fill( Vcand.at(0).p4.Pt(), Vcand.at(0).puppi_softdropMass);
    Hist( "PtvsMPR_den" )->Fill( Vcand.at(0).p4.Pt(), Vcand.at(0).prunedMass);

    for( std::map<std::string,bool>::iterator it2 = (data_.HLT_isFired)->begin(); it2 != (data_.HLT_isFired)->end(); it2++){
      std::string iter = it2->first;
      bool value = it2->second;
      if( iter.find("AK8PFJet360_TrimMass30")!= std::string::npos && value ){
        Hist( "PtvsMSD_num" )->Fill( Vcand.at(0).p4.Pt(), Vcand.at(0).puppi_softdropMass);
        Hist( "PtvsMPR_num" )->Fill( Vcand.at(0).p4.Pt(), Vcand.at(0).prunedMass);
      }
    }
  }
  return;
}

//==============================================================================================
  
  

void ExoDiBosonAnalysis::doGenTTReco( void ){
  int nrBquarks = 0;
  int nrquarks = 0;
  int indx = -1;
  float dMmin = 999;
  float Mmin = 999;
  float chi2 = 999;
  float Mt1 = 0;
  float Mt2 = 0;
  TLorentzVector genP;
  std::vector<JetCandidate	>	AdditionalJ	;
  
  nBTags = 0;
  TLorentzVector jet;
  for( unsigned int j = 0; j < (data_.jetAK4_pt)->size(); ++j ){ 
    if( (*data_.jetAK4_IDLoose).at(j) != 1 ) continue;
    if( (*data_.jetAK4_pt).at(j) <= 30. ) continue;
    if( fabs((*data_.jetAK4_eta).at(j)) >= JetEtaCut_ ) continue;
    jet.SetPtEtaPhiE( (*data_.jetAK4_pt).at(j), (*data_.jetAK4_eta).at(j), (*data_.jetAK4_phi).at(j), (*data_.jetAK4_e).at(j) );
    JetCandidate Ajet(jet);
    Ajet.csv = (*data_.jetAK4_csv).at(j);
    Ajet.flavor = abs((*data_.jetAK4_flavor).at(j));
    AdditionalJ.push_back(Ajet);
  }
  
  
  std::map<int,TLorentzVector>::iterator it = genCandidates_.find(24)!=genCandidates_.end() ? genCandidates_.find(24) : genCandidates_.find(-24);
  // setGenCandidates();
  
  for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
    if( (*data_.genParticle_pt).at(p) < 0.1) continue;
    if( (*data_.genParticle_status).at(p) != 4 && (*data_.genParticle_status).at(p) != 22 && (*data_.genParticle_status).at(p) != 23) continue;
     

    for( unsigned int m = 0; m < (*data_.genParticle_mother)[p].size(); ++m ){
      genP.SetPtEtaPhiE( (*data_.genParticle_pt).at(p), (*data_.genParticle_eta).at(p), (*data_.genParticle_phi).at(p), (*data_.genParticle_e).at(p) );

      for(int i=0; i < abs(AdditionalJ.size()); i++ ){
        float dR = genP.DeltaR(AdditionalJ.at(i).p4);
        if(dR<0.4){
          if( abs((*data_.genParticle_pdgId)[p]) == 5 && abs((*data_.genParticle_mother)[p][m]) == 6 ){
            AK4bjetCand_.push_back(AdditionalJ.at(i));
            nrBquarks++;
          }
          else if( abs((*data_.genParticle_pdgId)[p]) != 5 && abs((*data_.genParticle_mother)[p][m]) == 24){
            AK4jetCand_.push_back(AdditionalJ.at(i));
            nrquarks++;
          }
        }
      }     
      
    }  
  }

  if(AK4bjetCand_.size()<2 || AK4jetCand_.size()<2 ) {
    throw SError( SError::SkipEvent );
  }
          
  for(int i=0; i < abs(AK4jetCand_.size()); i++ ){
    if( (AK4bjetCand_.at(0).p4.Pt() == AK4jetCand_.at(i).p4.Pt()) || (AK4bjetCand_.at(1).p4.Pt() == AK4jetCand_.at(i).p4.Pt()))continue;
    for(int j=0; j < abs(AK4jetCand_.size()); j++ ){
      if( (AK4bjetCand_.at(0).p4.Pt() == AK4jetCand_.at(j).p4.Pt()) || (AK4bjetCand_.at(1).p4.Pt() == AK4jetCand_.at(j).p4.Pt()) || j==i)continue;
      float M = (AK4jetCand_.at(j).p4+AK4jetCand_.at(i).p4).M();
      float dM= fabs(80-M);
      if(dM<dMmin) {
        dMmin=dM;
        Mmin = M;
        Mt1 = (AK4jetCand_.at(j).p4+AK4jetCand_.at(i).p4 + AK4bjetCand_.at(0).p4 ).M();
        Mt2 = (AK4jetCand_.at(j).p4+AK4jetCand_.at(i).p4 + AK4bjetCand_.at(1).p4 ).M();
      }
    }
  }
          
  if(fabs(180-Mt1)< fabs(180-Mt2)){
    float deltaWmass = Mmin-pdgMw;
    float deltaTmass = Mt1-pdgMtop;
    chi2 = pow((deltaTmass/pdgWidthtop),2)+pow((deltaWmass/pdgWidthw),2);  
    Hist( "tmass"			      	)->Fill ( Mt1);
    Hist( "Chi2vsTMass"        )->Fill ( chi2,Mt1);
  }
  else if(fabs(180-Mt1)> fabs(180-Mt2)){
    float deltaWmass = Mmin-pdgMw;
    float deltaTmass = Mt2-pdgMtop;
    chi2 = pow((deltaTmass/pdgWidthtop),2)+pow((deltaWmass/pdgWidthw),2);  
    Hist( "Chi2vsTMass"        )->Fill ( chi2,Mt2);
    Hist( "tmass")->Fill ( Mt2);         
  }
          
  Hist( "Chi2"              )->Fill ( chi2, weight_ );
  Hist( "Chi2vsWMass"        )->Fill ( chi2,Mmin);
  Hist( "wmass"			      	)->Fill ( Mmin);				     
      																														  
} 

////////////////////////////////////////////////////// GEN STUDIES ////////////////////////////////////////////////////////////////////////////
void ExoDiBosonAnalysis::doSubstructureStudies( TString infile ){
    
  int pdgV = 24;
  
  if( infile.Contains("BulkGravToZZ") or infile.Contains("WprimeToWZ") or infile.Contains("RadionToZZ") or infile.Contains("ZZ") ) pdgV = 23;
  if( infile.Contains("WprimeToWhToWhadhbb") or infile.Contains("RSGravTohhTohbbhbb")) pdgV = 25;
  // TLorentzVector genP_W;
  // std::vector<TLorentzVector> genWs;
  TLorentzVector genP;
  std::vector<TLorentzVector> daus;
  TLorentzVector hadW;
  //Getting all gen jets 
  
  for( int j = 0; j < data_.ngenJetsAK8 ; ++j ){
    // if( (*data_.genJetAK8_pt).at(j) <= 200.      )continue;
    // if( fabs((*data_.genJetAK8_eta).at(j)) >= 2.4)continue;
    TLorentzVector myGenJet;
    myGenJet.SetPtEtaPhiE( (*data_.genJetAK8_pt).at(j), (*data_.genJetAK8_eta).at(j), (*data_.genJetAK8_phi).at(j), (*data_.genJetAK8_e).at(j) );
    
    JetCandidate jet(myGenJet);
    jet.prunedMass		= (*data_.genJetAK8_prunedmass).at(j)    ;
    jet.softdropMass	= (*data_.genJetAK8_softdropmass).at(j);
    genJetCand.push_back(jet);
  }
      
      
  // //Getting all gen hadronic Ws
  // for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
  //   bool isHad = false;
  //   if( (*data_.genParticle_pt).at(p) < 0.1) continue;
  //   if( fabs((*data_.genParticle_pdgId).at(p)) != 24) continue;
  //   if ((*data_.genParticle_dau)[p].size() < 2) continue;
  //   for( unsigned int d = 0; d < (*data_.genParticle_dau)[p].size(); ++d ) {
  //     if( fabs((*data_.genParticle_dau)[p][d]) > 9) continue;
  //     isHad = true;
  //   }
  //   if (!isHad) continue;
  //   genP_W.SetPtEtaPhiE( (*data_.genParticle_pt).at(p), (*data_.genParticle_eta).at(p), (*data_.genParticle_phi).at(p), (*data_.genParticle_e).at(p) );
  //   genWs.push_back(genP_W);
  // }
  
  for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
    bool isHad = false;
    if( (*data_.genParticle_pt).at(p) < 0.1) continue;
    if( fabs((*data_.genParticle_pdgId).at(p)) > 9) continue;
    for( unsigned int d = 0; d < (*data_.genParticle_mother)[p].size(); ++d ) {
      if( fabs((*data_.genParticle_mother)[p][d]) != pdgV ) continue;
      isHad = true;
    }
    if (!isHad) continue;
    genP.SetPtEtaPhiE( (*data_.genParticle_pt).at(p), (*data_.genParticle_eta).at(p), (*data_.genParticle_phi).at(p), (*data_.genParticle_e).at(p) );
    daus.push_back(genP);
  }

 
  //Finding AK8 CHS reco W-jets
  for( int j = 0; j < data_.njetsAK8 ; ++j ){
    TLorentzVector myJet;
    if( (*data_.jetAK8_pt).at(j) <= 200.      )continue;
    if( infile.Contains("WW_TuneCUETP8M1")  && (*data_.jetAK8_pt).at(j) > 250.      )continue;
    if( fabs((*data_.jetAK8_eta).at(j)) >= 2.4)continue;
    if( (*data_.jetAK8_IDTight).at(j) != 1    )continue;
    myJet.SetPtEtaPhiE( (*data_.jetAK8_pt).at(j), (*data_.jetAK8_eta).at(j), (*data_.jetAK8_phi).at(j), (*data_.jetAK8_e).at(j) );
    bool isW = false;
    int isMatch = 0;
    if(runOnMC_){
      for( unsigned int p = 0; p < daus.size(); ++p ){
        float dR = daus.at(p).DeltaR(myJet);
        if (dR < 0.8 ) isMatch +=1;
      }
    }
    if(!runOnMC_)isMatch = 0;
    if (isMatch > 1) isW = true;
    if(isSignal_ and !isW ) continue;
    Hist( "prunedJECvsPT")  ->Fill( (*data_.jetAK8_pt).at(j), (*data_.jetAK8_pruned_jec).at(j) );
    Hist( "gen_PrunedMass"    )  ->Fill( (*data_.jetAK8_prunedmass).at(j), weight_ );
    Hist( "gen_Mass"    )  ->Fill( (*data_.jetAK8_mass).at(j), weight_ );
    if( (*data_.jetAK8_prunedmass).at(j) <= 105.0 && (*data_.jetAK8_prunedmass).at(j) > 65.0 )Hist( "gen_Tau21"  )->Fill ( (*data_.jetAK8_tau2).at(j)/(*data_.jetAK8_tau1).at(j), weight_ );
    
    int jetIndex = 99 ;
    float dRmin = 9999. ;
    for( unsigned int jj = 0; jj < genJetCand.size(); ++jj ){
      float dR = myJet.DeltaR(genJetCand[jj].p4);
      if(dR > dRmin) continue;
      dRmin = dR;
      jetIndex = jj;
    }
    float massShift = ((*data_.jetAK8_prunedmass_unCorr).at(j) - genJetCand.at(jetIndex).prunedMass) / (*data_.jetAK8_prunedmass_unCorr).at(j) ;
    Hist( "GenAK8PrunedMass"    )  ->Fill( genJetCand.at(jetIndex).prunedMass );
    if( fabs( genJetCand[jetIndex].p4.Eta() ) <= 1.3 ) Hist( "GenAK8PrunedMass_eta1v3"    )  ->Fill( genJetCand.at(jetIndex).prunedMass );
    if( fabs( genJetCand[jetIndex].p4.Eta() ) >  1.3 ) Hist( "GenAK8PrunedMass_etaUP1v3"    )  ->Fill( genJetCand.at(jetIndex).prunedMass );
    Hist( "massShift_pruning"    )  ->Fill( massShift );
    if( fabs((*data_.jetAK8_eta).at(j)) <= 1.3 ) Hist( "massShift_pruning_eta1v3"    )  ->Fill( massShift );
    if( fabs((*data_.jetAK8_eta).at(j)) >  1.3 ) Hist( "massShift_pruning_etaUP1v3"  )  ->Fill( massShift );
  }
  
  
  
  //Finding AK8 PUPPI reco W-jets 
  for( unsigned int j = 0; j < (data_.jetAK8_puppi_pt)->size() ; ++j ){
    TLorentzVector myJetPUPPI;
    if( (*data_.jetAK8_puppi_pt).at(j) <= 200.      )continue;
    if( infile.Contains("WW_TuneCUETP8M1")  && (*data_.jetAK8_puppi_pt).at(j) > 250.      )continue;
    if( fabs((*data_.jetAK8_puppi_eta).at(j)) >= 2.4)continue;
    myJetPUPPI.SetPtEtaPhiE( (*data_.jetAK8_puppi_pt).at(j), (*data_.jetAK8_puppi_eta).at(j), (*data_.jetAK8_puppi_phi).at(j), (*data_.jetAK8_puppi_e).at(j) );
    bool isW = false;
    int isMatch = 0;
    if(runOnMC_){
      for( unsigned int p = 0; p < daus.size(); ++p ){
        float dR = daus.at(p).DeltaR(myJetPUPPI);
        if (dR < 0.8 ) isMatch +=1;
      }
    }
    if(!runOnMC_)isMatch = 0;
    if (isMatch > 1) isW = true;
    if( isSignal_ && !isW ) continue;
        
        
    int jetIndex = 99 ;
    float dRmin = 9999. ;
    for( int jj = 0; jj < data_.njetsAK8 ; ++jj ){
      
      TLorentzVector myJet;
      myJet.SetPtEtaPhiE( (*data_.jetAK8_pt).at(jj), (*data_.jetAK8_eta).at(jj), (*data_.jetAK8_phi).at(jj), (*data_.jetAK8_e).at(jj) );
      float dR = myJetPUPPI.DeltaR(myJet);
      if(dR > dRmin) continue;
      dRmin = dR;
      jetIndex = jj;
    }
    Hist( "gen_SoftdropMassCHSCorr"  )->Fill ( (*data_.jetAK8_puppi_softdrop_massUnCorr).at(j)*(*data_.jetAK8_pruned_jec).at(jetIndex), weight_);
    
    float puppiCorr = getPUPPIweight( (*data_.jetAK8_puppi_pt).at(j) , (*data_.jetAK8_puppi_eta).at(j) );
    float puppiCorr_gen = getPUPPIweight_gen( (*data_.jetAK8_puppi_pt).at(j) , (*data_.jetAK8_puppi_eta).at(j) );
    float puppiCorr_rec = getPUPPIweight_rec( (*data_.jetAK8_puppi_pt).at(j) , (*data_.jetAK8_puppi_eta).at(j) );
    
    Hist( "gen_SoftdropMass_NEWCORR"  )->Fill ( (*data_.jetAK8_puppi_softdrop_massUnCorr).at(j)*puppiCorr);  
    Hist( "gen_SoftdropMass"          )->Fill ( (*data_.jetAK8_puppi_softdrop_massCorr).at(j));
    // jetAK8_uppi_pruned_mass is empty!! do not use this variable
    //Hist( "gen_PuppiPrunedMass_Uncorr")->Fill ( (*data_.jetAK8_puppi_pruned_massUnCorr).at(j));
    //Hist( "gen_PuppiPrunedMass_Corr"  )->Fill ( (*data_.jetAK8_puppi_pruned_massCorr).at(j));
    
    Hist( "PUPPISDvsNPV")->Fill ( data_.nPVs                     ,(*data_.jetAK8_puppi_softdrop_massUnCorr).at(j)* puppiCorr);
    Hist( "PUPPISDvsETA")->Fill ( (*data_.jetAK8_puppi_eta).at(j),(*data_.jetAK8_puppi_softdrop_massUnCorr).at(j)* puppiCorr);  
    Hist( "gen_eta")          ->Fill( (*data_.jetAK8_puppi_eta).at(j), weight_); 
    
    if( fabs((*data_.jetAK8_puppi_eta).at(j)) <= 1.3 ) {
     Hist( "gen_pt_eta1v3")          ->Fill( (*data_.jetAK8_puppi_pt).at(j), weight_);
     Hist( "gen_nPV_eta1v3")          ->Fill( data_.nPVs, weight_);
      Hist( "puppiJECvsPT_eta1v3")    ->Fill( (*data_.jetAK8_puppi_pt).at(j), (*data_.jetAK8_puppi_softdrop_jec).at(j) );
     Hist( "gen_SoftdropMass_eta1v3")->Fill( (*data_.jetAK8_puppi_softdrop_massUnCorr).at(j), weight_);
      
      Hist( "PUPPIcorr_eta1v3"  )->Fill( puppiCorr );
      Hist( "gen_SoftdropMass_eta1v3_NEWCORR"  )->Fill ( (*data_.jetAK8_puppi_softdrop_massUnCorr).at(j)* puppiCorr);
      //Hist( "gen_SoftdropMass_eta1v3_NEWCORR_gen"  )->Fill ( (*data_.jetAK8_puppi_softdrop_massUnCorr).at(j)* puppiCorr_gen);
      
      
      Hist( "gen_chsJEC_eta1v3"  )->Fill( (*data_.jetAK8_pt).at(jetIndex), (*data_.jetAK8_pruned_jec).at(jetIndex) );
    }
    
    if( fabs((*data_.jetAK8_puppi_eta).at(j)) > 1.3 ){
     Hist( "gen_pt_etaUP1v3")  ->Fill( (*data_.jetAK8_puppi_pt).at(j), weight_);
     Hist( "gen_nPV_etaUP1v3")         ->Fill( data_.nPVs, weight_);
      Hist( "puppiJECvsPT_etaUP1v3")    ->Fill( (*data_.jetAK8_puppi_pt).at(j), (*data_.jetAK8_puppi_softdrop_jec).at(j) );
     Hist( "gen_SoftdropMass_etaUP1v3")->Fill ( (*data_.jetAK8_puppi_softdrop_massUnCorr).at(j), weight_);
      
      Hist( "PUPPIcorr_etaUP1v3"  )->Fill( puppiCorr );
      Hist( "gen_SoftdropMass_etaUP1v3_NEWCORR"  )->Fill ( (*data_.jetAK8_puppi_softdrop_massUnCorr).at(j)* puppiCorr);
    
      
      
      Hist( "gen_chsJEC_etaUP1v3"  )->Fill ( (*data_.jetAK8_pt).at(jetIndex), (*data_.jetAK8_pruned_jec).at(jetIndex) );
    }
    Hist( "puppiJECvsPT")  ->Fill( (*data_.jetAK8_puppi_pt).at(j), (*data_.jetAK8_puppi_softdrop_jec).at(j) );
    
   if( (*data_.jetAK8_puppi_pt).at(j) > 500.      )Hist( "gen_SoftdropMass_pt500"  )->Fill ( (*data_.jetAK8_puppi_softdrop_massCorr).at(j), weight_);
    
        
        
    if( (*data_.jetAK8_puppi_softdrop_massCorr).at(j) <= 105.0 && (*data_.jetAK8_puppi_softdrop_massCorr).at(j) >= 65.0 ){
      float DDT = ( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j) ) + 0.063*log( ((*data_.jetAK8_puppi_softdrop_massCorr).at(j)*(*data_.jetAK8_puppi_softdrop_massCorr).at(j)) / ((*data_.jetAK8_puppi_pt).at(j)) );
      Hist( "gen_PUPPITau21"    )     ->Fill ( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j), weight_ );
     Hist( "gen_DDT")                ->Fill ( DDT, weight_ );
    }
    jetIndex = 99 ;
    dRmin = 9999. ;
    for( unsigned int jj = 0; jj < genJetCand.size(); ++jj ){
      float dR = myJetPUPPI.DeltaR(genJetCand[jj].p4);
      if(dR > dRmin) continue;
      dRmin = dR;
      jetIndex = jj;
    }

    float genCorr = (puppisd_corrGEN->Eval(  (*data_.jetAK8_puppi_pt).at(j) ));
    float massShift = ( (*data_.jetAK8_puppi_softdrop_massUnCorr).at(j) - (genJetCand.at(jetIndex).softdropMass*genCorr)) / (*data_.jetAK8_puppi_softdrop_massUnCorr).at(j) ;
    //Hist( "PUPPI_SoftdopMass_NOCorr") ->Fill((*data_.jetAK8_puppi_softdrop_massUnCorr).at(j));
    //if( fabs((*data_.jetAK8_puppi_eta).at(j)) <= 1.3 ) Hist( "PUPPI_SoftdopMass_eta1v3_NOCorr") ->Fill((*data_.jetAK8_puppi_softdrop_massUnCorr).at(j));
    //if( fabs((*data_.jetAK8_puppi_eta).at(j)) > 1.3 ) Hist( "PUPPI_SoftdopMass_etaUP1v3_NOCorr") ->Fill((*data_.jetAK8_puppi_softdrop_massUnCorr).at(j));
    Hist( "GenAK8SoftdropMass"    )  ->Fill( genJetCand.at(jetIndex).softdropMass );
    if(  fabs((*data_.jetAK8_puppi_eta).at(j)) <= 1.3 ) Hist( "GenAK8SoftdropMass_eta1v3"   )  ->Fill( genJetCand.at(jetIndex).softdropMass );
    if(  fabs((*data_.jetAK8_puppi_eta).at(j)) >  1.3 ) Hist( "GenAK8SoftdropMass_etaUP1v3" )  ->Fill( genJetCand.at(jetIndex).softdropMass );
    Hist( "GenAK8SoftdropMass_CORR"    )  ->Fill( genJetCand.at(jetIndex).softdropMass );
    if(  fabs((*data_.jetAK8_puppi_eta).at(j)) <= 1.3 ) Hist( "GenAK8SoftdropMass_eta1v3_CORR"   )  ->Fill( genJetCand.at(jetIndex).softdropMass*genCorr );
    if(  fabs((*data_.jetAK8_puppi_eta).at(j)) >  1.3 ) Hist( "GenAK8SoftdropMass_etaUP1v3_CORR" )  ->Fill( genJetCand.at(jetIndex).softdropMass*genCorr );
    Hist( "massShift_softdrop"    )  ->Fill( massShift );
    if( fabs((*data_.jetAK8_puppi_eta).at(j)) <= 1.3 ) Hist( "massShift_softdrop_eta1v3"    )  ->Fill( massShift );
    if( fabs((*data_.jetAK8_puppi_eta).at(j)) >  1.3 ) Hist( "massShift_softdrop_etaUP1v3"  )  ->Fill( massShift ); 
  }
}

////////////////////////////////////////////////////// GET PUPPI SOFTDROP CORRECTION ////////////////////////////////////////////////////////////////////////////

float ExoDiBosonAnalysis::getPUPPIweight(float puppipt, float puppieta ){
  
  float genCorr  = 1.;
  float recoCorr = 1.;
  float totalWeight = 1.;
        
  genCorr =  puppisd_corrGEN->Eval( puppipt );
  
  // std::cout<< "for PUPPI jet pT = 300 GeV : 1./genCorr = " << 1./(puppisd_corrGEN->Eval( 300. )) << " recoCorr = " <<puppisd_corrRECO_cen->Eval( 300 ) << " Total corr = " << (1./(puppisd_corrGEN->Eval( 300. )))*puppisd_corrRECO_cen->Eval( 300 )<<  std::endl;

  if( fabs(puppieta)  <= 1.3 ) recoCorr = puppisd_corrRECO_cen->Eval( puppipt );
  else
    if( fabs(puppieta) > 1.3 ) recoCorr = puppisd_corrRECO_for->Eval( puppipt );
  
  totalWeight = genCorr * recoCorr;
  // std::cout<< "for PUPPI jet pT = " << puppipt << " and eta = " << puppieta << " my weight is: " << std::endl;
  // std::cout<< "Gen corr = " << (1./genCorr) << " recoCorr = " << recoCorr << " Total = " << totalWeight << std::endl;
  return totalWeight;
}

float ExoDiBosonAnalysis::getPUPPIweight_gen(float puppipt, float puppieta ){
  
  float genCorr  = 1.;
  float recoCorr = 1.;
  float totalWeight = 1.;
        
  genCorr =  puppisd_corrGEN->Eval( puppipt );

  return genCorr;
}

float ExoDiBosonAnalysis::getPUPPIweight_rec(float puppipt, float puppieta ){
  
  float genCorr  = 1.;
  float recoCorr = 1.;
  float totalWeight = 1.;
        
  if( fabs(puppieta)  <= 1.3 ) recoCorr = puppisd_corrRECO_cen->Eval( puppipt );
  else
    if( fabs(puppieta) > 1.3 ) recoCorr = puppisd_corrRECO_for->Eval( puppipt );
  
  totalWeight = genCorr * recoCorr;
  return totalWeight;
}
  

////////////////////////////////////////////////////// GEN STUDIES ////////////////////////////////////////////////////////////////////////////
void ExoDiBosonAnalysis::doWTagEfficiency( TString infile ){
  
  TLorentzVector genP_W;
  std::vector<TLorentzVector> genWs;
  TLorentzVector genP;
  std::vector<TLorentzVector> daus;
  TLorentzVector hadW;

  if(runOnMC_){
    for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
      bool isHad = false;
      if( (*data_.genParticle_pt).at(p) < 0.1) continue;
      if( fabs((*data_.genParticle_pdgId).at(p)) != 24) continue;
      if ((*data_.genParticle_dau)[p].size() < 2) continue;
      for( unsigned int d = 0; d < (*data_.genParticle_dau)[p].size(); ++d ) {
        if( fabs((*data_.genParticle_dau)[p][d]) > 9) continue;
        isHad = true;
      }
      if (!isHad) continue;
      genP_W.SetPtEtaPhiE( (*data_.genParticle_pt).at(p), (*data_.genParticle_eta).at(p), (*data_.genParticle_phi).at(p), (*data_.genParticle_e).at(p) );
      genWs.push_back(genP_W);
    }
    for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
      bool isHad = false;
      if( (*data_.genParticle_pt).at(p) < 0.1) continue;
      if( fabs((*data_.genParticle_pdgId).at(p)) > 9) continue;
      for( unsigned int d = 0; d < (*data_.genParticle_mother)[p].size(); ++d ) {
        if( fabs((*data_.genParticle_mother)[p][d]) != 24 ) continue;
        isHad = true;
      }
      if (!isHad) continue;
      genP.SetPtEtaPhiE( (*data_.genParticle_pt).at(p), (*data_.genParticle_eta).at(p), (*data_.genParticle_phi).at(p), (*data_.genParticle_e).at(p) );
      daus.push_back(genP);
    }
  }
  
  // if( (daus.size() > 1 && isSignal_) or (!isSignal_)){
  for( int j = 0; j < data_.njetsAK8 ; ++j ){
    TLorentzVector myJet;
    if( (*data_.jetAK8_pt).at(j) <= 200.      )continue;
    if( fabs((*data_.jetAK8_eta).at(j)) >= 2.4)continue;
    if( (*data_.jetAK8_IDTight).at(j) != 1    )continue;
    myJet.SetPtEtaPhiE( (*data_.jetAK8_pt).at(j), (*data_.jetAK8_eta).at(j), (*data_.jetAK8_phi).at(j), (*data_.jetAK8_e).at(j) );
    bool isW = false;
    int isMatch = 0;
    int jetID = 99;
    if(runOnMC_){
    
      for( unsigned int p = 0; p < daus.size(); ++p ){
        float dR = daus.at(p).DeltaR(myJet);
        if (dR < 0.8 ) isMatch +=1;
      }   
      
      for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
        if( (*data_.genParticle_status).at(p) != 23) continue;
        TLorentzVector myParton;
        myParton.SetPtEtaPhiE( (*data_.genParticle_pt).at(p), (*data_.genParticle_eta).at(p), (*data_.genParticle_phi).at(p), (*data_.genParticle_e).at(p) );
        float dR = myParton.DeltaR(myJet);
        if (dR > 0.8) continue;
        if( fabs((*data_.genParticle_pdgId).at(p)) < 9) jetID = (*data_.genParticle_pdgId).at(p);
        else if ( fabs((*data_.genParticle_pdgId).at(p)) == 21 or fabs((*data_.genParticle_pdgId).at(p)) == 9) jetID = (*data_.genParticle_pdgId).at(p);
        else jetID = 0;
      }
    }
    
    if(!runOnMC_)isMatch = 0;
    if (isMatch > 1) isW = true;
    if( isSignal_ && !isW ) continue;

    Hist( "denNPV" )->Fill ( data_.nPVs);
    Hist( "denPT" )->Fill ( (*data_.jetAK8_pt).at(j));
    if( runOnMC_ && (fabs(jetID) == 21 or fabs(jetID) < 10) ) {
      Hist( "denPT_QG" )->Fill ( (*data_.jetAK8_pt).at(j));
    }
    
    Hist( "ForROC_Pruned_DEN" )->Fill ( (*data_.jetAK8_tau2).at(j)/(*data_.jetAK8_tau1).at(j) );
    if( (*data_.jetAK8_pt).at(j) <= 300. ) Hist( "PrunedMass_200GeV" )->Fill( (*data_.jetAK8_prunedmass).at(j));
    if( (*data_.jetAK8_pt).at(j) > 500.  ) Hist( "PrunedMass_500GeV" )->Fill( (*data_.jetAK8_prunedmass).at(j));
    if( (*data_.jetAK8_pt).at(j) > 1000. ) Hist( "PrunedMass_1000GeV" )->Fill( (*data_.jetAK8_prunedmass).at(j));

    if( (*data_.jetAK8_pt).at(j) <= 400. )                                          Hist( "ForROC_Pruned_DEN_pt1"  )->Fill ( (*data_.jetAK8_tau2).at(j)/(*data_.jetAK8_tau1).at(j) );
    else if( (*data_.jetAK8_pt).at(j) > 400. && (*data_.jetAK8_pt).at(j) <= 800. )  Hist( "ForROC_Pruned_DEN_pt2"  )->Fill ( (*data_.jetAK8_tau2).at(j)/(*data_.jetAK8_tau1).at(j) );
    else if( (*data_.jetAK8_pt).at(j) > 800. && (*data_.jetAK8_pt).at(j) <= 1200. ) Hist( "ForROC_Pruned_DEN_pt3"  )->Fill ( (*data_.jetAK8_tau2).at(j)/(*data_.jetAK8_tau1).at(j) );
    else if( (*data_.jetAK8_pt).at(j) > 1200.                                     ) Hist( "ForROC_Pruned_DEN_pt4"  )->Fill ( (*data_.jetAK8_tau2).at(j)/(*data_.jetAK8_tau1).at(j) );

    if( (*data_.jetAK8_prunedmass).at(j) <= 105.0 && (*data_.jetAK8_prunedmass).at(j) > 65.0 ){
      Hist( "numNPV_mj" )->Fill ( data_.nPVs);
      Hist( "numPT_mj"  )->Fill ( (*data_.jetAK8_pt).at(j));
      Hist( "ForROC_tau21"  )->Fill ( (*data_.jetAK8_tau2).at(j)/(*data_.jetAK8_tau1).at(j) );
      if( (*data_.jetAK8_pt).at(j) <= 400. )                                          Hist( "ForROC_tau21_pt1"  )->Fill ( (*data_.jetAK8_tau2).at(j)/(*data_.jetAK8_tau1).at(j) );
      else if( (*data_.jetAK8_pt).at(j) > 400. && (*data_.jetAK8_pt).at(j) <= 800. )  Hist( "ForROC_tau21_pt2"  )->Fill ( (*data_.jetAK8_tau2).at(j)/(*data_.jetAK8_tau1).at(j) );
      else if( (*data_.jetAK8_pt).at(j) > 800. && (*data_.jetAK8_pt).at(j) <= 1200. ) Hist( "ForROC_tau21_pt3"  )->Fill ( (*data_.jetAK8_tau2).at(j)/(*data_.jetAK8_tau1).at(j) );
      else if( (*data_.jetAK8_pt).at(j) > 1200.                                     ) Hist( "ForROC_tau21_pt4"  )->Fill ( (*data_.jetAK8_tau2).at(j)/(*data_.jetAK8_tau1).at(j) );

      if( (*data_.jetAK8_tau2).at(j)/(*data_.jetAK8_tau1).at(j) <= 0.45 ){
        Hist( "numNPV_mjtau21" )->Fill ( data_.nPVs);
        Hist( "numPT_mjtau21"  )->Fill ( (*data_.jetAK8_pt).at(j));
        if( runOnMC_ &&  fabs(jetID)  <  9 )                      Hist( "numPT_mjtau21_Q" )->Fill ( (*data_.jetAK8_pt).at(j));
        if( runOnMC_ && (fabs(jetID) == 21 or fabs(jetID) == 9) ) Hist( "numPT_mjtau21_G" )->Fill ( (*data_.jetAK8_pt).at(j));
      }
    }
  }

  for( unsigned int j = 0; j < (data_.jetAK8_puppi_pt)->size() ; ++j ){
    TLorentzVector myJetPUPPI;
    if( (*data_.jetAK8_puppi_pt).at(j) <= 200.      )continue;
    if( fabs((*data_.jetAK8_puppi_eta).at(j)) >= 2.4)continue;
    myJetPUPPI.SetPtEtaPhiE( (*data_.jetAK8_puppi_pt).at(j), (*data_.jetAK8_puppi_eta).at(j), (*data_.jetAK8_puppi_phi).at(j), (*data_.jetAK8_puppi_e).at(j) );
    bool isW = false;
    int isMatch = 0;
    int jetID = 99;
    if(runOnMC_){
      for( unsigned int p = 0; p < daus.size(); ++p ){
        float dR = daus.at(p).DeltaR(myJetPUPPI);
        if (dR < 0.8 ) isMatch +=1;
      }
      
      for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
        if( (*data_.genParticle_status).at(p) != 23) continue;
        TLorentzVector myParton;
        myParton.SetPtEtaPhiE( (*data_.genParticle_pt).at(p), (*data_.genParticle_eta).at(p), (*data_.genParticle_phi).at(p), (*data_.genParticle_e).at(p) );
        float dR = myParton.DeltaR(myJetPUPPI);
        if (dR > 0.8) continue;
        if( fabs((*data_.genParticle_pdgId).at(p)) < 9) jetID = (*data_.genParticle_pdgId).at(p);
        else if ( fabs((*data_.genParticle_pdgId).at(p)) == 21 or fabs((*data_.genParticle_pdgId).at(p)) == 9) jetID = (*data_.genParticle_pdgId).at(p);
        else jetID = 0;
      }
    }
    
    if(!runOnMC_)isMatch = 0;
    if (isMatch > 1) isW = true;
    if( isSignal_ && !isW ) continue;

    Hist( "denNPV_puppi" )->Fill ( data_.nPVs);
    Hist( "denPT_puppi"  )->Fill ( (*data_.jetAK8_puppi_pt).at(j));
    Hist( "ForROC_PUPPI_DEN"  )->Fill ( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j) );
   
    
    if( runOnMC_ && (fabs(jetID) == 21 or fabs(jetID) < 10) ) Hist( "denPT_puppi_QG"  )->Fill ( (*data_.jetAK8_puppi_pt).at(j));
    
    if( (*data_.jetAK8_puppi_pt).at(j) <= 400. )                                           Hist( "ForROC_PUPPI_DEN_pt1"  )->Fill ( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j) );
    if( (*data_.jetAK8_puppi_pt).at(j) > 400. && (*data_.jetAK8_puppi_pt).at(j) <= 800. )  Hist( "ForROC_PUPPI_DEN_pt2"  )->Fill ( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j) );
    if( (*data_.jetAK8_puppi_pt).at(j) > 800. && (*data_.jetAK8_puppi_pt).at(j) <= 1200. ) Hist( "ForROC_PUPPI_DEN_pt3"  )->Fill ( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j) );
    if( (*data_.jetAK8_puppi_pt).at(j) > 1200.                                           ) Hist( "ForROC_PUPPI_DEN_pt4"  )->Fill ( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j) );
    
    float puppiCorr = getPUPPIweight( (*data_.jetAK8_puppi_pt).at(j) , (*data_.jetAK8_puppi_eta).at(j) );
    float puppiMass =  (*data_.jetAK8_puppi_softdrop_massUnCorr).at(j)* puppiCorr;  
    
    //if( (*data_.jetAK8_puppi_pt).at(j) <= 300. ) Hist( "PuppiPrunedMass_200GeV" )->Fill( (*data_.jetAK8_puppi_pruned_massCorr).at(j));
    if( (*data_.jetAK8_puppi_pt).at(j) <= 300. ) Hist( "PuppiSoftdropMass_200GeV" )->Fill( puppiMass);
   // if( (*data_.jetAK8_puppi_pt).at(j) > 500.  ) Hist( "PuppiPrunedMass_500GeV" )->Fill( (*data_.jetAK8_puppi_pruned_massCorr).at(j));
    if( (*data_.jetAK8_puppi_pt).at(j) > 500.  ) Hist( "PuppiSoftdropMass_500GeV" )->Fill( puppiMass);
    //if( (*data_.jetAK8_puppi_pt).at(j) > 1000.  ) Hist( "PuppiPrunedMass_1000GeV" )->Fill( (*data_.jetAK8_puppi_pruned_massCorr).at(j));
    if( (*data_.jetAK8_puppi_pt).at(j) > 1000.  ) Hist( "PuppiSoftdropMass_1000GeV" )->Fill( puppiMass);

    if( puppiMass <= 105.0 && puppiMass > 65.0 ){

      Hist( "numNPV_mj_puppi" )->Fill ( data_.nPVs);
      Hist( "numPT_mj_puppi"  )->Fill ( (*data_.jetAK8_puppi_pt).at(j));
      
      Hist( "ForROC_PUPPItau21"  )->Fill ( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j) );
      if( (*data_.jetAK8_puppi_pt).at(j) <= 400.      )                                            Hist( "ForROC_PUPPItau21_pt1"  )->Fill ( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j) );
      else if( (*data_.jetAK8_puppi_pt).at(j) > 400. && (*data_.jetAK8_puppi_pt).at(j) <= 800. )   Hist( "ForROC_PUPPItau21_pt2"  )->Fill ( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j) );
      else if( (*data_.jetAK8_puppi_pt).at(j) > 800. && (*data_.jetAK8_puppi_pt).at(j) <= 1200. )  Hist( "ForROC_PUPPItau21_pt3"  )->Fill ( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j) );
      else if( (*data_.jetAK8_puppi_pt).at(j) > 1200.                                           )  Hist( "ForROC_PUPPItau21_pt4"  )->Fill ( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j) );

      float DDT = ( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j) ) + 0.063*log( ((*data_.jetAK8_puppi_softdrop_massCorr).at(j)*(*data_.jetAK8_puppi_softdrop_massCorr).at(j)) / ((*data_.jetAK8_puppi_pt).at(j)) );
      Hist( "ForROC_DDT"  )->Fill ( DDT );
      if( (*data_.jetAK8_puppi_pt).at(j) <= 400.      )                                            Hist( "ForROC_DDT_pt1"  )->Fill ( DDT );
      else if( (*data_.jetAK8_puppi_pt).at(j) > 400. && (*data_.jetAK8_puppi_pt).at(j) <= 800. )   Hist( "ForROC_DDT_pt2"  )->Fill ( DDT );
      else if( (*data_.jetAK8_puppi_pt).at(j) > 800. && (*data_.jetAK8_puppi_pt).at(j) <= 1200. )  Hist( "ForROC_DDT_pt3"  )->Fill ( DDT );
      else if( (*data_.jetAK8_puppi_pt).at(j) > 1200.                                           )  Hist( "ForROC_DDT_pt4"  )->Fill ( DDT );

      if( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j) <= 0.40 ){
        Hist( "numNPV_mjtau21_puppi" )->Fill ( data_.nPVs);
        Hist( "numPT_mjtau21_puppi"  )->Fill ( (*data_.jetAK8_puppi_pt).at(j));
        if( runOnMC_ &&  fabs(jetID)  <  9 )                      Hist( "numPT_mjtau21_puppi_Q"  )->Fill ( (*data_.jetAK8_puppi_pt).at(j));
        if( runOnMC_ && (fabs(jetID) == 21 or fabs(jetID) == 9) ) Hist( "numPT_mjtau21_puppi_G"  )->Fill ( (*data_.jetAK8_puppi_pt).at(j));
      }

      if( DDT <= 0.52 ){
        Hist( "numNPV_mjDDT_puppi" )->Fill ( data_.nPVs);
        Hist( "numPT_mjDDT_puppi"  )->Fill ( (*data_.jetAK8_puppi_pt).at(j));
        if( runOnMC_ &&  fabs(jetID)  <  9 )                      Hist( "numPT_mjDDT_puppi_Q" )->Fill ( (*data_.jetAK8_pt).at(j));
        if( runOnMC_ && (fabs(jetID) == 21 or fabs(jetID) == 9) ) Hist( "numPT_mjDDT_puppi_G" )->Fill ( (*data_.jetAK8_pt).at(j));
      }
    }
    
    
    //float puppiPrunedMass =  (*data_.jetAK8_puppi_pruned_massCorr).at(j);  

//     if( puppiPrunedMass <= 105.0 && puppiPrunedMass > 65.0 ){
// 
//       Hist( "numNPV_mj_puppi_pruning" )->Fill ( data_.nPVs);
//       Hist( "numPT_mj_puppi_pruning"  )->Fill ( (*data_.jetAK8_puppi_pt).at(j));
//       
//       if( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j) <= 0.40 ){
//         Hist( "numNPV_mjtau21_puppi_pruning" )->Fill ( data_.nPVs);
//         Hist( "numPT_mjtau21_puppi_pruning"  )->Fill ( (*data_.jetAK8_puppi_pt).at(j));
//         if( runOnMC_ &&  fabs(jetID)  <  9 )                      Hist( "numPT_mjtau21_puppi_Q"  )->Fill ( (*data_.jetAK8_puppi_pt).at(j));
//         if( runOnMC_ && (fabs(jetID) == 21 or fabs(jetID) == 9) ) Hist( "numPT_mjtau21_puppi_G"  )->Fill ( (*data_.jetAK8_puppi_pt).at(j));
//       }
      
      
      Hist( "ForROC_PUPPItau21_pruning"  )->Fill ( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j) );
      if( (*data_.jetAK8_puppi_pt).at(j) <= 400.      )                                            Hist( "ForROC_PUPPItau21_pt1_pruning"  )->Fill ( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j) );
      else if( (*data_.jetAK8_puppi_pt).at(j) > 400. && (*data_.jetAK8_puppi_pt).at(j) <= 800. )   Hist( "ForROC_PUPPItau21_pt2_pruning"  )->Fill ( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j) );
      else if( (*data_.jetAK8_puppi_pt).at(j) > 800. && (*data_.jetAK8_puppi_pt).at(j) <= 1200. )  Hist( "ForROC_PUPPItau21_pt3_pruning"  )->Fill ( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j) );
      else if( (*data_.jetAK8_puppi_pt).at(j) > 1200.                                           )  Hist( "ForROC_PUPPItau21_pt4_pruning"  )->Fill ( (*data_.jetAK8_puppi_tau2).at(j)/(*data_.jetAK8_puppi_tau1).at(j) );
  
  }
    
    
    
 }


////////////////////////////////// SMEAR WITH JET ENERGY SCALE UNCETAINTY AND RESOLUTION /////////////////////////////////////////////////////////////////
double ExoDiBosonAnalysis::getJetEnergyScale( int ak8JetID ){
  
  if( !isSignal_ ) return (*data_.jetAK8_pt).at(ak8JetID);
  float pt = 0;
  
  float ptold    = (*data_.jetAK8_pt).at(ak8JetID); 
  float eta      = (*data_.jetAK8_eta).at(ak8JetID);
  float phi      = (*data_.jetAK8_phi).at(ak8JetID);
  float e        = (*data_.jetAK8_e).at(ak8JetID);   
  
  TLorentzVector AK8jet;
  AK8jet.SetPtEtaPhiE( ptold , eta, phi , e );
  
  float corr     = (*data_.jetAK8_jec).at(ak8JetID);
  float corrUp   = (*data_.jetAK8_jecUp).at(ak8JetID);
  float corrDown = (*data_.jetAK8_jecDown).at(ak8JetID);
  
  float jerSF      = (*data_.jetAK8_jer_sf).at(ak8JetID);
  float jerSFUp    = (*data_.jetAK8_jer_sf_up).at(ak8JetID);
  float jerSFDown  = (*data_.jetAK8_jer_sf_down).at(ak8JetID);
  float jerSigmaPt = (*data_.jetAK8_jer_sigma_pt).at(ak8JetID);
  
  Hist( "JetPt_preSmearing" )->Fill(ptold);
  
  //JEC already applied!
  //JER: Smear all jets by default (! NOT systematics)
  //-----------------------------------------------------------------------------------------------------  
  //https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetResolution#MC_truth_JER_at_13_TeV_new
  //There are two different prescriptions available on how to over-smear reconstructed jets in simulated events so that their pT resolution would be the same as we measure it in data:

  // Scaling: Scale corrected reco jet pT based on the pT difference between matched reco and gen jets:
  // pT->max[0.,pTgen+SF*(pT–pTgen)], where "SF" is the core resolution scaling factor, ie. the measured data/MC resolution ratio.
  // This method only works for jets that are well matched to gen jet, otherwise it can produce large response shifts.
  // The matching should require dR(reco jet, gen jet)<Rcone/2 and dpt=abs(pT-pTgen)<3*sigma_MC, where Rcone is the AK cone parameter, and sigma_MC_pT is jet pT absolute resolution.

  // Smearing: Randomly smear corrected reco jet pT using a Gaussian of the width √(SF^2-1) * sigma_MC_PT.
  // This method only allows one to worsen the resolution (SF>1).

  // We recommend using "hybrid" method: apply scaling for well matched jets; apply smearing for the rest.
  //-----------------------------------------------------------------------------------------------------
  
  if(! (scaleUncPar_.find("JER") != std::string::npos)){  //Dont smear jets used when computing JER systematics!
    //First try scaling:   
    for( int j = 0; j < data_.ngenJetsAK8 ; ++j ){
      TLorentzVector genJet;
      genJet.SetPtEtaPhiE( (*data_.genJetAK8_pt).at(j), (*data_.genJetAK8_eta).at(j), (*data_.genJetAK8_phi).at(j), (*data_.genJetAK8_e).at(j) );
      if( AK8jet.DeltaR(genJet) > 0.4) continue;
      if( jerSF < 1.) pt = max(0., genJet.Pt() + ( jerSF*(AK8jet.Pt()-genJet.Pt()) ) );
      if( ( fabs(AK8jet.Pt()-genJet.Pt()) > (3*AK8jet.Pt()*jerSigmaPt) ) ) continue;
      pt = max(0., genJet.Pt() + ( jerSF*(AK8jet.Pt()-genJet.Pt()) ) );
    }
    //Scaling failed, move to smearing: 
    if( pt == 0){
      if( jerSF < 1.) pt = ptold;
      else{
        pt = tr_->Gaus( ptold, TMath::Sqrt(jerSF*jerSF-1)*(jerSigmaPt*AK8jet.Pt()) ); 
      }
    }
    AK8jet.SetPtEtaPhiE( pt , eta, phi , e );
  }
  
  
  // Now do systematics
  if( scaleUncPar_.find("JESup")   != std::string::npos  ){
    pt = pt/corr; 
    pt = pt*corrUp;
  }
  else if( scaleUncPar_.find("JESdown") != std::string::npos  ){ 
    pt = pt/corr; 
    pt = pt*corrDown;
  } 
  else if( scaleUncPar_.find("JERup") != std::string::npos  ){
    //First try scaling:   
    for( int j = 0; j < data_.ngenJetsAK8 ; ++j ){
      TLorentzVector genJet;
      genJet.SetPtEtaPhiE( (*data_.genJetAK8_pt).at(j), (*data_.genJetAK8_eta).at(j), (*data_.genJetAK8_phi).at(j), (*data_.genJetAK8_e).at(j) );
      if( AK8jet.DeltaR(genJet) > 0.4) continue;
      if( jerSFUp < 1.) pt = max(0., genJet.Pt() + ( jerSF*(AK8jet.Pt()-genJet.Pt()) ) );
      if( ( fabs(AK8jet.Pt()-genJet.Pt()) > (3*AK8jet.Pt()*jerSigmaPt) ) ) continue;
      pt = max(0., genJet.Pt() + ( jerSFUp*(AK8jet.Pt()-genJet.Pt()) ) );
    }
    //Scaling failed, move to smearing: 
    if( pt == 0){
      if( jerSFUp < 1.) pt = ptold;
      else{
        pt = tr_->Gaus( ptold, TMath::Sqrt(jerSFUp*jerSFUp-1)*(jerSigmaPt*AK8jet.Pt()) );
      }
    }
  }

  else if( scaleUncPar_.find("JERdown") != std::string::npos  ){
    //First try scaling:   
    for( int j = 0; j < data_.ngenJetsAK8 ; ++j ){
      TLorentzVector genJet;
      genJet.SetPtEtaPhiE( (*data_.genJetAK8_pt).at(j), (*data_.genJetAK8_eta).at(j), (*data_.genJetAK8_phi).at(j), (*data_.genJetAK8_e).at(j) );
      if( AK8jet.DeltaR(genJet) > 0.4) continue;
      if( jerSFDown < 1.) pt = max(0., genJet.Pt() + ( jerSFDown*(AK8jet.Pt()-genJet.Pt()) ) );
      if( ( fabs(AK8jet.Pt()-genJet.Pt()) > (3*AK8jet.Pt()*jerSigmaPt) ) ) continue;
      pt = max(0., genJet.Pt() + (jerSFDown*(AK8jet.Pt()-genJet.Pt()) ) );
    }
    //Scaling failed, move to smearing: 
    if( pt == 0){
      if(jerSFDown<1.) pt = ptold;
      else{ pt = tr_->Gaus( ptold, TMath::Sqrt(jerSFDown*jerSFDown-1)*(jerSigmaPt*AK8jet.Pt()) ); 
      }
    }
  }
  
  Hist( "JetPt_postSmearing" )->Fill(pt);
  
  // std::cout<< "jet pt after systematic = " << pt << std::endl;
  return pt;
}
////////////////////////////////// SMEAR WITH JET ENERGY SCALE UNCETAINTY AND RESOLUTION /////////////////////////////////////////////////////////////////
double ExoDiBosonAnalysis::getJetMassScale( float oldmass, float jerSigmaPt, TLorentzVector puppijet_tlv, TLorentzVector AK8jet_tlv ){
  
  if( !isSignal_ ) return oldmass;

  float mass             = 0;             
  float jms              = JMS_;
  float jmsUnc           = JMSunc_;
  float jmr              = JMR_;
  float jmrUnc           = JMRunc_;
  float massResolution   = 0;
  
  if( fabs(puppijet_tlv.Eta()) <= 1.3 ){
    massResolution = puppisd_resolution_cen->Eval( puppijet_tlv.Pt() );
  }
  else{
    massResolution = puppisd_resolution_for->Eval( puppijet_tlv.Pt() );
  }
  
  mass = oldmass*jms;
  Hist( "SoftdropMass_preJMR"  )->Fill(mass);

  bool scaled = false;
  if( !(scaleUncPar_.find("JMR")!= std::string::npos) ){
    //First try scaling:
    for( int j = 0; j < data_.ngenJetsAK8 ; ++j ){
      if( (*data_.genJetAK8_pt).at(j) < 0.01 ) continue;
      TLorentzVector genJet;
      genJet.SetPtEtaPhiE( (*data_.genJetAK8_pt).at(j), (*data_.genJetAK8_eta).at(j), (*data_.genJetAK8_phi).at(j), (*data_.genJetAK8_e).at(j) );
      if( AK8jet_tlv.DeltaR(genJet) > 0.4 || ( fabs(AK8jet_tlv.Pt()-genJet.Pt()) > (3*AK8jet_tlv.Pt()*jerSigmaPt))) continue;
      float genMass = (*data_.genJetAK8_softdropmass).at(j);
      mass = max(float(0.), genMass + (jmr*(mass-genMass)));
      Hist( "SoftdropMass_postScaling"  )->Fill( mass );
      scaled = true; 
      break;
    }
    //Scaling failed, move to smearing:
    if( !scaled ){
      mass = tr_->Gaus( mass, TMath::Sqrt(jmr*jmr-1)*(massResolution-1)*mass);
      Hist( "SoftdropMass_postSmearing" )->Fill( mass );
    }
  }
  // Now do systematics
  if( scaleUncPar_.find("JMSup")   != std::string::npos  ){
    mass = mass/jms;
    mass = mass*(jms+jmsUnc);
  }
  else if( scaleUncPar_.find("JMSdown") != std::string::npos  ){
    mass = mass/jms;
    mass = mass*(jms-jmsUnc);
  }
  else if( scaleUncPar_.find("JMRup") != std::string::npos  ){
    for( int j = 0; j < data_.ngenJetsAK8 ; ++j ){
      if( (*data_.genJetAK8_pt).at(j) < 0.01 ) continue;
      float genMass = (*data_.genJetAK8_softdropmass).at(j);
      TLorentzVector genJet;
      genJet.SetPtEtaPhiE( (*data_.genJetAK8_pt).at(j), (*data_.genJetAK8_eta).at(j), (*data_.genJetAK8_phi).at(j), (*data_.genJetAK8_e).at(j) );
      if( AK8jet_tlv.DeltaR(genJet) > 0.4) continue;
      mass = max(float(0.), genMass + ((jmr+jmrUnc)*(mass-genMass)));
    }
  }
  else if( scaleUncPar_.find("JMRdown") != std::string::npos  ){
    for( int j = 0; j < data_.ngenJetsAK8 ; ++j ){
      if( (*data_.genJetAK8_pt).at(j) < 0.01 ) continue;
      float genMass = (*data_.genJetAK8_softdropmass).at(j);
      TLorentzVector genJet;
      genJet.SetPtEtaPhiE( (*data_.genJetAK8_pt).at(j), (*data_.genJetAK8_eta).at(j), (*data_.genJetAK8_phi).at(j), (*data_.genJetAK8_e).at(j) );
      if( AK8jet_tlv.DeltaR(genJet) > 0.4) continue;
      mass = max(float(0.), genMass + ((jmr-jmrUnc)*(mass-genMass)));
    }
  }
  
  Hist( "SoftdropMass_postJMR" )->Fill(mass);
  return mass;
}

///////////////////////// inialize PDF set used for reweighting ////////////////////////////////////////////////////////////////////
void ExoDiBosonAnalysis::InitPDFSet(int pdfset)
{
  if(pdfset>0)
  {
    LHAPDF::initPDFSet(pdfset,0);
    const int NUMBER = LHAPDF::numberPDF();
    for(int n=0;n<=NUMBER;n++)
    {
       nEvents_wPDF_.push_back(0);
       nPassed_wPDF_.push_back(0);   
    }
  }
  if(pdfset==0)
  {
    nEvents_wPDF_.push_back(0);
    nPassed_wPDF_.push_back(0);    
      
  }
    
}

///////////////////////// calculate PDF weight for given pdfset ////////////////////////////////////////////////////////////////////
std::vector<double> ExoDiBosonAnalysis::PDFweight(int pdfset)
{
 //LHAPDF::initPDFSet(pdfset,0);
 
 vector<double> weight;
 if(data_.PDF_x->size() >2 or data_.PDF_x->size()<2)
    {
     m_logger << INFO << " size larger/smaller 2 " << SLogger::endmsg;
     return weight;
    }
 float x1 = data_.PDF_x->at(0);
 float x2 = data_.PDF_x->at(1);
 float Q  = data_.qScale;
 int fl1 = data_.PDF_id->at(0);
 int fl2 = data_.PDF_id->at(1);
 if(fl1==21)
 {
   fl1 =0;   
 }
 if(fl2==21)
 {
  fl2 = 0;   
 }
 
 
 //int used_pdfset = 22; //what is the number if the used PDF set? find here: https://lhapdf.hepforge.org/pdfsets.html Which PDF set used?
 float x1pdf1   =   data_.PDF_xPDF->at(0);
 float x2pdf2   =   data_.PDF_xPDF->at(1);
 if(x1pdf1 ==0 and x2pdf2==0)
 {
   //LHAPDF::initPDFSet(262400,0);  
   LHAPDF::usePDFMember(0);  
   x1pdf1 = LHAPDF::xfx(x1, Q,fl1);
   x2pdf2 = LHAPDF::xfx( x2, Q, fl2);
   
   //LHAPDF::initPDFSet(pdfset,0);   
 }
 //float x1pdf1    = LHAPDF::xfx(used_pdfset,x1,Q,fl1);
 //float x2pdf2    = LHAPDF::xfx(used_pdfset,x2,Q,fl2);
 double x1newpdf1 = 1;
 double x2newpdf2 = 1;

 m_logger << DEBUG << " flavour 1 : "<< fl1 << " flavour 2 : " << fl2 << SLogger::endmsg;
// m_logger << DEBUG << "x1 : " << x1 << " x2 : "<< x2 << " Q : "<< Q<< SLogger::endmsg;
if(PDFSET_>0)
{
 const int NUMBER = LHAPDF::numberPDF();
 for(int n=0;n<=NUMBER;n++)
 {
    if(pdfset>0)
    {
    LHAPDF::usePDFMember(n);
    x1newpdf1 = LHAPDF::xfx(x1, Q,fl1);
    x2newpdf2 = LHAPDF::xfx( x2, Q, fl2);
    }
//   m_logger << DEBUG << "x1newpdf1 : "<< x1newpdf1 << " x2newpdf2 : " << x2newpdf2 << SLogger::endmsg;
  weight.push_back( x1newpdf1*x2newpdf2/(x1pdf1*x2pdf2));
  //m_logger << DEBUG << " new PDF weight : "<< weight.at(n) << SLogger::endmsg;
 }
}
else
{
  weight.push_back((x1*x2)/(x1pdf1*x2pdf2));  
}
//  m_logger << DEBUG << "x1newpdf1 : "<< x1newpdf1 << " x2newpdf2 : " << x2newpdf2 << SLogger::endmsg;
//  m_logger << DEBUG << "x1pdf1 : "<< x1pdf1 << " x2pdf2 : " << x2pdf2 << SLogger::endmsg;
//  m_logger << DEBUG << "weight : " << weight.at(0) << SLogger::endmsg;
    
 return weight;   
}

////////////////////////////////////// calculate reweighted number of events //////////////////////////////////////////////////////////////////////

void ExoDiBosonAnalysis::calcPDFweight(bool all)
{
   if(PDFSET_>=0)
   {

   std::vector<double> weights = PDFweight(PDFSET_);
   int NUMBER = weights.size();
   
   for(int n=0;n<NUMBER;n++)
   {
     if(all)
     {
        nEvents_wPDF_.at(n) += weights.at(n); 
     }
     else
     {
        nPassed_wPDF_.at(n) +=weights.at(n);
        if( scaleUncPar_.find("PDF")!=std::string::npos)
        {
          pdfweight_ = weights;   
        }
     }
   }
   }
   //m_logger << DEBUG << "test : "<< nEvents.at(0)<< SLogger::endmsg;
}


bool ExoDiBosonAnalysis::passedTau21Selections(std::string cat)
{
 bool passedTau21Cut=0;
 float nsub_jet1 = Vcand.at(0).tau2/Vcand.at(0).tau1;
 float nsub_jet2 = Vcand.at(1).tau2/Vcand.at(1).tau1;
 if(Channel_.find("VV")!=std::string::npos)
 {
   if (cat.find("HP")!=std::string::npos && nsub_jet1 > Tau21HPLow_ && nsub_jet1 <= Tau21HPHigh_ && nsub_jet2 > Tau21HPLow_ && nsub_jet2 <= Tau21HPHigh_  ){
          passedTau21Cut = true ;
        }

    else if(cat.find("LP")!=std::string::npos &&  (( nsub_jet1 > Tau21HPLow_ && nsub_jet1 <= Tau21HPHigh_ && nsub_jet2 > Tau21Low_ && nsub_jet2 <= Tau21High_  ) ||
                  (nsub_jet2 > Tau21HPLow_ && nsub_jet2 <= Tau21HPHigh_ && nsub_jet1 > Tau21Low_ && nsub_jet1 <= Tau21High_) )) {
            passedTau21Cut = true;
          }
    else if(cat.find("NP")!=std::string::npos)
        passedTau21Cut = true;
 }
 if(Channel_.find("qV")!=std::string::npos)
 {
    if( cat.find("HP")!=std::string::npos &&( nsub_jet1 > Tau21HPLow_ && nsub_jet1 <= Tau21HPHigh_ )){
            passedTau21Cut = true;
          }
    else if(cat.find("LP")!=std::string::npos && ( nsub_jet1 > Tau21Low_ && nsub_jet1 <= Tau21High_ )){
           passedTau21Cut = true;
            }
    else if (cat.find("NP")!=std::string::npos) {
           passedTau21Cut = true;
          }  
     
 }
 return passedTau21Cut;
}



bool ExoDiBosonAnalysis::preparationOfHistosForPUreweighting()
{
     double puw;
     if(Channel_.find("PU")==std::string::npos and  Channel_.find("VVdijet")==std::string::npos and Channel_.find("qVdijet")==std::string::npos)
        return 0;
     else if(runOnMC_ == true )
     {
        std::vector<int>* TruePU = data_.nPUTrue;
        if(TruePU->size()==0)
        {
            TruePU = data_.nPuVtxTrue;   
        }
  
        for( unsigned int v = 0; v < TruePU->size(); ++v ){
        if( (*data_.bX)[v] == 0 ){ puw = puweight_;//PUWeight_.getPUWeight( (*TruePU)[v] );
        
        Hist( "nPUVtxTrue" )->Fill((TruePU)->at(v),lumiweight_*genweight_);
        Hist( "nPUVtx"     )->Fill((data_.nPuVtx)->at(v),lumiweight_*genweight_);
        Hist( "nPUVtx_rew" )->Fill((data_.nPuVtx)->at(v), puw*lumiweight_*genweight_);
        Hist( "nPUVtxTrue_rew" )->Fill((TruePU)->at(v), puw*lumiweight_*genweight_);
        Hist( "nPUVtx2"     )->Fill((data_.PV_N),lumiweight_*genweight_);
        Hist( "nPUVtx2_rew" )->Fill((data_.PV_N), puw*lumiweight_*genweight_);
        return 1;
        }
        }
         
//         for( unsigned int i =0; i< (data_.bX)->size() ;i++)
//         {
//             if((data_.bX)->at(i)==0)
//             {
//                 Hist( "nPUVtxTrue" )->Fill((data_.nPuVtxTrue)->at(i),lumiweight_*genweight_);
//                 Hist( "nPUVtx"     )->Fill((data_.nPuVtx)->at(i),lumiweight_*genweight_);
//                 Hist( "nPUVtx_rew" )->Fill((data_.nPuVtx)->at(i), PUWeight_.getPUWeight( (data_.nPuVtxTrue)->at(i) )*lumiweight_*genweight_);
//                 Hist( "nPUVtxTrue_rew" )->Fill((data_.nPuVtxTrue)->at(i), PUWeight_.getPUWeight( (data_.nPuVtxTrue)->at(i) )*lumiweight_*genweight_);
//                 return 1;
//             }
//         }
        return 1;
     }
     else
     {
       Hist( "nPUVtx" )->Fill( data_.nPVs ); //what about PV_N?
       Hist( "nPUVtx2" )->Fill( data_.PV_N ); //what about PV_N?
       return 1;   
     }
}






////////////////////////////////////////////////////// RHO RATIO (Sal) ////////////////////////////////////////////////////////////////////////////
// void ExoDiBosonAnalysis::setPredictedDistribution()
// {
//   fMistag_ = TFile::Open( "data/mistagRate_mod_wjetsmc.root" );
//   hMistag_ = (TH1D*)fMistag_->Get("rLoMod");
//
//   hvv_pred = new PredictedDistribution (hMistag_, "hvv_pred", "Predicted VV Mass", 100, 0, 5000);
//   hvv_pred->GetTaggableHist()->SetDirectory(0);
//   hvv_pred->GetObservedHist()->SetDirectory(0);
//   hvv_pred->GetPredictedHist()->SetDirectory(0);
//
// }
