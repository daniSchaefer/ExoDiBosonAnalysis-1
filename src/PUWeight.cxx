#include "include/PUWeight.h"

#include "TFile.h"

#include <iostream>

//==============================================================================================
// Get MC pile-up scenario from string representation
PUWeight::Scenario PUWeight::toScenario(const std::string& str) {
  PUWeight::Scenario sc = Winter15_25ns;
  if( str == "PUS25ns" ) sc = Winter15_25ns;
  else if( str == "PUS25ns76X" )sc = Fall15_25ns;
  else if( str == "PUS25ns80X" )sc = Spring16_25ns;
  else if( str == "PUS25ns80X_full2016")sc = Summer16_25ns;
  else if( str == "PU25ns80X_flatPU") sc = Summer16_25ns_FlatPU;
  else {
    std::cerr << "\n\nERROR unknown scenario '" << str << "'" << std::endl;
    throw std::exception();
  }

  return sc;
}

//==============================================================================================
// MC pile-up scenario to string representation
std::string PUWeight::toString(const PUWeight::Scenario sc) {
  std::string str;
  if     ( sc == Winter15_25ns) str = "PUS25ns";
  else if( sc == Fall15_25ns  ) str = "PUS25ns76X";
  else if( sc == Spring16_25ns) str = "PUS25ns80X";
  else if( sc == Summer16_25ns) str = "PUS25ns80X_full2016";
  else if( sc == Summer16_25ns_FlatPU) str = "PUS25ns80X_flatPU";
  else {
    std::cerr << "\n\nERROR unknown scenario '" << sc << "'" << std::endl;
    throw std::exception();
  }

  return str;
}

//==============================================================================================
// Constructor. Initializes default behaviour to return PU weight of 1
PUWeight::PUWeight()
  : isInit_(false), nPUMax_(0) {}

//==============================================================================================
// Initialise weights for a given MC pile-up scenario. Can only be
// called once.
void PUWeight::initPUWeights(const std::string& nameOfDataDistribution, const PUWeight::Scenario sc) {

  if( isInit_ ) {
    std::cerr << "\n\nERROR in PUWeight: weights already initialised" << std::endl;
    // throw std::exception();
  }

  // Get data distribution from file
  TFile file(nameOfDataDistribution.c_str(), "READ");
  TH1* h = NULL;
  file.GetObject("pileup",h);
  if( h == NULL ) {
    std::cerr << "\n\nERROR in PUWeight: Histogram 'pileup' does not exist in file '" << nameOfDataDistribution << "'\n.";
    throw std::exception();
  }
  h->SetDirectory(0);
  file.Close();

  // Computing weights
  puWeigths_ = generateWeights(sc,h);
  nPUMax_ = puWeigths_.size();
    
//   for( int i =0;i< puWeigths_.size();i++)
//   {
//    std::cout << puWeigths_.at(i) << std::endl;   
//   }
  // Clean up
  delete h;

  isInit_ = true;
}

//==============================================================================================
// Get weight factor dependent on number of added PU interactions
double PUWeight::getPUWeight(const int nPU) const {

  double w = 1.;
  if( isInit_ ) {
    if( nPU >= nPUMax_ ) {
      //std::cerr << "WARNING: Number of PU vertices = " << nPU << " out of histogram binning." << std::endl;
      // In case nPU is out-of data-profile binning,
      // use weight from last bin
      w = puWeigths_.back();
    } else {
      w = puWeigths_.at(nPU);
    }
  }
  //std::cout <<  " pileup weights : "<< w << std::endl;
  return w;
}

