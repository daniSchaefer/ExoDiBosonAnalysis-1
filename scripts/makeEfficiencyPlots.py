#python do-jes.py -s JES -c VV --signal BulkWW
import xml.etree.ElementTree as ET
import os,commands
import sys
from optparse import OptionParser
import ROOT
from ROOT import *
import math
import multiprocessing
import time
#from numpy import array
from array import array
import CMS_lumi, tdrstyle
#argv = sys.argv
#parser = OptionParser()
#parser.add_option("--doCV", dest="doCV", default=False, action="store_true",help="Produce samples with central value! No scaleUP/DOWN")
#parser.add_option('-s', '--sys',action="store",type="string",dest="sys",default="JES")           #JES JER JMS JMR ALL
#parser.add_option('-c', '--channel',action="store",type="string",dest="channel",default="VV")    #VV qV
#parser.add_option('-S', '--signal',action="store",type="string",dest="signal",default="BulkWW")  #VBulkWW BulkZZ WprimeWZ ZprimeWW QstarQW QstarQZ
#(opts, args) = parser.parse_args(argv)

lumi="36.5 fb^{-1}"

CMS_lumi.lumi_13TeV = ""
CMS_lumi.writeExtraText = 1
CMS_lumi.extraText = "Simulation"
CMS_lumi.lumi_sqrtS = "13 TeV" # used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

iPos = 0
if( iPos==0 ): CMS_lumi.relPosX = 0.12
iPeriod = 4

H_ref = 600; 
W_ref = 800; 
W = W_ref
H  = H_ref
# references for T, B, L, R
T = 0.08*H_ref
B = 0.12*H_ref 
L = 0.12*W_ref
R = 0.04*W_ref


def get_canvas(name):
 canvas = TCanvas(name,name,50,50,W,H)
 canvas.SetFillColor(0)
 canvas.SetBorderMode(0)
 canvas.SetFrameFillStyle(0)
 canvas.SetFrameBorderMode(0)
 canvas.SetLeftMargin( L/W )
 canvas.SetRightMargin( R/W )
 canvas.SetTopMargin( T/H )
 canvas.SetBottomMargin( B/H )
 canvas.SetTickx(0)
 canvas.SetTicky(0)
 return canvas


def addExtraText(signal):
    addInfo = TPaveText(0.12,0.7437063,0.995302,0.9363636,"NDC")
    addInfo.SetFillColor(0)
    addInfo.SetLineColor(0)
    addInfo.SetFillStyle(0)
    addInfo.SetBorderSize(0)
    addInfo.SetTextFont(42)
    addInfo.SetTextSize(0.040)
    addInfo.SetTextAlign(12)

    if signal.find("BulkWW")!=-1:
        text="G_{Bulk} #rightarrow WW"
    if signal.find("BulkZZ")!=-1:
         text="G_{Bulk} #rightarrow ZZ"
    if signal.find("Zprime")!=-1:
         text="Z' #rightarrow WW"
    if signal.find("Wprime")!=-1:
        text="W' #rightarrow WZ"
    if signal.find("QZ")!=-1:    
         text="q* #rightarrow qZ"    
    if signal.find("QW")!=-1:
         text="q* #rightarrow qW"
    addInfo.AddText(text)
    return addInfo


