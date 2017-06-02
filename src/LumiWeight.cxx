#include "include/LumiWeight.h"

#include <iostream>

//==============================================================================================
LumiWeight::LumiWeight( void ){

}

//==============================================================================================
LumiWeight::~LumiWeight( void ){

}

//==============================================================================================
double LumiWeight::getLumiWeight( TString sample ){

  xSec_ = 1.;
  genEvents_ = 1.;
	
  
  if( sample.Contains( "Fall15" ) ){
    //single top samples
    if( sample.Contains( "ST_t-channel_top" ) ){ //DONE
      xSec_ = 136.02*0.3272;
      genEvents_ = 3299200.;
    } 
    else if( sample.Contains( "QCD_HT500to700" ) ){
      xSec_ = 29370.0;
      genEvents_ =19664159.;
    }
    else if( sample.Contains( "QCD_HT700to1000" ) ){
      xSec_ = 6524.0;
      genEvents_ = 15356448.;
    }
    else if( sample.Contains( "QCD_HT1000to1500" ) ){
      xSec_ = 1064.0;
      genEvents_ = 4963895.;
    } 
    else if( sample.Contains( "QCD_HT1500to2000" ) ){
      xSec_ = 121.5;
      genEvents_ = 3868886.;
    }
    else if( sample.Contains( "QCD_HT2000toInf" ) ){
      xSec_ = 25.42;
      genEvents_ = 1912529.;
    }    
    else if( sample.Contains( "ST_t-channel_antitop" ) ){ //DONE
      xSec_ = 80.95*0.3272;
      genEvents_ = 1630900.;
    }         

    else if( sample.Contains( "ST_s-channel" ) ){ //DONE
      xSec_ = 11.36*0.3272;
      //genEvents_ = 984400.; //das
      genEvents_ = 621946.; //genweights 
    }	  
    else if( sample.Contains( "ST_tW_top" ) ){ //DONE
      xSec_ = 35.6;
      genEvents_ = 1000000.;
    } 
    else if( sample.Contains( "ST_tW_antitop" ) ){ //DONE
      xSec_ = 35.6;
      genEvents_ = 999400.;
    }   
    else if( sample.Contains( "TT" ) && sample.Contains("herwig") ){ //TO DO
      xSec_ = 831.76;
      genEvents_ = 19409316;  //DAS 17520956.
    }

    else if( sample.Contains( "TT" ) && sample.Contains("pythia8") && !sample.Contains("madgraph") ){ //DONE
      xSec_ = 831.76;
      genEvents_ = 97994456.;
    }
    
    else if( sample.Contains( "TTJets_SingleLeptFromT" ) && sample.Contains("madgraph")){ //DONE
      xSec_ = 831.76*0.435; //semilep. BR
      genEvents_ = 11770038.; //CHANGE THIS WHEN SAMPLE IS DONE!!!!!!
    }
    else if( sample.Contains( "TTJets" ) && sample.Contains("madgraphMLM-pythia8")){ //DONE
      xSec_ = 831.76;
      genEvents_ = 4674268.; 
    }

    else if( sample.Contains( "WWToLNuQQ") ){ //DONE
      xSec_ = 49.997;
      genEvents_ = 6996000.;
    }
    else if( sample.Contains( "WZTo1L1Nu2Q" ) ){  //DONE
      xSec_ = 10.71;
      //genEvents_ = 978512.;//das
      genEvents_ = 11466086.; //gen weights
    }   
    else if( sample.Contains( "ZZTo2L2Q" ) ){  //DONE
      xSec_ = 3.22;
      //genEvents_ = 18790122.;//das
      genEvents_ = 9660541.;//gen weights
    } 
    
    else if( sample.Contains( "WJetsToLNu_HT-100To200" ) ){ //DONE
      xSec_ = 1.21*1345.;//1292.;
      genEvents_ = 10205377.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-200To400" ) ){ //DONE
      xSec_ = 1.21*359.7;//385.9;
      genEvents_ = 4949568.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-400To600" ) ){ //DONE
      xSec_ = 1.21*48.91;//47.9;
      genEvents_ = 1722920.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-600To800" ) ){ //DONE
      xSec_ = 1.21*12.05;//47.9;
      genEvents_ = 3767766.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-800To1200" ) ){ //DONE
      xSec_ = 1.21*5.501;//47.9;
      genEvents_ = 1568277.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-1200To2500" ) ){ //DONE
      xSec_ = 1.21*1.329;//47.9;
      genEvents_ = 246239.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-2500ToInf" ) ){ //DONE
      xSec_ = 1.21*0.03216;//47.9;
      genEvents_ = 251982.;
    } 
  }
  else if( sample.Contains( "Spring15" ) ){
    if( sample.Contains( "ST_t-channel_top" ) ){
      xSec_ = 136.02*0.3272;
      genEvents_ = 3299800.;
    }  
    else if( sample.Contains( "ST_t-channel_antitop" ) ){
      xSec_ = 80.95*0.3272;
      genEvents_ = 1680200.;
    }         
    else if( sample.Contains( "ST_t-channel" ) && sample.Contains( "ext" ) ){
      xSec_ = 216.99*0.322;
      //genEvents_ = 29954054.; //das
      genEvents_ =  6456052.; //gen weights
    }  
    else if( sample.Contains( "ST_s-channel" ) ){
      xSec_ = 11.36*0.3272;
      //genEvents_ = 984400.; //das
      genEvents_ = 613384.; //genweights
    }	  
    else if( sample.Contains( "ST_tW_top" ) ){
      xSec_ = 35.6;
      genEvents_ = 995600.;
    } 
    else if( sample.Contains( "ST_tW_antitop" ) ){
      xSec_ = 35.6;
      genEvents_ = 988500.;
    }   
    else if( sample.Contains( "TT" ) && sample.Contains("herwig") ){
      xSec_ = 831.76;
      genEvents_ = 16640209;  //DAS 17520956.
    }
    else if( sample.Contains( "TT" ) && sample.Contains("pythia8") && !sample.Contains("Fall15")){
      xSec_ = 831.76;
      genEvents_ = 19757192.; //LOWMASS 17427174
    }
    else if( sample.Contains( "_WW_" ) && !sample.Contains( "powheg" ) ){
      xSec_ = 118.7;
      genEvents_ = 993640.;
    }
    else if( sample.Contains( "_WW" ) && sample.Contains( "powheg" ) ){
      xSec_ = 49.997;
      genEvents_ = 1951600.;
    }
    else if( sample.Contains( "_WZ_" ) && !sample.Contains( "amcatnlo" ) ){
      xSec_ = 47.13;
      genEvents_ = 978512.;
    }
    else if( sample.Contains( "_WZ" ) && sample.Contains( "amcatnlo" ) ){
      xSec_ = 10.71;
      //genEvents_ = 978512.;//das
      genEvents_ = 14346866; //gen weights
    }
    else if( sample.Contains( "_ZZ_" ) && !sample.Contains( "amcatnlo" ) ){
      xSec_ = 16.5;
      genEvents_ = 996944.;
    }      
    else if( sample.Contains( "_ZZ" ) && sample.Contains( "amcatnlo" ) ){
      xSec_ = 3.22;
      //genEvents_ = 18790122.;//das
      genEvents_ = 11863244.;//gen weights
    } 
    else if( sample.Contains( "WJetsToLNu_HT-100To200" ) ){
      xSec_ = 1.21*1345.;//1292.;
      genEvents_ = 10152718.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-200To400" ) ){
      xSec_ = 1.21*359.7;//385.9;
      genEvents_ = 5221599.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-400To600" ) ){
      xSec_ = 1.21*48.91;//47.9;
      genEvents_ = 1745914.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-600To800" ) ){
      xSec_ = 1.21*12.05;//47.9;
      genEvents_ = 4041997.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-800To1200" ) ){
      xSec_ = 1.21*5.501;//47.9;
      genEvents_ = 1574633.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-1200To2500" ) ){
      xSec_ = 1.21*1.329;//47.9;
      genEvents_ = 255637.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-2500ToInf" ) ){
      xSec_ = 1.21*0.03216;//47.9;
      genEvents_ = 253036.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-600ToInf" ) ){
      xSec_ = 1.21*18.77;//19.9;
      genEvents_ = 1039152.;
    } 
    else if( sample.Contains( "_DYJetsToLL_" ) && sample.Contains("-madgraphMLM-")){
      xSec_ = 4895.0;
      genEvents_ = 9042031.;
    }
    else if( sample.Contains( "QCD_Pt_170to300_" ) ){
      xSec_ = 117276.;
      // genEvents_ = 3364368.;
      genEvents_ = 2582714; //OK!!!   
    }
    else if( sample.Contains( "QCD_Pt_300to470_" ) ){
      xSec_ = 7823.; //OK
      // genEvents_ = 2933611.;
      genEvents_ = 2360270; //OK!
    }
    else if( sample.Contains( "QCD_Pt_470to600_" ) ){
      xSec_ = 648.2; //OK
      // genEvents_ = 1936832.;
      genEvents_ = 1685205;   //OK!!
    }
    else if( sample.Contains( "QCD_Pt_600to800_" ) ){
      xSec_ = 186.9; //OK
      // genEvents_ = 1964128.;
      genEvents_ = 1492632; //OK!
     
    }
    else if( sample.Contains( "QCD_Pt_800to1000_" ) ){
      xSec_ = 32.293; //OK
      // genEvents_ = 1937216.;
      genEvents_ = 1863188;   //OK!
    
    }
    else if( sample.Contains( "QCD_Pt_1000to1400_" ) ){
      xSec_ = 9.4183; //OK
      // genEvents_ = 1487136.;
      genEvents_ = 1479203;   //OK!
    }  
    else if( sample.Contains( "QCD_Pt_1400to1800_" ) ){
      xSec_ = 0.84265; //OK
      // genEvents_ = 197959.;
      genEvents_ = 174095;   //OK!!
    }
    else if( sample.Contains( "QCD_Pt_1800to2400_" ) ){
      xSec_ = 0.114943; //OK
      // genEvents_ = 193608.;
      genEvents_ = 193608;    //OK!!!!
    
    }
    else if( sample.Contains( "QCD_Pt_2400to3200_" ) ){
      xSec_ = 0.006830; //OK
      genEvents_ = 194456.;   //OK!!!!
    }
    else if( sample.Contains( "QCD_Pt_3200toInf_" ) ){
      xSec_ = 0.000165445; //OK
      // genEvents_ = 192944.;
      genEvents_ = 191778;   //ok!
    }
    else if( sample.Contains( "WJetsToQQ_HT-600ToInf" ) ){
      xSec_ = 95.14;
      genEvents_ = 1006060.;
    }
    else if( sample.Contains( "ZJetsToQQ_HT600toInf" ) ){
      xSec_ = 5.670000;
      genEvents_ = 982095.;
    } 
    else if( sample.Contains( "QCD_HT200to300" ) ){
      xSec_ = 1735000.0;
      genEvents_ =18718905.;
    }
    else if( sample.Contains( "QCD_HT300to500" ) ){
      xSec_ = 366800.0;
      genEvents_ =19826197.;
    }
    else if( sample.Contains( "QCD_HT500to700" ) ){
      xSec_ = 29370.0;
      genEvents_ =19664159.;
    }
    else if( sample.Contains( "QCD_HT700to1000" ) ){
      xSec_ = 6524.0;
      genEvents_ = 15356448.;
    }
    else if( sample.Contains( "QCD_HT1000to1500" ) ){
      xSec_ = 1064.0;
      genEvents_ = 4963895.;
    } 
    else if( sample.Contains( "QCD_HT1500to2000" ) ){
      xSec_ = 121.5;
      genEvents_ = 3868886.;
    }
    else if( sample.Contains( "QCD_HT2000toInf" ) ){
      xSec_ = 25.42;
      genEvents_ = 1912529.;
    }    
    else if( sample.Contains( "_QCD_HT_250To500_ext_" ) ){
      xSec_ = 670500.;
      genEvents_ = 2004219.;
    }
    else if( sample.Contains( "_QCD_HT_250To500_" ) ){
      xSec_ = 670500.;
      genEvents_ = 663953.;
    }
    else if( sample.Contains( "_QCD_HT_500To1000_ext_" ) ){
      xSec_ = 26740.;
      genEvents_  = 3214312.;
    }
    else if( sample.Contains( "_QCD_HT_500To1000_" ) ){
      xSec_ = 26740.;
      genEvents_ = 849033.;
    }
    else if( sample.Contains( "_QCD_HT_1000ToInf_ext_" ) ){
      xSec_ = 769.7;
      genEvents_ = 1130720.;
    }
    else if( sample.Contains( "_QCD_HT_1000ToInf_" ) ){
      xSec_ = 769.7;
      genEvents_ = 333733.;
    }
  }
  if( sample.Contains( "_RSGravToWW_kMpl01_M-600_" ) ){
    // xSec_ = 2.37;
    xSec_ = 1.;
    // genEvents_ = 27614.; //PHYS14
    genEvents_ = 30000.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-800_" ) ){
    // xSec_ = 2.37;
    xSec_ = 1.;
    // genEvents_ = 27614.; //PHYS14
    genEvents_ = 30000.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-1000_" ) ){
    // xSec_ = 2.37;
    xSec_ = 1.;
    // genEvents_ = 27614.; //PHYS14
    genEvents_ = 29751.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-1200_" ) ){
    // xSec_ = 2.37;
    xSec_ = 1.;
    // genEvents_ = 27614.; //PHYS14
    genEvents_ = 29176.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-1400_" ) ){
    // xSec_ = 2.37;
    xSec_ = 1.;
    // genEvents_ = 27614.; //PHYS14
    genEvents_ = 30000.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-1600_" ) ){
    // xSec_ = 2.37;
    xSec_ = 1.;
    // genEvents_ = 27614.; //PHYS14
    genEvents_ = 29028.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-1800_" ) ){
    // xSec_ = 2.37;
    xSec_ = 1.;
    // genEvents_ = 27614.; //PHYS14
    genEvents_ = 98980.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-2000_" ) ){
    // xSec_ = 0.04797;
    xSec_ = 1.;
    // genEvents_ = 39068.;
    genEvents_ = 29680.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-2500_" ) ){
    xSec_ = 1.; //0.012210
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-3000_" ) ){
    // xSec_ = 0.00292;
    xSec_ = 1.0;
    // genEvents_ = 28983.;
    genEvents_ = 30000.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-3500_" ) ){
    xSec_ = 1.; //0.000952
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-4000_" ) ){
    // xSec_ = 0.0002739;
    xSec_ = 1.;
    // genEvents_ = 28687.;
    genEvents_ = 30000.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-4500_" ) ){
    xSec_ = 1.; //0.000094
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-800_" ) ){
    // xSec_ = 
    xSec_ = 1.;
    genEvents_ = 29839.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-1000_" ) ){
    // xSec_ = 
    xSec_ = 1.;
    genEvents_ = 29586.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-1200_" ) ){
    // xSec_ =
    xSec_ = 1.;
    genEvents_ = 29514.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-1400_" ) ){
    // xSec_ = 
    xSec_ = 1.;
    genEvents_ = 30000.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-1600_" ) ){
    // xSec_ = 
    xSec_ = 1.;
    genEvents_ = 27803.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-1800_" ) ){
    // xSec_ = 
    xSec_ = 1.;
    genEvents_ = 100000.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-2000_" ) ){
    // xSec_ =
    xSec_ = 1.;
    genEvents_ = 29751.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-2500_" ) ){
    xSec_ = 1.; 
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-3000_" ) ){
    // xSec_ = 
    xSec_ = 1.0;
    genEvents_ = 30000.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-3500_" ) ){
    xSec_ = 1.; 
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-4000_" ) ){
    // xSec_ = 
    xSec_ = 1.;
    genEvents_ = 29829.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-4500_" ) ){
    xSec_ = 1.; //
    genEvents_ = 30000.;
  }

  else if( sample.Contains( "BulkGravToWW_narrow_M-600" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-800" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-1000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-1200" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-1400" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-1600" ) ){
    xSec_ = 1.;
    genEvents_ = 29000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-1800" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-2000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-2500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-3000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-3500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-4000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-4500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZ_M-1000" ) ){
    xSec_ = 1.;
    genEvents_ = 29388.;
  }
  else if( sample.Contains( "WprimeToWZ_M-1200" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZ_M-1400" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZ_M-1600" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZ_M-1800" ) ){
    xSec_ = 1.;
    genEvents_ = 100000.;
  }
  else if( sample.Contains( "WprimeToWZ_M-2000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZ_M-2500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZ_M-3000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZ_M-3500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZ_M-4000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZ_M-4500" ) ){
    xSec_ = 1.;
    genEvents_ = 29690.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-1000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-1200" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-1400" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-1600" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-1800" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-2000" ) ){
    xSec_ = 1.;
    genEvents_ = 29200.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-2500" ) ){
    xSec_ = 1.;
    genEvents_ = 28800.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-3000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-3500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-4000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-4500" ) ){
    xSec_ = 1.;
    genEvents_ = 29200.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-1000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-1200" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-1400" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-1600" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-1800" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-2000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-2500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-3000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-3500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-4000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-4500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-1000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-1200" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-1400" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-1600" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-1800" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-2000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-2500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-3000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-3500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-4000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-4500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  
  if( sample.Contains("Ntuple_80")){
    
    if( sample.Contains("QCD_HT1500to2000" ) ){
      xSec_ = 119.9;
      genEvents_ = 3928444.;
    }
    else if( sample.Contains("QCD_HT1000to1500" ) ){
      xSec_ = 1207.;
      genEvents_ = 10327758.;
    }
    else if( sample.Contains("QCD_HT2000toInf" ) ){
      xSec_ = 25.24;
      genEvents_ = 4047532.;
    }
    else if( sample.Contains("QCD_HT200to300" ) ){
      xSec_ = 1712000.;
      genEvents_ = 38500860.; //Old? Dont know why this is different: 38816436. Used for VV an!;
    }
    else if( sample.Contains("QCD_HT500to700" ) ){
      xSec_ = 32100.;
      genEvents_ = 44138664.;
    }
    else if( sample.Contains("QCD_HT700to1000" ) ){
      xSec_ = 6831.;
      genEvents_ = 15621634.;
    }
    else if( sample.Contains("QCD_HT300to500" ) ){
      xSec_ = 347700.;
      genEvents_ = 37221432.; ////Old? Dont know why this is different: .;
    }
    
    else if( sample.Contains( "TT" ) && sample.Contains("powheg")){
      xSec_ = 831.76;
      genEvents_ = 32103976.; // !!Old? Dont know why this is different: 92683848.; // Without ext samples!
    }
    else if( sample.Contains("TTJets_HT-1200to2500")){
      xSec_ = 0.12;
      genEvents_ = 2864277.; 
    }
    else if( sample.Contains("TTJets_HT-2500toInf")){
      xSec_ = 0.00143;
      genEvents_ = 523931.; 
    }
    else if( sample.Contains("TTJets_HT-600to800")){
      xSec_ = 1.61;
      genEvents_ = 13369517.; 
    }
    else if( sample.Contains("TTJets_HT-800to1200")){
      xSec_ = 0.663;
      genEvents_ = 10462980.; 
    }
    if( sample.Contains( "ST_t-channel_top" ) ){
      xSec_ = 136.02*0.3272;
      genEvents_ = 3279190.;
    }  
    else if( sample.Contains( "ST_t-channel_antitop" )  && sample.Contains("inclusiveDecays") ){
      xSec_ = 80.95;
      genEvents_ = 19825828.;
    }    
    else if( sample.Contains( "ST_t-channel_antitop" )  && sample.Contains("leptonDecays") ){
      xSec_ = 80.95*0.3272;
      genEvents_ = 1632598; //1682398.;
    }       

    else if( sample.Contains( "ST_s-channel" ) ){ 
      xSec_ = 11.36*0.3272;
      genEvents_ = 593375; //622986.;
    }	  
    else if( sample.Contains( "ST_tW_top" ) ){ 
      xSec_ = 35.6;
      genEvents_ = 998397.;
    } 
    else if( sample.Contains( "ST_tW_antitop" ) ){ 
      xSec_ = 35.6;
      genEvents_ = 984998.;
    }   
    else if( sample.Contains( "WJetsToLNu_HT-100To200" ) ){ 
      xSec_ = 1.21*1345.;//1292.;
      genEvents_ = 26747710;// 27488666.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-200To400" ) ){
      xSec_ = 1.21*359.7;//385.9;
      genEvents_ = 4963226.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-400To600" ) ){ 
      xSec_ = 1.21*48.91;//47.9;
      genEvents_ = 1963451.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-600To800" ) ){
      xSec_ = 1.21*12.05;//47.9;
      genEvents_ = 3676840.;//3722340.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-800To1200" ) ){ 
      xSec_ = 1.21*5.501;//47.9;
      genEvents_ = 1540401.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-1200To2500" ) ){ 
      xSec_ = 1.21*1.329;//47.9;
      genEvents_ = 246698.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-2500ToInf" ) ){
      xSec_ = 1.21*0.03216;//47.9;
      genEvents_ = 253336.;
    } 
    else if( sample.Contains( "WW_TuneCUET" ) ){
      xSec_ = 63.21;
      genEvents_ = 993211.;
    }
    else if( sample.Contains( "WZ_TuneCUET" ) ){
      xSec_ = 22.82;
      genEvents_ = 999997.;
    }
    else if( sample.Contains( "ZZ_TuneCUET" ) ){
      xSec_ = 10.32;
      genEvents_ = 989310.;
    }
  
  }
  else if( sample.Contains("Spring16")){
    
    if( sample.Contains( "TT" ) && sample.Contains("powheg-pythia8")){
      xSec_ = 831.76;
      genEvents_ = 32103976.;
    }
    if( sample.Contains( "TT" ) && sample.Contains("madgraphMLM-pythia8")){
      xSec_ = 831.76;
      genEvents_ = 10259851.; 
    }
    if( sample.Contains( "TT" ) && sample.Contains("herwig")){
      xSec_ = 831.76;
      genEvents_ = 19797004.;
    }
    
    
    if( sample.Contains("BulkGravToWW_narrow_M-1000" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("BulkGravToWW_narrow_M-1200" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("BulkGravToWW_narrow_M-1400" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("BulkGravToWW_narrow_M-1600" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("BulkGravToWW_narrow_M-1600" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("BulkGravToWW_narrow_M-1800" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("BulkGravToWW_narrow_M-2000" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("BulkGravToWW_narrow_M-2500" ) ){
      xSec_ = 1.0;
      genEvents_ = 29800;
    }
    else if( sample.Contains("BulkGravToWW_narrow_M-3000" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("BulkGravToWW_narrow_M-3500" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("BulkGravToWW_narrow_M-4000" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("BulkGravToWW_narrow_M-4500" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("BulkGravToZZToZhadZhad_narrow_M-1000" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("BulkGravToZZToZhadZhad_narrow_M-1200" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("BulkGravToZZToZhadZhad_narrow_M-1400" ) ){
      xSec_ = 1.0;
      genEvents_ = 29800;
    }
    else if( sample.Contains("BulkGravToZZToZhadZhad_narrow_M-1600" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("BulkGravToZZToZhadZhad_narrow_M-1800" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("BulkGravToZZToZhadZhad_narrow_M-2000" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("BulkGravToZZToZhadZhad_narrow_M-2500" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("BulkGravToZZToZhadZhad_narrow_M-3000" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("BulkGravToZZToZhadZhad_narrow_M-3500" ) ){
      xSec_ = 1.0;
      genEvents_ = 29000;
    }
    else if( sample.Contains("BulkGravToZZToZhadZhad_narrow_M-4000" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("WprimeToWZToWhadZhad_narrow_M-1000" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("WprimeToWZToWhadZhad_narrow_M-1200" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("WprimeToWZToWhadZhad_narrow_M-1400" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("WprimeToWZToWhadZhad_narrow_M-1600" ) ){
      xSec_ = 1.0;
      genEvents_ = 29600;
    }
    else if( sample.Contains("WprimeToWZToWhadZhad_narrow_M-1800" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("WprimeToWZToWhadZhad_narrow_M-2500" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("WprimeToWZToWhadZhad_narrow_M-3000" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("WprimeToWZToWhadZhad_narrow_M-3500" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("WprimeToWZToWhadZhad_narrow_M-4000" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("WprimeToWZToWhadZhad_narrow_M-4500" ) ){
      xSec_ = 1.0;
      genEvents_ = 29000;
    }
    else if( sample.Contains("ZprimeToWW_narrow_M-1000" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("ZprimeToWW_narrow_M-1200" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("ZprimeToWW_narrow_M-1400" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("ZprimeToWW_narrow_M-1600" ) ){
      xSec_ = 1.0;
      genEvents_ = 29000;
    }
    else if( sample.Contains("ZprimeToWW_narrow_M-1800" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("ZprimeToWW_narrow_M-2000" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("ZprimeToWW_narrow_M-2500" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("ZprimeToWW_narrow_M-3000" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("ZprimeToWW_narrow_M-3500" ) ){
      xSec_ = 1.0;
      genEvents_ = 29000;
    }
    else if( sample.Contains("ZprimeToWW_narrow_M-4000" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains("ZprimeToWW_narrow_M-4500" ) ){
      xSec_ = 1.0;
      genEvents_ = 30000;
    }
    else if( sample.Contains( "WJetsToQQ" ) ){
      xSec_ = 95.14;
      genEvents_ = 1025005.;
    }
    else if( sample.Contains( "ZJetsToQQ" ) ){
      xSec_ = 5.670000;
      genEvents_ = 1000000.;
    } 
    else if( sample.Contains( "QCD_Pt-15to7000" ) ){
      xSec_ = 3.095141e+09;
      genEvents_ = 259420.;
    }
    
    
    else if( sample.Contains( "QCD_Pt_170to300_" ) ){
      xSec_ = 117276.;
      genEvents_ = 6914051; 
    }
    else if( sample.Contains( "QCD_Pt_300to470_" ) ){
      xSec_ = 7823.; //OK
      genEvents_ = 5970464; //UPDATEME!

    }
    else if( sample.Contains( "QCD_Pt_470to600_" ) ){
      xSec_ = 648.2; //OK
      genEvents_ = 15265387;
    }
    else if( sample.Contains( "QCD_Pt_600to800_" ) ){
      xSec_ = 186.9; //OK
      genEvents_ = 9343371;
     
    }
    else if( sample.Contains( "QCD_Pt_800to1000_" ) ){
      xSec_ = 32.293; //OK
      genEvents_ = 3922735;
    
    }
    else if( sample.Contains( "QCD_Pt_1000to1400_" ) ){
      xSec_ = 9.4183; //OK
      genEvents_ = 2997201;
    }  
    else if( sample.Contains( "QCD_Pt_1400to1800_" ) ){
      xSec_ = 0.84265; //OK
      genEvents_ = 395949;
    }
    else if( sample.Contains( "QCD_Pt_1800to2400_" ) ){
      xSec_ = 0.114943; //OK
      genEvents_ = 395397;
    
    }
    else if( sample.Contains( "QCD_Pt_2400to3200_" ) ){
      xSec_ = 0.006830; //OK
      genEvents_ = 398097;
    }
    else if( sample.Contains( "QCD_Pt_3200toInf_" ) ){
      xSec_ = 0.000165445; //OK
      genEvents_ = 382520;
    }
    
  }
  else if( sample.Contains( "QstarToQW_M_1000" ) ){
      xSec_ = 1.;
      genEvents_ = 33000.;
      }
  else if( sample.Contains( "QstarToQW_M_1200" ) ){
      xSec_ = 1.;
      genEvents_ = 32997.;
      }
  else if( sample.Contains( "QstarToQW_M_1400" ) ){
      xSec_ = 1.;
      genEvents_ = 32999.;
      }
  else if( sample.Contains( "QstarToQW_M_1600" ) ){
      xSec_ = 1.;
      genEvents_ = 32994.;
      }
  else if( sample.Contains( "QstarToQW_M_1800" ) ){
      xSec_ = 1.;
      genEvents_ = 32994.;
      }
  else if( sample.Contains( "QstarToQW_M_2000" ) ){
      xSec_ = 1.;
      genEvents_ = 32991.;
      }
  else if( sample.Contains( "QstarToQW_M_2500" ) ){
      xSec_ = 1.;
      genEvents_ = 32984.;
      }
  else if( sample.Contains( "QstarToQW_M_3000" ) ){
      xSec_ = 1.;
      genEvents_ = 32979.;
      }
  else if( sample.Contains( "QstarToQW_M_3500" ) ){
      xSec_ = 1.;
      genEvents_ = 32973.;
      }
  else if( sample.Contains( "QstarToQW_M_4000" ) ){
      xSec_ = 1.;
      genEvents_ = 32965.;
      }
  else if( sample.Contains( "QstarToQW_M_4500" ) ){
      xSec_ = 1.;
      genEvents_ = 19168.;
      }
  else if( sample.Contains( "QstarToQW_M_5000" ) ){
      xSec_ = 1.;
      genEvents_ = 32551.;
      }
  else if( sample.Contains( "QstarToQW_M_5500" ) ){
      xSec_ = 1.;
      genEvents_ = 32938.;
      }
  else if( sample.Contains( "QstarToQW_M_6000" ) ){
      xSec_ = 1.;
      genEvents_ = 32742.;
      }
  else if( sample.Contains( "QstarToQW_M_600"  ) ){
      xSec_ = 1.;
      genEvents_ =32800.;
      }
  else if( sample.Contains( "QstarToQW_M_6500" ) ){
      xSec_ = 1.;
      genEvents_ = 32934.;
      }
  else if( sample.Contains( "QstarToQW_M_7000" ) ){
      xSec_ = 1.;
      genEvents_ = 32136.;
      }
  else if( sample.Contains( "QstarToQW_M_7500" ) ){
      xSec_ = 1.;
      genEvents_ = 32945.;
      }
  else if( sample.Contains( "QstarToQW_M_800"  ) ){
      xSec_ = 1.;
      genEvents_ =32997.;
      }
  else if( sample.Contains( "QstarToQZ_M_1000" ) ){
      xSec_ = 1.;
      genEvents_ = 32997.;
      }
  else if( sample.Contains( "QstarToQZ_M_1200" ) ){
      xSec_ = 1.;
      genEvents_ = 32997.;
      }
  else if( sample.Contains( "QstarToQZ_M_1400" ) ){
      xSec_ = 1.;
      genEvents_ = 32998.;
      }
  else if( sample.Contains( "QstarToQZ_M_1600" ) ){
      xSec_ = 1.;
      genEvents_ = 32993.;
      }
  else if( sample.Contains( "QstarToQZ_M_1800" ) ){
      xSec_ = 1.;
      genEvents_ = 32995.;
      }
  else if( sample.Contains( "QstarToQZ_M_2000" ) ){
      xSec_ = 1.;
      genEvents_ = 6200.;
      }
  else if( sample.Contains( "QstarToQZ_M_2500" ) ){
      xSec_ = 1.;
      genEvents_ = 32983.;
      }
  else if( sample.Contains( "QstarToQZ_M_3000" ) ){
      xSec_ = 1.;
      genEvents_ = 32780.;
      }
  else if( sample.Contains( "QstarToQZ_M_3500" ) ){
      xSec_ = 1.;
      genEvents_ = 32978.;
      }
  else if( sample.Contains( "QstarToQZ_M_4000" ) ){
      xSec_ = 1.;
      genEvents_ = 32960.;
      }
  else if( sample.Contains( "QstarToQZ_M_4500" ) ){
      xSec_ = 1.;
      genEvents_ = 32966.;
      }
  else if( sample.Contains( "QstarToQZ_M_5000" ) ){
      xSec_ = 1.;
      genEvents_ = 32759.;
      }
  else if( sample.Contains( "QstarToQZ_M_5500" ) ){
      xSec_ = 1.;
      genEvents_ = 32949.;
      }
  else if( sample.Contains( "QstarToQZ_M_6000" ) ){
      xSec_ = 1.;
      genEvents_ = 32948.;
      }
  else if( sample.Contains( "QstarToQZ_M_600"  ) ){
      xSec_ = 1.;
      genEvents_ =33000.;
      }
  else if( sample.Contains( "QstarToQZ_M_6500" ) ){
      xSec_ = 1.;
      genEvents_ = 32939.;
      }
  else if( sample.Contains( "QstarToQZ_M_7000" ) ){
      xSec_ = 1.;
      genEvents_ = 32943.;
      }
  else if( sample.Contains( "QstarToQZ_M_7500" ) ){
      xSec_ = 1.;
      genEvents_ = 32940.;
      }
  else if( sample.Contains( "QstarToQZ_M_800"  ) ){
      xSec_ = 1.;
      genEvents_ =32999.;
      } 
  
  if (sample.Contains("Summer16") or sample.Contains("postMoriond")) {
  
      //std::cout << sample << std::endl;
    if( sample.Contains( "WJetsToQQ_HT" ) ){
       xSec_ = 95.14;
       genEvents_ = 1026587.;
       //std::cout << "gets to WJetsToQQ_HT" << std::endl;
     } 
    if( sample.Contains( "ZJetsToQQ_HT600toInf" ) ){
      xSec_ = 41.34; // number was calculated by Andreas (Hinzman) using madgraph (LO cross section)
      genEvents_ = 995999.;
    } 
//     else if( sample.Contains( "_DYJetsToLL_" ) && sample.Contains("-madgraphMLM-")){
//       xSec_ = 4895.0;
//       genEvents_ = 9042031.;
//     }
      //std::cout << "summer16"<<std::endl;
      
      //QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia820170203_QCD/170203_134720/0000/flatTuple_1.root
    if( sample.Contains( "QCD_Pt_170to300_" ) ){
      xSec_ = 117276.;     //                    \\ should have in v1:  6958708 & 117276          do have:    6596736
      // genEvents_ = 3364368.;                \\ should have in ext-v1:  7838066 & 117276       do have:     7508444
      genEvents_ = 6958708; //OK!!!            \\ -> all pythia samples
    }
    
    if( sample.Contains( "QCD_Pt_170to300_" ) and  sample.Contains( "ext")){
      xSec_ = 117276.;     //                    \\ should have in v1:  6958708 & 117276          do have:    6596736
      // genEvents_ = 3364368.;                \\ should have in ext-v1:  7838066 & 117276       do have:     7508444
      genEvents_ = 7838066; //OK!!!            \\ -> all pythia samples
    }
    if( sample.Contains( "QCD_Pt_300to470_" ) ){
	xSec_ = 7823.; //OK                      \\ should have in v1:    18253032 &7823        do have:      4150584
      // genEvents_ = 2933611.;                \\ should have in ext-v1: 4150588 & 7823        do have:      15647833
      genEvents_ = 4150384; //OK!              \\ -> all pythia samples
    }
    if( sample.Contains( "QCD_Pt_300to470_" ) and  sample.Contains( "ext")){
	xSec_ = 7823.; //OK                      \\ should have in v1:    18253032 &7823        do have:      4150584
      // genEvents_ = 2933611.;                \\ should have in ext-v1: 4150588 & 7823        do have:      15647833
      genEvents_ = 18253016; //OK!              \\ -> all pythia samples
    }
    if( sample.Contains( "QCD_Pt_470to600_" ) ){
      xSec_ = 648.2; //OK                        \\ should have in v1:   3959986 & 648.2         do have:  3959966
      // genEvents_ = 1936832.;                  \\ should have in ext-v1: 15458074 & 648.2       do have:  not existing
      genEvents_ = 3959966;   //OK!!             \\ -> all pythia samples
    }
    if( sample.Contains( "QCD_Pt_470to600_" ) and  sample.Contains( "ext")){
      xSec_ = 648.2; //OK                        \\ should have in v1:   3959986 & 648.2         do have:  3959966
      // genEvents_ = 1936832.;                  \\ should have in ext-v1: 15458074 & 648.2       do have:  not existing
      genEvents_ = 15458013;   //OK!!             \\ -> all pythia samples
    }
    if( sample.Contains( "QCD_Pt_600to800_" ) ){
      xSec_ = 186.9; //OK                          \\ should have in v1:  3896412 & 186.9          do have:    3730760
      // genEvents_ = 1964128.;                    \\ should have in ext-v1: 9622896 & 186.9       do have:    9539427
      genEvents_ = 3896387; //OK!   !!               \\ -> all pythia samples
     
    }
    
    if( sample.Contains( "QCD_Pt_600to800_" ) and  sample.Contains( "ext") ){
      xSec_ = 186.9; //OK                          \\ should have in v1:  3896412 & 186.9          do have:    3730760
      // genEvents_ = 1964128.;                    \\ should have in ext-v1: 9622896 & 186.9       do have:    9539427
      genEvents_ = 8709857; //OK!         !!         \\ -> all pythia samples
     
    }
    if( sample.Contains( "QCD_Pt_800to1000_" ) ){
      xSec_ = 32.293; //OK                               \\ should have in v1: 3992112 & 32.293         do have:   3651423
      // genEvents_ = 1937216.;                          \\  should have in ext-v1: 15704980 & 32.293   do have:   15623555
      genEvents_ = 3229334; //OK!    !!                   \\ -> all 800to1000 pythia samples   3651423+15623555
    }
    if( sample.Contains( "QCD_Pt_800to1000_" ) and  sample.Contains( "ext")){
      xSec_ = 32.293; //OK                               \\ should have in v1: 3992112 & 32.293         do have:   3651423
      // genEvents_ = 1937216.;                          \\  should have in ext-v1: 15704980 & 32.293   do have:   15623555
      genEvents_ = 15704707; //OK!                       \\ -> all 800to1000 pythia samples   3651423+15623555
    }
    if( sample.Contains( "QCD_Pt_1000to1400_" ) ){

       xSec_ = 9.4183; //OK                        \\ should have in v1: 2999069 & 9.4183         do have:   2998947
       // genEvents_ = 1487136.;                   \\  should have in ext-v1: 6982586 &9.4183     do have:   6511034
       genEvents_ = 2998947;   //OK! !              \\ -> all pythia samples
    }  
    if( sample.Contains( "QCD_Pt_1000to1400_" ) and  sample.Contains( "ext")){
       xSec_ = 9.4183; //OK                        \\ should have in v1: 2999069 & 9.4183         do have:   2998947
       // genEvents_ = 1487136.;                   \\  should have in ext-v1: 6982586 &9.4183     do have:   6511034
       genEvents_ = 6982323;   //OK!               \\ -> all pythia samples
    }  
    if( sample.Contains( "QCD_Pt_1400to1800_" ) ){
      xSec_ = 0.84265; //OK                       \\ should have in v1: 396409 & 0.84265            do have:   396364   
      // genEvents_ = 197959.;                    \\  should have in ext-v1: 2477018  & 0.84265     do have:   2416320
      genEvents_ = 396364;   //OK!!               \\ -> all pythia samples 396364
    }
    if( sample.Contains( "QCD_Pt_1400to1800_" )and  sample.Contains( "ext") ){
      xSec_ = 0.84265; //OK                       \\ should have in v1: 396409 & 0.84265            do have:   396364   
      // genEvents_ = 197959.;                    \\  should have in ext-v1: 2477018  & 0.84265     do have:   2416320
      genEvents_ = 2476814;   //OK!!               \\ -> all pythia samples
    }
    if( sample.Contains( "QCD_Pt_1800to2400_" ) ){
      xSec_ = 0.114943; //OK                       \\ should have in v1:  397660 & 0.114943          do have: 397595     
      // genEvents_ = 193608.;                     \\ should have in ext-v1: 1552064 & 0.114943       do have: 1551842  
      genEvents_ = 397695;    //OK!!!!             \\ -> all pythia samples                   397595+1551842
    
    }
    if( sample.Contains( "QCD_Pt_1800to2400_" ) and  sample.Contains( "ext")){
      xSec_ = 0.114943; //OK                       \\ should have in v1:  397660 & 0.114943          do have: 397595     
      // genEvents_ = 193608.;                     \\ should have in ext-v1: 1552064 & 0.114943       do have: 1551842  
      genEvents_ = 1551842;    //OK!!!!             \\ -> all pythia samples                   397595+1551842
    }
    if( sample.Contains( "QCD_Pt_2400to3200_" ) ){
      xSec_ = 0.006830; //OK                       \\ should have in v1:    399226 & 0.00682981        do have:  399131
                                                 // \\ should have in ext-v1: 596904 & 0.00682981       do have: 596747
      genEvents_ = 399131;   //OK!!!!             \\ -> all pythia samples          399131+596747
    }
    if( sample.Contains( "QCD_Pt_2400to3200_" ) and  sample.Contains("ext")){
      xSec_ = 0.006830; //OK                       \\ should have in v1:    399226 & 0.00682981        do have:  399131
                                                 // \\ should have in ext-v1: 596904 & 0.00682981       do have: 596747
      genEvents_ = 595973;   //OK!!!!             \\ -> all pythia samples          399131+596747
    }
    
    if( sample.Contains( "QCD_Pt_3200toInf_" ) ){
      xSec_ = 0.000165445; //OK                    \\ should have in v1:   391735 & 0.000165445         do have:  391583
      // genEvents_ = 192944.;                     \\ should have in ext-v1:        do have: 
      genEvents_ = 391583;   //ok!                 \\ -> all pythia samples
    }
    if( sample.Contains( "QCD_Pt_3200toInf_" ) and  sample.Contains("ext")){
      xSec_ = 0.000165445; //OK                    \\ should have in v1:   391735 & 0.000165445         do have:  391583
      // genEvents_ = 192944.;                     \\ should have in ext-v1:        do have: 
      genEvents_ = 391583;   //ok!                 \\ -> all pythia samples
    }
//     else if( sample.Contains( "WJetsToQQ_HT-600ToInf" ) ){
//       xSec_ = 95.14;                                \\ should have in v1:            do have: 
  //                                                   \\ should have in ext-v1:        do have: 
//       genEvents_ = 1006060.;                        \\ -> all pythia samples
//     }
//     else if( sample.Contains( "ZJetsToQQ_HT600toInf" ) ){
//                                                     \\ should have in v1:            do have: 
//          xSec_ = 5.670000;                          \\ should have in ext-v1:        do have: 
//       genEvents_ = 982095.;                         \\ -> all pythia samples
//     }
     if( sample.Contains( "QCD_HT100to200" ) ){
       xSec_ = 2.785e07;
       genEvents_ = 51960247.;
     }

     if( sample.Contains( "QCD_HT200to300" ) ){
       xSec_ = 1717000.;
       genEvents_ = (18722416.);
     }
     if( sample.Contains( "QCD_HT200to300" ) and  sample.Contains( "ext")){
       xSec_ = 1717000.;
       genEvents_ = (38857975.);
     }
     if( sample.Contains( "QCD_HT300to500" ) ){
       xSec_ = 351300.0;
       genEvents_ = (17035890.);
     }
     if( sample.Contains( "QCD_HT300to500" ) and sample.Contains( "ext" ) ) 
     {
         xSec_ = 351300.0;
       genEvents_ = ( 37502011.);
     }
     if( sample.Contains( "QCD_HT500to700" ) ){
       xSec_ = 31630.;
       genEvents_ = (18929948.0);
     }
     if( sample.Contains( "QCD_HT500to700" ) and sample.Contains( "ext" ) )
     {
       xSec_ = 31630.;
       genEvents_ = (43170745.0);  
     }
     if( sample.Contains( "QCD_HT700to1000" ) ){
       xSec_ = 6802.;
       genEvents_ = (15629236.);
     }
     if( sample.Contains( "QCD_HT700to1000" ) and sample.Contains( "ext" )){
         xSec_ = 6802.;
       genEvents_ = (29783497.);
     }
     if( sample.Contains( "QCD_HT1000to1500" ) ){
       xSec_ = 1206.0;
       genEvents_ = (4767084.);
     } 
     else if( sample.Contains( "QCD_HT1000to1500" )  and sample.Contains( "ext" )){
         xSec_ = 1206.0;
       genEvents_ = ( 10360159.);
     }
     if( sample.Contains( "QCD_HT1500to2000" ) ){
       xSec_ = 120.4;
       genEvents_ = ( 3970787.);
     }
     if( sample.Contains( "QCD_HT1500to2000" )  and sample.Contains( "ext" )){
       xSec_ = 120.4;
       genEvents_ = (7855817.); 
     }
     if( sample.Contains( "QCD_HT2000toInf" ) ){
       xSec_ = 25.25;
       genEvents_ = 1991583.;
     }    
     if( sample.Contains( "QCD_HT2000toInf" ) and sample.Contains( "ext" ) ){
       xSec_ = 25.25;
       genEvents_ = 4047228.;
     }    
      
   if( sample.Contains( "QCD_Pt-15to7000" ) or sample.Contains( "QCD_Pt_15to7000" )){
      xSec_ =  2.022100000e+09;//3.095141e+09;
      genEvents_ = 9936472.;//259420.;
    }   
    
  
}
  if( sample.Contains("BulkGrav") or sample.Contains("Qstar") or sample.Contains("Wprime") or sample.Contains("Zprime"))
  {
    xSec_ = 1.;
    genEvents_ = 30000.; 
    //std::cout << "gest to signal lumi " << std::endl;
  }
  //std::cout<< "Crosssection = " << xSec_ << "genEvents = " << genEvents_ << "Weight = " << xSec_/genEvents_ <<std::endl;
  return xSec_/genEvents_;

      
}
