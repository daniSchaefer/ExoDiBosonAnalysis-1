#python do-jes.py -s JES -c VV --signal BulkWW
import xml.etree.ElementTree as ET
import os,commands
import sys
from optparse import OptionParser
import ROOT
from ROOT import *
import math
import multiprocessing

argv = sys.argv
parser = OptionParser()
parser.add_option("--doCV", dest="doCV", default=False, action="store_true",help="Produce samples with central value! No scaleUP/DOWN")
parser.add_option('-s', '--sys',action="store",type="string",dest="sys",default="JES")           #JES JER JMS JMR ALL
parser.add_option('-c', '--channel',action="store",type="string",dest="channel",default="VV")    #VV qV
parser.add_option('-S', '--signal',action="store",type="string",dest="signal",default="BulkWW")  #VBulkWW BulkZZ WprimeWZ ZprimeWW QstarQW QstarQZ
(opts, args) = parser.parse_args(argv)


unc_yield_jes_up = []
unc_yield_jer_up = []
unc_yield_jms_up = []
unc_yield_jmr_up = []
unc_migration_jes_up = []
unc_migration_jer_up = []
unc_migration_jms_up = []
unc_migration_jmr_up = []

unc_yield_jes_down = []
unc_yield_jer_down = []
unc_yield_jms_down = []
unc_yield_jmr_down = []
unc_migration_jes_down = []
unc_migration_jer_down = []
unc_migration_jms_down = []
unc_migration_jmr_down = []


unc_yield_scale_down = []
unc_yield_res_down = []
unc_yield_scale_up = []
unc_yield_res_up = []
unc_migration_scale_down = []
unc_migration_res_down = []
unc_migration_scale_up = []
unc_migration_res_up = []
  
#def createOutfiles(sys, channel):
  #xmlfile = '/mnt/t3nfs01/data01/shome/thaarres/EXOVVAnalysisRunII/ExoDiBosonAnalysis/config/sys/%s_sys.xml' %channel
  #tree = ET.parse(xmlfile)
  #root = tree.getroot()
  #print "Doing systematics: %s" %sys 
  
  #r = root.find('Cycle').find('UserConfig')																    
  #for i in r.findall('Item'):	
    #if i.get('Name') == 'scaleUncPar':	
      #if sys == 'CV':		
        #i.set('Value','')
      #else:		
        #i.set('Value','%s'%sys)
  #print "Changing version name to: %s" %sys   
  #rr = root.find('Cycle')    
  #for i in rr.findall('InputData'):	
    #i.set('Version','%s'%sys)

  #fname = '/mnt/t3nfs01/data01/shome/thaarres/EXOVVAnalysisRunII/ExoDiBosonAnalysis/config/sys/%s_%s.xml' %(channel,sys)
  #print "Saving .xml as: %s" %fname            
  #with open( fname , 'w') as f:
    #f.write('<?xml version="1.0" encoding="UTF-8"?>\n<!DOCTYPE JobConfiguration PUBLIC "" "/mnt/t3nfs01/data01/shome/thaarres/EXOVVAnalysisRunII/ExoDiBosonAnalysis/config/JobConfig.dtd">\n')
    #tree.write(f, 'utf-8')

#def runSFrame(xml): 
  #cmd = 'sframe_main %s' %(xml)
  #print cmd
  #os.system(cmd)
  
#def runMultiprocess(doSys, channel): 
  
  #print "start multiprocess"
  ##gROOT.SetBatch(True)
  ##parallelProcesses = multiprocessing.cpu_count()
  
  #files = []
  #for sys in doSys:
    #fname = '/mnt/t3nfs01/data01/shome/thaarres/EXOVVAnalysisRunII/ExoDiBosonAnalysis/config/sys/%s_%s.xml' %(channel,sys)
    #files.append(fname)

  ### create Pool
  ##p = multiprocessing.Pool(parallelProcesses)
  ##print "Using %i parallel processes" %parallelProcesses

  #for f in files:
    #cmd = 'sframe_main %s &' %(f)
    #print cmd
    #os.system(cmd)
    ## run jobs
    ## p.apply_async(runSFrame, args = (f))

 ## p.close()
  ##p.join()