def getPassVtag(infile, category):

    cut = ""

    if category.find("VVHP")!=-1:
        cut =  "jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 105 && jet_puppi_tau2tau1_jet1 <= 0.35 && jet_puppi_tau2tau1_jet2 <= 0.35"

    if category.find("VVLP")!=-1:
        cut =  "jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 105 && ((jet_puppi_tau2tau1_jet1 <= 0.35 && jet_puppi_tau2tau1_jet2 > 0.35 && jet_puppi_tau2tau1_jet2 < 0.75) || (jet_puppi_tau2tau1_jet2 <= 0.35 && jet_puppi_tau2tau1_jet1 > 0.35 && jet_puppi_tau2tau1_jet1 < 0.75))"
    

    if category.find("WWHP")!=-1:
        cut =  "jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 85 && jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 85 && jet_puppi_tau2tau1_jet1 <= 0.35 && jet_puppi_tau2tau1_jet2 <= 0.35"

    if category.find("WWLP")!=-1:
        cut =  "jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 85 && jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 85 &&  ((jet_puppi_tau2tau1_jet1 <= 0.35 && jet_puppi_tau2tau1_jet2 > 0.35 && jet_puppi_tau2tau1_jet2 < 0.75) || (jet_puppi_tau2tau1_jet2 <= 0.35 && jet_puppi_tau2tau1_jet1 > 0.35 && jet_puppi_tau2tau1_jet1 < 0.75))"


    if category.find("WZHP")!=-1:
        cut =  "((jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 85 && jet_puppi_softdrop_jet2 > 85 && jet_puppi_softdrop_jet2 < 105) || (jet_puppi_softdrop_jet1 > 85 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 85)) && jet_puppi_tau2tau1_jet1 <= 0.35 && jet_puppi_tau2tau1_jet2 <= 0.35"
    

    if category.find("WZLP")!=-1:
        cut =  "((jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 85 && jet_puppi_softdrop_jet2 > 85 && jet_puppi_softdrop_jet2 < 105) || (jet_puppi_softdrop_jet1 > 85 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 85)) &&  ((jet_puppi_tau2tau1_jet1 <= 0.35 && jet_puppi_tau2tau1_jet2 > 0.35 && jet_puppi_tau2tau1_jet2 < 0.75) || (jet_puppi_tau2tau1_jet2 <= 0.35 && jet_puppi_tau2tau1_jet1 > 0.35 && jet_puppi_tau2tau1_jet1 < 0.75))"
    

    if category.find("ZZHP")!=-1:
        cut =  "jet_puppi_softdrop_jet1 > 85 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_softdrop_jet2 > 85 && jet_puppi_softdrop_jet2 < 105 && jet_puppi_tau2tau1_jet1 <= 0.35 && jet_puppi_tau2tau1_jet2 <= 0.35"
    

    if category.find("ZZLP")!=-1:
        cut =  "jet_puppi_softdrop_jet1 > 85 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_softdrop_jet2 > 85 && jet_puppi_softdrop_jet2 < 105 && ((jet_puppi_tau2tau1_jet1 <= 0.35 && jet_puppi_tau2tau1_jet2 > 0.35 && jet_puppi_tau2tau1_jet2 < 0.75) || (jet_puppi_tau2tau1_jet2 <= 0.35 && jet_puppi_tau2tau1_jet1 > 0.35 && jet_puppi_tau2tau1_jet1 < 0.75))"
        
        
    if category.find("qVHP")!=-1:
       cut =  "(jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_tau2tau1_jet1 <= 0.35) || (jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 105 && jet_puppi_tau2tau1_jet2 <= 0.35)"

    if category.find("qVLP")!=-1:
        cut =  "(jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_tau2tau1_jet1 > 0.35 && jet_puppi_tau2tau1_jet1 < 0.75) || (jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 105 && jet_puppi_tau2tau1_jet2 > 0.35 && jet_puppi_tau2tau1_jet2 < 0.75)"
    

    if category.find("qWHP")!=-1:
        cut =  "(jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 85 && jet_puppi_tau2tau1_jet1 <= 0.35) || (jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 85 && jet_puppi_tau2tau1_jet2 <= 0.35)"

    if category.find("qWLP")!=-1:
        cut =  "(jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 85 && jet_puppi_tau2tau1_jet1 > 0.35 && jet_puppi_tau2tau1_jet1 < 0.75) || (jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 85 && jet_puppi_tau2tau1_jet2 > 0.35 && jet_puppi_tau2tau1_jet2 < 0.75)"


    if category.find("qZHP")!=-1:
        cut = "(jet_puppi_softdrop_jet1 > 85 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_tau2tau1_jet1 <= 0.35) || (jet_puppi_softdrop_jet2 > 85 && jet_puppi_softdrop_jet2 < 105 && jet_puppi_tau2tau1_jet2 <= 0.35)"
    

    if category.find("qZLP")!=-1:
         cut = "(jet_puppi_softdrop_jet1 > 85 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_tau2tau1_jet1 > 0.35 && jet_puppi_tau2tau1_jet1 < 0.75) || (jet_puppi_softdrop_jet2 > 85 && jet_puppi_softdrop_jet2 < 105 && jet_puppi_tau2tau1_jet2 > 0.35 && jet_puppi_tau2tau1_jet2 < 0.75)"
    
    #print cut
    #rint "######## infile = %s #########" %infile
    tfile = ROOT.TFile.Open(infile,'READ')
    tree = tfile.Get("tree")
    eff = float(tree.GetEntries(cut))
    #print "efficiency = %.3f" %(eff)
    tfile.Close()
    tfile.Delete()
    
    return eff



