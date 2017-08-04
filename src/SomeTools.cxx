#include "include/SomeTools.h"
#include "include/InputData.h"
#include "include/LeptonCandidate.h"
#include "include/JetCandidate.h"
#include "include/HistosManager.h"
#include "include/ExoDiBosonAnalysis.h""

#include <TLorentzVector.h>
#include <TVector3.h>
#include <iostream>
#include <vector>
#include <map>


bool isHadronicEvent(InputData& data)
{
    int N = (data.genParticle_pdgId)->size();
    
    std::vector<int>* pdgID = data.genParticle_pdgId;
    
    std::vector<int> indexV;
    std::vector<int> indexDaughter;
    std::vector<std::vector<int> >* daughters = data.genParticle_dau  ;
    std::vector<std::vector<int> >* mothers   = data.genParticle_mother  ;
    
    //std::cout << N << std::endl;
    //std::cout << " ====================== "<< data.EVENT_event << " =============================== " << std::endl;
    for( int i =0; i< N; i++)
    {
      //  std::cout << TMath::Abs(pdgID->at(i)) << std::endl;
        if( TMath::Abs(pdgID->at(i)) != 24 and TMath::Abs(pdgID->at(i)) !=23)
            continue;
        if( ! ComesFromGraviton(data, i))
            continue;
        if( (daughters->at(i)).size() ==1)
            continue;
        indexV.push_back(i);
    }
    //std::cout << " number W bosons found " << indexV.size() << std::endl;
    for( int i=0;i<indexV.size();i++)
    {
        indexDaughter = FindDaughterIndex(pdgID,mothers, daughters->at(indexV.at(i)), indexV.at(i));
        for(int j=0;j<indexDaughter.size();j++)
        {
          //std::cout <<" index : "<< indexDaughter.at(j) << std::endl;
          if (indexDaughter.at(j)==-99)   
              return 0;
          int ID = TMath::Abs(pdgID->at(indexDaughter.at(j)));
          //std::cout << " pdgID daughter " << ID << std::endl;
          if(ID >= 11 and ID <= 18)
          {
            //  std::cout << " leptonic or semileptonic " << std::endl;
              return 0;
          }
          //std::cout << "hadronic event " << std::endl;
        }
    }
   return 1; 
}


TLorentzVector getGENLVParticle(InputData& data,int index)
{
  std::vector<float>* pt  = data.genParticle_pt;
  std::vector<float>* eta = data.genParticle_eta;
  std::vector<float>* phi = data.genParticle_phi;
  std::vector<float>* e   = data.genParticle_e; 
  TLorentzVector result;
  result.SetPtEtaPhiE(pt->at(index),eta->at(index),phi->at(index),e->at(index));
  return result;
}

double getGravitonGenMass(InputData& data)
{
  int N = (data.genParticle_pdgId)->size();
  std::vector<int>* pdg = data.genParticle_pdgId;
  int gravitonIndex=-99;
  for(int i=0;i<N;i++)
  {
    int pdgID = pdg->at(i);
    if ( pdgID == 39 or (pdgID > 4000000 and pdgID < 4000013) or pdgID == 32 or pdgID ==34 or pdgID == 9000002 or pdgID == 9000001 or pdgID == 24 or pdgID ==23)
    {
      gravitonIndex=i;   
    }  
  }
  if( gravitonIndex==-99)
      return 0;
  else
      return getGENLVParticle(data,gravitonIndex).M();
}

bool ComesFromGraviton(InputData& data, int index)
{
  bool findGraviton =0;
  std::vector<int>* pdgID = data.genParticle_pdgId;
  std::vector<std::vector<int> >* mothers = data.genParticle_mother;
  for(int i =0; i< mothers->at(index).size();i++)
  {
    int pdgID = TMath::Abs((mothers->at(index)).at(i) );
    //std::cout << pdgID << std::endl;
    if ( pdgID == 39 or (pdgID > 4000000 and pdgID < 4000013) or pdgID == 32 or pdgID ==34 or pdgID == 9000002 or pdgID == 9000001 or pdgID == 24 or pdgID ==23)
    {
      findGraviton =1;   
    }
  }
  //std::cout << findGraviton << std::endl;
  return findGraviton;  
}

