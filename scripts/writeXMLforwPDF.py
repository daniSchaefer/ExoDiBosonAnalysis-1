import os
import glob
import math
import array
import ROOT
import ntpath
import sys
import subprocess
import time
import numpy
from subprocess import Popen
from optparse import OptionParser
from array import array

from ROOT import gROOT, TPaveLabel, gStyle, gSystem, TGaxis, TStyle, TLatex, TString, TF1,TFile,TLine, TLegend, TH1D,TH1F,TH2D,THStack,TChain, TCanvas, TMatrixDSym, TMath, TText, TPad

from array import array

#parser = OptionParser()

#parser.add_option('--filename', action="store",type="string",dest = "filename",default="../config/BulkWW_M1000.xml")
#parser.add_option('--outname',action="store",type="string",dest="outname",default="N")
#parser.add_option('--s',action="store",type="string",dest="suffix",default="")

#(options, args) = parser.parse_args()



def write(pdfset,mass,model,direc,N,sb=0):
    VV = 'VV'
    suffix = ''
    if model.find('BulkWW')!=-1:
        suffix = 'BulkGravToWW'
    if model.find('BulkZZ')!=-1:
        suffix = 'BulkGravToZZToZhadZhad'
    if model.find('Zprime')!=-1:
        suffix = 'ZprimeToWW'
    if model.find('Wprime')!=-1:
        suffix = 'WprimeToWZToWhadZhad'
    if model.find('QstarQW')!=-1:
        suffix = 'QstarToQW'
        VV ='qV'
    if model.find('QstarQZ')!=-1:
        suffix = 'QstarToQZ' 
        VV= 'qV'
    VV='PDF'    
    name = '../config/'+model+"_M"+str(int(mass))+".xml"
    if sb:
        name = '../config/'+model+"_M"+str(int(mass))+"_SB.xml"
        VV +='_SBtest'
    f = open(name,"w")
    f.write('<?xml version="1.0" encoding="UTF-8"?>\n')
    f.write('<!DOCTYPE JobConfiguration PUBLIC "" "JobConfig.dtd">\n')
    f.write('<JobConfiguration JobName="exovvJob" OutputLevel="INFO">\n')
    f.write('<Library Name="libGoodRunsLists" />\n')
    f.write('<Library Name="libLHAPDF"/>\n')
    f.write('<Library Name="libExoDiBosonAnalysis" />\n')

    f.write('<Package Name="SFrameCore.par" />\n')
    f.write('<Package Name="ExoDiBosonAnalysis.par" />\n')
      
    f.write('<Cycle Name="ExoDiBosonAnalysis" OutputDirectory="../AnalysisOutput/80X/SignalMC/Summer16/Sys/" PostFix="" ProofServer="lite" ProofWorkDir="" RunMode="LOCAL" TargetLumi="1.0">\n')
    
    for n in range(1,N+1):
        f.write('<InputData Lumi="0.0" NEventsMax="-1" NEventsSkip="0" SkipValid="False" Version="'+VV+'" Type="'+model+'_13TeV_'+str(int(mass))+'GeV">\n')
        if model.find('Qstar')==-1:
            f.write('  <In FileName=" dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/t3groups/uniz-higgs/Summer16/Ntuple_80_20170203/'+suffix+'_narrow_M-'+str(int(mass))+'_13TeV-madgraph/'+suffix+'_narrow_M-'+str(int(mass))+'_13TeV-madgraph20170203_signal/'+direc+'/0000/flatTuple_'+str(n)+'.root" Lumi="1.0"/>  \n')
        
        else:
            f.write('  <In FileName="dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/t3groups/uniz-higgs/Summer16/Ntuple_80_20170203/'+suffix+'_M-'+str(int(mass))+'_TuneCUETP8M2T4_13TeV-pythia8/'+suffix+'_M-'+str(int(mass))+'_TuneCUETP8M2T4_13TeV-pythia820170203_signal/'+direc+'/0000/flatTuple_'+str(n)+'.root" Lumi="1.0"/> \n') 
        
        f.write('<InputTree Name="ntuplizer/tree" /> \n')   
        f.write('      <OutputTree Name="tree" />    \n')
        f.write('    </InputData>                    \n')

    
    
    f.write('<UserConfig>\n')                    
                   
    f.write('<!--general settings-->                     \n')
    f.write('<Item Name="InputTreeName" Value="tree" />  \n')
    f.write('<Item Name="OutputTreeName" Value="tree" /> \n')
    f.write('<Item Name="isSignal" Value="true" />       \n')
    f.write('<Item Name="runOnMC" Value="true" />        \n')
    f.write('<Item Name="usePuppiSD" Value="true" />     \n')
    f.write('<Item Name="GenStudies" Value="false" />    \n')
    if model.find("Qstar")==-1:
        if sb:
            f.write('<Item Name="Channel" Value="jetmassSidebandVVdijet" />     \n')
        else:
            f.write('<Item Name="Channel" Value="VVdijet" />     \n')
    else:
        if sb:
            f.write('<Item Name="Channel" Value="jetmassSidebandqVdijet" />     \n')
        else:
            f.write('<Item Name="Channel" Value="qVdijet" />     \n')
    f.write('<Item Name="MassWindow" Value="VV" />       \n')
    f.write('<Item Name="Trigger" Value="false" />       \n')
    f.write('<Item Name="applyFilters" Value="false" />  \n')
    f.write('                                            \n')
    f.write('<!--leptonic selections-->                  \n')
    f.write('<Item Name="LeptPtCut" Value="30" />        \n')
    f.write('<Item Name="LeptEtaCut" Value="2.1" />      \n')
    f.write('<Item Name="AleptPtCut" Value="30" />       \n')
    f.write('<Item Name="AleptEtaCut" Value="2.4" />     \n')
    f.write('<Item Name="METCut" Value="30" />           \n')
    f.write('                                            \n')
    f.write('<!--jet selections-->                       \n')
    f.write('                                            \n')
    f.write('<Item Name="dEtaCut" Value="1.3" />         \n')
    f.write('<Item Name="MjjCut" Value="1050.0" />        \n')
    f.write('<Item Name="JetPtCutLoose" Value="30." />   \n')
    f.write('<Item Name="JetPtCutTight" Value="200." />  \n')
    f.write('<Item Name="JetEtaCut" Value="2.5" />       \n')
    f.write('<Item Name="Tau21Cut" Value="true" />       \n')
    f.write('<Item Name="Tau21HPLow" Value="0.00" />     \n')
    f.write('<Item Name="Tau21HPHigh" Value="0.35" />    \n') 
    f.write('<Item Name="Tau21Low" Value="0.35" />       \n')
    f.write('<Item Name="Tau21High" Value="0.75" />      \n')
    f.write('                                            \n')
    f.write('<Item Name="mWLow" Value="65." />           \n')
    f.write('<Item Name="mWHigh" Value="85." />          \n')
    f.write('<Item Name="mZLow" Value="85." />           \n')
    f.write('<Item Name="mZHigh" Value="105." />         \n')
    f.write('                                            \n')
    f.write('<Item Name="xSec" Value="1." />             \n')
    f.write('<Item Name="genEvents" Value="1." />        \n')
    f.write('<Item Name="Lumi" Value="1." />             \n')
    f.write('<Item Name="PUdata" Value="/mnt/t3nfs01/data01/shome/dschafer/ExoDiBosonAnalysis/results/PU/DataPUDistribution.root" /> \n')
    f.write('<Item Name="JSONfile" Value="No" />\n')
    f.write('<Item Name="BTagEff4vetoData" Value="data/TT_CT10_TuneZ2star_8TeV-powheg-tauola_AK5PF_CSVM_bTaggingEfficiencyMap.root" />  \n')
    f.write('<Item Name="BTagEff4fatjetData" Value="data/BtagEfficienciesMap_fatjets_Wp.root" />  \n')
    f.write('<Item Name="BTagEff4subjetData" Value="data/btag-efficiency-maps.root" />           \n')
    f.write('<Item Name="PUPPIJEC" Value="/mnt/t3nfs01/data01/shome/dschafer/ExoDiBosonAnalysis/data/puppiCorr.root" /> \n')
    f.write('<Item Name="PUPPIJMR" Value="/mnt/t3nfs01/data01/shome/dschafer/ExoDiBosonAnalysis/data/jetmassResolution.root" /> \n')
    f.write('<Item Name="scaleUncPar" Value="PDF" /> <!-- -1 = NoScaling   0/1 = JMS UP/DOWN   2/3 =JMR UP/DOWN 4/5 = JES UP/DOWN 6/7 = JER UP/DOWN  -->  \n')
    f.write('<Item Name="JMS" Value="0.999" />  \n')
    f.write('<Item Name="JMSunc" Value="0.004" />  \n')
    f.write('<Item Name="JMR" Value="1.079" />      \n')
    f.write('<Item Name="JMRunc" Value="0.105" />    \n')
    f.write('<Item Name="PDFSET" Value="'+str(int(pdfset))+'" />    \n')
    #f.write('<Item Name="wPDFname" Value="wpdf_M'+str(int(mass))+'_'+model+'" />  \n')
    
    f.write('  </UserConfig>  \n')
    f.write('</Cycle>  \n')
    f.write('</JobConfiguration>\n')
    
    
    
    
    
    
    
    