def getPassPresel(infile):
    #print "######## open file = %s #########" %infile
    tfile = ROOT.TFile.Open(infile,'READ')
    hm = tfile.Get('Mjj')
    #num = hm.Integral()
    num = hm.GetEntries()
    return num

def getAll(infile):
    #tfile = ROOT.TFile.Open(infile,'READ')
    #hm = tfile.Get('gen_COS_Theta1')
    #num = hm.Integral()
    num = 30000.
    #if infile.find("BulkWW")!=-1 or infile.find("Zprime")!=-1:
        #return num*0.66*0.66
    #if infile.find("QW")!=-1:
        #return num*0.66
    #if infile.find("QZ")!=-1:
        #return num*0.6991
    #return num
    if infile.find("BulkZZ")!=-1:
        return num/(0.6991*0.6991)
    if infile.find("WprimeWZ")!=-1:
        return num/(0.66*0.6991)
    return num
 
 
def getEfficiency(model,mass,channel):
    infile = '/storage/jbod/dschaefer/AnalysisOutput/80X/SignalMC/Summer16/ExoDiBosonAnalysis.'+model+'_13TeV_'+str(mass)+'GeV.CV.root'
    if model.find("Qstar")!=-1:
        infile = '/storage/jbod/dschaefer/AnalysisOutput/80X/SignalMC/Summer16/ExoDiBosonAnalysis.'+model+'_13TeV_'+str(mass)+'GeV.qV.root'
    num = getPassVtag(infile,channel)
    denum = getPassPresel(infile)
    #print num
    #print denum
    if denum!=0:
        eff = num/float(denum)
        #print "eff %f" %eff
        return num/float(denum)
    else :
       print "events passing preselections are 0!"
       return 0
   
   
def getAcceptance(model,mass):
    infile = '/storage/jbod/dschaefer/AnalysisOutput/80X/SignalMC/Summer16/ExoDiBosonAnalysis.'+model+'_13TeV_'+str(mass)+'GeV.CV.root'
    if model.find("Qstar")!=-1:
        infile = '/storage/jbod/dschaefer/AnalysisOutput/80X/SignalMC/Summer16/ExoDiBosonAnalysis.'+model+'_13TeV_'+str(mass)+'GeV.qV.root'
    
    num = getPassPresel(infile)
    denum = getAll(infile)
    if denum!=0:
        return num/denum
    else :
       print "events passing preselections are 0!"
       return 0
   
   

