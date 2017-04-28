# to get PU JSON see: https://twiki.cern.ch/twiki/bin/view/CMS/PileupJSONFileforData


import ROOT
from ROOT import *
import time
import CMS_lumi, tdrstyle
#import PhysicsTools.Utilities as PT
from optparse import OptionParser
import os

nPUVtx_data = ROOT.TH1F()

def get_canvas(cname,lumi):

   CMS_lumi.lumi_13TeV = "%.1f pb^{-1},#sqrt{s} = " %(lumi)
   CMS_lumi.writeExtraText = 1
   CMS_lumi.extraText = "Preliminary"

   iPos = 0
   if( iPos==0 ): CMS_lumi.relPosX = 0.15

   H_ref = 600; 
   W_ref = 800; 
   W = W_ref
   H  = H_ref

   T = 0.08*H_ref
   B = 0.12*H_ref 
   L = 0.12*W_ref
   R = 0.06*W_ref

   canvas = ROOT.TCanvas(cname,cname,W,H)
   canvas.SetFillColor(0)
   canvas.SetBorderMode(0)
   canvas.SetFrameFillStyle(0)
   canvas.SetFrameBorderMode(0)
   canvas.SetLeftMargin( L/W+0.01 )
   canvas.SetRightMargin( R/W )
   canvas.SetTopMargin( T/H )
   canvas.SetBottomMargin( B/H+0.03 )
   canvas.SetTickx()
   canvas.SetTicky()
   
   return canvas

def getPadUp(c):
   c.cd()
   H_ref = 600; 
   W_ref = 800; 
   W = W_ref
   H  = H_ref

   T = 0.08*H_ref
   B = 0.12*H_ref 
   L = 0.12*W_ref
   R = 0.06*W_ref
   # Upper plot will be in pad1
   #pad1 = ROOT.TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
   #pad1 = c.GetPad(1)
   pad1 = ROOT.TPad("pad","pad",0.01,0.26,0.99,0.98)
   pad1.SetLogy()
   pad1.SetBottomMargin(0.025)
   pad1.Draw();            #Draw the upper pad: pad1
   pad1.SetFillColor(0)
   pad1.SetBorderMode(0)
   pad1.SetFrameFillStyle(0)
   pad1.SetFrameBorderMode(0)
   pad1.SetLeftMargin( L/W+0.01 )
   pad1.SetRightMargin( R/W )
   pad1.SetTopMargin( T/H )
   #canvas.SetBottomMargin( B/H+0.03 )
   pad1.cd();             # pad1 becomes the current pad
   
   return pad1
   
   
def getPadDown(c):   
   c.cd()   
   H_ref = 600; 
   W_ref = 800; 
   W = W_ref
   H  = H_ref

   T = 0.08*H_ref   
   B = 0.12*H_ref    
   L = 0.12*W_ref   
   R = 0.06*W_ref   


   pad1 = ROOT.TPad("pad","pad",0.01,0.02,0.99,0.27)  
   #pad1.SetLogy()
   pad1.SetBottomMargin(0.025)   
   pad1.Draw();            #Draw the upper pad: pad1   
   pad1.SetFillColor(0)   
   pad1.SetBorderMode(0)   
   pad1.SetFrameFillStyle(0)   
   pad1.SetFrameBorderMode(0)   
   pad1.SetLeftMargin( L/W+0.01 )   
   pad1.SetRightMargin( R/W )   
   #pad1.SetTopMargin( T/H )
   pad1.SetBottomMargin(0.35)
   pad1.SetGridx()
   pad1.SetGridy()
   #canvas.SetBottomMargin( B/H+0.03 )   
   pad1.cd();             # pad1 becomes the current pad   
   return pad1


