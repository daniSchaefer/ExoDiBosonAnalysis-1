#include "include/HistosManager.h"
#include "include/ExoDiBosonAnalysis.h"
#include "include/Utilities.h"

#include <TProfile.h>
#include <TH1F.h>
#include <TH2F.h>

////////////////////////////////////////////////////////////////////
HistosManager::HistosManager( ExoDiBosonAnalysis* theAnalysis):theAnalysis_( theAnalysis )
{

}

////////////////////////////////////////////////////////////////////
HistosManager::~HistosManager( void ){


}

////////////////////////////////////////////////////////////////////
void HistosManager::bookHistos( std::string Channel_ ){
  theAnalysis_->Book( TH1F( "gen_COS_Theta1"           , "cos(theta1) ", 100	, -1.	, 1.	) );  
  theAnalysis_->Book( TH1F( "Mjet_gen_V"           , "m_jet ", 100	, 0.	, 300.	) ); 
  theAnalysis_->Book( TH1F( "Mjet_gen_Q"           , "m_jet ", 100	, 0.	, 300.	) ); 
  theAnalysis_->Book( TH1F( "Mjet_reco_V"           , "m_jet ", 100	, 0.	, 300.	) ); 
  theAnalysis_->Book( TH1F( "Mjet_reco_Q"           , "m_jet ", 100	, 0.	, 300.	) ); 
  theAnalysis_->Book( TH1F( "Mjet_gen_V"           , "m_jet ", 100	, 0.	, 300.	) ); 
  theAnalysis_->Book( TH1F( "Mjet_reco_V_res"      , "m_jet ", 100	, 0.	, 300.	) );
  theAnalysis_->Book( TH1F( "Mjet_reco_V_nonres"  , "m_jet ", 100	, 0.	, 300.	) );
  
  theAnalysis_->Book( TH1F( "QVjet_missID"           , "miss ID ", 2	, 0.	, 1.	) ); 
  
  
  
  theAnalysis_->Book( TH1F( "Mjj_allHadGen"           , "m_jj_allHadronicGen", 1000	, 0.	, 7000.	) );  
  theAnalysis_->Book( TH1F( "PrunedMass_200GeV"       ,   "PrunedMass_200GeV"       , 200, 0, 200 ) );
  theAnalysis_->Book( TH1F( "PuppiPrunedMass_200GeV"  ,   "PuppiPrunedMass_200GeV"  , 200, 0, 200 ) );
  theAnalysis_->Book( TH1F( "PuppiSoftdropMass_200GeV",   "PuppiSoftdropMass_200GeV", 200, 0, 200 ) );
  
  theAnalysis_->Book( TH1F( "PrunedMass_500GeV"       ,   "PrunedMass_500GeV"       , 200, 0, 200 ) );
  theAnalysis_->Book( TH1F( "PuppiPrunedMass_500GeV"  ,   "PuppiPrunedMass_500GeV"  , 200, 0, 200 ) );
  theAnalysis_->Book( TH1F( "PuppiSoftdropMass_500GeV",   "PuppiSoftdropMass_500GeV", 200, 0, 200 ) );
  
  theAnalysis_->Book( TH1F( "PrunedMass_1000GeV"       ,   "PrunedMass_1000GeV"       , 200, 0, 200 ) );
  theAnalysis_->Book( TH1F( "PuppiPrunedMass_1000GeV"  ,   "PuppiPrunedMass_1000GeV"  , 200, 0, 200 ) );
  theAnalysis_->Book( TH1F( "PuppiSoftdropMass_1000GeV",   "PuppiSoftdropMass_1000GeV", 200, 0, 200 ) );
  
     
 theAnalysis_->Book( TH1F( "SoftdropMass_preJMR", "SoftdropMass_preJMR"       , 200, 0, 200 ) );
 theAnalysis_->Book( TH1F( "SoftdropMass_postJMR", "SoftdropMass_postJMR"       , 200, 0, 200 ) );
 theAnalysis_->Book( TH1F( "SoftdropMass_postSmearing", "SoftdropMass_postSmearing"     , 200, 0, 200 ) );
 theAnalysis_->Book( TH1F( "SoftdropMass_postScaling", "SoftdropMass_postScaling"     , 200, 0, 200 ) );
 //theAnalysis_->Book( TH1F("PUPPI_SoftdopMass_NOCorr", 200, 0, 200 ) );
 //theAnalysis_->Book( TH1F("PUPPI_SoftdopMass_eta1v3_NOCorr", 200, 0, 200 ) );
 //theAnalysis_->Book( TH1F("PUPPI_SoftdopMass_etaUPv1v3_NOCorr", 200, 0, 200 ) );
 
 theAnalysis_->Book( TH1F( "JetPt_preSmearing", "JetPt_preSmearing"      , 200, 0, 2000 ) );
 theAnalysis_->Book( TH1F( "JetPt_postSmearing","JetPt_postSmearing"     , 200, 0, 2000 ) );
 
 
 theAnalysis_->Book( TH1F( "runNumber", "run number"       , 1000, 251000, 252000 ) );
 theAnalysis_->Book( TH1F( "nVertices", "number of PVs"    ,  50, 0. ,  50. ) );
 theAnalysis_->Book( TH1F( "Rho", "Rho"    ,  60, 0. ,  30. ) );
 theAnalysis_->Book( TH1F( "PV_rho", "PV Rho"    ,  60, 0.1 ,  0.25 ) );
 theAnalysis_->Book( TH1F( "sumGenWeight"                  , "sumGenWeight", 1	, 0.5, 1.5		) );
 
 if( Channel_.find("VVdijet")!=std::string::npos || Channel_.find("qVdijet")!=std::string::npos ){
   
     
   theAnalysis_->Book( TH1F( "Mjj_genMatched"           , "M_{jj} ", 7000	, 0.	, 7000.	) );
   
   // theAnalysis_->Book( TH2F( "prunedJECvsPT" , "Pruned JEC vs. p_{T}" , 23  , 0.  , 2300., 40, 0.,2.  ) );
   // theAnalysis_->Book( TH2F( "puppiJECvsPT"  , " PUPPI JEC vs. p_{T}" , 23  , 0.  , 2300., 40, 0.,2.  ) );
   
   theAnalysis_->Book( TH2F( "PUPPISDvsNPV" , "PUPPI softdrop vs. nPV" , 50	, 0.	, 50., 200. ,0., 200.	) );
   theAnalysis_->Book( TH2F( "PUPPISDvsETA" , "PUPPI softdrop vs. #eta", 50	, -2.5	, 2.5, 200. ,0., 200.	) );
   
   
   theAnalysis_->Book( TProfile( "prunedJECvsPT" , "Pruned JEC vs. p_{T}" , 23	, 0.	, 2300., 0.,2.	) );
   theAnalysis_->Book( TProfile( "puppiJECvsPT"  , " PUPPI JEC vs. p_{T}" , 23	, 0.	, 2300., 0.,2.	) );
   theAnalysis_->Book( TProfile( "puppiJECvsPT_eta1v3"  , " PUPPI JEC vs. p_{T} (|#eta|<1.3)" , 23	, 0.	, 2300., 0.,2.	) );
   theAnalysis_->Book( TProfile( "puppiJECvsPT_etaUP1v3"  , " PUPPI JEC vs. p_{T} (|#eta|<1.3)" , 23	, 0.	, 2300., 0.,2.	) );
   theAnalysis_->Book( TH1F( "gen_Mass"  , "Mass (GeV)" , 80	, 0.	, 400.	) );
   theAnalysis_->Book( TH1F( "gen_PrunedMass"  , "Pruned mass (GeV)" , 40	, 0.	, 200.	) );
   theAnalysis_->Book( TH1F( "gen_Tau21"       , "#tau_{21}"         , 20	, 0.	, 1.	  ) );
   
   
   theAnalysis_->Book( TProfile( "gen_chsJEC_eta1v3" , "Pruned JEC vs. p_{T}" , 23	, 0.	, 2300., 0.,2.	) );
   theAnalysis_->Book( TProfile( "gen_chsJEC_etaUP1v3" , "Pruned JEC vs. p_{T}" , 23	, 0.	, 2300., 0.,2.	) );
   
   theAnalysis_->Book( TH1F( "gen_eta"  , "#eta (GeV)" , 50	, -2.5	, 2.5) );
   theAnalysis_->Book( TH1F( "gen_nPV_eta1v3"  , "p_{T} (GeV)" , 25	, 0.	, 50.) );
   theAnalysis_->Book( TH1F( "gen_nPV_etaUP1v3"  , "p_{T} (GeV)" , 25	, 0.	, 50.) );
   
   theAnalysis_->Book( TH1F( "gen_pt_eta1v3"  , "p_{T} (GeV)" , 46	, 0.	, 2300.) );
   theAnalysis_->Book( TH1F( "gen_pt_etaUP1v3"  , "p_{T} (GeV)" , 46	, 0.	, 2300.) );
   theAnalysis_->Book( TH1F( "gen_SoftdropMass_eta1v3"  , "Softdrop mass (GeV)"   , 200	, 0.	, 200.) );
   theAnalysis_->Book( TH1F( "gen_SoftdropMass_etaUP1v3"  , "Softdrop mass (GeV)" , 200	, 0.	, 200.) ); 
   
   
   theAnalysis_->Book( TH1F( "PUPPIcorr_etaUP1v3"  , "PUPPI corrections" , 150	, 0.	, 1.5) );
   theAnalysis_->Book( TH1F( "PUPPIcorr_eta1v3"  , "PUPPI corrections" , 150	, 0.	, 1.5) );
     
  theAnalysis_->Book( TH1F( "gen_SoftdropMass_NEWCORR"  , "Softdrop mass (GeV)" , 200	, 0.	, 200.) );   
   theAnalysis_->Book( TH1F( "gen_SoftdropMass_eta1v3_NEWCORR"  , "Softdrop mass (GeV)" , 200	, 0.	, 200.) );
   theAnalysis_->Book( TH1F( "gen_SoftdropMass_etaUP1v3_NEWCORR", "Softdrop mass (GeV)" , 200	, 0.	, 200.) ); 
   
//    theAnalysis_->Book( TH1F( "rec_SoftdropMass_eta1v3_NEWCORR"  , "Softdrop mass (GeV)" , 200	, 0.	, 200.) );
//    theAnalysis_->Book( TH1F( "rec_SoftdropMass_etaUP1v3_NEWCORR", "Softdrop mass (GeV)" , 200	, 0.	, 200.) ); 
   
   
   theAnalysis_->Book( TH1F( "gen_SoftdropMass_pt500"  , "Softdrop mass (GeV) (p_{T} > 500)" , 40	, 0.	, 200.) );
   theAnalysis_->Book( TH1F( "gen_SoftdropMassCHSCorr"  , "Softdrop mass (GeV) (CHS L2L3)" , 40	, 0.	, 200.) );     
   theAnalysis_->Book( TH1F( "gen_SoftdropMass"  , "Softdrop mass (GeV)" , 40	, 0.	, 200.) );
   theAnalysis_->Book( TH1F( "gen_SoftdropMassUnCorr"  , "Softdrop mass (GeV)" , 40	, 0.	, 200.) );
   theAnalysis_->Book( TH1F( "gen_PUPPITau21"    , "PUPPI #tau_{21}"     , 20	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "gen_DDT"           , "DDT"                 , 20	, 0.	, 1.	) );
   
   
   theAnalysis_->Book( TH1F( "GenAK8SoftdropMass"  , "Gen AK8 Softdrop mass (GeV)" , 200	, 0.	, 200.) );
   theAnalysis_->Book( TH1F( "GenAK8SoftdropMass_eta1v3"  , "Gen AK8 Softdrop mass (GeV)" , 200	, 0.	, 200.) );
   theAnalysis_->Book( TH1F( "GenAK8SoftdropMass_etaUP1v3"  , "Gen AK8 Softdrop mass (GeV)" , 200	, 0.	, 200.) );
   
   theAnalysis_->Book( TH1F( "GenAK8SoftdropMass_CORR"  , "Gen AK8 Softdrop mass (GeV)" , 200	, 0.	, 200.) );
   theAnalysis_->Book( TH1F( "GenAK8SoftdropMass_eta1v3_CORR"  , "Gen AK8 Softdrop mass (GeV)" , 200	, 0.	, 200.) );
   theAnalysis_->Book( TH1F( "GenAK8SoftdropMass_etaUP1v3_CORR"  , "Gen AK8 Softdrop mass (GeV)" , 200	, 0.	, 200.) );
   
   theAnalysis_->Book( TH1F( "GenAK8PrunedMass"  , "Gen AK8 Pruned mass (GeV)" , 200	, 0.	, 200.) );
   theAnalysis_->Book( TH1F( "GenAK8PrunedMass_eta1v3"  , "Gen AK8 Pruned mass (GeV)" , 200	, 0.	, 200.) );
   theAnalysis_->Book( TH1F( "GenAK8PrunedMass_etaUP1v3"  , "Gen AK8 Pruned mass (GeV)" , 200	, 0.	, 200.) );
   

   theAnalysis_->Book( TH1F( "massShift_pruning", "Reco-Gen/Reco mass", 200, -1., 1. ));
   theAnalysis_->Book( TH1F( "massShift_pruning_eta1v3", "Reco-Gen/Reco mass", 200, -1., 1. ));
   theAnalysis_->Book( TH1F( "massShift_pruning_etaUP1v3", "Reco-Gen/Reco mass", 200, -1., 1. ));
   theAnalysis_->Book( TH1F( "massShift_softdrop", "Reco-Gen/Reco mass", 200, -1., 1. ));
   theAnalysis_->Book( TH1F( "massShift_softdrop_eta1v3", "Reco-Gen/Reco mass", 200, -1., 1. ));
   theAnalysis_->Book( TH1F( "massShift_softdrop_etaUP1v3", "Reco-Gen/Reco mass", 200, -1., 1. ));
   
   theAnalysis_->Book( TH1F( "ForROC_Pruned_DEN"    , "#tau_{21}" , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_Pruned_DEN_pt1", "#tau_{21}" , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_Pruned_DEN_pt2", "#tau_{21}" , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_Pruned_DEN_pt3", "#tau_{21}" , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_Pruned_DEN_pt4", "#tau_{21}" , 100	, 0.	, 1.	) );
   
   theAnalysis_->Book( TH1F( "ForROC_PUPPI_DEN", "PUPPI #tau_{21}" , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_PUPPI_DEN_pt1", "PUPPI #tau_{21}" , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_PUPPI_DEN_pt2", "PUPPI #tau_{21}" , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_PUPPI_DEN_pt3", "PUPPI #tau_{21}" , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_PUPPI_DEN_pt4", "PUPPI #tau_{21}" , 100	, 0.	, 1.	) );
   
   theAnalysis_->Book( TH1F( "ForROC_PUPPItau21", "PUPPI #tau_{21}" , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_PUPPItau21_pt1", "PUPPI #tau_{21}" , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_PUPPItau21_pt2", "PUPPI #tau_{21}" , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_PUPPItau21_pt3", "PUPPI #tau_{21}" , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_PUPPItau21_pt4", "PUPPI #tau_{21}" , 100	, 0.	, 1.	) );
   
   theAnalysis_->Book( TH1F( "ForROC_DDT", "DDT" , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_DDT_pt1", "DDT" , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_DDT_pt2", "DDT" , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_DDT_pt3", "DDT" , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_DDT_pt4", "DDT" , 100	, 0.	, 1.	) );
   
   theAnalysis_->Book( TH1F( "ForROC_tau21", "#tau_{21}"     , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_tau21_pt1", "#tau_{21}" , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_tau21_pt2", "#tau_{21}" , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_tau21_pt3", "#tau_{21}" , 100	, 0.	, 1.	) );
   theAnalysis_->Book( TH1F( "ForROC_tau21_pt4", "#tau_{21}" , 100	, 0.	, 1.	) );
   
   theAnalysis_->Book( TH1F( "denPT"          , " AK8 jet pt" , 23	, 0.	, 2300.	) );
   theAnalysis_->Book( TH1F( "denPT_QG"          , " AK8 jet pt" , 23	, 0.	, 2300.	) );
   theAnalysis_->Book( TH1F( "denNPV"         , "nPVs"        , 20	, 0.	, 40.	) );
   
   theAnalysis_->Book( TH1F( "numPT_mj"       , " AK8 jet pt" , 23	, 0.	, 2300.	) );
   theAnalysis_->Book( TH1F( "numNPV_mj"      , "nPVs"        , 20	, 0.	, 40.	) );
   
   theAnalysis_->Book( TH1F( "numPT_mjtau21"  , " AK8 jet pt" , 23	, 0.	, 2300.	) );
   theAnalysis_->Book( TH1F( "numPT_mjtau21_Q"  , " AK8 jet pt" , 23	, 0.	, 2300.	) );
   theAnalysis_->Book( TH1F( "numPT_mjtau21_G"  , " AK8 jet pt" , 23	, 0.	, 2300.	) );
   theAnalysis_->Book( TH1F( "numNPV_mjtau21" , "nPVs"        , 20	, 0.	, 40.	) );
   
   theAnalysis_->Book( TH1F( "denPT_puppi"          , " AK8 jet pt" , 23	, 0.	, 2300.	) );
   theAnalysis_->Book( TH1F( "denPT_puppi_QG"       , " AK8 jet pt" , 23	, 0.	, 2300.	) );
   theAnalysis_->Book( TH1F( "denNPV_puppi"         , "nPVs"        , 20	, 0.	, 40.	) );
   
   theAnalysis_->Book( TH1F( "numPT_mj_puppi"       , " AK8 jet pt" , 23	, 0.	, 2300.	) );
   theAnalysis_->Book( TH1F( "numNPV_mj_puppi"      , "nPVs"        , 20	, 0.	, 40.	) );
   
   theAnalysis_->Book( TH1F( "numPT_mjtau21_puppi"  , " AK8 jet pt" , 23	, 0.	, 2300.	) );
   theAnalysis_->Book( TH1F( "numPT_mjtau21_puppi_Q"  , " AK8 jet pt" , 23	, 0.	, 2300.	) );
   theAnalysis_->Book( TH1F( "numPT_mjtau21_puppi_G"  , " AK8 jet pt" , 23	, 0.	, 2300.	) );
   theAnalysis_->Book( TH1F( "numNPV_mjtau21_puppi" , "nPVs"        , 20	, 0.	, 40.	) );
   
   theAnalysis_->Book( TH1F( "numPT_mjDDT_puppi"  , " AK8 jet pt" , 23	, 0.	, 2300.	) );
   theAnalysis_->Book( TH1F( "numPT_mjDDT_puppi_Q"  , " AK8 jet pt" , 23	, 0.	, 2300.	) );
   theAnalysis_->Book( TH1F( "numPT_mjDDT_puppi_G"  , " AK8 jet pt" , 23	, 0.	, 2300.	) );
   theAnalysis_->Book( TH1F( "numNPV_mjDDT_puppi" , "nPVs"        , 20	, 0.	, 40.	) );
   
   theAnalysis_->Book( TH1F( "numNPV_mj_puppi_pruning"      ,"numNPV_mj_puppi_pruning"       , 20	  , 0.	, 40.	  ) );
   theAnalysis_->Book( TH1F( "numPT_mj_puppi_pruning"       ,"numPT_mj_puppi_pruning"        , 23	  , 0.	, 2300.	) );
   theAnalysis_->Book( TH1F( "numNPV_mjtau21_puppi_pruning" ,"numNPV_mjtau21_puppi_pruning"  , 20	  , 0.	, 40.	  ) );
   theAnalysis_->Book( TH1F( "numPT_mjtau21_puppi_pruning"  ,"numPT_mjtau21_puppi_pruning"   , 23	  , 0.	, 2300.	) );
   theAnalysis_->Book( TH1F( "ForROC_PUPPItau21_pruning"    ,"ForROC_PUPPItau21_pruning"     , 100	, 0.	, 1.	  ) );
   theAnalysis_->Book( TH1F( "ForROC_PUPPItau21_pt1_pruning","ForROC_PUPPItau21_pt1_pruning" , 100	, 0.	, 1.	  ) );
   theAnalysis_->Book( TH1F( "ForROC_PUPPItau21_pt2_pruning","ForROC_PUPPItau21_pt2_pruning" , 100	, 0.	, 1.	  ) );
   theAnalysis_->Book( TH1F( "ForROC_PUPPItau21_pt3_pruning","ForROC_PUPPItau21_pt3_pruning" , 100	, 0.	, 1.	  ) );
   theAnalysis_->Book( TH1F( "ForROC_PUPPItau21_pt4_pruning","ForROC_PUPPItau21_pt4_pruning" , 100	, 0.	, 1.	  ) );
   
   theAnalysis_->Book( TH1F( "gen_PuppiPrunedMass_Uncorr", "gen_PuppiPrunedMass_Uncorr", 200	, 0.	, 200.) );
   theAnalysis_->Book( TH1F( "gen_PuppiPrunedMass_Corr"  , "gen_PuppiPrunedMass_Corr"  , 200	, 0.	, 200.) );     

	
  theAnalysis_->Book( TH1F( "METsumET", "MET/sumEt"      , 100	, 0.	, 1.	) );
  theAnalysis_->Book( TH1F( "MET"   , "MET"  , 500	, 0.	, 1000.	) );
 
  // theAnalysis_->Book( TH1F( "LeptonJet_JetID"   , "0 = AllLooseJets, 1 = Jets+tightID, 2 = GenLeptonMatch(EleMu), 3 = GenLeptonMatch(EleMuTau), 4 = GenLeptonMatch+tightID, 5 =RecoLeptonMatch, 6 =RecoLeptonMatch+TightID"  , 7  , 0.  , 7.  ) );
 
  /* V candidate */
  theAnalysis_->Book( TH1F( "Mjj_afterPrunedMass"           , "M_{jj} "	   								  , 100	, 1000.	, 6000.	) );
  theAnalysis_->Book( TH1F( "Mjj_final"                     , "M_{jj} "	   								  , 7000	, 0.	, 7000.	) );
  theAnalysis_->Book( TH1F( "Mjj"                           , "M_{jj} "                     , 7000	, 0.	, 7000.	) );
  theAnalysis_->Book( TH1F( "MjjAK4"  					 					 		, "M_{jj} AK4 "	   								  , 7000	, 0.	, 7000.	) );
  theAnalysis_->Book( TH1F( "DeltaEta"	 	  															, "#Delta#eta_{jj}, Mjj cut"	   				 	, 31	, 0.	, 1.5		) );
  theAnalysis_->Book( TH1F( "DeltaR"	 	  													 		, "#DeltaR_{jj}, Mjj cut"	   				 	  , 40	, 0.	, 4.		) );
  theAnalysis_->Book( TH1F( "PrunedMass"																		, "pruned M_{j}, dEta+Mjj cut"		, 60	, 0.	, 300.	) );
  theAnalysis_->Book( TH1F( "PrunedMass_afterTau21"																		, "pruned M_{j}"		, 60	, 0.	, 300.	) );
  theAnalysis_->Book( TH1F( "Tau21_afterPrunedMass"              ,"#tau_{21}",20,0.,1. ) );
  theAnalysis_->Book( TH1F( "PUPPITau21_afterPUPPISoftdropMass"  ,"PUPPI #tau_{21}",20,0.,1. ) );
  theAnalysis_->Book( TH1F( "PuppiSoftdropMass"																	, "softdrop M_{j}, dEta+Mjj cut	"	, 60	, 0.	, 300.	) );
  theAnalysis_->Book( TH1F( "PuppiSoftdropMass_afterTau21"                      , "PUPPI softdrop M_{j}"		, 60	, 0.	, 300.	) );
  theAnalysis_->Book( TH1F( "Mass"																	    , " M_{j}, dEta+Mjj cut	"	, 60	, 0.	, 300.	) );
  theAnalysis_->Book( TH1F( "Tau21", "#tau_{21}" 	 				   , 20	, 0. , 1. 	) );  
  theAnalysis_->Book( TH1F( "Pt" 	  																, " AK8 jet pt"						, 160	, 200.	, 2000.	) );
  theAnalysis_->Book( TH1F( "Pt_jet1" 	  																, " AK8 jet1 pt"						, 160	, 200.	, 2000.	) );
  theAnalysis_->Book( TH1F( "Pt_jet2" 	  																, " AK8 jet2 pt"						, 160	, 200.	, 2000.	) );
  theAnalysis_->Book( TH1F( "Eta"	  																, " AK8 jet eta"						, 50	, -2.5, 2.5		) );
  theAnalysis_->Book( TH1F( "Phi"	  																, " AK8 jet phi"						, 64	, -3.2, 3.2		) );
  theAnalysis_->Book( TH1F( "Mass" 	  															, " AK8 jet mass"					, 60	, 0. , 300.	) );
  theAnalysis_->Book( TH1F( "Weight", "Weight", 100, 0, 5));
  theAnalysis_->Book( TH1F( "PUWeight", "PUWeight", 100, 0, 5));
  theAnalysis_->Book( TH1F( "LumiWeight", "LumiWeight", 100, 0, 5));
  theAnalysis_->Book( TH1F( "GenWeight", "GenWeight", 100, 0, 5));
  theAnalysis_->Book( TH1F( "PtWeight", "PtWeight", 100, 0, 5));
  theAnalysis_->Book( TH1F( "BtagWeight", "BtagWeight", 100, 0, 5));
  theAnalysis_->Book( TH1F( "HLTWeight", "HLTWeight", 100, 0, 5));
  
  theAnalysis_->Book( TH1F( "nPUVtxTrue", "nPUVtxTrue", 70, 0, 70) ); 
  theAnalysis_->Book( TH1F( "nPUVtx", "nPUVtx", 140, 0, 140) );
  theAnalysis_->Book( TH1F( "nPUVtx2", "nPUVtx2", 140, 0, 140) );
  theAnalysis_->Book( TH1F( "nPUVtx_rew",   "nPUVtx_rew",140,0,140) );
  theAnalysis_->Book( TH1F( "nPUVtx2_rew",   "nPUVtx2_rew",140,0,140) );
  theAnalysis_->Book( TH1F( "nPUVtxTrue_rew",   "nPUVtxTrue_rew",140,0,140) );
  
  theAnalysis_->Book( TH1F( "cm"   ,"(*data_.jetAK8_cm	 )",20,0.,100. ) );
  theAnalysis_->Book( TH1F( "nm"   ,"(*data_.jetAK8_nm	 )",20,0.,90. ) );
  theAnalysis_->Book( TH1F( "muf"   ,"(*data_.jetAK8_muf)",20,0.,1. ) );
  theAnalysis_->Book( TH1F( "phf"   ,"(*data_.jetAK8_phf)",20,0.,1. ) );
  theAnalysis_->Book( TH1F( "emf"   ,"(*data_.jetAK8_emf)",20,0.,1. ) );
  theAnalysis_->Book( TH1F( "nhf"   ,"(*data_.jetAK8_nhf)",20,0.,1. ) );
  theAnalysis_->Book( TH1F( "chf"   ,"(*data_.jetAK8_chf)",20,0.,1. ) );
  theAnalysis_->Book( TH1F( "area"  ,"(*data_.jetAK8_area)",40,1.,4. ) );
  theAnalysis_->Book( TH1F( "tau1"  ,"(*data_.jetAK8_tau1)",20,0.,1. ) );
  theAnalysis_->Book( TH1F( "tau2"  ,"(*data_.jetAK8_tau2)",20,0.,1. ) );
  theAnalysis_->Book( TH1F( "puppi_tau1"  ,"(*data_.jetAK8_tau1)",20,0.,1. ) );
  theAnalysis_->Book( TH1F( "puppi_tau2"  ,"(*data_.jetAK8_tau2)",20,0.,1. ) );
  theAnalysis_->Book( TH1F( "tau2tau1"  ,"(*data_.jetAK8_tau21)",20,0.,1. ) );
  theAnalysis_->Book( TH1F( "tau3tau1"  ,"(*data_.jetAK8_tau31)",20,0.,1. ) );
  theAnalysis_->Book( TH1F( "tau3tau2"  ,"(*data_.jetAK8_tau32)",20,0.,1. ) );
  theAnalysis_->Book( TH1F( "puppi_tau2tau1"  ,"(*data_.jetAK8_tau21)",20,0.,1. ) );
  theAnalysis_->Book( TH1F( "puppi_tau3tau1"  ,"(*data_.jetAK8_tau31)",20,0.,1. ) );
  theAnalysis_->Book( TH1F( "puppi_tau3tau2"  ,"(*data_.jetAK8_tau32)",20,0.,1. ) );
  theAnalysis_->Book( TH1F( "tau3"  ,"(*data_.jetAK8_tau3)",20,0.,1. ) );
  theAnalysis_->Book( TH1F( "che"   ,"(*data_.jetAK8_che)",30,0.,3000. ) );
  theAnalysis_->Book( TH1F( "ne"   ,"(*data_.jetAK8_ne)",50,0.,5000. ) );
  theAnalysis_->Book( TH1F( "HFHadronEnergyFraction", "HFHadronEnergyFraction" , 30, 0., 0.1 ) );
  theAnalysis_->Book( TH1F( "HFEMEnergyFraction", "HFEMEnergyFraction" , 100, 0., .1 ) );
  theAnalysis_->Book( TH1F( "hoEnergyFraction", "hoEnergyFraction" , 100, 0., .1 ) );
  theAnalysis_->Book( TH1F( "chargedHadronMultiplicity", "chargedHadronMultiplicity" , 60, 0., 120 ) );
  theAnalysis_->Book( TH1F( "neutralHadronMultiplicity", "neutralHadronMultiplicity" , 30, 0., 30. ) );
  theAnalysis_->Book( TH1F( "photonMultiplicity", "photonMultiplicity" , 50, 0., 100. ) );
  theAnalysis_->Book( TH1F( "neutralEmEnergyFraction", "neutralEmEnergyFraction" , 20, 0., 1. ) );
  theAnalysis_->Book( TH1F( "chargedEmEnergyFraction", "chargedEmEnergyFraction" , 20, 0., 1. ) );
  theAnalysis_->Book( TH1F( "charge", "charge" , 21, -30., 30. ) );
  
  
  
  theAnalysis_->Book( TH1F( "Tau21_punzi"   	  													, "#tau_{21}, dEta+Mjj+Mass cut" 	 				, 100	, 0. , 1. 	) );
  theAnalysis_->Book( TH1F( "Tau21_punzi1"   	  													, "#tau_{21}, dEta+Mjj+Mass cut" 	 				, 100	, 0. , 1. 	) );
  theAnalysis_->Book( TH1F( "Tau21_punzi2"   	  													, "#tau_{21}, dEta+Mjj+Mass cut" 	 				, 100	, 0. , 1. 	) );
  theAnalysis_->Book( TH1F( "Tau21_punzi1TeV"                                 , "#tau_{21}, dEta+Mjj+Mass cut"            , 100  , 0. , 1.   ) );
  theAnalysis_->Book( TH1F( "Tau21_punzi1v2TeV"                                 , "#tau_{21}, dEta+Mjj+Mass cut"            , 100  , 0. , 1.   ) );
  theAnalysis_->Book( TH1F( "Tau21_punzi1v6TeV"                                 , "#tau_{21}, dEta+Mjj+Mass cut"            , 100  , 0. , 1.   ) );
   theAnalysis_->Book( TH1F( "Tau21_punzi1v8TeV"                                 , "#tau_{21}, dEta+Mjj+Mass cut"            , 100  , 0. , 1.   ) );
  theAnalysis_->Book( TH1F( "Tau21_punzi2TeV"                                 , "#tau_{21}, dEta+Mjj+Mass cut"            , 100  , 0. , 1.   ) );
  theAnalysis_->Book( TH1F( "Tau21_punzi2v5TeV"                                 , "#tau_{21}, dEta+Mjj+Mass cut"            , 100  , 0. , 1.   ) );
  theAnalysis_->Book( TH1F( "Tau21_punzi3TeV"                                 , "#tau_{21}, dEta+Mjj+Mass cut"            , 100  , 0. , 1.   ) );
  theAnalysis_->Book( TH1F( "Tau21_punzi4TeV"                                 , "#tau_{21}, dEta+Mjj+Mass cut"            , 100  , 0. , 1.   ) );

			
	
  theAnalysis_->Book( TH1F( "VVdeltaEta"		 																, "#Delta#eta_{jj}, all cuts"	  		, 14	, 0., 1.4 	) );
  theAnalysis_->Book( TH1F( "VcandPrunedMass" 															, "pruned M_{j}, all cuts applied"		, 30,   50. , 110.	) );
  theAnalysis_->Book( TH1F( "VcandSoftdropMass" 														, "Softdrop M_{j}, all cuts applied"	, 30,   50. , 110.	) ); 	
  theAnalysis_->Book( TH1F( "VcandTau21"   	  													, "Jet #tau_{21}, all cuts applied"		, 20	, 0. , 1.		) );
  theAnalysis_->Book( TH1F( "DiBosonInvMass"	   											  	, "di-bosons inv. mass"						,7000 	, 0.	, 7000.	) );
  theAnalysis_->Book( TH1F( "VcandPt" 	  																, " AK8 jet pt"						, 140	, 200.	, 2000.	) );
  theAnalysis_->Book( TH1F( "VcandEta"	  																, " AK8 jet eta"						, 50	, -2.5, 2.5		) );
  theAnalysis_->Book( TH1F( "VcandPhi"	  																, " AK8 jet phi"						, 64	, -3.2, 3.2		) );
  theAnalysis_->Book( TH1F( "VcandMass" 	  															, " AK8 jet mass"					, 80	, 0. , 200.	) );
	
  /* Cut flow */
  theAnalysis_->Book( TH1F( "nEvents" 												           	, "nEvents"									 	  , 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedJSON"     													  , "nPassedJSON"					 		    , 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedFilter"     													, "nPassedFilter"					 		  , 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedTrigger"     													, "nPassedTrigger"							, 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedFoundJets"    												, "nPassedFoundJets"						, 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedJetsDEta"    													, "nPassedJetsDEta"							, 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedMjj"												         	, "nPassedMjj"									, 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedTrigger"     													, "nPassedTrigger"							, 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedPrunedJetMass"  											, "nPassedPrunedJetMass"				, 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedTau21Cut"    													, "nPassedTau21Cut"							, 1	, 0.5, 1.5		) );
 
  /* Triggers */

  theAnalysis_->Book( TH1F( "PFHT650", "PFHT650", 5000, 0.	, 5000.	) ); 
  theAnalysis_->Book( TH1F( "HT800", "HT800", 5000, 0.	, 5000.	) ); 
  theAnalysis_->Book( TH1F( "PFJet360_Trim"   , "AK8PFJet360_TrimMass30"      , 5000, 0.	, 5000.	) );  
  theAnalysis_->Book( TH1F( "HT700_Trim"    , "HT700_Trim50"    , 5000, 0.	, 5000.	) );
  theAnalysis_->Book( TH1F( "DiPFJet280_200_TrimMass30" , "DiPFJet280_200_TrimMass30", 5000, 0.	, 5000.	) );  
  theAnalysis_->Book( TH1F( "Substructure"   , "OR (substructure only)"      , 5000, 0.	, 5000.	) );  
  theAnalysis_->Book( TH1F( "HT650_MJJ950"   , "HT650_MJJ950"    , 5000, 0.	, 5000.	) ); 
  theAnalysis_->Book( TH1F( "HT650_MJJ900"   , "HT650_MJJ900"    , 5000, 0.	, 5000.	) ); 
  theAnalysis_->Book( TH1F( "HT" , "OR (HT only)"    , 5000, 0.	, 5000.	) ); 
  theAnalysis_->Book( TH1F( "ALL" , "ALL" , 5000, 0.	, 5000.	) ); 
  //theAnalysis_->Book( TH1F( "", "", 5000, 0.	, 5000.	);
  
  
  theAnalysis_->Book( TH2F( "PtvsMSD_num" , "PtvsMSD_num" , 1000	, 0. , 1000. , 200	, 0. , 200.	) ); 
  theAnalysis_->Book( TH2F( "PtvsMSD_den" , "PtvsMSD_den" , 1000	, 0. , 1000. , 200	, 0. , 200.	) ); 
  theAnalysis_->Book( TH2F( "PtvsMPR_num" , "PtvsMPR_num" , 1000	, 0. , 1000. , 200	, 0. , 200.	) ); 
  theAnalysis_->Book( TH2F( "PtvsMPR_den" , "PtvsMPR_den" , 1000	, 0. , 1000. , 200	, 0. , 200.	) ); 
  theAnalysis_->Book( TH1F( "ALL_vsSD"    , "ALL_vsSD", 200, 0.	, 200.	) ); 
  theAnalysis_->Book( TH1F( "ALL_vsPR"    , "ALL_vsPR", 200, 0.	, 200.	) );   
  theAnalysis_->Book( TH1F( "PFHT650_vsSD"  , "PFHT650_vsSD", 200, 0.	, 200.	) ); 
  theAnalysis_->Book( TH1F( "PFHT650_vsPR"    , "PFHT650_vsPR", 200, 0.	, 200.	) ); 
  theAnalysis_->Book( TH1F( "HT800_vsSD"    , "HT800_vsSD", 200, 0.	, 200.	) ); 
  theAnalysis_->Book( TH1F( "HT800_vsPR"    , "HT800_vsPR", 200, 0.	, 200.	) ); 
  
  theAnalysis_->Book( TH1F( "PFHT650_VV", "PFHT650", 5000, 0.	, 5000.	) ); 
  theAnalysis_->Book( TH1F( "HT800_VV", "HT800", 5000, 0.	, 5000.	) ); 
  theAnalysis_->Book( TH1F( "PFJet360_Trim_VV"   , "AK8PFJet360_TrimMass30"      , 5000, 0.	, 5000.	) );  
  theAnalysis_->Book( TH1F( "HT700_Trim_VV"    , "HT700_Trim50"    , 5000, 0.	, 5000.	) );
  theAnalysis_->Book( TH1F( "DiPFJet280_200_TrimMass30_VV" , "DiPFJet280_200_TrimMass30", 5000, 0.	, 5000.	) );  
  theAnalysis_->Book( TH1F( "HT650_MJJ950_VV"   , "HT650_MJJ950"    , 5000, 0.	, 5000.	) ); 
  theAnalysis_->Book( TH1F( "HT650_MJJ900_VV"   , "HT650_MJJ900"    , 5000, 0.	, 5000.	) ); 
  theAnalysis_->Book( TH1F( "Substructure_VV"   , "OR (substructure only)"      , 5000, 0.	, 5000.	) );  
  theAnalysis_->Book( TH1F( "HT_VV" , "OR (HT only)"    , 5000, 0.	, 5000.	) ); 
  theAnalysis_->Book( TH1F( "ALL_VV" , "ALL" , 5000, 0.	, 5000.	) ); 
  
  
  theAnalysis_->Book( TH1F( "PFHT650_noTag", "PFHT650", 5000, 0.	, 5000.	) ); 
  theAnalysis_->Book( TH1F( "HT800_noTag", "HT800", 5000, 0.	, 5000.	) ); 
  theAnalysis_->Book( TH1F( "PFJet360_Trim_noTag"   , "AK8PFJet360_TrimMass30"      , 5000, 0.	, 5000.	) );  
  theAnalysis_->Book( TH1F( "HT700_Trim_noTag"    , "HT700_Trim50"    , 5000, 0.	, 5000.	) );
  theAnalysis_->Book( TH1F( "DiPFJet280_200_TrimMass30_noTag" , "DiPFJet280_200_TrimMass30", 5000, 0.	, 5000.	) );  
  theAnalysis_->Book( TH1F( "HT650_MJJ950_noTag"   , "HT650_MJJ950"    , 5000, 0.	, 5000.	) ); 
  theAnalysis_->Book( TH1F( "HT650_MJJ900_noTag"   , "HT650_MJJ900"    , 5000, 0.	, 5000.	) ); 
  theAnalysis_->Book( TH1F( "Substructure_noTag"   , "OR (substructure only)"      , 5000, 0.	, 5000.	) );  
  theAnalysis_->Book( TH1F( "HT_noTag" , "OR (HT only)"    , 5000, 0.	, 5000.	) ); 
  theAnalysis_->Book( TH1F( "ALL_noTag" , "ALL" , 5000, 0.	, 5000.	) ); 
  
  
 
  theAnalysis_->Book( TH1F( "PFJet320_SD"  , "PFJet320", 200, 0.	, 200.	) ); 
  theAnalysis_->Book( TH1F( "PFHT650_SD"  , "PFHT650", 200, 0.	, 200.	) ); 
  theAnalysis_->Book( TH1F( "PFJet360_Trim_SD", "AK8PFJet360_TrimMass30"   , 200, 0.	, 200.	) ); 
  theAnalysis_->Book( TH1F( "HT700_Trim_SD" , "HT700_Trim50"     , 200 , 0. , 200. ) );  
  theAnalysis_->Book( TH1F( "DiPFJet280_200_TrimMass30_SD" , "DiPFJet280_200_TrimMass30"    , 200 , 0. , 200. ) );  
  theAnalysis_->Book( TH1F( "Substructure_SD", "OR (substructure only)"      , 200 , 0. , 200. ) );
  theAnalysis_->Book( TH1F( "Base_SD", "Base_SD", 200 , 0. , 200. )	);
  
 
  theAnalysis_->Book( TH1F( "PFJet320_P"    , "PFHT650", 200, 0.	, 200.	) ); 
  theAnalysis_->Book( TH1F( "PFJet360_Trim_P", "AK8PFJet360_TrimMass30"   , 200, 0.	, 200.	) ); 
  theAnalysis_->Book( TH1F( "HT700_Trim_P" , "HT700_Trim50"     , 200 , 0. , 200. ) );  
  theAnalysis_->Book( TH1F( "DiPFJet280_200_TrimMass30_P" , "DiPFJet280_200_TrimMass30"    , 200 , 0. , 200. ) );  
  theAnalysis_->Book( TH1F( "Substructure_P", "OR (substructure only)"      , 200 , 0. , 200. ) );
 }
 
 else if( Channel_ == "SFmuJets" || Channel_ == "SFeleJets" ){
  
  /************************ SF ************************/
  theAnalysis_->Book( TH1F( "leptonPT" 	  		 												, "leptonPT"	   				, 60	, 0.	, 600.	) );
  theAnalysis_->Book( TH1F( "leptonPhi" 	  		 											, "leptonPhi"	   				, 50	, -5.	, 5.	) );
  theAnalysis_->Book( TH1F( "leptonEta" 	  		 											, "leptonEta"	   				, 50	, -5.0	, 5.0	) );
  theAnalysis_->Book( TH1F( "MET_beforeCut", "MET"   , 50	, 0.	, 500.	) );
  theAnalysis_->Book( TH1F( "MET_afterCut", "MET"   , 50	, 0.	, 500.	) );
  theAnalysis_->Book( TH1F( "JetPt_Leading1", "Pt"   , 200	, 0.	, 500.	) );
  theAnalysis_->Book( TH1F( "JetPt_Leading2", "Pt"   , 200	, 0.	, 500.	) );
  theAnalysis_->Book( TH1F( "JetPt_Leading3", "Pt"   , 200	, 0.	, 500.	) );
  theAnalysis_->Book( TH1F( "JetPt_Leading4", "Pt"   , 200	, 0.	, 500.	) );
  theAnalysis_->Book( TH1F( "MET", "MET"   , 50	, 0.	, 500.	) );
  
  /* AK4 */
  theAnalysis_->Book( TH1F( "nAK4" 	  		 														, "# AK4"	   											, 12	, 0.	, 12.		) );
  theAnalysis_->Book( TH1F( "nbTagAK4" 	  		 												, "# b-tag AK4"	 									, 12	, 0.	, 12.		) );
  theAnalysis_->Book( TH1F( "AK4jetPt" 	  		 												, "Leading AK4 jet pt"	   				, 200	, 0.	, 1000.	) );
  theAnalysis_->Book( TH1F( "AK4jetHT" 	  		 												, "Leading AK4 jet HT"	   				, 200	, 0.	, 1000.	) );
  theAnalysis_->Book( TH1F( "AK4jetCSV" 	  		 											, "Leading AK4 jet CSV"	   				, 100	, 0.	, 1.	) );
  theAnalysis_->Book( TH1F( "AK4jetMass" 	  		 										, "Leading AK4 jet Mass"	   				, 100	, 0.	, 200.	) );
	
  theAnalysis_->Book( TH1F( "tmass" 	  												    	, "Tmass"    , 1000	, 0. , 1000.	) );
  theAnalysis_->Book( TH1F( "wmass" 	  												    	, "Wmass"    , 1000	, 0. , 1000.	) );
  theAnalysis_->Book( TH1F( "Chi2" 	  												    	, "Chi2"    , 200	, 0. , 50000.	) );
  theAnalysis_->Book( TH2F( "Chi2vsTMass" 	  												 , "Chi2vsTMass" , 1000	, 0. , 1000. , 400	, 0. , 400.	) ); 
  theAnalysis_->Book( TH2F( "Chi2vsWMass" 	  												 , "Chi2vsWMass" , 1000	, 0. , 1000. , 400	, 0. , 400.	) ); 
  theAnalysis_->Book( TH2F( "Chi2vsbCandFlav" 	  											, "Chi2vsbCandFlav" , 1000	, 0. , 1000. , 26	, 0. , 25.	) );  
 
 
  theAnalysis_->Book( TH1F( "Mlj" 														, "M_{#ellb}"    , 500	, 0. , 500.	) );
  theAnalysis_->Book( TH1F( "MljbDepleted" 	  													, "M_{#ellb}"    , 500	, 0. , 500.	) );
  theAnalysis_->Book( TH1F( "MljbEnriched" 	  													, "M_{#ellb}"    , 500	, 0. , 500.	) );
 
  theAnalysis_->Book( TH1F( "CSV_enriched" 	  														, "CSV"										     	, 100	, 0. , 1.		) );
  theAnalysis_->Book( TH1F( "CSV_depleted" 	  														, "CSV"										     	, 100	, 0. , 1.		) );
  theAnalysis_->Book( TH1F( "CSV_enriched_trueB" 	  											, "CSV"										     	, 100	, 0. , 1.		) );
  theAnalysis_->Book( TH1F( "CSV_enriched_nonB" 	  											, "CSV"										     	, 100	, 0. , 1.		) );
 
  theAnalysis_->Book( TH1F( "Method2_CSV_enriched" 	  														, "CSV"										     	, 100	, 0. , 1.		) );
  theAnalysis_->Book( TH1F( "Method2_CSV_depleted" 	  														, "CSV"										     	, 100	, 0. , 1.		) );
  theAnalysis_->Book( TH1F( "Method2_CSV_enriched_trueB" 	  											, "CSV"										     	, 100	, 0. , 1.		) );
  theAnalysis_->Book( TH1F( "Method2_CSV_enriched_nonB" 	  											, "CSV"										     	, 100	, 0. , 1.		) );
   
  theAnalysis_->Book( TH1F( "LeptonicWMass" 	  													, "W transverse mass leptonic"    , 20	, 0. , 200.	) );
  theAnalysis_->Book( TH1F( "LeptonicTopMass" 	  												, "Leptonic top mass"									, 80	, 0. , 800.	) );	
  theAnalysis_->Book( TH1F( "LeptonicTopMass_B" 	  											, "Leptonic top mass"									, 80	, 0. , 800.	) );	
  theAnalysis_->Book( TH1F( "LeptonicTopMass_nonB" 	  										, "Leptonic top mass"									, 80	, 0. , 800.	) );	
  theAnalysis_->Book( TH1F( "LeptonicbCSV" 	  														, "CSV"										     	, 100	, 0. , 1.		) );
  theAnalysis_->Book( TH1F( "LeptonicbCSV_B" 	  													, "CSV"										     	, 100	, 0. , 1.		) );
  theAnalysis_->Book( TH1F( "LeptonicbCSV_nonB" 	  											, "CSV"										     	, 100	, 0. , 1.		) );
  theAnalysis_->Book( TH1F( "LeptonicbFlavor" 	  												, "Flavor"								     	, 25	, 0. , 25.	) );
  theAnalysis_->Book( TH1F( "LeptonicbFlavor_B" 	  											, "Flavor"								     	, 25	, 0. , 25.	) );
  theAnalysis_->Book( TH1F( "LeptonicbFlavor_nonB" 	  										, "Flavor"								     	, 25	, 0. , 25.	) );
 
  theAnalysis_->Book( TH1F( "HadronicWMass" 	  													, "W mass hadronic"   , 20	, 0. , 200.	) );
  theAnalysis_->Book( TH1F( "HadronicTopMass" 	  												, "Hadronic top mass"									, 40	, 0. , 400.	) );
  theAnalysis_->Book( TH1F( "HadronicbCSV" 	  														, "CSV"										     	, 100	, 0. , 1.		) );
  theAnalysis_->Book( TH1F( "HadronicbFlavor" 	  												, "Flavor"									     , 25	, 0. , 25.	) );

 
  theAnalysis_->Book( TH1F( "nEvents" 											          		, "nEvents"									 	    , 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedJSON"     													  , "nPassedJSON"					 		      , 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedFilter"     													, "nPassedFilter"					 		    , 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedTrigger"     													, "nPassedTrigger"							  , 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedFoundLept" 											  		, "nPassedFoundLept"							, 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedVetoLep" 								 			    		, "nPassedVetoLep"								, 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedFoundMET" 								 			  		, "nPassedFoundMET"								, 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassed1Jet"    												    	, "nPassed1Jet"									 	, 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassed2Jet"    													    , "nPassed2Jet"									 	, 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassed3Jet"    													    , "nPassed3Jet"									 	, 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassed4Jet"    													    , "nPassed4Jet"									 	, 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassed1bTag"    													  , "nPassed1bTag"									, 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassed2bTag"    													  , "nPassed2bTag"									, 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedChi2"    													    , "nPassedChi2"									 	, 1	, 0.5, 1.5		) );
  
   
 }
 
 else if( Channel_.find("WtagSF") != std::string::npos){
  
  /************************ SF ************************/
 
  theAnalysis_->Book( TH1F( "MET_beforeCut", "MET"   , 50	, 0.	, 500.	) );
  theAnalysis_->Book( TH1F( "MET_afterCut", "MET"   , 50	, 0.	, 500.	) );
  
  theAnalysis_->Book( TH1F( "leptonPT" 	  		 												, "leptonPT"	   				, 60	, 0.	, 600.	) );
  theAnalysis_->Book( TH1F( "leptonPhi" 	  		 											, "leptonPhi"	   				, 50	, -5.	, 5.  	) );
  theAnalysis_->Book( TH1F( "leptonEta" 	  		 											, "leptonEta"	   				, 50	, -5.	, 5.  	) );
  theAnalysis_->Book( TH1F( "MET"                                     , "MET"                 , 50	, 0.	, 500.	) );
  theAnalysis_->Book( TH1F( "Wcand_pt" 	  		 												, "Wcand_pt"	   				, 60	, 0.	, 600.	) );
  
 
  theAnalysis_->Book( TH1F( "nEvents"           , "nEvents"           , 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedJSON"       , "nPassedJSON"       , 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedFilter"     , "nPassedFilter"     , 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedTrigger"    , "nPassedTrigger"    , 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedFoundLept"  , "nPassedFoundLept"  , 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedVetoLep"    , "nPassedVetoLep"    , 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedFoundMET"   , "nPassedFoundMET"   , 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedFoundW"     , "nPassedFoundW"     , 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedFoundJet"   , "nPassedFoundJet"   , 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedLepJetDR"   , "nPassedLepJetDR"   , 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassedPrunedJetMass"   , "nPassedPrunedJetMass"   , 1	, 0.5, 1.5		) );
  theAnalysis_->Book( TH1F( "nPassed1bTag"      , "nPassed1bTag"      , 1	, 0.5, 1.5		) );
  
  theAnalysis_->Book( TH1F( "nNopuppi" 													, "nNopuppi"									 	, 1	, 0.5, 1.5		) );
   
 }
//  else if(Channel_.find("PU")!=std::string::npos or Channel_.find("VVdijet")!=std::string::npos or Channel_.find("qVdijet")!=std::string::npos)
//  {
//      
//    theAnalysis_->Book( TH1F( "nPUVtxTrue", "nPUVtxTrue", 70, 0, 70) ); 
//    theAnalysis_->Book( TH1F( "nPUVtx", "nPUVtx", 140, 0, 140) );
//    theAnalysis_->Book( TH1F( "nPUVtx_rew",   "nPUVtx_rew",140,0,140) );
//    theAnalysis_->Book( TH1F( "nPUVtxTrue_rew",   "nPUVtxTrue_rew",140,0,140) );
//      
//  }
}

////////////////////////////////////////////////////////////////////
void HistosManager::formatHistos( std::string Channel_ ){
  
 if( Channel_.find("VVdijet")!=std::string::npos || Channel_.find("qVdijet")!=std::string::npos ){
   
    
  theAnalysis_->Hist( "DiBosonInvMass"			)->GetXaxis()->SetTitle( "M_{G} (GeV)");
  theAnalysis_->Hist( "VVdeltaEta"					)->GetXaxis()->SetTitle( "#Delta#eta_{jj}"     );
  theAnalysis_->Hist( "DeltaEta")->GetXaxis()->SetTitle( "#Delta#eta_{jj}"     );
  theAnalysis_->Hist( "Mjj"  )->GetXaxis()->SetTitle( "M_{jj} (GeV)");
  theAnalysis_->Hist( "Mjj"  )->GetXaxis()->SetTitle( "M_{jj} (GeV)");
  theAnalysis_->Hist( "Tau21_punzi"		 		)->GetXaxis()->SetTitle( "#tau_{21}"			  	 	);
  theAnalysis_->Hist( "PrunedMass"					)->GetXaxis()->SetTitle( "M_{j} (GeV)"      	 );
  theAnalysis_->Hist( "PrunedMass_afterTau21"					)->GetXaxis()->SetTitle( "Pruned M_{j} (GeV)"      	 );
  theAnalysis_->Hist( "PuppiSoftdropMass_afterTau21"  )->GetXaxis()->SetTitle( "PUPPI softdrop M_{j} (GeV)"      	 );
  theAnalysis_->Hist( "VcandPrunedMass"			)->GetXaxis()->SetTitle( "M_{j} (GeV)"      	 );
  theAnalysis_->Hist( "VcandSoftdropMass"		)->GetXaxis()->SetTitle( "M_{j} (GeV)"      	 );	
  theAnalysis_->Hist( "VcandPt"					)->GetXaxis()->SetTitle( "W_{hadr} p_{T} (GeV)"    );
  theAnalysis_->Hist( "VcandEta"					)->GetXaxis()->SetTitle( "W_{hadr} #eta");
  theAnalysis_->Hist( "VcandPhi"					)->GetXaxis()->SetTitle( "W_{hadr} #phi [rad]"    );
  theAnalysis_->Hist( "VcandMass"				)->GetXaxis()->SetTitle( "W_{hadr} mass (GeV)"    );
  theAnalysis_->Hist( "VcandTau21"				)->GetXaxis()->SetTitle( "#tau_{21}"  );
  
  theAnalysis_->Hist( "PV_rho" )->GetXaxis()->SetTitle( "PV #rho");
  theAnalysis_->Hist( "Rho" )->GetXaxis()->SetTitle( "#rho");
  theAnalysis_->Hist( "METsumET" )->GetXaxis()->SetTitle( "MET/sumET");
  theAnalysis_->Hist( "MET"    )->GetXaxis()->SetTitle( "MET (GeV)");
  theAnalysis_->Hist( "PrunedMass"	)->GetXaxis()->SetTitle( "Pruned mass (GeV)");
  theAnalysis_->Hist( "PuppiSoftdropMass")->GetXaxis()->SetTitle( "PUPPI Softdrop mass (GeV)");
  theAnalysis_->Hist( "Mass"		)->GetXaxis()->SetTitle( "M (GeV)");
  theAnalysis_->Hist( "Tau21" )->GetXaxis()->SetTitle( "#tau_{21}");
  theAnalysis_->Hist( "Pt" 	  )->GetXaxis()->SetTitle( "p_{T} (GeV)");
  theAnalysis_->Hist( "Eta")->GetXaxis()->SetTitle( "#eta");
  theAnalysis_->Hist( "Phi")->GetXaxis()->SetTitle( "#phi"); 
  theAnalysis_->Hist( "cm")->GetXaxis()->SetTitle( "Charged Multiplicity" );
  theAnalysis_->Hist( "nm")->GetXaxis()->SetTitle( "Neutral Multiplicity" );
  theAnalysis_->Hist( "muf")->GetXaxis()->SetTitle( "Muon energy fraction" );
  theAnalysis_->Hist( "phf")->GetXaxis()->SetTitle( "Photon fraction" );
  theAnalysis_->Hist( "emf")->GetXaxis()->SetTitle( "EM fraction" );
  theAnalysis_->Hist( "nhf")->GetXaxis()->SetTitle( "Neutral hadron fraction" );
  theAnalysis_->Hist( "chf")->GetXaxis()->SetTitle( "Charged hadron fraction" );
  theAnalysis_->Hist( "area")->GetXaxis()->SetTitle( "Jet area" );
  theAnalysis_->Hist( "tau1")->GetXaxis()->SetTitle( "#tau_{1}" );
  theAnalysis_->Hist( "tau2")->GetXaxis()->SetTitle( "#tau_{2}" );
  theAnalysis_->Hist( "puppi_tau1")->GetXaxis()->SetTitle( "PUPPI #tau_{1}" );
  theAnalysis_->Hist( "puppi_tau2")->GetXaxis()->SetTitle( "PUPPI #tau_{2}" );
  theAnalysis_->Hist( "tau3")->GetXaxis()->SetTitle( "#tau_{3}" );
  theAnalysis_->Hist( "tau2tau1")->GetXaxis()->SetTitle( "#tau_{21}" );
  theAnalysis_->Hist( "tau3tau1")->GetXaxis()->SetTitle( "#tau_{31}" );
  theAnalysis_->Hist( "tau3tau2")->GetXaxis()->SetTitle( "#tau_{32}" );
  theAnalysis_->Hist( "che")->GetXaxis()->SetTitle( "Charged energy" );
  theAnalysis_->Hist( "ne")->GetXaxis()->SetTitle( "Neutral energy" );
  theAnalysis_->Hist( "HFHadronEnergyFraction")->GetXaxis()->SetTitle( "HF Hadron Energy Fraction");
  theAnalysis_->Hist( "HFEMEnergyFraction")->GetXaxis()->SetTitle( "HF EM Energy Fraction");
  theAnalysis_->Hist( "hoEnergyFraction")->GetXaxis()->SetTitle( "HO Energy Fraction");
  theAnalysis_->Hist( "chargedHadronMultiplicity")->GetXaxis()->SetTitle( "Charged Hadron Multiplicity");
  theAnalysis_->Hist( "neutralHadronMultiplicity")->GetXaxis()->SetTitle( "Neutral Hadron Multiplicity");
  theAnalysis_->Hist( "photonMultiplicity")->GetXaxis()->SetTitle( "Photon Multiplicity");
  theAnalysis_->Hist( "neutralEmEnergyFraction")->GetXaxis()->SetTitle( "Neutral EM Energy Fraction");
  theAnalysis_->Hist( "chargedEmEnergyFraction")->GetXaxis()->SetTitle( "Charged EM Energy Fraction");
  theAnalysis_->Hist( "charge")->GetXaxis()->SetTitle( "Jet charge");
  
  
  
  // Utilities::OverflowToLast( theAnalysis_->Hist( "denPT") );
  // Utilities::OverflowToLast( theAnalysis_->Hist( "denNPV") );
  //
  // Utilities::OverflowToLast( theAnalysis_->Hist( "numPT_mj") );
  // Utilities::OverflowToLast( theAnalysis_->Hist( "numNPV_mj" ) );
  //
  // Utilities::OverflowToLast( theAnalysis_->Hist( "numPT_mjtau21") );
  // Utilities::OverflowToLast( theAnalysis_->Hist( "numNPV_mjtau21") );
  //
  // Utilities::OverflowToLast( theAnalysis_->Hist( "denPT_puppi") );
  // Utilities::OverflowToLast( theAnalysis_->Hist( "denNPV_puppi") );
  //
  // Utilities::OverflowToLast( theAnalysis_->Hist( "numPT_mj_puppi") );
  // Utilities::OverflowToLast( theAnalysis_->Hist( "numNPV_mj_puppi") );
  //
  // Utilities::OverflowToLast( theAnalysis_->Hist( "numPT_mjtau21_puppi" ) );
  // Utilities::OverflowToLast( theAnalysis_->Hist( "numNPV_mjtau21_puppi" ) );
  
  
  
  Utilities::OverflowToLast( theAnalysis_->Hist( "massShift_pruning") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "massShift_pruning_eta1v3") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "massShift_pruning_etaUP1v3") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "massShift_softdrop") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "massShift_softdrop_eta1v3") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "massShift_softdrop_etaUP1v3") );
  
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_Pruned_DEN"    ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_Pruned_DEN_pt1") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_Pruned_DEN_pt2") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_Pruned_DEN_pt3") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_Pruned_DEN_pt4") );
  
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_PUPPI_DEN") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_PUPPI_DEN_pt1") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_PUPPI_DEN_pt2") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_PUPPI_DEN_pt3") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_PUPPI_DEN_pt4") );
  
  
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_PUPPItau21") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_PUPPItau21_pt1") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_PUPPItau21_pt2") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_PUPPItau21_pt3") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_PUPPItau21_pt4") );
  
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_DDT") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_DDT_pt1") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_DDT_pt2") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_DDT_pt3") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_DDT_pt4") );
  
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_tau21") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_tau21_pt1") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_tau21_pt2") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_tau21_pt3") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "ForROC_tau21_pt4") );
  
  
  
  Utilities::OverflowToLast( theAnalysis_->Hist( "PV_rho" 	 ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "Rho" 	 ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "METsumET" 	 ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "MET" 	 ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "DiBosonInvMass" ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "VVdeltaEta"          ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "DeltaEta"     ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "Mjj") );
   Utilities::OverflowToLast( theAnalysis_->Hist( "Mjj") );
  Utilities::OverflowToLast( theAnalysis_->Hist( "Mass"     ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "PrunedMass"     ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "PrunedMass_afterTau21"     ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "PuppiSoftdropMass"    ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "Tau21_punzi"				) ); 
  Utilities::OverflowToLast( theAnalysis_->Hist( "VcandPt"          ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "VcandEta"          ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "VcandPhi"          ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "VcandMass"          ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "VcandTau21"          ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "HFHadronEnergyFraction" ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "HFEMEnergyFraction" ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "hoEnergyFraction" ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "chargedHadronMultiplicity" ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "neutralHadronMultiplicity" ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "photonMultiplicity" ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "neutralEmEnergyFraction" ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "chargedEmEnergyFraction" ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "charge" ) );	
  Utilities::OverflowToLast( theAnalysis_->Hist( "cm" ) ); 
  Utilities::OverflowToLast( theAnalysis_->Hist( "nm" ) ); 
  Utilities::OverflowToLast( theAnalysis_->Hist( "muf" ) ); 
  Utilities::OverflowToLast( theAnalysis_->Hist( "phf" ) ); 
  Utilities::OverflowToLast( theAnalysis_->Hist( "emf" ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "nhf" ) ); 
  Utilities::OverflowToLast( theAnalysis_->Hist( "chf" ) ); 
  Utilities::OverflowToLast( theAnalysis_->Hist( "area" ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "tau1" ) ); 
  Utilities::OverflowToLast( theAnalysis_->Hist( "tau2" ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "tau3" ) ); 
  Utilities::OverflowToLast( theAnalysis_->Hist( "che" ) ); 
  Utilities::OverflowToLast( theAnalysis_->Hist( "ne" ) );
 
 }
 
 else if( Channel_ == "SFmuJets" || Channel_ == "SFeleJets" ){
  
  theAnalysis_->Hist( "LeptonicWMass"    )->GetXaxis()->SetTitle( "M (GeV)");
  theAnalysis_->Hist( "HadronicWMass" 	  )->GetXaxis()->SetTitle( "M (GeV)");
  theAnalysis_->Hist( "HadronicTopMass"   )->GetXaxis()->SetTitle( "M (GeV)");
  theAnalysis_->Hist( "LeptonicTopMass"   )->GetXaxis()->SetTitle( "M (GeV)");
  theAnalysis_->Hist( "AK4jetHT"					 )->GetXaxis()->SetTitle( "H_{T} (GeV)" );
  theAnalysis_->Hist( "AK4jetPt"					 )->GetXaxis()->SetTitle( "p_{T} (GeV)" );
   
  Utilities::OverflowToLast( theAnalysis_->Hist( "AK4jetPt"					) ); 
  Utilities::OverflowToLast( theAnalysis_->Hist( "tmass" 	 ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "wmass" 	  	) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "Chi2" 	  ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "Mlj" 	   ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "MljbDepleted" ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "MljbEnriched" ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "LeptonicWMass" ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "LeptonicTopMass" ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "LeptonicTopMass_B" 	) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "LeptonicTopMass_nonB" ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "LeptonicbCSV" 	  ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "LeptonicbCSV_B" 	 ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "LeptonicbCSV_nonB" 	) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "LeptonicbFlavor" 	 ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "HadronicWMass" 	) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "HadronicTopMass" ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "HadronicbCSV" 	 ) );
  Utilities::OverflowToLast( theAnalysis_->Hist( "HadronicbFlavor" ) );
   
 }
 
 else if(Channel_.find("PU")!=std::string::npos)
 {
     
    theAnalysis_->Hist( "nPUVtxTrue")->GetXaxis()->SetTitle("# PU vertices true");  
    theAnalysis_->Hist( "nPUVtx")->GetXaxis()->SetTitle("# PU vertices");
     
 }

 // theAnalysis_->setPredictedDistribution();


   
}