if __name__=="__main__":
    signals = ["BulkWW","BulkZZ","ZprimeWW","WprimeWZ"]
    channels = ["WWHP","WZHP","ZZHP","WWLP","WZLP","ZZLP"]
    linestyle = [2,3,4,6,10,1]
    
    #signals = ["QstarQW","QstarQZ"]
    #channels = ["qWHP","qZHP","qWLP","qZLP"]
    #linestyle = [2,1,6,10,1]
    reg = "VV"
    #Bins = [1100,1300,1500,1700,1900,2250,2750,3250,3750,4250,4750]
    color = [kRed,kGreen,kBlue,kOrange,kPink]
    
    
    legChan = TLegend(0.2,0.7,0.48,0.9)
    legChan.SetTextSize(0.033)
    legChan.SetLineColor(0)
    legChan.SetShadowColor(0)
    legChan.SetLineStyle(1)
    legChan.SetLineWidth(1)
    legChan.SetFillColor(0)
    legChan.SetFillStyle(0)
    legChan.SetMargin(0.35)
    ls =0
    t1 = []
    for c in channels:
        tmp = TGraph(1)
        tmp.SetLineWidth(2)
        tmp.SetLineColor(kBlack)
        t1.append(tmp)
    ls =0
    for t in t1:
        t.SetLineStyle(linestyle[ls])
        legChan.AddEntry(t,channels[ls],"l")
        ls+=1
        
        
    legSig = TLegend(0.7,0.7,0.9,0.9)
    legSig.SetTextSize(0.033)
    legSig.SetLineColor(0)
    legSig.SetShadowColor(0)
    legSig.SetLineStyle(1)
    legSig.SetLineWidth(1)
    legSig.SetFillColor(0)
    legSig.SetFillStyle(0)
    legSig.SetMargin(0.35)
    ls =0
    t2 = []
    for s in signals:
        tmp = TGraph(1)
        tmp.SetLineWidth(2)
        tmp.SetLineStyle(1)
        t2.append(tmp)
    ls =0
    text =""
    for t in t2:
        t.SetLineColor(color[ls])
        if signals[ls].find("BulkWW")!=-1:
            text="G_{Bulk} #rightarrow WW"
        if signals[ls].find("BulkZZ")!=-1:
            text="G_{Bulk} #rightarrow ZZ"
        if signals[ls].find("Zprime")!=-1:
            text="Z' #rightarrow WW"
        if signals[ls].find("Wprime")!=-1:
            text="W' #rightarrow WZ"
        if signals[ls].find("QZ")!=-1:    
            text="q* #rightarrow qZ"    
        if signals[ls].find("QW")!=-1:
            text="q* #rightarrow qW"
        
        legSig.AddEntry(t,text,"l")
        ls+=1    
        
    
    #####################################################################################################
    ################ efficiency not stacked #############################################################
    
    #ls =0
    #c = get_canvas("efficiency")
    #graphsw =[]
    #for channel in channels:
        #masses = [1200,1400,1600,1800,2000,2500,3000,3500,4000,4500]
        ##hist = TH1F("hist"+signal+channel,"hist"+signal+channel,len(Bins),array('f',Bins))
        #graphs=[]
        #for signal in signals:
            #if signal.find("Qstar")!=-1:
                #reg="qV"
            #else:
                #reg="VV"
            #if signal.find("BulkZZ")!=-1:
                #masses = [1200,1400,1600,1800,2000,2500,3000,3500,4000]
            #else:
                #masses = [1200,1400,1600,1800,2000,2500,3000,3500,4000,4500]
            #if signal.find("Qstar")!=-1:
                #masses = [1200,1400,1600,1800,2000,2500,3000,4500,6000]
            ##print array('f',Bins)
            #g = TGraph(1)
            #for i in range(0,len( masses)):
                #e = getEfficiency(signal,masses[i],channel)
                #print signal+" channel "+channel+" eff "+str(e)
                #g.SetPoint(i,masses[i],getEfficiency(signal,masses[i],channel)) 
            #graphs.append(g)
        #graphsw.append(graphs)        
        
        
        
    #graphsw[0][0].SetMaximum(0.35)
    #if reg.find("qV")!=-1:
       #graphsw[0][0].SetMaximum(0.5) 
    #graphsw[0][0].SetTitle("")
    #graphsw[0][0].SetMinimum(0)
    #graphsw[0][0].GetYaxis().SetTitleSize(0.06)
    #graphsw[0][0].GetYaxis().SetTitleOffset(0.95)
    #graphsw[0][0].GetXaxis().SetLabelSize(0.05)
    #graphsw[0][0].GetXaxis().SetTitleSize(0.06)
    #graphsw[0][0].GetXaxis().SetLabelSize(0.05)
    #graphsw[0][0].GetXaxis().SetTitle("Resonance mass (GeV)")
    #graphsw[0][0].GetYaxis().SetTitle("Tagging efficiency")
    #graphsw[0][0].SetLineColor(color[0])
    #graphsw[0][0].SetLineWidth(2)
    #graphsw[0][0].SetLineStyle(linestyle[0])
    #graphsw[0][0].Draw("ALP")
        
    #print len(graphsw)
    #for i in range(0,len(graphsw)):
        #for j in range(0,len(graphsw[i])):
            #if j==0 and i==0:
                #continue
            #graphsw[i][j].SetLineColor(color[j])
            #graphsw[i][j].SetLineWidth(2)
            #graphsw[i][j].SetLineStyle(linestyle[i])
            #graphsw[i][j].Draw("LPsame")
        
    #print "draw graphs"
    #c.Update()
    #legChan.Draw("same")
    #legSig.Draw("same")
    #CMS_lumi.CMS_lumi(c, iPeriod, iPos)
    #c.SaveAs("efficiency"+reg+".pdf")
    #time.sleep(10)
    
    
    ######################################################################################################
    ################# efficiency     stacked #############################################################
    
    #slegChan = TLegend(0.13,0.65,0.48,0.9)
    #slegChan.SetTextSize(0.033)
    #slegChan.SetLineColor(0)
    #slegChan.SetShadowColor(0)
    #slegChan.SetLineStyle(1)
    #slegChan.SetLineWidth(1)
    #slegChan.SetFillColor(0)
    #slegChan.SetFillStyle(0)
    #slegChan.SetMargin(0.35)
    #ls =0
    #t1 = []
    #for c in channels:
        #tmp = TGraph(1)
        #tmp.SetLineWidth(2)
        #tmp.SetLineColor(kBlack)
        #t1.append(tmp)
    #ls =0
    #for t in t1:
        #t.SetLineStyle(linestyle[ls])
        #text=channels[ls]
        #for i in range(0,ls):
            #text+="+"+channels[i]
        #slegChan.AddEntry(t,text,"l")
        #ls+=1
    
    
    #ls =0
    #canvas = get_canvas("efficiency_stacked")
    #graphsw =[]
    #for signal in signals:
        #masses = [1200,1400]#,1600,1800,2000,2500,3000,3500,4000,4500]
        ##hist = TH1F("hist"+signal+channel,"hist"+signal+channel,len(Bins),array('f',Bins))
        #graphs=[]
        #counter =0
        #for channel in channels:
            #if signal.find("BulkZZ")!=-1:
                #masses = [1200,1400,1600,1800,2000,2500,3000,3500,4000]
            #else:
                #masses = [1200,1400,1600,1800,2000,2500,3000,3500,4000,4500]
            #if signal.find("Qstar")!=-1:
                #masses = [1200,1400,1600,1800,2000,2500,3000,4500,6000]#print array('f',Bins)
            #g = TGraph(1)
            #for i in range(0,len( masses)):
                #eff = getEfficiency(signal,masses[i],channel)
                #print "channel "+channel+" eff "+str(eff)
                #for c in range(0,counter):
                    #e = getEfficiency(signal,masses[i],channels[c]) 
                    #eff+= e
                    #print "plus  channel "+channels[c]+" eff "+str(e)
                #print "eff %s"%eff
                #g.SetPoint(i,masses[i],eff) 
            #graphs.append(g)
            #counter+=1
        #graphsw.append(graphs)        
        
        
        
    #graphsw[0][0].SetMaximum(1.)
    #if reg.find("qV")!=-1:
       #graphsw[0][0].SetMaximum(1.3) 
    #graphsw[0][0].SetTitle("")
    #graphsw[0][0].SetMinimum(0)
    #graphsw[0][0].GetYaxis().SetTitleSize(0.06)
    #graphsw[0][0].GetYaxis().SetTitleOffset(0.95)
    #graphsw[0][0].GetXaxis().SetLabelSize(0.05)
    #graphsw[0][0].GetXaxis().SetTitleSize(0.06)
    #graphsw[0][0].GetXaxis().SetLabelSize(0.05)
    #graphsw[0][0].GetXaxis().SetTitle("Resonance mass (GeV)")
    #graphsw[0][0].GetYaxis().SetTitle("Tagging efficiency")
    #graphsw[0][0].SetLineColor(color[0])
    #graphsw[0][0].SetLineWidth(2)
    #graphsw[0][0].SetLineStyle(linestyle[0])
    #graphsw[0][0].Draw("ALP")
        
    #print len(graphsw)
    #for i in range(0,len(graphsw)):
        #print len(graphsw[i])
        #for j in range(0,len(graphsw[i])):
            #if i==0 and j==0:
                #continue
            #graphsw[i][j].SetLineColor(color[i])
            #graphsw[i][j].SetLineWidth(2)
            #graphsw[i][j].SetLineStyle(linestyle[j])
            #graphsw[i][j].Draw("LPsame")
        
    #print "draw graphs"
    #canvas.Update()
    #slegChan.Draw("same")
    #legSig.Draw("same")
    #CMS_lumi.CMS_lumi(canvas, iPeriod, iPos)
    #canvas.SaveAs("efficiency_stacked"+reg+".pdf")
    #time.sleep(10)
    
    