def setPullStyle(h_data_MC):
    h_data_MC.SetTitle("")
    h_data_MC.SetXTitle("number of Vertices")
    h_data_MC.SetYTitle("#frac{Data}{MC}")
    h_data_MC.GetYaxis().SetTitleSize(0.15)
    h_data_MC.GetYaxis().SetTitleOffset(0.350)
    h_data_MC.GetYaxis().SetLabelSize(0.09)
    h_data_MC.GetXaxis().SetTitleSize(0.18)
    h_data_MC.GetXaxis().SetTitleOffset(0.90)
    h_data_MC.GetXaxis().SetLabelSize(0.12)
    h_data_MC.GetXaxis().SetNdivisions(605)
    h_data_MC.GetYaxis().SetNdivisions(504)
    h_data_MC.GetYaxis().CenterTitle()
    h_data_MC.SetMaximum(1.5)
    h_data_MC.SetMinimum(0.5)
    h_data_MC.SetMarkerStyle(20)
    h_data_MC.SetMarkerColor(kBlue)
    return 1

   




        #/mnt/t3nfs01/data01/shome/dschafer/ExoDiBosonAnalysis/results/PU/MCBackgroundPU.root
        #/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/80X/PU/ExoDiBosonAnalysis.bkg.VV.root
        #~/AnalysisOutput/80X/SignalMC/Summer16/ExoDiBosonAnalysis.BulkWW_13TeV_2500GeV.VV.root
parser = OptionParser()
parser.add_option('--data', '--data',action="store",type="string",dest="data",default="DataPUDistribution.root")
parser.add_option('--mc', '--mc',action="store",type="string",dest="mc",default="/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/80X/Bkg/QCD_Spring16_Ptbinned_pythia8.root")
parser.add_option('--rebin', '--rebin',action="store",type="int",dest="rebin",default=2)
parser.add_option('--outdir',action='store',type='string',dest='outdir',default='/mnt/t3nfs01/data01/shome/dschafer/ExoDiBosonAnalysis/results/PU/')
(options, args) = parser.parse_args()

tdrstyle.setTDRStyle()

rebin = options.rebin
directory = '../../AnalysisOutput/80X/'
#fmc = TFile.Open(directory+options.mc,'READ')
#pumc   = ROOT.TH1F(fmc.Get('nVertices'))
#pumc.SetName('pumc')

JSONfullpromtreco = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON_NoL1T.txt'
PUJSONfullpromtreco= '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt'
outfilename = options.outdir+options.data

lumi = 35.9 #fb^-1


