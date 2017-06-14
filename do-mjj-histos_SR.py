# for data SB: python do-mjj-histos_SR.py --dataSB >> results/Data_VVdijet_SB.log
# for anything MC just leave our --dataSB and uncomment one of the filenames specifiyng which sample to use
# for signal MC use: python do-mjj-histos_SR.py --signal ZprimeWW --mass 4500
# to make the histos we need for the limit setting to not scale to lumi -> add option --noLumiScale => the output gets written to the input dir in DijetCombineLimitCode

from optparse import OptionParser
import os,commands, os.path
import sys
from ROOT import *
import math
import time
from array import *
# import CMS_lumi, tdrstyle
import copy
# ---------------------------------------------------------------------------------------------------------------------------
def write(fname, histolist):
    """Write the new histogram to disk"""
    base = fname
    outfname = "results/" + base + ".root"
    if opts.noLumiScale:
        outfname =  base + ".root"
    # outfname = base + ".root"
    if opts.doSmeared!="":
        outfname = "/usr/users/dschaefer/SFrame_setup/ExoDiBosonAnalysis/forSystematics/histosForShapeUnc/" + base + ".root"
    print "Saving file %s " %outfname
    fout = TFile(outfname,"RECREATE")
    for h in histolist:
      h.Write()
    fout.Close()
# ---------------------------------------------------------------------------------------------------------------------------
argv = sys.argv
parser = OptionParser()   
parser.add_option("-L", "--lumi", dest="lumi", default=35967,
                              help="Set lumi")
parser.add_option("--dataSB", dest="dataSB", action="store_true",default=False)
parser.add_option("--signal", dest="signal", action="store",default="")
parser.add_option("--mass",dest="mass",action="store",default=1200)
parser.add_option("--noLumiScale", dest="noLumiScale", action="store_true",default=False)
parser.add_option("--doSmeared", dest="doSmeared", action="store",default="")
parser.add_option("--bkg",dest="which_bkg",action="store",default="QCD")
parser.add_option("--path",dest="path",action="store",default="/storage/jbod/dschaefer/AnalysisOutput/80X/Bkg/Summer16/")
parser.add_option("--data",dest="data",action="store",default="")

(opts, args) = parser.parse_args(argv)  

if opts.data != "":
    opts.dataSB = True
path =opts.path
histolist = []
rebin = 1
#data_filename = "Data_VVdijet_SB_36400ifb.root"
#data_filename = "Data_VVdijet_SB_36814ifb_JECv2.root"
#data_filename = "Data_qVdijet_SB_36814ifb.root"
#data_filename = "Data_qVdijet_SB_36400ifb.root"
data_filename = opts.data+".root"
#data_filename = "JetHT_Run2016B_qVdijet_SR.root"
#data_filename = "JetHT_Run2016B_rerereco_qVdijet_SR.root"

#filename = "QCD_Spring16_Ptbinned_pythia8_qVdijet.root"
#filename = "QCD_Spring16_Ptbinned_pythia8_qVdijet_SB_test.root"
#filename = "QCD_Spring16_madgraph_pythia8_VVdijet.root"
#filename = "QCD_Spring16_madgraph_pythia8_VVdijet_SB.root"
#filename = "QCD_Spring16_madgraph_pythia8_qVdijet.root"
#filename = "QCD_Spring16_madgraph_pythia8_qVdijet_SB.root"
#filename = "ExoDiBosonAnalysis.QCD_herwigpp_qVdijet_SB.root"
#filename = "QCD_pythia8_qVdijet_SB.root"
#filename = "QCD_pythia8_qVdijet_SR.root"
#filename = ""
#filename = "QCD_pythia8_qVdijet_SB_test.root"
filename = opts.which_bkg +".root"
#filename = "QCD_pythia8_qVdijet_SR.root"
#filename = "QCD_madgraph_pythia8_VVdijet_SB.root"
#if (opts.which_bkg).find("W")!=-1:
    #filename = "ExoDiBosonAnalysis.Wjets_VVdijet_SR.root"

# ---------------------------------------------------------------------------------------------------------------------------  