//==============================================================================================
// Generate weights for given data PU distribution
// Scenarios from: https://twiki.cern.ch/twiki/bin/view/CMS/Pileup_MC_Gen_Scenarios
// Code adapted from: https://twiki.cern.ch/twiki/bin/viewauth/CMS/PileupReweighting
std::vector<double> PUWeight::generateWeights(const PUWeight::Scenario sc, const TH1* data_npu_estimated) const {

  // Store probabilites for each pu bin
  unsigned int nPUMax = 0;
  double *npuProbs = 0;

  if( sc == Winter15_25ns ) {
    std::cout<<"IN WINTER 15!!!!"<<std::endl;
  
    nPUMax = 52;
    double npuWinter15_25ns[52] = {
      4.8551E-07,
      1.74806E-06,
      3.30868E-06,
      1.62972E-05,
      4.95667E-05,
      0.000606966,
      0.003307249,
      0.010340741,
      0.022852296,
      0.041948781,
      0.058609363,
      0.067475755,
      0.072817826,
      0.075931405,
      0.076782504,
      0.076202319,
      0.074502547,
      0.072355135,
      0.069642102,
      0.064920999,
      0.05725576,
      0.047289348,
      0.036528446,
      0.026376131,
      0.017806872,
      0.011249422,
      0.006643385,
      0.003662904,
      0.001899681,
      0.00095614,
      0.00050028,
      0.000297353,
      0.000208717,
      0.000165856,
      0.000139974,
      0.000120481,
      0.000103826,
      8.88868E-05,
      7.53323E-05,
      6.30863E-05,
      5.21356E-05,
      4.24754E-05,
      3.40876E-05,
      2.69282E-05,
      2.09267E-05,
      1.5989E-05,
      4.8551E-06,
      2.42755E-06,
      4.8551E-07,
      2.42755E-07,
      1.21378E-07,
      4.8551E-08};
      npuProbs = npuWinter15_25ns;
      std::cout<<"npuWinter15_25ns[0] = " << npuWinter15_25ns[0] <<"    npuProbs[0] = "<<npuProbs[0]<<std::endl;
    }
  
    else if( sc == Fall15_25ns ) {   //from https://github.com/cms-sw/cmssw/blob/CMSSW_7_6_X/SimGeneral/MixingModule/python/mix_2015_25ns_FallMC_matchData_PoissonOOTPU_cfi.py
      std::cout<<"IN FALL 15!!!!"<<std::endl;
                     // for new promtreco 70 pile-up bins!!
      nPUMax = 70;    
      double npuFall15_25ns[70] = {                      0.000108645538111,                      // 0.000108643,                                                                                                                                          
                                                        0.000394333629534,                     // 0.000388957,                                                                                                                                                            
                                                        0.000339768859866,                   // 0.000332882,                                                                                                                                                              
                                                        0.000383481812597,                   // 0.00038397,                                                                                                                                                               
                                                        0.000548831915265,                   // 0.000549167,                                                                                                                                                              
                                                        0.00105094497545,                    // 0.00105412,                                                                                                                                                               
                                                        0.00458736360941,                    // 0.00459007,                                                                                                                                                         
                                                        0.02100178115,                       // 0.0210314,                                                                                                                                                                
                                                        0.0573840258554,                    // 0.0573688,                                                                                                                                                                 
                                                        0.103937912934,                     // 0.103986,                                                                                                                                                            
                                                        0.142366234607,                     // 0.142369,                                                                                                                                                            
                                                        0.157713429447,                     // 0.157729,                                                                                                                                                            
                                                        0.147719695734,                     // 0.147685,                                                                                                                                                            
                                                        0.12107593778,                      // 0.121027,                                                                                                                                                            
                                                        0.0885830250224,                    // 0.08855,                                                                                                                                                             
                                                        0.0582848540299,                    // 0.0582866,                                                                                                                                                           
                                                        0.0348511450412,                    // 0.0348526,                                                                                                                                                           
                                                        0.0194561105015,                    // 0.019457,                                                                                                                                                            
                                                        0.0107643400838,                    // 0.0107907,                                                                                                                                                           
                                                        0.00653139273976,                   // 0.00654313,                                                                                                                                                  
                                                        0.00463459193946,                   // 0.00463195,                                                                                                                                                          
                                                        0.00371565192965,                   // 0.00370927,                                                                                                                                                          
                                                        0.003111720296,                     // 0.0031137,                                                                                                                                                           
                                                        0.00260932702457,                   // 0.00261141,                                                                                                                                                  
                                                        0.00214888901722,                   // 0.00215499,                                                                                                                                                          
                                                        0.00174479894194,                   // 0.00174491,                                                                                                                                                          
                                                        0.00138263865699,                   // 0.00138268,                                                                                                                                                          
                                                        0.00106895491577,                   // 0.00106731,                                                                                                                                                          
                                                        0.000802168345866,                  // 0.000798828,                                                                                                                                                         
                                                        0.000581310944829,                  // 0.00057785,                                                                                                                                                          
                                                        0.000402281439121,                  // 0.00040336,                                                                                                                                                          
                                                        0.000268467837316,                  // 0.00027161,                                                                                                                                                          
                                                        0.000172584647293,                  // 0.000176535,                                                                                                                                                         
                                                        0.000110785333,                     // 0.00011092,                                                                                                                                                                
                                                        7.14283912928e-05,                  // 6.75502e-05,                                                                                                                                                               
                                                        3.96881004401e-05,                  // 4.00323e-05,                                                                                                                                                               
                                                        2.2697110072e-05,                   // 2.32123e-05,                                                                                                                                                               
                                                        1.19217143812e-05,                  // 1.32585e-05,                                                                                                                                                               
                                                        6.77601714832e-06,                  // 7.51611e-06,                                                                                                                                                               
                                                        4.35601102392e-06,                  // 4.25902e-06,                                                                                                                                                         
                                                        2.08884739159e-06,                  // 2.42513e-06,                                                                                                                                                 
                                                        1.40105617728e-06,                  // 1.39077e-06,                                                                                                                                                 
                                                        9.17054952404e-07,                  // 8.02452e-07,                                                                                                                                                 
                                                        5.34948722235e-07,                  // 4.64159e-07,                                                                                                                                                        
                                                        5.09474973558e-07,                  // 2.67845e-07,                                                                                                                                                 
                                                        1.52842492067e-07,                  // 1.5344e-07,                                                                                                                                                  
                                                        7.64212460336e-08,                  // 8.68966e-08,                                                                                                                                                 
                                                        2.54737486779e-08,                  // 4.84931e-08,                                                                                                                                                 
                                                        0.0,                                // 2.6606e-08,                                                                                                                                                          
                                                        0.0,                                // 1.433e-08};                                                                                                                                                          
                                                        0.0,                                                                                                                                                                                        
                                                        0.0,                                                                                                                                                                                                      
                                                        0.0,                                                                                                                                                                                                
                                                        0.0,                                                                                                                                                                                                
                                                        0.0,                                                                                                                                                                                                
                                                        0.0,                                                                                                                                                                                                
                                                        0.0,                                                                                                                                                                                                
                                                        0.0,                                                                                                                                                                                                
                                                        0.0,                                                                                                                                                                                                
                                                        0.0,                                                                                                                                                                                                
                                                        0.0,                                                                                                                                                                                                
                                                        0.0,                                                                                                                                                                                                
                                                        0.0,                                                                                                                                                                                                
                                                        0.0,                   
                                                        0.0,                   
                                                        0.0,                   
                                                        0.0,                   
                                                        0.0,                   
                                                        0.0,                   
                                                        0.0};                   
                                                                              
           		   
        npuProbs = npuFall15_25ns;
        std::cout<<"npuFall15_25ns[0] = " << npuFall15_25ns[0] <<"    npuProbs[0] = "<<npuProbs[0]<<std::endl;
      }
      else if( sc == Spring16_25ns ) {   //from https://github.com/cms-sw/cmssw/blob/CMSSW_8_1_X/SimGeneral/MixingModule/python/mix_2016_25ns_SpringMC_PUScenarioV1_PoissonOOTPU_cfi.py
        std::cout<<"IN SPRING 16!!!!"<<std::endl;
  
        nPUMax = 70;
        double npuSpring16_25ns[70] = {
                      0.000831123670347,          // 0.000733382225482,                                                                                                                                                       
                       0.001242371322,             // 0.00123341556104, 		                                                                                                                                             
                       0.00340472335733,           // 0.00290019334622, 		                                                                                                                                             
                       0.00407915512544,           // 0.00433362224148, 		                                                                                                                                             
                       0.00383602817798,           // 0.00340022668178, 		                                                                                                                                             
                       0.00658446582858,           // 0.00660044002934,		                                                                                                                                             
                       0.00817288008118,           // 0.00860057337156, 		                                                                                                                                             
                       0.00944395586106,           // 0.00880058670578, 		                                                                                                                                             
                       0.0137942990487,            // 0.0144342956197, 		                                                                                                                                             
                       0.0170519806511,            // 0.0163677578505, 		                                                                                                                                             
                       0.0213392194439,            // 0.0223681578772, 		                                                                                                                                             
                       0.0247627322057,            // 0.0249349956664, 		                                                                                                                                             
                       0.0280985610798,            // 0.0288685912394, 		                                                                                                                                             
                       0.0323384195413,            // 0.0308353890259, 		                                                                                                                                             
                       0.0370704355172,            // 0.0386692446163, 		                                                                                                                                             
                       0.0456867682516,            // 0.0452030135342, 		                                                                                                                                             
                       0.0559489241543,            // 0.0577038469231, 		                                                                                                                                             
                       0.0577136901191,            // 0.0586705780385, 		                                                                                                                                             
                       0.0625770805519,            // 0.062104140276, 		                                                                                                                                             
                       0.0591081174882,            // 0.0608373891593, 		                                                                                                                                             
                       0.0656817032487,            // 0.0675711714114, 		                                                                                                                                             
                       0.0677644131857,            // 0.0689379291953, 		                                                                                                                                             
                       0.0625313653441,            // 0.060304020268, 		                                                                                                                                             
                       0.054749354074,             // 0.0532035469031, 		                                                                                                                                             
                       0.0503255751573,            // 0.0493699579972, 		                                                                                                                                             
                       0.0402051818112,            // 0.0400693379559, 		                                                                                                                                             
                       0.0374666970577,            // 0.0356357090473, 		                                                                                                                                             
                       0.0299467535145,            // 0.0304686979132, 		                                                                                                                                             
                       0.0271823079724,            // 0.0262017467831, 		                                                                                                                                             
                       0.0219326467399,            // 0.0217347823188, 		                                                                                                                                             
                       0.0179333040095,            // 0.0176011734116, 		                                                                                                                                             
                       0.0142917736051,            // 0.0149009933996, 		                                                                                                                                             
                       0.00838588343144,           // 0.00826721781452, 		                                                                                                                                             
                       0.00522805247122,           // 0.00486699113274, 		                                                                                                                                             
                       0.0022455135992,            // 0.00246683112207, 		                                                                                                                                             
                       0.00077806678182,           // 0.000633375558371, 	                                                                                                                                                     
                       0.00019478160146,           // 0.000100006667111, 	                                                                                                                                                     
                       7.16949181984e-05,          // 6.66711114074e-05, 	                                                                                                                                                     
                       0.0,                        //             0.0, 		                                                                                                                                             
                       0.0,                        //             0.0,		                                                                                                                                             
                       0.0,                        //             0.0,		                                                                                                                                             
                       0.0,                        //             0.0,		                                                                                                                                             
                       0.0,                        //             0.0,	                                                                                                                                                     
                       0.0,                        //             0.0,		                                                                                                                                             
                       0.0,                        //             0.0,		                                                                                                                                             
                       0.0,                        //             0.0,		                                                                                                                                             
                       0.0,                        //             0.0,		                                                                                                                                             
                       0.0,                        //             0.0, 		                                                                                                                                             
                       0.0,                        //             0.0, 		                                                                                                                                             
                       0.0,                        //             0.0, 		                                                                                                                                             
                       0.0,                        // 0.0, 		                                                                                                                                                                                  
                       0.0,                        // 0.0, 		                                                                                                                                                                                  
                       0.0,                        // 0.0, 		                                                                                                                                                                                  
                       0.0,                        // 0.0, 		                                                                                                                                                                                  
                       0.0,                        // 0.0, 		                                                                                                                                                                                  
                       0.0,                        // 0.0, 		                                                                                                                                                                                  
                       0.0,                        // 0.0, 		                                                                                                                                                                                  
                       0.0,                        // 0.0, 		                                                                                                                                                                                  
                       0.0,                        // 0.0, 		                                                                                                                                                                                  
                       0.0,                        // 0.0, 		                                                                                                                                                                                  
                       0.0,                        // 0.0, 		                                                                                                                                                                                  
                       0.0,                        // 0.0, 		                                                                                                                                                                                  
                       0.0,                        // 0.0, 		                                                                                                                                                                                  
                       0.0,                        // 0.0, 		                                                                                                                                                                                  
                       0.0,                        // 0.0, 		                               
                       0.0,                        // 0.0, 		                               
                       0.0,                        // 0.0, 		                               
                       0.0,                        // 0.0, 		                               
                       0.0,                        // 0.0, 		                               
                       0.0                        // 0.0                                                
           		
            };
            npuProbs = npuSpring16_25ns;
        std::cout<<"npuSpring16_25ns[0] = " << npuSpring16_25ns[0] <<"    npuProbs[0] = "<<npuProbs[0]<<std::endl;
      }
          else if( sc == Summer16_25ns ) {   //from https://github.com/cms-sw/cmssw/blob/CMSSW_8_1_X/SimGeneral/MixingModule/python/mix_2016_25ns_SpringMC_PUScenarioV1_PoissonOOTPU_cfi.py
        std::cout<<"IN SUMMER 16!!!!"<<std::endl;
  
        nPUMax = 70;
        double npuSummer16_25ns[70] = {
        //Moriond17 PU                    // QCD sample with flat PU
        0.0,                              //      0.0142735060623,                                                                                                                                                                
        0.0,                              //      0.014285787689,                                                                                                                                                                
        6.71208510924e-05,                //    0.0142411728001,                                                                                                                                                                
        0.000134241702185,                //    0.014356469704,                                                                                                                                                                
        3.35604255462e-05,                //    0.0142649841172,                                                                                                                                                                
        0.000201362553277,                //    0.0143162411104,                                                                                                                                                                
        0.000402725106554,                //    0.0143540885723,                                                                                                                                                                
        0.000671208510924,                //    0.0142439299,                                                                                                                                                                
        0.00127529617076,                 //   0.0142980693157,                                                                                                                                                                
        0.00214786723496,                 //   0.0142703729943,                                                                                                                                                                
        0.00543678893848,                 //   0.0142399195729,                                                                                                                                                                
        0.0087928314931,                  //  0.0141889132252,                                                                                                                                                                
        0.0143974225593,                  //  0.0142453084499,                                                                                                                                                                
        0.0209081451153,                  //  0.0143816595711,                                                                                                                                                                
        0.0273517468201,                  //  0.0142760125167,                                                                                                                                                                
        0.035574051079,                   // 0.0142380397321,                                                                                                                                                                
        0.0383931268248,                  //  0.0143133586878,                                                                                                                                                                
        0.044299761721,                   // 0.0143176196603,                                                                                                                                                                
        0.0498707923616,                  //  0.014341180332,                                                                                                                                                                
        0.0516830553411,                  //  0.0142579660448,                                                                                                                                                                
        0.0561801523643,                  //  0.0142819026847,                                                                                                                                                                
        0.0559452293855,                  //  0.0142411728001,
        0.0569184817263,                  //  0.0142587179811,
        0.05560962513,                    //0.0143095990061,
        0.0527905493842,                  //  0.0143014530292,
        0.045776420445,                   // 0.0143183715967,
        0.0451723327852,                  //  0.0143133586878,
        0.0383595663993,                  //  0.0143504542134,
        0.0338289089506,                  //  0.0142935576978,
        0.0327885357586,                  //  0.0142865396254,
        0.0266469778837,                  //  0.0142930564069,
        0.0227539685203,                  //  0.0143429348501,
        0.0199013323489,                  //  0.0142489428089,
        0.0185253549015,                  //  0.0142928057614,
        0.0158405208578,                  //  0.0143350395186,
        0.014867268517,                   // 0.0143033328701,
        0.0128200825586,                  //  0.0143127320742,
        0.0121488740477,                  //  0.0143696285898,
        0.0107057757492,                  //  0.0142715008988,
        0.00943047957848,                 //   0.0142446818363,
        0.00956472128067,                 //   0.0142406715092,
        0.00721549149243,                 //   0.0142011948519,
        0.00714837064134,                 //   0.014225006169,
        0.00667852468369,                 //   0.0143401777502,
        0.00550390978958,                 //   0.0142330268232,
        0.00496694298084,                 //   0.0142867902708,
        0.00432929489546,                 //   0.0143017036747,
        0.00332248212907,                 //   0.0141757543394,
        0.0030539987247,                  //  0.0142978186703,
        0.00181226297949,                 //   0.0142339040822,
        0.00228210893714,                 //   0.0142657360536,
        0.00137597744739,                 //   0.0142783936484,
        0.00137597744739,                 //   0.0142594699175,
        0.00127529617076,                 //   0.0142524518451,
        0.000570527234285,                //    0.0142866649481,
        0.000134241702185,                //    0.0143671221354,
        0.000234922978823,                //    0.0143183715967,
        0.00026848340437,                 //   0.0142243795554,
        6.71208510924e-05,                //    0.0143257656372,
        0.0,                              //      0.0142424260273,
        6.71208510924e-05,                //    0.0142030746927,
        3.35604255462e-05,                //    0.0142689944443,
        0.0,                              //       0.0142762631622,
        3.35604255462e-05,                //    0.0143499529225,
        0.0,                              //       0.0143098496516,
        0.0,                              //      0.0144071000836,
        0.0,                              //       0.0142941843114,
        3.35604255462e-05,                //    0.0143332850005,
        0.0,                              //      0.0142584673357,
        0.0                               //      0.0142676158944        
            };   
            
          npuProbs = npuSummer16_25ns;
          std::cout<<"npuSummer16_25ns[0] = " << npuSummer16_25ns[0] <<"    npuProbs[0] = "<<npuProbs[0]<<std::endl;
        } 
        
        else if( sc == Summer16_25ns_FlatPU ) {   //from https://github.com/cms-sw/cmssw/blob/CMSSW_8_1_X/SimGeneral/MixingModule/python/mix_2016_25ns_SpringMC_PUScenarioV1_PoissonOOTPU_cfi.py
        std::cout<<"IN SUMMER 16 with Flat PU!!!!"<<std::endl;
  
        nPUMax = 70;
        double npuSummer16_25ns[70] = {
        //Moriond17 PU                    // QCD sample with flat PU
             0.0142735060623,                                                                                                                                                                
             0.014285787689,                                                                                                                                                                
           0.0142411728001,                                                                                                                                                                
           0.014356469704,                                                                                                                                                                
           0.0142649841172,                                                                                                                                                                
           0.0143162411104,                                                                                                                                                                
           0.0143540885723,                                                                                                                                                                
           0.0142439299,                                                                                                                                                                
          0.0142980693157,                                                                                                                                                                
          0.0142703729943,                                                                                                                                                                
          0.0142399195729,                                                                                                                                                                
         0.0141889132252,                                                                                                                                                                
         0.0142453084499,                                                                                                                                                                
         0.0143816595711,                                                                                                                                                                
         0.0142760125167,                                                                                                                                                                
        0.0142380397321,                                                                                                                                                                
         0.0143133586878,                                                                                                                                                                
        0.0143176196603,                                                                                                                                                                
         0.014341180332,                                                                                                                                                                
         0.0142579660448,                                                                                                                                                                
         0.0142819026847,                                                                                                                                                                
         0.0142411728001,
         0.0142587179811,
       0.0143095990061,
         0.0143014530292,
        0.0143183715967,
         0.0143133586878,
         0.0143504542134,
         0.0142935576978,
         0.0142865396254,
         0.0142930564069,
         0.0143429348501,
         0.0142489428089,
         0.0142928057614,
         0.0143350395186,
        0.0143033328701,
         0.0143127320742,
         0.0143696285898,
         0.0142715008988,
          0.0142446818363,
          0.0142406715092,
          0.0142011948519,
          0.014225006169,
          0.0143401777502,
          0.0142330268232,
          0.0142867902708,
          0.0143017036747,
          0.0141757543394,
         0.0142978186703,
          0.0142339040822,
          0.0142657360536,
          0.0142783936484,
          0.0142594699175,
          0.0142524518451,
           0.0142866649481,
           0.0143671221354,
           0.0143183715967,
          0.0142243795554,
           0.0143257656372,
             0.0142424260273,
           0.0142030746927,
           0.0142689944443,
              0.0142762631622,
           0.0143499529225,
              0.0143098496516,
             0.0144071000836,
              0.0142941843114,
           0.0143332850005,
             0.0142584673357,
             0.0142676158944        
            };   
            
          npuProbs = npuSummer16_25ns;
          std::cout<<"npuSummer16_25ns[0] = " << npuSummer16_25ns[0] <<"    npuProbs[0] = "<<npuProbs[0]<<std::endl;
        } 

      // Check that binning of data-profile matches MC scenario
      if( nPUMax != static_cast<unsigned int>(data_npu_estimated->GetNbinsX()) ) {
        std::cerr << "\n\nERROR number of bins (" << data_npu_estimated->GetNbinsX() << ") in data PU-profile does not match number of bins (" << nPUMax << ") in MC scenario " << toString(sc) << std::endl;
        throw std::exception();
      }

      std::vector<double> result(nPUMax,0.);
      double s = 0.;
      for(unsigned int npu = 0; npu < nPUMax; ++npu) {
        const double npu_estimated = data_npu_estimated->GetBinContent(data_npu_estimated->GetXaxis()->FindBin(npu));
        if(npuProbs[npu] >1.0e-10)
        {
        result[npu] = npu_estimated / npuProbs[npu];
        }
        else
        {
         result[npu] = 0;   
        }
        s += npu_estimated;
      }
      // normalize weights such that the total sum of weights over thw whole sample is 1.0, i.e., sum_i  result[i] * npu_probs[i] should be 1.0 (!)
      for(unsigned int npu = 0; npu < nPUMax; ++npu) {
        result[npu] /= s;
      }
      
      return result;
    }