if __name__=='__main__':
    xsMinBias     = 69200
    xsMinBiasdown = 66016.8
    xsMinBiasup   = 72383.2
    command ='pileupCalc.py -i '+JSONfullpromtreco+' --inputLumiJSON '+PUJSONfullpromtreco+' --calcMode true --minBiasXsec '+str(xsMinBiasdown)+' --maxPileupBin 70 --numPileupBins 70 '+outfilename
    print command
    #pileupCalc.py -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON_NoL1T.txt --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt --calcMode true --minBiasXsec 69200 --maxPileupBin 50 --numPileupBins 50 DataPUDistribution_50Bins.root
    #os.system(command)
    mc  = options.mc
    mc = "/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/80X/Bkg/QCD_Spring16_Ptbinned_pythia8_VVdijet_SR.root"
    
    rebin = options.rebin
    directory = '../../AnalysisOutput/80X/'
    fmc = TFile.Open(mc,'READ')
    pumc   = ROOT.TH1F(fmc.Get('nPUVtxTrue'))
    pumc.SetName('pumc')
    fdata = TFile.Open(outfilename,'READ')
    pudata = fdata.Get('pileup')
    pudata.SetName('pudata')
    
    
    
    #c = TCanvas("ct","ct",400,400)
    #pumc.Draw()
    
    #print "MC PU distribution : "
    #for w in range(1,70+1):
        #print str(pumc.GetBinContent(w)/pumc.Integral())+","
    
    #l = ROOT.TLegend(0.5574713,0.729021,0.7571839,0.8653846,"","NDC")
    #l.SetLineWidth(2)
    #l.SetBorderSize(0)
    #l.SetFillColor(0)
    #l.SetTextFont(42)
    #l.SetTextSize(0.035)
    #l.SetTextAlign(12)
        
    #pumc.SetLineColor(kRed)
    #pudata.SetLineColor(kBlack)
    #pudata.SetMarkerStyle(20)
    #pudata.SetLineStyle(2)
    #pudata.GetXaxis().SetTitle('Number of Vertices')
    #pudata.GetYaxis().SetTitle('Normalized')
    #pudata.GetYaxis().SetTitleOffset(1.1)
    #pudata.GetYaxis().SetNdivisions(505)
    #pudata.SetMaximum(0.3)
    #l.AddEntry(pudata,'Run 2016 all promtreco','PL')
    #l.AddEntry(pumc,'QCD MC','L')
    
    #pudata.Rebin(rebin)
    #pumc.Rebin(rebin)
    #scaleData = 1./pudata.Integral()
    #pudata.Scale(scaleData)
    #pumc.Scale(1./pumc.Integral())
    #canv = get_canvas('c',lumi)
    #canv.cd()
    #pudata.Draw('PC')
    #pumc.Draw('same')
    #l.Draw()

    #CMS_lumi.CMS_lumi(canv, 4, 0)	
    #canv.cd()
    #canv.Update()
    #canv.RedrawAxis()
    #frame = canv.GetFrame()
    #frame.Draw()
    #canv.cd()
    #canv.Update()   
    ##canv.SaveAs('nVertices.pdf','pdf')
    
    #hweights = ROOT.TH1F('puweights','puweights',pudata.GetNbinsX(),pudata.GetXaxis().GetXmin(),pudata.GetXaxis().GetXmax())
    #for b in range(1,pudata.GetNbinsX()+1):
        #if pumc.GetBinContent(b) !=0:
            #hweights.SetBinContent(b,pudata.GetBinContent(b)/pumc.GetBinContent(b))
      ##print "%.2f" %(pudata.GetBinContent(b)/pumc.GetBinContent(b))
        #else: hweights.SetBinContent(b,0.) 

    #c = get_canvas('c2',1.)
    #c.cd()
    #hweights.GetXaxis().SetTitle('Number of Vertices')
    #hweights.GetYaxis().SetTitle('PU weight')
    #hweights.GetYaxis().SetTitleOffset(0.9)
    #hweights.SetFillColor(kViolet+8)
    #hweights.SetLineColor(kBlack)
    #hweights.SetLineWidth(2)
    #hweights.SetFillStyle(3001)
    #hweights.Draw('hist')
    #c.Update()   
    #c.SaveAs(options.outdir+'puweights.png','png')
    #hweights.SaveAs(options.outdir+'puweights.root')
    
    #print "weights :"
    #for i in range(1,hweights.GetNbinsX()+1):
        #print hweights.GetBinContent(i)
    ##ctest = get_canvas("ctext",1.)
    ##ctest.cd()
    ##pudata.Draw("PC")
    ##for b in range(1,pumc.GetNbinsX()+1):
    ##   pumc.SetBinContent(b,pumc.GetBinContent(b)*hweights.GetBinContent(b))
    #pumc.Draw("Same")
    
    #print pumc.GetNbinsX()
    
    ##time.sleep(10)