def calculateYields(sys):
  
  outpath = '/mnt/t3nfs01/data01/shome/dschafer/ExoDiBosonAnalysis/forSystematics/'
  inpath  = '/mnt/t3nfs01/data01/shome/dschafer//AnalysisOutput/80X/SignalMC/Summer16/Sys/'
  
  status,ls_la = commands.getstatusoutput( 'ls -l %s' %sys )													      
  if status:																				      
    os.system('mkdir %s/%s' %(outpath,sys))
    
  
  signals = ['%s'%opts.signal]
  if opts.signal == 'ALL':
    signals = ['BulkWW','BulkZZ','WprimeWZ',"ZprimeWW"]
  
  for signal in signals:
    masses = [1200,1400,1600,1800,2000,2500,3000,3500,4000,4500]
    if opts.signal.find("BulkWW")!=-1:
      masses = [1200,1400,1600,1800,2000,2500,3500,4000,4500]

    if signal.find("BulkZZ")!=-1: 
      masses = [1200,1400,1600,1800,2000,2500,3000,3500,4000]

  
    fout = ['%s/%s/%ssys_HPVV_%s.txt'%(outpath,sys,sys,signal),'%s/%s/%ssys_LPVV_%s.txt'%(outpath,sys,sys,signal),
            '%s/%s/%ssys_HPWW_%s.txt'%(outpath,sys,sys,signal),'%s/%s/%ssys_LPWW_%s.txt'%(outpath,sys,sys,signal),
            '%s/%s/%ssys_HPWZ_%s.txt'%(outpath,sys,sys,signal),'%s/%s/%ssys_LPWZ_%s.txt'%(outpath,sys,sys,signal),
            '%s/%s/%ssys_HPZZ_%s.txt'%(outpath,sys,sys,signal),'%s/%s/%ssys_LPZZ_%s.txt'%(outpath,sys,sys,signal)]

    cuts = []
    debugs = []

    debugs.append("VV HP category")
    cut =  "jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 105 && jet_puppi_tau2tau1_jet1 < 0.35 && jet_puppi_tau2tau1_jet2 < 0.35"
    cuts.append(cut)

    debugs.append("VV LP category")
    cut =  "jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 105 && ((jet_puppi_tau2tau1_jet1 < 0.35 && jet_puppi_tau2tau1_jet2 > 0.35 && jet_puppi_tau2tau1_jet2 < 0.75) || (jet_puppi_tau2tau1_jet2 < 0.35 && jet_puppi_tau2tau1_jet1 > 0.35 && jet_puppi_tau2tau1_jet1 < 0.75))"
    cuts.append(cut)

    debugs.append("WW HP category")
    cut =  "jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 85 && jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 85 && jet_puppi_tau2tau1_jet1 < 0.35 && jet_puppi_tau2tau1_jet2 < 0.35"
    cuts.append(cut)

    debugs.append("WW LP category")
    cut =  "jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 85 && jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 85 &&  ((jet_puppi_tau2tau1_jet1 < 0.35 && jet_puppi_tau2tau1_jet2 > 0.35 && jet_puppi_tau2tau1_jet2 < 0.75) || (jet_puppi_tau2tau1_jet2 < 0.35 && jet_puppi_tau2tau1_jet1 > 0.35 && jet_puppi_tau2tau1_jet1 < 0.75))"
    cuts.append(cut)

    debugs.append("WZ HP category")
    cut =  "((jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 85 && jet_puppi_softdrop_jet2 > 85 && jet_puppi_softdrop_jet2 < 105) || (jet_puppi_softdrop_jet1 > 85 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 85)) && jet_puppi_tau2tau1_jet1 < 0.35 && jet_puppi_tau2tau1_jet2 < 0.35"
    cuts.append(cut)

    debugs.append("WZ LP category")
    cut =  "((jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 85 && jet_puppi_softdrop_jet2 > 85 && jet_puppi_softdrop_jet2 < 105) || (jet_puppi_softdrop_jet1 > 85 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 85)) &&  ((jet_puppi_tau2tau1_jet1 < 0.35 && jet_puppi_tau2tau1_jet2 > 0.35 && jet_puppi_tau2tau1_jet2 < 0.75) || (jet_puppi_tau2tau1_jet2 < 0.35 && jet_puppi_tau2tau1_jet1 > 0.35 && jet_puppi_tau2tau1_jet1 < 0.75))"
    cuts.append(cut)

    debugs.append("ZZ HP category")
    cut =  "jet_puppi_softdrop_jet1 > 85 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_softdrop_jet2 > 85 && jet_puppi_softdrop_jet2 < 105 && jet_puppi_tau2tau1_jet1 < 0.35 && jet_puppi_tau2tau1_jet2 < 0.35"
    cuts.append(cut)

    debugs.append("ZZ LP category")
    cut =  "jet_puppi_softdrop_jet1 > 85 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_softdrop_jet2 > 85 && jet_puppi_softdrop_jet2 < 105 && ((jet_puppi_tau2tau1_jet1 < 0.35 && jet_puppi_tau2tau1_jet2 > 0.35 && jet_puppi_tau2tau1_jet2 < 0.75) || (jet_puppi_tau2tau1_jet2 < 0.35 && jet_puppi_tau2tau1_jet1 > 0.35 && jet_puppi_tau2tau1_jet1 < 0.75))"
    cuts.append(cut)
    
    for f in range(len(fout)):
      
      print "Writing to file: " ,fout[f]
      outfile = open(fout[f],'w')
      outfile.write('mass %sUp %sDown (in percent)\n'%(sys,sys))
      outfile.write('\n')
      
      print ""
      print debugs[f]
      print cuts[f]
      print ""

      for mass in masses:
       
       #Central value
       print "######## Mass = %i #########" %mass
       fname = inpath + 'ExoDiBosonAnalysis.%s_13TeV_%sGeV.CV.root' %(signal,mass)
       tfile = ROOT.TFile.Open(fname,'READ')
       tree = tfile.Get("tree")
       cv = float(tree.GetEntries(cuts[f]))
       print "Central value = %.3f" %(cv)
       tfile.Close()
       tfile.Delete()
       
       #Scale up value
       fname = inpath + 'ExoDiBosonAnalysis.%s_13TeV_%sGeV.%sup.root' %(signal,mass,sys)
       tfile = ROOT.TFile.Open(fname,'READ')
       tree = tfile.Get("tree")
       up = float(tree.GetEntries(cuts[f]))
       print "Sys up = %.3f" %(up)
       tfile.Close()
       tfile.Delete()
       
       #Scale down value
       fname = inpath + 'ExoDiBosonAnalysis.%s_13TeV_%sGeV.%sdown.root' %(signal,mass,sys)
       tfile = ROOT.TFile.Open(fname,'READ')
       tree = tfile.Get("tree")
       down = float(tree.GetEntries(cuts[f]))
       print "Sys down = %.3f" %(down)
       tfile.Close()
       tfile.Delete()
       
       sup = up-cv
       sdown = down-cv
       if sup < 0 and sdown < 0: sdown = -sdown
       
       if f == 0 or f == 1:
         if sys.find("JES")!= -1: 
           unc_yield_jes_up.append(math.fabs(sup*100/cv))
           unc_yield_jes_down.append(math.fabs(sdown*100/cv))
         elif sys.find("JER")!= -1: 
           unc_yield_jer_up.append(math.fabs(sup*100/cv))
           unc_yield_jer_down.append(math.fabs(sdown*100/cv))
         elif sys.find("JMS")!= -1: 
           unc_yield_jms_up.append(math.fabs(sup*100/cv))
           unc_yield_jms_down.append(math.fabs(sdown*100/cv))
         elif sys.find("JMR")!= -1: 
           unc_yield_jmr_up.append(math.fabs(sup*100/cv))
           unc_yield_jmr_down.append(math.fabs(sdown*100/cv))
         elif sys.find("SCALE")!=-1:
            unc_yield_scale_up.append(math.fabs(sup*100/cv))
            unc_yield_scale_down.append(math.fabs(sdown*100/cv))  
         elif sys.find("RES")!=-1:  
            unc_yield_res_up.append(math.fabs(sup*100/cv))  
            unc_yield_res_down.append(math.fabs(sdown*100/cv))    
           
       else:
         if sys.find("JES")!= -1: 
           unc_migration_jes_up.append(math.fabs(sup*100/cv))
           unc_migration_jes_down.append(math.fabs(sdown*100/cv))
         elif sys.find("JER")!= -1: 
           unc_migration_jer_up.append(math.fabs(sup*100/cv))
           unc_migration_jer_down.append(math.fabs(sdown*100/cv))
         elif sys.find("JMS")!= -1: 
           unc_migration_jms_up.append(math.fabs(sup*100/cv))
           unc_migration_jms_down.append(math.fabs(sdown*100/cv))
         elif sys.find("JMR")!= -1: 
           unc_migration_jmr_up.append(math.fabs(sup*100/cv))
           unc_migration_jmr_down.append(math.fabs(sdown*100/cv))
         elif sys.find("SCALE")!=-1:
            unc_migration_scale_up.append(math.fabs(sup*100/cv))
            unc_migration_scale_down.append(math.fabs(sdown*100/cv))  
         elif sys.find("RES")!=-1:
            unc_migration_res_up.append(math.fabs(sup*100/cv))
            unc_migration_res_down.append(math.fabs(sdown*100/cv))  
           
       print '%s_M%i %.3f %.3f\n' %(signal,mass,sup*100/cv,sdown*100/cv)
       outfile.write('%s_M%i %.3f %.3f\n' %(signal,mass,sup*100/cv,sdown*100/cv))
     
      outfile.close()
  
       
