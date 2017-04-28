import ROOT as rt
from array import *
import time
import CMS_lumi, tdrstyle
from heapq import nsmallest


tdrstyle.setTDRStyle()
rt.gStyle.SetOptFit(0) 
CMS_lumi.lumi_13TeV = "run B"
CMS_lumi.writeExtraText = 1
CMS_lumi.extraText = "Preliminary"
CMS_lumi.lumi_sqrtS = "13 TeV" # used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)
iPos = 11
if( iPos==0 ): CMS_lumi.relPosX = 0.12
iPeriod=4



rt.gStyle.SetOptFit(1)

massBins =[1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325, 354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 955, 1000, 1058, #944 to 955!
             1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607, 1687, 1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 
             4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808]

xbins = array('d',massBins)
outdir = "/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/figures/bkgfit/ReReco2016/"

fileIN = rt.TFile.Open("/mnt/t3nfs01/data01/shome/dschafer/ExoDiBosonAnalysis/results/Data_runB_VVdijet.root")
fileIN2 = rt.TFile.Open("/mnt/t3nfs01/data01/shome/dschafer/ExoDiBosonAnalysis/results/Data_runB_VVdijet_rerereco.root")


categories = ["WW, high-purity","WW, low-purity","WZ, high-purity","WZ, low-purity","ZZ, high-purity","ZZ, low-purity"]#,"VV, high-purity","VV, low-purity"]     
histos = ["DijetMassHighPuriWW","DijetMassLowPuriWW","DijetMassHighPuriWZ", "DijetMassLowPuriWZ", "DijetMassHighPuriZZ","DijetMassLowPuriZZ"]#,"DijetMassHighPuriVV","DijetMassLowPuriVV"]

#histos = ["DijetMassHighPuriqW","DijetMassLowPuriqW","DijetMassHighPuriqZ", "DijetMassLowPuriqZ", "DijetMassHighPuriqV","DijetMassLowPuriqV"]