# ==============================================================================================================================
#=============== test PU weights in MC Distribution ============================================================================
#===============================================================================================================================
    #qcdSample = "/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/80X/Bkg/Summer16/QCD_pythia8_VVdijet_SR.root"
    #qcdSample = "/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/80X/Bkg/QCD_Spring16_Ptbinned_pythia8.root"
    
    testReweightingMC_py = "/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/80X/Bkg/QCD_Spring16_Ptbinned_pythia8_VVdijet_SR.root"
    testReweightingSignalMC = '/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/80X/PU/ExoDiBosonAnalysis.BulkZZ_13TeV_1200GeV.VV.root'
    testReweightingMC_mapy  = '/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/80X/Bkg/QCD_Spring16_madgraph_pythia8_VVdijet.root'
    #testReweightingMCFall15 = "/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/80X/Bkg/QCD_Spring16_Ptbinned_pythia8.root"
    #testReweightingData = "/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/80X/PU/DataPUdistribution_nVertices.root"
    testReweightingData = "/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/80X/Data/PU/testPU_36460ifb_new.root"
    
    out = '/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/figures/controlplots/'
    
    f_py   = TFile.Open(testReweightingMC_py,'READ')
    f_mapy = TFile.Open(testReweightingMC_mapy,"READ")
    f_sig  = TFile.Open(testReweightingSignalMC,'READ')
    f_data = TFile.Open(testReweightingData,'READ')
    
    
    nPUVtx_py              = f_py.Get('nPUVtx')
    nPUVtxTrue_py          = f_py.Get('nPUVtxTrue')
    nPUVtxTrue_rew_py      = f_py.Get('nPUVtxTrue_rew')
    nPUVtx_rew_py          = f_py.Get('nPUVtx_rew')
    nPUVtx_afterPresel_py  = f_py.Get('nVertices')
    
    nPUVtx_mapy              = f_mapy.Get('nPUVtx')
    nPUVtxTrue_mapy          = f_mapy.Get('nPUVtxTrue')
    nPUVtxTrue_rew_mapy      = f_mapy.Get('nPUVtxTrue_rew')
    nPUVtx_rew_mapy          = f_mapy.Get('nPUVtx_rew')
    nPUVtx_afterPresel_mapy  = f_mapy.Get('nVertices')
    
    nPUVtx_sig              = f_sig.Get('nPUVtx')
    nPUVtxTrue_sig          = f_sig.Get('nPUVtxTrue')
    nPUVtxTrue_rew_sig      = f_sig.Get('nPUVtxTrue_rew')
    nPUVtx_rew_sig          = f_sig.Get('nPUVtx_rew')
    nPUVtx_afterPresel_sig  = f_sig.Get('nVertices')
    
    nPUVtx_data              = f_data.Get('nPUVtx')
    nPUVtxTrue_data          = fdata.Get('pileup')
    nPUVtxTrue_rew_data      = f_data.Get('nPUVtxTrue_rew')
    nPUVtx_rew_data          = f_data.Get('nPUVtx_rew')
    nPUVtx_afterPresel_data  = f_data.Get('nVertices')
    
    
    
    lumi_data = 36460.
    
    nPUVtx_py              .Rebin(rebin)
    nPUVtxTrue_py          .Rebin(rebin)
    nPUVtxTrue_rew_py      .Rebin(rebin)
    nPUVtx_rew_py          .Rebin(rebin)
    nPUVtx_afterPresel_py  .Rebin(rebin)
                           
    nPUVtx_mapy            .Rebin(rebin)
    nPUVtxTrue_mapy        .Rebin(rebin)
    nPUVtxTrue_rew_mapy    .Rebin(rebin)
    nPUVtx_rew_mapy        .Rebin(rebin)
    nPUVtx_afterPresel_mapy.Rebin(rebin)
                         
    nPUVtx_sig             .Rebin(rebin)
    nPUVtxTrue_sig         .Rebin(rebin)
    nPUVtxTrue_rew_sig     .Rebin(rebin)
    nPUVtx_rew_sig         .Rebin(rebin)
    nPUVtx_afterPresel_sig .Rebin(rebin)
                          
    nPUVtx_data            .Rebin(rebin)
    nPUVtxTrue_data        .Rebin(rebin)
    nPUVtxTrue_rew_data    .Rebin(rebin)
    nPUVtx_rew_data        .Rebin(rebin)
    nPUVtx_afterPresel_data.Rebin(rebin)
        
    nPUVtx_py              .Scale(1/nPUVtx_py              .Integral())
    nPUVtxTrue_py          .Scale(1/nPUVtxTrue_py          .Integral())
    nPUVtxTrue_rew_py      .Scale(1/nPUVtxTrue_rew_py      .Integral())
    nPUVtx_rew_py          .Scale(1/nPUVtx_rew_py          .Integral())
    nPUVtx_afterPresel_py  .Scale(1/nPUVtx_afterPresel_py  .Integral())
                            
    nPUVtx_mapy            .Scale(1/nPUVtx_mapy            .Integral())
    nPUVtxTrue_mapy        .Scale(1/nPUVtxTrue_mapy        .Integral())
    nPUVtxTrue_rew_mapy    .Scale(1/nPUVtxTrue_rew_mapy    .Integral())
    nPUVtx_rew_mapy        .Scale(1/nPUVtx_rew_mapy        .Integral())
    nPUVtx_afterPresel_mapy.Scale(1/nPUVtx_afterPresel_mapy.Integral())
                            
    nPUVtx_sig             .Scale(1/nPUVtx_sig             .Integral())
    nPUVtxTrue_sig         .Scale(1/nPUVtxTrue_sig         .Integral())
    nPUVtxTrue_rew_sig     .Scale(1/nPUVtxTrue_rew_sig     .Integral())
    nPUVtx_rew_sig         .Scale(1/nPUVtx_rew_sig         .Integral())
    nPUVtx_afterPresel_sig .Scale(1/nPUVtx_afterPresel_sig .Integral())
                            
    nPUVtx_data            .Scale(1/nPUVtx_data            .Integral())
    nPUVtxTrue_data        .Scale(1/nPUVtxTrue_data        .Integral())
    #nPUVtxTrue_rew_data    .Scale(1/nPUVtxTrue_rew_data    .Integral())
    #nPUVtx_rew_data        .Scale(1/nPUVtx_rew_data        .Integral())
    nPUVtx_afterPresel_data.Scale(1/nPUVtx_afterPresel_data.Integral())
    
    
    nPUVtx_py              .SetLineColor(kBlue)
    nPUVtxTrue_py          .SetLineColor(kBlue)
    nPUVtxTrue_rew_py      .SetLineColor(kBlue)
    nPUVtx_rew_py          .SetLineColor(kBlue)
    nPUVtx_afterPresel_py  .SetLineColor(kBlue)
                           
    nPUVtx_mapy            .SetLineColor(kCyan)
    nPUVtxTrue_mapy        .SetLineColor(kCyan)
    nPUVtxTrue_rew_mapy    .SetLineColor(kCyan)
    nPUVtx_rew_mapy        .SetLineColor(kCyan)
    nPUVtx_afterPresel_mapy.SetLineColor(kCyan)
                           
    nPUVtx_sig             .SetLineColor(kRed)
    nPUVtxTrue_sig         .SetLineColor(kRed)
    nPUVtxTrue_rew_sig     .SetLineColor(kRed)
    nPUVtx_rew_sig         .SetLineColor(kRed)
    nPUVtx_afterPresel_sig .SetLineColor(kRed)
                           
    nPUVtx_data            .SetLineColor(kBlack)
    nPUVtxTrue_data        .SetLineColor(kBlack)
    nPUVtx_afterPresel_data.SetLineColor(kBlack)
    
    nPUVtx_data            .SetMarkerStyle(20)
    nPUVtxTrue_data        .SetMarkerStyle(20)
    nPUVtx_afterPresel_data.SetMarkerStyle(20)
    
    nPUVtx_data            .SetLineStyle(2)
    nPUVtxTrue_data        .SetLineStyle(2)
    nPUVtx_afterPresel_data.SetLineStyle(2)
    
    nPUVtx_data            .SetTitle('Number of Vertices')
    nPUVtxTrue_data        .SetTitle('True Number of Vertices')
    nPUVtxTrue_data        .GetXaxis().SetTitle("number of vertices")
    nPUVtx_afterPresel_data.SetTitle('Number of Vertices after preselections')
    
    nPUVtx_data            .GetYaxis().SetTitle('# events normalized')
    nPUVtxTrue_data        .GetYaxis().SetTitle('# events normalized')
    nPUVtx_afterPresel_data.GetYaxis().SetTitle('# events normalized')
    
    nPUVtx_data            .GetYaxis().SetTitleOffset(1.2)
    nPUVtxTrue_data        .GetYaxis().SetTitleOffset(1.2)
    nPUVtx_afterPresel_data.GetYaxis().SetTitleOffset(1.2)
    
    nPUVtx_data            .SetTitleOffset(1.1)
    nPUVtxTrue_data        .SetTitleOffset(1.1)
    nPUVtx_afterPresel_data.SetTitleOffset(1.1)
    
    
    nPUVtx_data            .SetNdivisions(505)
    nPUVtxTrue_data        .SetNdivisions(505)
    nPUVtx_afterPresel_data.SetNdivisions(505)
    
    nPUVtx_data            .SetMaximum(0.8)
    nPUVtxTrue_data        .SetMaximum(0.2)
    nPUVtx_afterPresel_data.SetMaximum(0.8)
    
    nPUVtx_data.GetXaxis().SetRangeUser(0,65)
    
    
    leg = ROOT.TLegend(0.5574713,0.729021,0.7571839,0.8653846,"","NDC")
    leg.SetLineWidth(2)
    leg.SetBorderSize(0)
    leg.SetFillColor(0)
    leg.SetTextFont(42)
    leg.SetTextSize(0.035)
    leg.SetTextAlign(12)
        
    

    leg.AddEntry(nPUVtx_data,'Run 2016 full promtreco','PL')
    leg.AddEntry(nPUVtx_mapy,'QCD madgraph+pythia8','L')
    leg.AddEntry(nPUVtx_py, 'QCD pythia8','L')
    leg.AddEntry(nPUVtx_sig,'G_{Bulk} #rightarrow ZZ (1.2 TeV)','L')
    

    canvtest = get_canvas('ctest',lumi)
    canvtest.cd()
    canvtest.SetLogy()
    canvtest.SetTitle("number of vertices with PU reweighting applied")
    p11_1 = getPadUp(canvtest)
    nPUVtx_data.Draw('PC')
    nPUVtx_rew_py.Draw('same')
    nPUVtx_rew_mapy.Draw('same')
    nPUVtx_rew_sig.Draw('same')
    leg.Draw()

    CMS_lumi.CMS_lumi(canvtest, 4, 0)	
    canvtest.cd()
    p11_2 = getPadDown(canvtest)
    h_data_MC = nPUVtx_data.Clone("pull")
    h_data_MC.Divide(nPUVtx_rew_py)
    #h_data_MC.Draw()
    #vFrame2 = p11_2.DrawFrame(1000, 0.1, p11_1.GetUxmax(), 1.9)
    setPullStyle(h_data_MC)
    h_data_MC.Draw("same")
    p11_2.RedrawAxis()
    p11_2.Update()
    
    
    
    canvtest.Update()
    canvtest.RedrawAxis()
    testframe = canvtest.GetFrame()
    testframe.Draw()
    canvtest.cd()
    canvtest.Update()
    
    canvtest.SaveAs(out+"nPV_distribution_data_mc_comparison.pdf","pdf")
    
    c1 = get_canvas('c1',lumi)
    c1.cd()
    c1.SetLogy()
    c1.SetTitle("number of vertices with PU rew, after presel")
    pc1_1 = getPadUp(c1)
    nPUVtx_afterPresel_data.Draw('PC')
    nPUVtx_afterPresel_py.Draw('same')
    nPUVtx_afterPresel_mapy.Draw('same')
    nPUVtx_afterPresel_sig.Draw('same')
    leg.Draw()

    CMS_lumi.CMS_lumi(c1, 4, 0)	
    c1.cd()
    pc1_2 = getPadDown(c1)
    h_data_MC_presel = nPUVtx_afterPresel_data.Clone("pull")
    h_data_MC_presel.Divide(nPUVtx_afterPresel_py)
    #h_data_MC.Draw()
    #vFrame2 = p11_2.DrawFrame(1000, 0.1, p11_1.GetUxmax(), 1.9)
    setPullStyle(h_data_MC_presel)
    h_data_MC_presel.Draw("same")
    pc1_2.RedrawAxis()
    pc1_2.Update()
    
    
    c1.Update()
    c1.RedrawAxis()
    
    c1.SaveAs(out+"nVertices_data_mc_comparison.pdf","pdf")
    
    c2 = get_canvas('c12',lumi)
    c2.cd()
    #c2.SetLogy()
    c2.SetTitle("number of vertices with PU rew, after presel")
    #pc2_1 = getPadUp(c2)
    nPUVtxTrue_data.Draw('PC')
    nPUVtxTrue_rew_py.Draw('same')
    nPUVtxTrue_rew_mapy.Draw('same')
    nPUVtxTrue_rew_sig.Draw('same')
    leg.Draw()
    #pc2_2 = getPadDown(c2)
    #h_data_MC_True = nPUVtxTrue_data.Clone("pull")
    #h_data_MC_True.Divide(nPUVtxTrue_py)
    #setPullStyle(h_data_MC_True)
    #h_data_MC_True.Draw("same")
    #pc2_2.RedrawAxis()
    #pc2_2.Update()
    

    CMS_lumi.CMS_lumi(c12, 4, 0)	
    c2.cd()
    c2.Update()
    c2.RedrawAxis()
    c2.SaveAs(out+"nPVTrue_data_mc_comparison.pdf","pdf")

    c3 = get_canvas('c13',lumi)
    c3.cd()
    c3.SetLogy()
    c3.SetTitle("number of vertices NO PU rew")

    nPUVtx_data.Draw('PC')
    nPUVtx_py.Draw('same')
    nPUVtx_mapy.Draw('same')
    nPUVtx_sig.Draw('same')
    leg.Draw()

    CMS_lumi.CMS_lumi(c3, 4, 0)	
    c3.cd()
    c3.Update()
    c3.RedrawAxis()
    c3.SaveAs(out+"nPV_data_mc_comparison_noRew.pdf","pdf")

    time.sleep(10)