### Start  main
if __name__ == '__main__':
  
  # Define which systematics to run
  doSys = []
  
  if   opts.sys == 'JES': doSys = ['JESup','JESdown']  
  if   opts.sys == 'JER': doSys = ['JERup','JERdown']  
  elif opts.sys == 'JMS': doSys = ['JMSup','JMSdown']  
  elif opts.sys == 'JMR': doSys = ['JMRup','JMRdown']
  elif opts.sys == 'ALL': doSys = ['JESup','JESdown','JERup','JERdown','JMSup','JMSdown','JMRup','JMRdown']
  else: 
    print "This systematic does not exist! Check spelling"
    
  #Compute central value. Neccessary first time you run
  #if opts.doCV:  
    #doSys.append('CV')
    
  print "Doing systematics for: " ,doSys
  
  # # Create XMLs for given systematics (+central value)
  # for sys in doSys:
  #   print "Creating output files for " ,sys
  #   createOutfiles(sys,opts.channel)

  # # Run SFrame for given systematics (+central value)
  # runMultiprocess(doSys,opts.channel)
  #
  #======================= Calculate yields ========================================================================================================
  if opts.sys == 'ALL':                 
    systematics = ['JMS','JMR',"JER","JES","SCALE","RES"]#["SCALE","RES"]##['JES','JER']#,'JMS','JMR']
    for s in systematics:
      calculateYields(s)
  else:
    calculateYields(opts.sys)

  print "For %s:" %opts.signal
  unc_yield_jes_up.sort();         unc_yield_jes_down.sort()
  unc_yield_jer_up.sort();         unc_yield_jer_down.sort()
  unc_yield_jms_up.sort();         unc_yield_jms_down.sort()
  unc_yield_jmr_up.sort();         unc_yield_jmr_down.sort()
  unc_migration_jes_up.sort();     unc_migration_jes_down.sort()
  unc_migration_jer_up.sort();     unc_migration_jer_down.sort()
  unc_migration_jms_up.sort();     unc_migration_jms_down.sort()
  unc_migration_jmr_up.sort();     unc_migration_jmr_down.sort()
  
  unc_yield_res_down.sort(); unc_yield_res_up.sort();unc_yield_scale_down.sort();unc_yield_scale_up.sort();
  unc_migration_res_down.sort(); unc_migration_res_up.sort();unc_migration_scale_down.sort();unc_migration_scale_up.sort();
  

  print "                  UP            DOWN"
  print "               min/max        min/max"
  print "yield_jes     %.6f/%.6f      %.6f/%.6f" %(unc_yield_jes_up[0],unc_yield_jes_up[-1], unc_yield_jes_down[0], unc_yield_jes_down[-1])
  print "yield_jer     %.6f/%.6f      %.6f/%.6f" %(unc_yield_jer_up[0],unc_yield_jer_up[-1], unc_yield_jer_down[0], unc_yield_jer_down[-1])
  
  print "yield_jms     %.6f/%.6f      %.6f/%.6f" %(unc_yield_jms_up[0],unc_yield_jms_up[-1], unc_yield_jms_down[0], unc_yield_jms_down[-1])
  print "yield_jmr     %.6f/%.6f      %.6f/%.6f" %(unc_yield_jmr_up[0],unc_yield_jmr_up[-1], unc_yield_jmr_down[0], unc_yield_jmr_down[-1])
  
  print "yield_scale     %.6f/%.6f      %.6f/%.6f" %(unc_yield_scale_up[0],unc_yield_scale_up[-1], unc_yield_scale_down[0], unc_yield_scale_down[-1])
  print "yield_res     %.6f/%.6f      %.6f/%.6f" %(unc_yield_res_up[0],unc_yield_res_up[-1], unc_yield_res_down[0], unc_yield_res_down[-1])
  
  print "migration_jes %.6f/%.6f      %.6f/%.6f" %(unc_migration_jes_up[0],unc_migration_jes_up[-1], unc_migration_jes_down[0], unc_migration_jes_down[-1])
  print "migration_jer %.6f/%.6f      %.6f/%.6f" %(unc_migration_jer_up[0],unc_migration_jer_up[-1], unc_migration_jer_down[0], unc_migration_jer_down[-1])
  
  print "migration_jms %.6f/%.6f      %.6f/%.6f" %(unc_migration_jms_up[0],unc_migration_jms_up[-1], unc_migration_jms_down[0], unc_migration_jms_down[-1])
  print "migration_jmr %.6f/%.6f      %.6f/%.6f" %(unc_migration_jmr_up[0],unc_migration_jmr_up[-1], unc_migration_jmr_down[0], unc_migration_jmr_down[-1])
  
  print "migration_scale %.6f/%.6f      %.6f/%.6f" %(unc_migration_scale_up[0],unc_migration_scale_up[-1], unc_migration_scale_down[0], unc_migration_scale_down[-1])
  print "migration_res  %.6f/%.6f      %.6f/%.6f" %(unc_migration_res_up[0],unc_migration_res_up[-1], unc_migration_res_down[0], unc_migration_res_down[-1])