######################## acceptance ###########################################################################
    #signals = ["QstarQW","QstarQZ","BulkWW","BulkZZ","ZprimeWW","WprimeWZ"]
    #color = [kRed,kGreen,kBlue,kOrange,kMagenta,kTeal]
    #linestyle = [1]
    
    
    #legSig = TLegend(0.7,0.7,0.9,0.9)
    #legSig.SetTextSize(0.033)
    #legSig.SetLineColor(0)
    #legSig.SetShadowColor(0)
    #legSig.SetLineStyle(1)
    #legSig.SetLineWidth(1)
    #legSig.SetFillColor(0)
    #legSig.SetFillStyle(0)
    #legSig.SetMargin(0.35)
    #ls =0
    #t2 = []
    #for s in signals:
        #tmp = TGraph(1)
        #tmp.SetLineWidth(2)
        #tmp.SetLineStyle(1)
        #t2.append(tmp)
    #ls =0
    #text =""
    #for t in t2:
        #t.SetLineColor(color[ls])
        #if signals[ls].find("BulkWW")!=-1:
            #text="G_{Bulk} #rightarrow WW"
        #if signals[ls].find("BulkZZ")!=-1:
            #text="G_{Bulk} #rightarrow ZZ"
        #if signals[ls].find("Zprime")!=-1:
            #text="Z' #rightarrow WW"
        #if signals[ls].find("Wprime")!=-1:
            #text="W' #rightarrow WZ"
        #if signals[ls].find("QZ")!=-1:    
            #text="q* #rightarrow qZ"    
        #if signals[ls].find("QW")!=-1:
            #text="q* #rightarrow qW"
        
        #legSig.AddEntry(t,text,"l")
        #ls+=1    
        


    #ls =0
    #c = get_canvas("acceptance")
    #masses = [1200,1400,1600,1800,2000,2500,3000,3500,4000,4500]
        ##hist = TH1F("hist"+signal+channel,"hist"+signal+channel,len(Bins),array('f',Bins))
    #graphs=[]
    #for signal in signals:
            #if signal.find("Qstar")!=-1:
                #reg="qV"
            #else:
                #reg="VV"
            #if signal.find("BulkZZ")!=-1:
                #masses = [1200,1400,1600,1800,2000,2500,3000,3500,4000]
            #else:
                #masses = [1200,1400,1600,1800,2000,2500,3000,3500,4000,4500]
            #if signal.find("Qstar")!=-1:
                #masses = [1200,1400,1600,1800,2000,2500,3000,4500,6000]
            ##print array('f',Bins)
            #g = TGraph(1)
            #for i in range(0,len( masses)):
                #e = getAcceptance(signal,masses[i])
                ##print signal+" channel "+channel+" eff "+str(e)
                #g.SetPoint(i,masses[i],e) 
            #graphs.append(g)
                
        
        
        
    #graphs[0].SetMaximum(0.5)
    #graphs[0].SetTitle("")
    #graphs[0].SetMinimum(0.2)
    #graphs[0].GetYaxis().SetTitleSize(0.06)
    #graphs[0].GetYaxis().SetTitleOffset(0.95)
    #graphs[0].GetXaxis().SetLabelSize(0.05)
    #graphs[0].GetXaxis().SetTitleSize(0.06)
    #graphs[0].GetXaxis().SetLabelSize(0.05)
    #graphs[0].GetXaxis().SetTitle("Resonance mass (GeV)")
    #graphs[0].GetYaxis().SetTitle("Acceptance")
    #graphs[0].SetLineColor(color[0])
    #graphs[0].SetLineWidth(2)
    #graphs[0].SetLineStyle(linestyle[0])
    #graphs[0].Draw("ALP")
        
    #print len(graphs)
    #for i in range(0,len(graphs)):

            #graphs[i].SetLineColor(color[i])
            #graphs[i].SetLineWidth(2)
            ##graphs[i].SetLineStyle(linestyle[i])
            #graphs[i].Draw("LPsame")
        
    #print "draw graphs"
    #c.Update()
    ##legChan.Draw("same")
    #legSig.Draw("same")
    #CMS_lumi.CMS_lumi(c, iPeriod, iPos)
    #c.SaveAs("acceptance"+reg+".pdf")
    #time.sleep(10)
    