#######################################
############ Main Code ################
#######################################

if __name__== '__main__':
  
  #masses=[800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500]
  #models=["WprimeWZ","ZprimeWW","BulkWW","BulkZZ"]
  #altmodels=["QstarQW","QstarQZ"]
  ##for model in models:
    ##for m in masses:
      ##write(263400,m,model)
  
  #massesalt=[800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500,5000,5500,6000,6500,7000,7500]
  
  #for amodel in altmodels:
      #for am in massesalt:
          #write(263400,am,amodel,1)
          
  masses=[1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500]
  model = "BulkWW"
  direc = ["170203_124015","170203_124102","170203_124212", "170203_124303","170203_124351", "170203_124445","170203_124543","170222_121405","170203_124637","170203_124725","170203_124815"]
  num =[2,2,5,5,3,1,4,3,1,2,2]
  for i in range(0,len(masses)):
      write(263400,masses[i],model,direc[i],num[i])
  
  
  #masses=[1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500,5000,6000,7000]
  #model = "QstarQW"
  #direc = ["170203_131033","170203_131119","170203_131245","170203_131334","170203_131424","170203_131525","170203_131617","170203_131737","170203_131834","170203_131927","170203_132026", "170203_132144","170203_132239","170203_132327"]
  #num = [13,16,15,5,11,3,1,14,6,3,4,11,9,21]
  #for i in range(0,len(masses)):
      #write(263400,masses[i],model,direc[i],num[i])    
  
  
  #masses=[1000,1200,1400,1600,1800,2000,2500,3000,4500,6000]
  #model = "QstarQZ"
  #direc = ["170203_132416", "170203_132501","170203_132550","170203_132643","170203_132755","170203_132843","170203_132932","170203_133028","170203_133122","170203_133213"]
  #num = [14,4,1,9,14,1,2,8,13,5]
  #for i in range(0,len(masses)):
      #write(263400,masses[i],model,direc[i],num[i])   
  