# cmd = "rm /shome/thaarres/EXOVVAnalysisRunII/CMSSW_7_1_5/src/DijetCombineLimitCode/input/*.root"
# print cmd
# os.system(cmd)

print path
#gROOT.SetBatch(kTRUE)
      
i =0
histolist = []
nEvents = []
gen = "pythia8"
if filename.find("madgraph")!=-1:
    gen = "madgraph_pythia8"
if filename.find("herwig")!=-1:
    gen= "herwig"
name = "QCD_"+gen+"_VV"
if filename.find("qV")!=-1:
    name = "QCD_"+gen+"_qV"
if path.find("Summer16")!=-1:
    name +="_summer16"
if (opts.which_bkg).find("W")!=-1:
    name = "Wjets"
    if filename.find("qV")!=-1:
        name += "_qV"
    if filename.find("VV")!=-1:
        name+="_VV"
    if filename.find("SB")!=-1:
        name+="_SB"
if opts.dataSB:
    name = "ReRecoData_VVdijet_test" 
    #name = "Data_runB_VVdijet"
    if data_filename.find("qV")!=-1:
        name = "ReRecoData_qVdijet_test"
        #name = "Data_runB_qVdijet"
    filename = data_filename
if opts.signal !="":
    filename =   "ExoDiBosonAnalysis."+opts.signal+"_13TeV_"+str(opts.mass)+"GeV.VV.root"
    if opts.signal.find("Qstar")!=-1:
        filename =   "ExoDiBosonAnalysis."+opts.signal+"_13TeV_"+str(opts.mass)+"GeV.qV.root"
if opts.doSmeared!= "":
    filename =   "ExoDiBosonAnalysis."+opts.signal+"_13TeV_"+str(opts.mass)+"GeV."+opts.doSmeared+".root"