######################## efficiency per signal (one plot for each signal)  ###########################################################################
    signals = ["BulkWW","BulkZZ","ZprimeWW","WprimeWZ","QstarQW","QstarQZ"]
    linestyle = [2,3,4,6,10,1]
    color = [kRed,kGreen,kBlue,kOrange,kMagenta,kTeal]
    channels =[]
    
    #signals = ["QstarQW","QstarQZ"]
    #channels = ["qWHP","qZHP","qWLP","qZLP"]
    #linestyle = [2,1,6,10,1]
    reg = "VV"
    Bins =[]


    
    graphsw =[]
    for signal in signals:
        if signal.find("WW")!=-1:
            channels = ["WWLP","WWHP","WZLP","WZHP","ZZLP","ZZHP"]
        if signal.find("WZ")!=-1:
            #channels = ["WZLP","WZHP","WWLP","WWHP","ZZLP","ZZHP"]
            channels = ["WWLP","WWHP","WZLP","WZHP","ZZLP","ZZHP"]
        if signal.find("ZZ")!=-1:
            #channels = ["ZZLP","WZLP","ZZHP","WZHP","WWLP","WWHP"]
            channels = ["WWLP","WWHP","WZLP","WZHP","ZZLP","ZZHP"]
        if signal.find("QW")!=-1:
            channels=["qWHP","qWLP","qZLP","qZHP"]
        if signal.find("QZ")!=-1:
           # channels=["qZLP","qZHP","qWLP","qWHP"]
           channels=["qWHP","qWLP","qZLP","qZHP"]
        ls =0
        masses = [1200,1400,1600,1800,2000,2500,3000,3500,4000,4500]
        #graphs=[]
        hstack = THStack(signal,signal)
        histlist=[]
        leg = TLegend(0.7,0.7,0.9,0.9)
        leg.SetTextSize(0.033)
        leg.SetLineColor(0)
        leg.SetShadowColor(0)
        leg.SetLineStyle(1)
        leg.SetLineWidth(1)
        leg.SetFillColor(0)
        leg.SetFillStyle(0)
        leg.SetMargin(0.35)
        for channel in channels:
            if signal.find("Qstar")!=-1:
                reg="qV"
            else:
                reg="VV"
            if signal.find("BulkZZ")!=-1:
                masses = [1200,1400,1600,1800,2000,2500,3000,3500,4000]
            else:
                masses = [1200,1400,1600,1800,2000,2500,3000,3500,4000,4500]
            if signal.find("Qstar")!=-1:
                masses = [1200,1400,1600,1800,2000,2500,3000,4500,6000]
            
            hist = TH1D("hist"+signal+channel,"hist"+signal+channel,34,1200,4600)
            print hist
            e=0
            sf = 0.99
            if reg.find("VV")!=-1:
                sf = sf*sf
            if channel.find("LP")!=-1:
                sf = 1.03
                if reg.find("VV")!=-1:
                    sf = sf*sf
            for i in range(0,34):
                mass = 1200+i*100
                if mass in masses:
                    print "found mass "
                    e = getEfficiency(signal,mass,channel)
                    print signal+" channel "+channel+" eff "+str(e)+ " mass "+str(mass)
                    hist.Fill(mass,e)
                else:
                    print signal+" channel "+channel+" eff "+str(e)+ " mass "+str(mass)
                    hist.Fill(mass,e)
            hist.SetTitleOffset(1.4,"y")
            hist.SetTitleOffset(1.2,"x")
            hist.SetTitleOffset(1.8,"z")
            hist.GetXaxis().SetTitle("Resonance mass (GeV)")
            hist.GetYaxis().SetTitle("Tagging efficiency")
            hist.GetYaxis().CenterTitle()
            hist.SetMaximum(1.0)
            hist.SetMinimum(0.0)
            hist.SetStats(0)
            hist.SetLineColor(color[ls]+2)
            hist.SetFillColorAlpha(color[ls]-3,0.1)
            hist.Scale(sf)
            histlist.append(hist)
            ls+=1
        print histlist
        #histlist[0].Draw("HIST")
        for i in range(0,len(channels)):
             index = len(channels)-i-1
             leg.AddEntry(histlist[index],channels[index] ,"f") 
        for i in range(0,len(histlist)):
            hstack.Add(histlist[i])
        hstack.SetMaximum(1.)
        hstack.SetTitle("")
        #print hstack.GetXaxis()
        
        
        c = get_canvas("efficiency histos stacked "+signal)
        hstack.Draw("HIST")
        hstack.GetXaxis().SetTitle("Resonance mass (GeV)")
        hstack.GetYaxis().SetTitle("Tagging efficiency")
        c.Update()
        leg.Draw("same")
        addText = addExtraText(signal)
        addText.Draw("same")
        CMS_lumi.CMS_lumi(c, iPeriod, iPos)
        c.SaveAs("efficiency"+signal+".pdf")
        #graphsw.append(hstack)        
 
    time.sleep(10)