ii = -1        
for h in histos:
    ii += 1
    # if ii !=4: continue
    title = h.replace("DijetMass","")
    print fileIN.GetName()
    print h
    htmp = fileIN.Get(h)
    htmp2= fileIN2.Get(h)
    
    firstbin = 1058.
    lastbin = htmp.GetBinCenter(htmp.FindLastBinAbove(0.99999))
    lower = (nsmallest(2, massBins, key=lambda x: abs(x-lastbin)))[0]
    higher  = (nsmallest(2, massBins, key=lambda x: abs(x-lastbin)))[1]
    if lower > higher:
      fFitXmax = lower
    if higher > lower:
      fFitXmax = higher
      
    print "Last non-zero bin is at x=%f. Closest dijet mass bins are L = %i  H = %i" %(lastbin,lower,higher)
    print "Using x max = %i" %lastbin
    print "Using x min = %i" %firstbin


    dataDistOLD = htmp.Rebin(len(xbins)-1,"hMass_rebinned",xbins)
    minVal = firstbin
    maxVal = fFitXmax


    bins = []
    for i in range(0, dataDistOLD.GetXaxis().GetNbins()):
        thisVal = dataDistOLD.GetXaxis().GetBinLowEdge(i+1)
        if thisVal >= minVal and thisVal <= maxVal:
          bins.append(dataDistOLD.GetXaxis().GetBinLowEdge(i+1))
    mjj = rt.RooRealVar("mjjCMS","Dijet invariant mass (GeV)",len(bins)-1, bins[0], bins[-1])
    dataDist = htmp
    dataDist2 =htmp2
    

    mjjbins = rt.RooBinning(len(bins)-1, array('d',bins), "mjjbins")
    mjj.setBinning(mjjbins)

    dataset = rt.RooDataHist("dataCMS", "dataCMS", rt.RooArgList(mjj), rt.RooFit.Import(dataDist))
    dataset2 = rt.RooDataHist("dataCMS2", "dataCMS2", rt.RooArgList(mjj), rt.RooFit.Import(dataDist2))
   

    frame = mjj.frame()
    #dataset.plotOn(frame,rt.RooFit.DataError(rt.RooAbsData.Poisson), rt.RooFit.Binning(mjjbins),rt.RooFit.Name("data"),rt.RooFit.Invisible())
    
    #dataset2.plotOn(frame,rt.RooFit.DataError(rt.RooAbsData.Poisson), rt.RooFit.Binning(mjjbins),rt.RooFit.Name("data2"),rt.RooFit.Invisible())
    
    frame3 = mjj.frame()
    #hpull = frame.pullHist("data","data2",True)
    #frame3.addPlotable(hpull,"X0 P E1")
    
    dataset.plotOn(frame,rt.RooFit.DataError(rt.RooAbsData.Poisson), rt.RooFit.Binning(mjjbins),rt.RooFit.Name("data"),rt.RooFit.XErrorSize(0))
    
    dataset2.plotOn(frame,rt.RooFit.DataError(rt.RooAbsData.Poisson), rt.RooFit.Binning(mjjbins),rt.RooFit.Name("data2"),rt.RooFit.XErrorSize(0),rt.RooFit.MarkerColor(rt.kRed),rt.RooFit.LineColor(rt.kRed),rt.RooFit.MarkerSize(0.5))
    
    #LineStyle(Int_t style)          -- Select line style by ROOT line style code, default is solid
  #// LineColor(Int_t color)          -- Select line color by ROOT color code, default is black
  #// LineWidth(Int_t width)          -- Select line with in pixels, default is 3
  #// MarkerStyle(Int_t style)        -- Select the ROOT marker style, default is 21
  #// MarkerColor(Int_t color)        -- Select the ROOT marker color, default is black
  #// MarkerSize(Double_t size)  

    c1 =rt.TCanvas("c1","",800,800)
    c1.SetLogy()
    #c1.Divide(1,2,0,0,0)
    #c1.SetLogy()
    #c1.cd(1)
    #p11_1 = c1.GetPad(1)
    #p11_1.SetPad(0.01,0.26,0.99,0.98)
    #p11_1.SetLogy()
    #p11_1.SetRightMargin(0.05)
    #p11_1.SetTopMargin(0.1)
    #p11_1.SetBottomMargin(0.02)
    #p11_1.SetFillColor(0)
    #p11_1.SetBorderMode(0)
    #p11_1.SetFrameFillStyle(0)
    #p11_1.SetFrameBorderMode(0)
    frame.GetYaxis().SetTitleSize(0.06)
    frame.GetYaxis().SetTitleOffset(0.98)
    # frame.GetYaxis().SetLabelSize(0.09)
    frame.SetMinimum(0.2)
    frame.SetMaximum(1E5)
    if h.find("q")!=-1:
        frame.SetMaximum(1E7)
    frame.GetXaxis().SetNdivisions(8)
    #frame.SetName("mjjFit")
    frame.GetYaxis().SetTitle("Events / 100 GeV")
    frame.SetTitle("")
    frame.Draw()

    legend = rt.TLegend(0.52097293,0.64183362,0.6681766,0.879833)
    legend2 = rt.TLegend(0.52097293,0.64183362,0.6681766,0.879833)
    legend.SetTextSize(0.038)
    legend.SetLineColor(0)
    legend.SetShadowColor(0)
    legend.SetLineStyle(1)
    legend.SetLineWidth(1)
    legend.SetFillColor(0)
    legend.SetFillStyle(0)
    legend.SetMargin(0.35)
    legend2.SetTextSize(0.038)
    legend2.SetLineColor(0)
    legend2.SetShadowColor(0)
    legend2.SetLineStyle(1)
    legend2.SetLineWidth(1)
    legend2.SetFillColor(0)
    legend2.SetFillStyle(0)
    legend2.SetMargin(0.35)
    legend.AddEntry(frame.findObject("data"),"CMS data","lpe")
    legend.AddEntry(frame.findObject("data2"),"CMS data Re-re-reco","lpe")

    legend.Draw("same")

    addInfo = rt.TPaveText(0.5110112,0.4166292,0.8502143,0.6123546,"NDC")
    addInfo.AddText(categories[ii])
    addInfo.AddText("|#eta| #leq 2.5, p_{T} > 200 GeV")
    addInfo.AddText("M_{jj} > 1050 GeV, |#Delta#eta_{jj}| #leq 1.3")
    addInfo.SetFillColor(0)
    addInfo.SetLineColor(0)
    addInfo.SetFillStyle(0)
    addInfo.SetBorderSize(0)
    addInfo.SetTextFont(42)
    addInfo.SetTextSize(0.040)
    addInfo.SetTextAlign(12)
    addInfo.Draw()
    CMS_lumi.CMS_lumi(c1, iPeriod, iPos)
    c1.Update()



    #c1.cd(2)
    #p11_2 = c1.GetPad(2)
    #p11_2.SetPad(0.01,0.02,0.99,0.27)
    #p11_2.SetBottomMargin(0.35)
    #p11_2.SetRightMargin(0.05)
    ## p11_2.SetGridx()
    ## p11_2.SetGridy()
    #frame3.SetMinimum(-2.9)
    #frame3.SetMaximum(2.9)
    #frame3.SetTitle("")
    #frame3.SetXTitle("Dijet invariant mass (GeV)")
    #frame3.GetXaxis().SetTitleSize(0.06)
    #frame3.SetYTitle("#frac{Data-Data2}{#sigma_{data}}")
    #frame3.GetYaxis().SetTitleSize(0.15)
    #frame3.GetYaxis().CenterTitle()
    #frame3.GetYaxis().SetTitleOffset(0.30)
    #frame3.GetYaxis().SetLabelSize(0.15)
    #frame3.GetXaxis().SetTitleSize(0.17)
    #frame3.GetXaxis().SetTitleOffset(0.91)
    #frame3.GetXaxis().SetLabelSize(0.12)
    #frame3.GetXaxis().SetNdivisions(906)
    #frame3.GetYaxis().SetNdivisions(305)
    #frame3.Draw("same")
    #line = rt.TLine(minVal,0,frame3.GetXaxis().GetXmax(),0)
    #line1  = rt.TLine(minVal,1,frame3.GetXaxis().GetXmax(),1)
    #line2  = rt.TLine(minVal,-1,frame3.GetXaxis().GetXmax(),-1)
    #line1.SetLineStyle(2)
    #line1.SetLineWidth(2)
    #line2.SetLineStyle(2)
    #line2.SetLineWidth(2)
    
    ##line.Draw("same")
    #line1.Draw("same")
    #line2.Draw("same")
    #c1.Update()

    print title
    canvname = outdir+"DataMiniAODcomp_%s.pdf"%histos[ii]
    c1.SaveAs(canvname)
    c1.SaveAs(canvname.replace("pdf","C"),"C")

    time.sleep(5)