for root, _, files in os.walk(path):
  for f in files:
    fullpath = os.path.join(root, f)                                                                               
    if f.find(filename)!=-1:
        print fullpath
        print "Working on  file %s" %fullpath
        if fullpath.find("QCD")!=-1 or opts.signal!="" or opts.which_bkg.find("W")!=-1:
            lumi = opts.lumi
        if fullpath.find("Data")!=-1:
            lumi = 1.
        if fullpath.find("SB")!=-1:
            name+= "_SB"  
        if fullpath.find("BulkWW")!=-1:
            name= "BulkWW_13TeV_"+str(opts.mass)+"GeV"
        if fullpath.find("BulkZZ")!=-1:
            name = "BulkZZ_13TeV_"+str(opts.mass)+"GeV"
        if fullpath.find("ZprimeWW")!=-1:
            name = "ZprimeWW_13TeV_"+str(opts.mass)+"GeV"
        if fullpath.find("WprimeWZ")!=-1:
            name = "WprimeWZ_13TeV_"+str(opts.mass)+"GeV"
        if fullpath.find("QstarQW")!=-1:
            name = "QstarQW_13TeV_"+str(opts.mass)+"GeV"
        if fullpath.find("QstarQZ")!=-1:
            name = "QstarQZ_13TeV_"+str(opts.mass)+"GeV"
        
        if opts.doSmeared!="":
            name+="_"+opts.doSmeared
        print "Will save to filename %s" %name
        filetmp = TFile.Open(fullpath,"READ") 
        intree = filetmp.Get("tree")
        if opts.noLumiScale:
            lumi = 1.
        print "Using lumi = %s" %lumi
    
        histolist=[]
        nEvents =[]

        VVHP = TH1F('DijetMassHighPuriVV','DijetMassHighPuriVV',7000,0,7000)
        WWHP = TH1F('DijetMassHighPuriWW','DijetMassHighPuriWW',7000,0,7000)
        WZHP = TH1F('DijetMassHighPuriWZ','DijetMassHighPuriWZ',7000,0,7000)
        ZZHP = TH1F('DijetMassHighPuriZZ','DijetMassHighPuriZZ',7000,0,7000)
        VVLP = TH1F('DijetMassLowPuriVV','DijetMassLowPuriVV',7000,0,7000)
        WWLP = TH1F('DijetMassLowPuriWW','DijetMassLowPuriWW',7000,0,7000)
        WZLP = TH1F('DijetMassLowPuriWZ','DijetMassLowPuriWZ',7000,0,7000)
        ZZLP = TH1F('DijetMassLowPuriZZ','DijetMassLowPuriZZ',7000,0,7000)
        qVHP = TH1F('DijetMassHighPuriqV','DijetMassHighPuriqV',8000,0,8000)
        qWHP = TH1F('DijetMassHighPuriqW','DijetMassHighPuriqW',8000,0,8000)
        qZHP = TH1F('DijetMassHighPuriqZ','DijetMassHighPuriqZ',8000,0,8000)
        qVLP = TH1F('DijetMassLowPuriqV','DijetMassLowPuriqV'  ,8000,0,8000)
        qWLP = TH1F('DijetMassLowPuriqW','DijetMassLowPuriqW'  ,8000,0,8000)
        qZLP = TH1F('DijetMassLowPuriqZ','DijetMassLowPuriqZ'  ,8000,0,8000)
        VVNP = TH1F('DijetMassNoPuriVV','DijetMassNoPuriVV',7000,0,7000)
        WWNP = TH1F('DijetMassNoPuriWW','DijetMassNoPuriWW',7000,0,7000)
        WZNP = TH1F('DijetMassNoPuriWZ','DijetMassNoPuriWZ',7000,0,7000)
        ZZNP = TH1F('DijetMassNoPuriZZ','DijetMassNoPuriZZ',7000,0,7000)
        qVNP = TH1F('DijetMassNoPuriqV','DijetMassNoPuriqV',7000,0,7000)
        qWNP = TH1F('DijetMassNoPuriqW','DijetMassNoPuriqW',7000,0,7000)
        qZNP = TH1F('DijetMassNoPuriqZ','DijetMassNoPuriqZ',7000,0,7000)
        
        
        if fullpath.find("q")==-1 and fullpath.find("Qstar")==-1:
            histolist.append(VVHP)
            histolist.append(WWHP)
            histolist.append(WZHP)
            histolist.append(ZZHP)
            histolist.append(VVLP)
            histolist.append(WWLP)
            histolist.append(WZLP)
            histolist.append(ZZLP)
            nEvents = [0,0,0,0,0,0,0,0]
            #histolist.append(VVNP)
            #histolist.append(WWNP)
            #histolist.append(WZNP)
            #histolist.append(ZZNP)
        else:
            histolist.append(qVHP)
            histolist.append(qWHP)
            histolist.append(qZHP)
            histolist.append(qVLP)
            histolist.append(qWLP)
            histolist.append(qZLP)
            nEvents = [0,0,0,0,0,0]
            #histolist.append(qVNP)
            #histolist.append(qWNP)
            #histolist.append(qZNP)
        
        mw_min_SB = 20. # old value = 20.
        mw_max_SB = 65. # old value = 65.
        
        mw_min_SB_qVdown = 45. # old value = 20.
        mw_max_SB_qVdown = 65. # old value = 65.
        mw_min_SB_qVup = 105.
        mw_max_SB_qVup = 200.
        
        HPcut = 0.35
        # events with the largest mass:
        massmax = -1
        eventmax =-1
        lumimax =-1
        run =-1
        jet1pt = 0
        jet1eta =0
        jet1phi =0
        jet1msSD =0
        jet1taumax =0
        jet2pt = 0
        jet2eta =0
        jet2phi =0
        jet2msSD =0
        jet2taumax =0
        
        LPmassmax = -1
        LPeventmax =-1
        LPlumi =-1
        LPrun =-1
        for event in intree:
                
               
               # VVdijet signal region :
            if fullpath.find("SB")==-1 and fullpath.find("q")==-1 and fullpath.find("Qstar")==-1:
                    print " VVdijet SR"
                    if ( event.MVV < 1050.0): continue
                    if event.jet_puppi_tau2tau1_jet2 <= HPcut and event.jet_puppi_tau2tau1_jet1 <= HPcut :
                        VVHP.Fill(event.MVV,event.weight)
                        nEvents[0]+=1
                        if (1100 < event.MVV < 1300):
                            if 90 < event.jet_puppi_softdrop_jet1 <92:
                                if 90 < event.jet_puppi_softdrop_jet2 <92:
                                    print "======================================="
                                    print "==============HP===================="
                                    print "inv mass: "+str(event.MVV)
                                    print "event : "+str(event.event)
                                    print "lumit : "+str(event.lumi)
                                    print "run   : "+str(event.run)
                                    print " jet1pt     :  "+str(event.jet_pt_jet1             )
                                    print " jet1eta    :  "+str(event.jet_eta_jet1            )
                                    print " jet1phi    :  "+str(event.jet_phi_jet1            )
                                    print " jet1msSD   :  "+str(event.jet_puppi_softdrop_jet1 )
                                    print " jet1taumax :  "+str(event.jet_puppi_tau2tau1_jet1 )
                                    print " jet2pt     :  "+str(event.jet_pt_jet2             )
                                    print " jet2eta    :  "+str(event.jet_eta_jet2            )
                                    print " jet2phi    :  "+str(event.jet_phi_jet2            )
                                    print " jet2msSD   :  "+str(event.jet_puppi_softdrop_jet2 )
                                    print " jet2taumax :  "+str(event.jet_puppi_tau2tau1_jet2 )
                        if event.MVV > massmax:
                            massmax = event.MVV
                            lumimax = event.lumi
                            run  = event.run 
                            eventmax = event.event
                            jet1pt      = event.jet_pt_jet1
                            jet1eta     = event.jet_eta_jet1
                            jet1phi     = event.jet_phi_jet1
                            jet1msSD    = event.jet_puppi_softdrop_jet1
                            jet1taumax  = event.jet_puppi_tau2tau1_jet1
                            jet2pt     = event.jet_pt_jet2
                            jet2eta    = event.jet_eta_jet2
                            jet2phi    = event.jet_phi_jet2
                            jet2msSD   = event.jet_puppi_softdrop_jet2
                            jet2taumax = event.jet_puppi_tau2tau1_jet2
                            
                        if (65. <= event.jet_puppi_softdrop_jet1 <= 85. and 65. <= event.jet_puppi_softdrop_jet2 <= 85.) :
                            WWHP.Fill(event.MVV,event.weight) #WWHP
                            nEvents[1]+=1
                        if (85. < event.jet_puppi_softdrop_jet1 <= 105. and 85. < event.jet_puppi_softdrop_jet2 < 105.) :
                            ZZHP.Fill(event.MVV,event.weight) #ZZHP
                            nEvents[2]+=1
                        if ( (85 < event.jet_puppi_softdrop_jet1 <= 105. and 65. <= event.jet_puppi_softdrop_jet2 <= 85.) or (85 < event.jet_puppi_softdrop_jet2 <= 105. and 65. <= event.jet_puppi_softdrop_jet1 <= 85.) ) :
                            WZHP.Fill(event.MVV,event.weight) #WZHP
                            nEvents[3]+=1
          
                    if (event.jet_puppi_tau2tau1_jet2 <= HPcut and HPcut < event.jet_puppi_tau2tau1_jet1 <= 0.75) or (event.jet_puppi_tau2tau1_jet1 <= HPcut and HPcut < event.jet_puppi_tau2tau1_jet2 <= 0.75) :
                        VVLP.Fill(event.MVV,event.weight)
                        nEvents[4]+=1
                        if event.MVV > LPmassmax:
                            LPmassmax = event.MVV
                            LPlumi = event.lumi
                            LPrun  = event.run 
                            LPeventmax = event.event
                        if (65 <= event.jet_puppi_softdrop_jet1 <= 85. and 65 <= event.jet_puppi_softdrop_jet2 < 85.) :
                            WWLP.Fill(event.MVV,event.weight) #WWLP
                            nEvents[5]+=1
                        if (85 < event.jet_puppi_softdrop_jet1 <= 105. and 85. < event.jet_puppi_softdrop_jet2 <= 105.) :
                            ZZLP.Fill(event.MVV,event.weight) #ZZLP
                            nEvents[6]+=1
                        if ( (85 < event.jet_puppi_softdrop_jet1 <= 105. and 65. <= event.jet_puppi_softdrop_jet2 < 85.) or (85 < event.jet_puppi_softdrop_jet2 <= 105. and 65. <= event.jet_puppi_softdrop_jet1 < 85.) ) :
                            WZLP.Fill(event.MVV,event.weight) #WZLP
                            nEvents[7]+=1
               
               # VVdijet sideband region: (technically here WW histos contain the events where 1W is found, while ZZ contains the histos where 1Z is found!)
            if fullpath.find("SB")!=-1 and fullpath.find("q")==-1 and fullpath.find("Qstar")==-1:
                   print "VVdijet SB region "
                   if ( event.MVV < 1070.0): continue
                   if (5000 < event.MVV < 6300):
                       print event.MVV
                       print event.jet_puppi_softdrop_jet1
                       print event.jet_puppi_softdrop_jet2
                       print event.jet_puppi_tau2tau1_jet1
                       print event.jet_puppi_tau2tau1_jet2
                   #=== play with jet mass window for sideband region ==============================
                   if  (mw_min_SB > event.jet_puppi_softdrop_jet1 or mw_min_SB > event.jet_puppi_softdrop_jet2): continue
                   if  (mw_max_SB < event.jet_puppi_softdrop_jet1 and mw_max_SB < event.jet_puppi_softdrop_jet2): continue
                   #================================================================================
                   if event.jet_puppi_tau2tau1_jet1 <= HPcut and event.jet_puppi_tau2tau1_jet2<=HPcut:
                       VVHP.Fill(event.MVV,event.weight)
                       nEvents[0]+=1
                       if (5000 < event.MVV < 6300): print "passed HP"
                       if ((65. <= event.jet_puppi_softdrop_jet1 <= 85.) or (65. <= event.jet_puppi_softdrop_jet2 <= 85.)) :
                            WWHP.Fill(event.MVV,event.weight) #WWHP
                            nEvents[1]+=1
                       if ((85. < event.jet_puppi_softdrop_jet1 <= 105.) or  (85. < event.jet_puppi_softdrop_jet2 < 105.)) :
                            ZZHP.Fill(event.MVV,event.weight) #ZZHP
                            nEvents[3]+=1
                   if (event.jet_puppi_tau2tau1_jet2 <= HPcut and HPcut < event.jet_puppi_tau2tau1_jet1 <= 0.75) or (event.jet_puppi_tau2tau1_jet1 <= HPcut and HPcut < event.jet_puppi_tau2tau1_jet2 <= 0.75) :
                       VVLP.Fill(event.MVV,event.weight)
                       nEvents[4]+=1
                       if (5000 < event.MVV < 6300): print "passed LP"
                       if ((65. <= event.jet_puppi_softdrop_jet1 <= 85.) or (65. <= event.jet_puppi_softdrop_jet2 <= 85.)) :
                            WWLP.Fill(event.MVV,event.weight) #WWLP
                            nEvents[5]+=1
                       if ((85. < event.jet_puppi_softdrop_jet1 <= 105.) or  (85. < event.jet_puppi_softdrop_jet2 < 105.)) :
                            ZZLP.Fill(event.MVV,event.weight) #ZZLP
                            nEvents[7]+=1
                   if (5000 < event.MVV < 6300): print "======================================="
     
            # qV sideband (fill histos for HP/LP region):
            
            if name.find("SB")!=-1 and (name.find("q")!=-1 or fullpath.find("Qstar")!=-1):
                    print "qV dijet SB region " 
                    if ( event.MVV < 1070.): continue
                    #if ( mw_min_SB_qVdown > event.jet_puppi_softdrop_jet1 or mw_min_SB_qVdown > event.jet_puppi_softdrop_jet2):
                        #continue
                    #if (event.jet_puppi_softdrop_jet1 > mw_max_SB_qVdown and event.jet_puppi_softdrop_jet1 < mw_min_SB_qVup):
                        #continue
                    #if (event.jet_puppi_softdrop_jet2 > mw_max_SB_qVdown and event.jet_puppi_softdrop_jet2 < mw_min_SB_qVup):
                        #continue
                    #if ( mw_max_SB_qVup < event.jet_puppi_softdrop_jet1 or mw_max_SB_qVup < event.jet_puppi_softdrop_jet2):
                        #continue
                    
                    #if ( event.jet_puppi_tau2tau1_jet1 <= HPcut or event.jet_puppi_tau2tau1_jet2<= HPcut):
                        #qVHP.Fill(event.MVV,event.weight)
                        #nEvents[0]+=1
                    #if ( HPcut <event.jet_puppi_tau2tau1_jet1 <= 0.75 or HPcut <event.jet_puppi_tau2tau1_jet1 <= 0.75):
                        #qVLP.Fill(event.MVV,event.weight)
                        #nEvents[3]+=1
                    
                    
                    if event.jet_puppi_tau2tau1_jet2 <= HPcut or event.jet_puppi_tau2tau1_jet1 <= HPcut :
                            if ( (45 < event.jet_puppi_softdrop_jet1 <= 65. and 105 < event.jet_puppi_softdrop_jet2) or (45 < event.jet_puppi_softdrop_jet2 <= 65. and 105 < event.jet_puppi_softdrop_jet1)):     
                                qVHP.Fill(event.MVV,event.weight) #qVHP
                    if HPcut < event.jet_puppi_tau2tau1_jet1 <= 0.75 or HPcut < event.jet_puppi_tau2tau1_jet2 <= 0.75 :
                            if ( (45 < event.jet_puppi_softdrop_jet1 <= 65. and 105 < event.jet_puppi_softdrop_jet2) or (45 < event.jet_puppi_softdrop_jet2 <= 65. and 105 < event.jet_puppi_softdrop_jet1)):     
                                qVLP.Fill(event.MVV,event.weight) #qVLP
                    
                    
                    
                    
                    
                    
                    
  
                        
                        
            # qV signal region (fill histos for W/Z and HP/LP):
            elif (name.find("q")!=-1 or name.find("Qstar")!=-1) and name.find("SB")==-1:
                 
                if ( event.MVV < 1050.): continue
                if ( (65. <= event.jet_puppi_softdrop_jet2 <= 105. and event.jet_puppi_tau2tau1_jet2 <= HPcut) or (65. <= event.jet_puppi_softdrop_jet1 <= 105. and event.jet_puppi_tau2tau1_jet1 <= HPcut)):
                    qVHP.Fill(event.MVV,event.weight) #qVHP
                    nEvents[0]+=1
                    if (1500 < event.MVV < 2500):
                        if (event.jet_puppi_softdrop_jet1 <= 65) and (event.jet_puppi_softdrop_jet1 >= 100):
                            if event.jet_pt_jet1 < 2050. and event.jet_pt_jet1 > 1950.:
                                print "======================================="
                                print "==============HP===================="
                                print "inv mass: "+str(event.MVV)
                                print "event : "+str(event.event)
                                print "lumit : "+str(event.lumi)
                                print "run   : "+str(event.run)
                                print " jet1pt     :  "+str(event.jet_pt_jet1             )
                                print " jet1eta    :  "+str(event.jet_eta_jet1            )
                                print " jet1phi    :  "+str(event.jet_phi_jet1            )
                                print " jet1msSD   :  "+str(event.jet_puppi_softdrop_jet1 )
                                print " jet1taumax :  "+str(event.jet_puppi_tau2tau1_jet1 )
                                print " jet2pt     :  "+str(event.jet_pt_jet2             )
                                print " jet2eta    :  "+str(event.jet_eta_jet2            )
                                print " jet2phi    :  "+str(event.jet_phi_jet2            )
                                print " jet2msSD   :  "+str(event.jet_puppi_softdrop_jet2 )
                                print " jet2taumax :  "+str(event.jet_puppi_tau2tau1_jet2 )
                    if event.MVV > massmax:
                            massmax = event.MVV
                            lumimax = event.lumi
                            run  = event.run 
                            eventmax = event.event
                            jet1pt      = event.jet_pt_jet1
                            jet1eta     = event.jet_eta_jet1
                            jet1phi     = event.jet_phi_jet1
                            jet1msSD    = event.jet_puppi_softdrop_jet1
                            jet1taumax  = event.jet_puppi_tau2tau1_jet1
                            jet2pt     = event.jet_pt_jet2
                            jet2eta    = event.jet_eta_jet2
                            jet2phi    = event.jet_phi_jet2
                            jet2msSD   = event.jet_puppi_softdrop_jet2
                            jet2taumax = event.jet_puppi_tau2tau1_jet2
                                
                            
                            
                if ( (65. <= event.jet_puppi_softdrop_jet2 <= 105. and HPcut <event.jet_puppi_tau2tau1_jet2 <= 0.75) or (65. <= event.jet_puppi_softdrop_jet1 <= 105. and HPcut <event.jet_puppi_tau2tau1_jet1 <= 0.75)):
                    qVLP.Fill(event.MVV,event.weight) #qVLP
                    nEvents[3]+=1
                    if event.MVV > LPmassmax:
                        LPmassmax = event.MVV
                        LPlumi = event.lumi
                        LPrun  = event.run 
                        LPeventmax = event.event

                if ( (85. < event.jet_puppi_softdrop_jet2 <= 105. and event.jet_puppi_tau2tau1_jet2 <= HPcut) or (85. < event.jet_puppi_softdrop_jet1 <= 105. and event.jet_puppi_tau2tau1_jet1 <= HPcut)):
                    qZHP.Fill(event.MVV,event.weight) #qZHP
                    nEvents[1]+=1
                if ( (85. < event.jet_puppi_softdrop_jet2 <= 105. and HPcut <event.jet_puppi_tau2tau1_jet2 <= 0.75) or (85. < event.jet_puppi_softdrop_jet1 <= 105. and HPcut <event.jet_puppi_tau2tau1_jet1 <= 0.75)):
                    qZLP.Fill(event.MVV,event.weight) #qZLP
                    nEvents[5]+=1
                if ( (65. <= event.jet_puppi_softdrop_jet2 <= 85. and event.jet_puppi_tau2tau1_jet2 <= HPcut) or (65. <= event.jet_puppi_softdrop_jet1 <= 85. and event.jet_puppi_tau2tau1_jet1 <= HPcut)):
                    qWHP.Fill(event.MVV,event.weight) #qWHP
                    nEvents[2]+=1
                if ( (65. <= event.jet_puppi_softdrop_jet2 <= 85. and HPcut <event.jet_puppi_tau2tau1_jet2 <= 0.75) or (65. <= event.jet_puppi_softdrop_jet1 <= 85. and HPcut <event.jet_puppi_tau2tau1_jet1 <= 0.75)):
                    qWLP.Fill(event.MVV,event.weight) #qWLP
                    nEvents[4]+=1
                
        i=0  
        print "==============HP===================="
        print "inv mass: "+str(massmax)
        print "event : "+str(eventmax)
        print "lumit : "+str(lumimax)
        print "run   : "+str(run)
        print " jet1pt     :  "+str(jet1pt     )
        print " jet1eta    :  "+str(jet1eta    )
        print " jet1phi    :  "+str(jet1phi    )
        print " jet1msSD   :  "+str(jet1msSD   )
        print " jet1taumax :  "+str(jet1taumax )
        print " jet2pt     :  "+str(jet2pt     )
        print " jet2eta    :  "+str(jet2eta    )
        print " jet2phi    :  "+str(jet2phi    )
        print " jet2msSD   :  "+str(jet2msSD   )
        print " jet2taumax :  "+str(jet2taumax )
        
        
        print "==============LP===================="
        print "inv mass: "+str(LPmassmax)
        print "event : "+str(LPeventmax)
        print "lumit : "+str(LPlumi)
        print "run   : "+str(LPrun)
        
        
        
        
        for n in nEvents:
            print n
        
        
        
        
        
        
        
        for n in nEvents:
            print histolist[i].GetName()+": "+str(n)
            i+=1
        for h in histolist:
            print "Scaling histogram to %f pb"%lumi
            print "Saving histogram %s" %h.GetName()
            h.Scale(lumi)
        write(name,histolist)
        filetmp.Close()
        
        
       
        del intree
        del histolist