std::vector<int> FindDaughterIndex(std::vector<int>* pdgID, std::vector<std::vector<int> >* mothers,std::vector<int> daughtersV , int Vindex)
{
    int ID = pdgID->at(Vindex);
    int index = -99;
    std::vector<int> result;
    //std::cout <<"number of daughter particles " << daughtersV.size() << std::endl;
    //std::cout << "ID " << ID << std::endl;
    for( int i =0; i< daughtersV.size();i++)
    {
        result.push_back(-99);
         int d_ID = daughtersV.at(i);
      //   std::cout << d_ID << std::endl;
         for( int ii =0; ii< pdgID->size(); ii++)
         {
           if( pdgID->at(ii) != d_ID)
              continue;
           for( int iii=0; iii< mothers->at(ii).size(); iii++)
           {
             if( mothers->at(ii).at(iii) != ID )
                 continue;
             //std::cout << mothers->at(ii).at(iii) << std::endl;           
             index = ii;
           }
         }
         
       result.at(i) = index; 
        
    }
  if( result.size() <1)
  {
    result = {-99,-99};   
  }
  if( result.size() == 1)
  {
    result.push_back(-99);   
  }
  //std::cout << result.at(0) << " " << result.at(1) << std::endl;
  return result;
}


void PrintLV(TLorentzVector V)
{
  std::cout << " pt " << V.Pt() << std::endl;
  std::cout << " eta " << V.Eta() << std::endl;
  std::cout << " phi " << V.Phi() << std::endl;
  std::cout << " e " << V.E() << std::endl;
  
  
  std::cout << " px " << V.Px() << std::endl;
  std::cout << " py " << V.Py() << std::endl;
  std::cout << " pz " << V.Pz() << std::endl;
  std::cout << " e " <<  V.E() << std::endl;
    
}

void PrintPdgIDs(InputData& t12)
{
  for(int i=0;i<80;i++)
       {std::cout <<"-" ;}
     std::cout <<std::endl;
     for(int i=0;i<80;i++)
       {std::cout <<"-" ;}
     std::cout <<std::endl;
     std::cout<< "event " << t12.EVENT_event <<std::endl;
     std::cout << t12.genParticle_pdgId->size() << " = number of particles" <<std::endl;
     std::cout <<std::endl;
    
   for(int k =0;k<t12.genParticle_pdgId->size() ;k++)
	    {
                
	      for(int i=0;i<80;i++)
	  	{std::cout <<"-" ;}
	      std::cout <<std::endl;
	      std::cout << "pdgId " << t12.genParticle_pdgId->at(k) <<std::endl;
	      for(int i=0;i<80;i++)
	  	{std::cout <<"-" ;}
	      std::cout <<std::endl;
	      std::cout <<"# of mother particles " << t12.genParticle_mother->at(k).size() << std::endl;
	   
	      if(t12.genParticle_mother->at(k).size() != 0)
	  	{
	  	  std::vector<int> tmp_moth =t12.genParticle_mother->at(k);
		  
	  	  for(int i=0;i<tmp_moth.size();i++)
	  	    {
	  	      std::cout <<tmp_moth.at(i)<< " , ";
	  	    }
	  	  std::cout << " size of vector " << tmp_moth.size()<< std::endl;
		  
	  	  std::cout <<std::endl;
	  	}
	      std::cout <<"# of daughter particles " << t12.genParticle_dau->at(k).size()<<std::endl;
	      if(t12.genParticle_dau->at(k).size() != 0)
	  	{
	     
	  	  std::vector<int> tmp_dau =t12.genParticle_dau->at(k);
		 
	  	  for(int i=0;i<tmp_dau.size();i++)
	  	    {
	  	      std::cout << tmp_dau.at(i)<< " , ";
	  	    }
	  	  std::cout << " size of vector " << tmp_dau.size()<<std::endl;
	
	  	}
	      std::cout <<std::endl;
	    }

 for(int i=0;i<80;i++)
   {std::cout <<"-" ;}
 std::cout <<std::endl;
 for(int i=0;i<80;i++)
   {std::cout <<"-" ;}
 std::cout <<std::endl;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// calculate cos( theta1) -> sensitive to polarisation of produced bosons (W or Z)


double CalculateCOSTheta1(InputData& data, bool genStudies)
{
    int N = (data.genParticle_pdgId)->size();
    
    std::vector<int>* pdgID = data.genParticle_pdgId;
    std::vector<float>* pt  = data.genParticle_pt;
    std::vector<float>* eta = data.genParticle_eta;
    std::vector<float>* phi = data.genParticle_phi;
    std::vector<float>* e   = data.genParticle_e;
    
    int indexV =-99;
    int indexDaughter = -99;
    std::vector<std::vector<int> >* daughters = data.genParticle_dau  ;
    std::vector<std::vector<int> >* mothers   = data.genParticle_mother  ;
    
    //std::cout << N << std::endl;
    //std::cout << " ===================================================== " << std::endl;
    for( int i =0; i< N; i++)
    {
      //  std::cout << TMath::Abs(pdgID->at(i)) << std::endl;
        if( TMath::Abs(pdgID->at(i)) != 24 and TMath::Abs(pdgID->at(i)) !=23)
            continue;
        if( ! ComesFromGraviton(data, i))
            continue;
        if( (daughters->at(i)).size() ==1)
            continue;
        indexV = i;
        break;
    }
    indexDaughter = FindDaughterIndex(pdgID,mothers, daughters->at(indexV), indexV).at(0);
    
    TLorentzVector VLab;
    TLorentzVector DLab;
    
    
    VLab.SetPtEtaPhiE(pt->at(indexV),eta->at(indexV),phi->at(indexV),e->at(indexV));
    DLab.SetPtEtaPhiE(pt->at(indexDaughter),eta->at(indexDaughter),phi->at(indexDaughter),e->at(indexDaughter));
    //PrintLV(VLab);
    //PrintLV(DLab);
    
    TLorentzVector VRest = VLab;
    TLorentzVector DRest = DLab;
    
    
    TVector3 boo = VLab.BoostVector();
    
    //std::cout << " M " << VLab.M() << std::endl;
    VRest.Boost(-boo.Px(),-boo.Py(),-boo.Pz());
    DRest.Boost(-boo.Px(),-boo.Py(),-boo.Pz());
    
    //std::cout << " M " << VRest.M() << std::endl;
    //PrintLV(VRest);
    //std::cout << " ===================" << std::endl;
    
    Double_t theta1 = DRest.Angle(VLab.Vect());
    //std::cout << theta1 << std::endl;
    return TMath::Cos(theta1);    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////  fill some histograms to test the new selection (without mass window) for Qstar ///////////////////////////////////////////////////////



int findGenV(InputData& data,bool isMC)
{
   int N = (data.genParticle_pdgId)->size(); 
   for (int i=0;i< N;i++){
         if (ComesFromGraviton(data,i))
         {
            int id = TMath::Abs(data.genParticle_pdgId->at(i));
            if(  id>=23 and id<=24) return i;
         }
    
  }
  return -99;
}


int findGenQuarkJet(InputData& data,bool isMC)
{
  int N = (data.genParticle_pdgId)->size();
  for (int i=0;i< N;i++){
         if (ComesFromGraviton(data,i))
         {
            int id = TMath::Abs(data.genParticle_pdgId->at(i));
            if(  id>=1 and id<=6) return i;
         }
    
  }
  return -99;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////  check if W is produced resonantly (i.e. if both generated quarks are within the AK8 jet) for Qstar ///////////////////////////////////////////////////////

bool mergedTruth(InputData &data, TLorentzVector AK8jet,bool isMC)
{
   if(!isMC) return 1;
   int associatedQuarks=0;
   std::vector<int> indices = getGenWZquarks(data, isMC);
   for(int i=0;i<indices.size();i++)
   {
    TLorentzVector q = getGENLVParticle(data,indices.at(i));
    //std::cout << AK8jet.DeltaR(q) << std::endl;
    if (AK8jet.DeltaR(q) < 0.8)
    {
      associatedQuarks+=1;  
    }
       
   }
   if (associatedQuarks ==2) return 1;
   else return 0;
}

std::vector<int> getGenWZquarks(InputData &data,bool isMC)
{
  std::vector<int> indices ={};
  if (!isMC) return indices;
  int N = (data.genParticle_pdgId)->size();
  std::vector<std::vector<int> >* mothers   = data.genParticle_mother  ;
  for(int i=0;i<N;i++)
  {
     if ( TMath::Abs(data.genParticle_pdgId->at(i)) <1 or TMath::Abs(data.genParticle_pdgId->at(i)) >6)
         continue;
     if (!( containsWZ(data,mothers->at(i)) or ComesFromGraviton(data,isMC)))
         continue;
     indices.push_back(i);
     //std::cout << " found quarks from W/Z or Graviton in the event " << std::endl;
      
  }
  return indices;  
}


bool containsWZ(InputData &data,std::vector<int> mothers)
{
  for( int i=0;i<mothers.size();i++)
  {
   if( TMath::Abs(mothers.at(i))==24 or  TMath::Abs(mothers.at(i))==23)
       return 1;
  }
  return 0;
}
