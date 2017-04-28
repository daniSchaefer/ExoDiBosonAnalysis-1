from ROOT import *
import time
import CMS_lumi, tdrstyle
import numpy

tdrstyle.setTDRStyle()
gROOT.SetBatch(True)
tdrstyle.setTDRStyle()
gStyle.SetOptFit(0) 
CMS_lumi.lumi_13TeV = ""
CMS_lumi.writeExtraText = 1
CMS_lumi.extraText = "  Simulation Preliminary"
CMS_lumi.lumi_sqrtS = "13 TeV" # used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)
iPos = 0
if( iPos==0 ): CMS_lumi.relPosX = 0.12
iPeriod = 4

W = 800
H = 800
H_ref = 700 
W_ref = 600 
T = 0.08*H_ref
B = 0.12*H_ref
L = 0.12*W_ref
R = 0.04*W_ref

#def getCanvas(name):
  #c = TCanvas(name,name,800,800)
  #c.GetWindowHeight()
  #c.GetWindowWidth()
  #c.SetTitle("")
  #return c


def doFitWithSignalFunction(hSignal, MASS):
    m = RooRealVar("m","m",1050,7000)
    data = RooDataHist("dh","dh", RooArgList( m), RooFit.Import(hSignal)) ;
    
    #binmax_pre = hPRE.GetMaximumBin();
    #x_pre = hPRE.GetXaxis().GetBinCenter(binmax_pre);
    #binmax_post = hPOST.GetMaximumBin();
    #x_post = hPOST.GetXaxis().GetBinCenter(binmax_post);
    # C r e a t e   m o d e l   a n d   d a t a s e t
    # -----------------------------------------------


    
    m0 = RooRealVar( "mean0", "mean0", MASS, 0.8*MASS, 1.2*MASS);
    gm0= RooRealVar( "gm0", "gm0", MASS, 0.8*MASS, 1.2*MASS);
    sigma = RooRealVar( "sigma" , "sigma", MASS*0.05 ,20., 700.);
    scalesigma = RooRealVar( "scalesigma", "scalesigma", 2., 1.2, 10.);
    alpha      = RooRealVar( "alpha", "alpha", 1.85288, 0.0, 20);
    sig_n      = RooRealVar( "sig_n"  , "sign", 129.697, 0., 300);
    frac       = RooRealVar( "frac", "frac", 0.0, 0.0, 0.35);
    
    gsigma  = RooFormulaVar( "gsigma","@0*@1", RooArgList( sigma, scalesigma ));
    
    gaus   = RooGaussian( "gauss", "gauss", m ,m0 , gsigma);
    cb     = RooCBShape ( "cb", "cb", m , m0 , sigma, alpha, sig_n);
    sigmodel = RooAddPdf  ( "model_"+str(MASS), "model_"+str(MASS), RooArgList( gaus, cb ), RooArgList(frac),1);
    
    sigmodel.fitTo(data,RooFit.Range(MASS*0.8,MASS*1.2),RooFit.SumW2Error(kTRUE),RooFit.PrintEvalErrors(-1),RooFit.Save(kTRUE));
    #sigmodel.plotOn(frame,RooFit.Range(995,5000),RooFit.LineColor(color))
    #data.plotOn(frame)#RooFit.Binning(100),RooFit.Rescale(data.sumEntries()))
    mean_res  = m0.getVal()
    sigma_res = gsigma.getVal()
       
    return [sigmodel,mean_res,sigma_res,m]
 
def getRightHisto(fnameCV, fnameSmeared,category,mass,signal):
    suffix = "JES"
    if fnameSmeared.find("JER")!=-1:
        suffix = "JER"
    if fnameSmeared.find("up")!=-1:
        suffix= suffix+"up"
    if fnameSmeared.find("down")!=-1:
        suffix= suffix+"down"    
    
    print fnameCV
    tfileCV = TFile.Open(fnameCV,'READ')
    print tfileCV
    print fnameSmeared
    tfileSmeared = TFile.Open(fnameSmeared,'READ')
    print tfileSmeared
    histoname = ""
    if category.find("HP")!=-1:
        histoname ="DijetMassHighPuri"
    if category.find("LP")!=-1:
        histoname ="DijetMassLowPuri"
    if category.find("WW")!=-1:
        histoname +="WW"
    if category.find("VV")!=-1:
        histoname +="VV"
    if category.find("ZZ")!=-1:
        histoname +="ZZ"
    if category.find("WZ")!=-1:
        histoname +="WZ"
    if category.find("qV")!=-1:
        histoname +="qV"
    if category.find("qW")!=-1:
        histoname +="qW"
    if category.find("qZ")!=-1:
        histoname +="qZ"
    

    hPRE  =tfileCV.Get(histoname)
    print hPRE
    hPOST =tfileSmeared.Get(histoname)
    print hPOST
    return [hPRE,hPOST]

def doFitPDF(infile,category,mass):
    histoname = category
    hCV = infile.Get(category+"0")
    print hCV
    hCV.Scale(1./hCV.Integral())
    hCV.Rebin(40)
    result =[]
    for i in range(1,101):
        #if i!=24:
            #continue
        hSmeared = infile.Get(category+str(i))
        hSmeared.Scale(1./hSmeared.Integral())
        hSmeared.Rebin(40)
        result.append(doFitOnly(hCV,hSmeared,mass,i))
        
    return result 

def getFitRegion(histo,mass=0):
    #print histo
    binmax = histo.GetMaximumBin()
   
    #print binmax
    x_max  = histo.GetXaxis().GetBinCenter(binmax)
    #print x_max
    n = float(histo.Integral())
    #print n
    frac = 0.6 # 0.8 for VV; 0.6 for qV
    nfrac = 0.
    nBins=0
    while nfrac < frac:
        nBins+=1
        nE = histo.GetBinContent(binmax)
        for b in range(1,nBins+1):
            nE += histo.GetBinContent(binmax+b)+ histo.GetBinContent(binmax-b)
        #print nE
        nfrac = nE/n
    return nBins
        

def doFitOnly(hPRE,hPOST,mass,pdfset):
    binmax_pre = hPRE.GetMaximumBin();
    x_pre = hPRE.GetXaxis().GetBinCenter(binmax_pre);
    binmax_post = hPOST.GetMaximumBin();
    x_post = hPOST.GetXaxis().GetBinCenter(binmax_post);
    nBinsPre = getFitRegion(hPRE)
    nBinsPost = getFitRegion(hPOST)
    
    mlowPRE = hPRE.GetXaxis().GetBinCenter(binmax_pre-nBinsPre)
    mupPRE = hPRE.GetXaxis().GetBinCenter(binmax_pre+nBinsPre)
    mlowPOST = hPOST.GetXaxis().GetBinCenter(binmax_post-nBinsPost)
    mupPOST = hPOST.GetXaxis().GetBinCenter(binmax_post+nBinsPost)
    if binmax_post < nBinsPost:
        mlowPOST = hPOST.GetXaxis().GetBinCenter(1)
    if binmax_pre < nBinsPre:
        mlowPRE = hPRE.GetXaxis().GetBinCenter(1)
    
    
    slow = 0.8
    sup  = 1.2
    
    gPRE  = TF1("gPRE" ,"gaus", mass*slow,mass*sup)
    gPOST = TF1("gPOST","gaus", mass*slow,mass*sup)
    #gPOST.SetParameter(2,100.)
    #gPOST.SetParLimits(2,80.,200.) 
    
    
    #gPRE  = TF1("gPRE" ,"gaus", mlowPRE,mupPRE)
    ##gPOST = TF1("gPOST","gaus", mlowPOST,mupPOST)
    #gPOST  = TF1("gPOST" ,"gaus", mlowPRE,mupPRE)
    
    print "Binmax : "+str(binmax_post) + "   "+str(binmax_pre)
    print "nBin : "+str(nBinsPost) + "   "+str(nBinsPre)
    print "========================================="
    print "Pre : "+str(mlowPRE )+ "   "+ str(mupPRE) 
    print "Post: "+str(mlowPOST )+ "    "+str(mupPOST)
    print "========================================="
    hPRE.Fit(gPRE,"SR")
    hPOST.Fit(gPOST,"SRL")
    #if mass == 3500 and pdfset==78:
    makePlot("test",str(pdfset),mass,gPRE,gPOST,hPRE,hPOST,x_pre,x_post)
    ratio =[ ((gPOST.GetParameter(2)/gPRE.GetParameter(2)-1)*100), ((gPOST.GetParameter(1)/gPRE.GetParameter(1)-1)*100)]
    
    #res2 = doFitWithSignalFunction(hPRE, mass)
    #res3 = doFitWithSignalFunction(hPOST, mass)
    
    #ratio_alt = [(res2[2]/res3[2]-1)*100,(res2[1]/res3[1]-1)*100 ]
    return ratio

def makePlot(signal,suffix,mass,gPRE,gPOST,hPRE,hPOST,x_pre,x_post):
    gPRE.SetLineColor(kRed)
    gPOST.SetLineColor(kBlue)
    canv = getCanvas(signal+"dijetMass"+suffix+"_M"+str(int(mass)))
    canv.cd()
    vFrame = canv.DrawFrame(x_pre*0.8,0,x_pre*1.2,hPRE.GetMaximum()*1.5)
    vFrame.SetYTitle("A.U")
    vFrame.SetXTitle("dijet mass (GeV)")
    vFrame.SetTitle(suffix)
    vFrame.GetXaxis().SetTitleSize(0.06)
    vFrame.GetXaxis().SetTitleOffset(0.95)
    vFrame.GetXaxis().SetLabelSize(0.05)
    vFrame.GetYaxis().SetTitleSize(0.06)
    vFrame.GetYaxis().SetTitleOffset(1.3)
    vFrame.GetYaxis().SetLabelSize(0.05)
    vFrame.GetXaxis().SetNdivisions(807)
    vFrame.GetYaxis().SetNdivisions(703)
    hPRE.SetLineColor(kRed)
    hPOST.SetLineColor(kBlue)
    hPRE.Draw("same")
    # hPRE.SetTitle("Smearing formula: mass = tr_->Gaus( mass, TMath::Sqrt(jmr*jmr-1)*(massResolution-1)*mass")
    hPOST.Draw('same')

    l = TLegend(0.560461809,0.7620725,0.70559296,0.9009845)
    l.SetHeader(suffix)
    l.SetTextSize(0.035)
    l.SetLineColor(0)
    l.SetShadowColor(0)
    l.SetLineStyle(1)
    l.SetLineWidth(1)
    l.SetFillColor(0)
    l.SetFillStyle(0)
    l.SetMargin(0.35)
    l.AddEntry(hPRE,"Pre-smear: #sigma = %.2f"%gPRE.GetParameter(2),"lp")
    l.AddEntry(hPOST,"Post-smear: #sigma = %.2f"%gPOST.GetParameter(2),"lp")
    ratio =[ ((gPOST.GetParameter(2)/gPRE.GetParameter(2)-1)*100), ((gPOST.GetParameter(1)/gPRE.GetParameter(1)-1)*100)]
    l.AddEntry(0,"Ratio_{#sigma} = %.2f %%" % ((gPOST.GetParameter(2)/gPRE.GetParameter(2)-1)*100),"")
    l.Draw("same")
    canv.SaveAs("/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/figures/systematics/preVsPostSmearing_dijetMass"+suffix+"_M"+str(int(mass))+"_"+signal+"_PDf.pdf")
    return 0


def doFit(fnameCV, fnameSmeared,category,mass,signal):
    suffix = "JES"
    if fnameSmeared.find("JER")!=-1:
        suffix = "JER"
    if fnameSmeared.find("up")!=-1:
        suffix= suffix+"up"
    if fnameSmeared.find("down")!=-1:
        suffix= suffix+"down"    
    
    print fnameCV
    tfileCV = TFile.Open(fnameCV,'READ')
    print tfileCV
    print fnameSmeared
    tfileSmeared = TFile.Open(fnameSmeared,'READ')
    print tfileSmeared
    histoname = ""
    if category.find("HP")!=-1:
        histoname ="DijetMassHighPuri"
    if category.find("LP")!=-1:
        histoname ="DijetMassLowPuri"
    if category.find("WW")!=-1:
        histoname +="WW"
    if category.find("VV")!=-1:
        histoname +="VV"
    if category.find("ZZ")!=-1:
        histoname +="ZZ"
    if category.find("WZ")!=-1:
        histoname +="WZ"
    if category.find("qV")!=-1:
        histoname +="qV"
    if category.find("qW")!=-1:
        histoname +="qW"
    if category.find("qZ")!=-1:
        histoname +="qZ"
    

    hPRE  =tfileCV.Get(histoname)
    print hPRE
    hPOST =tfileSmeared.Get(histoname)
    print hPOST
    hPRE .Scale(1./hPRE.Integral())
    hPOST.Scale(1./hPOST.Integral())
    hPRE .Rebin(40)
    hPOST.Rebin(40)
    binmax_pre = hPRE.GetMaximumBin();
    x_pre = hPRE.GetXaxis().GetBinCenter(binmax_pre);
    binmax_post = hPOST.GetMaximumBin();
    x_post = hPOST.GetXaxis().GetBinCenter(binmax_post);

    slow = 0.8
    sup  = 1.2
    if signal.find("Qstar")!=-1 or category.find("VV")!=-1:
        slow = 0.9
        sup = 1.1
    
    gPRE  = TF1("gPRE" ,"gaus", mass*slow,mass*sup)
    gPOST = TF1("gPOST","gaus", mass*slow,mass*sup)
    
    if suffix.find("JES")!=-1 or category.find("VV")==-1:
        gPRE  = TF1("gPRE" ,"gaus", x_pre*slow,x_pre*sup)
        gPOST = TF1("gPOST","gaus", x_post*slow,x_post*sup)
    
    
    gPRE.SetLineColor(kRed)
    gPOST.SetLineColor(kBlue)
    
    hPRE.Fit(gPRE,"SR")
    hPOST.Fit(gPOST,"SR")
    #fitres1 = doFitWithSignalFunction(hPRE, mass)
    #fitres2 = doFitWithSignalFunction(hPOST, mass)
    
    

    canv = getCanvas(signal+"dijetMass"+suffix+"_M"+str(int(mass)))
    canv.cd()
    #vFrame = fitres1[3].frame()
    vFrame = canv.DrawFrame(x_pre*0.8,0,x_pre*1.2,hPRE.GetMaximum()*1.5)
    #fitres1[0].plotOn(vFrame)
    vFrame.SetYTitle("A.U")
    vFrame.SetXTitle("dijet mass (GeV)")
    vFrame.SetTitle(suffix)
    vFrame.GetXaxis().SetTitleSize(0.06)
    vFrame.GetXaxis().SetTitleOffset(0.95)
    vFrame.GetXaxis().SetLabelSize(0.05)
    vFrame.GetYaxis().SetTitleSize(0.06)
    vFrame.GetYaxis().SetTitleOffset(1.3)
    vFrame.GetYaxis().SetLabelSize(0.05)
    vFrame.GetXaxis().SetNdivisions(807)
    vFrame.GetYaxis().SetNdivisions(703)
    hPRE.SetLineColor(kRed)
    hPOST.SetLineColor(kBlue)
    hPRE.Draw('same')
    # hPRE.SetTitle("Smearing formula: mass = tr_->Gaus( mass, TMath::Sqrt(jmr*jmr-1)*(massResolution-1)*mass")
    hPOST.Draw('same')

    l = TLegend(0.560461809,0.7620725,0.70559296,0.9009845)
    l.SetHeader(suffix)
    l.SetTextSize(0.035)
    l.SetLineColor(0)
    l.SetShadowColor(0)
    l.SetLineStyle(1)
    l.SetLineWidth(1)
    l.SetFillColor(0)
    l.SetFillStyle(0)
    l.SetMargin(0.35)
    l.AddEntry(hPRE,"Pre-smear: #sigma = %.2f"%gPRE.GetParameter(2),"lp")
    l.AddEntry(hPOST,"Post-smear: #sigma = %.2f"%gPOST.GetParameter(2),"lp")
    ratio =[ ((gPOST.GetParameter(2)/gPRE.GetParameter(2)-1)*100), ((gPOST.GetParameter(1)/gPRE.GetParameter(1)-1)*100)]
    l.AddEntry(0,"Ratio_{#sigma} = %.2f %%" % ((gPOST.GetParameter(2)/gPRE.GetParameter(2)-1)*100),"")
    l.Draw("same")
    canv.SaveAs("/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/figures/systematics/preVsPostSmearing_dijetMass"+suffix+"_M"+str(int(mass))+"_"+signal+".pdf")
    time.sleep(2)
    del canv, hPRE, hPOST, tfileCV, tfileSmeared
    
    return ratio


def getCanvas(name):
  c = TCanvas(name,name,W,H)
  c.SetTitle("")
  c.SetLeftMargin( L/W + 0.10)
  c.SetRightMargin( R/W +0.02)
  c.SetTopMargin( T/H )
  c.SetBottomMargin( B/H +0.02)
  c.SetTickx(0)
  c.SetTicky(0)
  return c
  
  

def plotEffectOnShape(fnameCV,fnameSmeared,mass,cat,sys):
    suffix = "JES"
    if fnameSmeared.find("JER")!=-1:
        suffix = "JER"
    if fnameSmeared.find("up")!=-1:
        suffix= suffix+"up"
    if fnameSmeared.find("down")!=-1:
        suffix= suffix+"down"    
    
    print fnameCV
    tfileCV = TFile.Open(fnameCV,'READ')
    print tfileCV
    print fnameSmeared
    tfileSmeared = TFile.Open(fnameSmeared,'READ')
    print tfileSmeared
    histoname = ""
    if category.find("HP")!=-1:
        histoname ="DijetMassHighPuri"
    if category.find("LP")!=-1:
        histoname ="DijetMassLowPuri"
    if category.find("WW")!=-1:
        histoname +="WW"
    if category.find("VV")!=-1:
        histoname +="VV"
    if category.find("ZZ")!=-1:
        histoname +="ZZ"
    if category.find("WZ")!=-1:
        histoname +="WZ"
    if category.find("qV")!=-1:
        histoname +="qV"
    if category.find("qW")!=-1:
        histoname +="qW"
    if category.find("qZ")!=-1:
        histoname +="qZ"
    

    hSignal  =tfileCV.Get(histoname)
    hSignalSmeared =tfileSmeared.Get(histoname)
        
    c2 = getCanvas("c"+str(m))
    c2.cd()
    hSignal.Scale(1/hSignal.Integral())
    hSignal.Rebin(40)
    hSignal.SetLineColor(kBlue)
    hSignal.SetMarkerColor(kBlue)
    hSignal.SetMarkerStyle(23)
    hSignal.GetXaxis().SetRangeUser(mass-0.2*mass,mass+0.2*mass)
    
    hSignalSmeared.Scale(1/hSignalSmeared.Integral())
    hSignalSmeared.Rebin(40)
    hSignalSmeared.SetLineColor(kRed)
    hSignalSmeared.SetMarkerColor(kRed)
    hSignalSmeared.SetMarkerStyle(24)
    
    hSignal.Draw("HIST")
    hSignalSmeared.Draw("HISTsame")
    CMS_lumi.CMS_lumi(c2, iPeriod, iPos)
    c2.Update()
    c2.SaveAs("test_M"+str(m)+"_"+category+"_"+sys+".pdf")
   
    return 0


if __name__=="__main__":
    gStyle.SetOptTitle(0)
    gStyle.SetOptStat(0)
    category = "qVLP"
    fout = "ShapeUncertainty"+category+".txt"
    outfile = open(fout,'w')
    systematics = ["JESup","JESdown","JERup","JERdown"]
    signals=["QstarQW"]#,"QstarQZ"]
    #signals=["QstarQW"]#,"BulkZZ","ZprimeWW","WprimeWZ"]
    #signals =["ZprimeWW","BulkWW","BulkZZ","WprimeWZ"]
    doPDF = True
    mass =[]
    if doPDF==False: 
        for signal in signals:
            JESup =[]
            JESdown =[]
            JERup = []
            JERdown =[]
            JESup_peak =[]
            JESdown_peak =[]
            JERup_peak = []
            JERdown_peak =[]
            if signal.find("prime")!=-1:
                #category = "HPVV"
                mass =[1200,1400,1600,1800,2000,2500,3000,3500,4000,4500] #Zprime /Wprime
            if signal.find("BulkWW")!=-1:
                #category = "HPVV"
                mass =[1200, 1400, 1600, 1800, 2000, 2500, 3500, 4000, 4500] #BulkWW
            if signal.find("BulkZZ")!=-1:
                #category = "HPVV"
                mass =[1200, 1400, 1600, 1800, 2000, 2500, 3000, 3500, 4000] #BulkZZ
            if signal.find("QstarQW")!=-1:
                #category = "HPqV"
                mass =[ 1200, 1400, 1600 ,1800, 2000 ,2500, 3000, 3500, 4000 ,4500, 5000, 6000, 7000] #QstarQW
                #mass =[6000]
            if signal.find("QstarQZ")!=-1:
                #category = "HPqV"
                mass =[1200, 1400, 1600, 1800, 2000, 2500, 3000, 4500, 6000] #QstarQZ
        
            #mass = [1200,2000,3000,4000,5000,6000,7000]
            for sys in systematics:
                for m in mass:
                    fname = "/shome/dschafer/ExoDiBosonAnalysis/forSystematics/histosForShapeUnc/"+signal+"_13TeV_"+str(int(m))+"GeV_"+sys+".root"
                    fname2 = "/shome/dschafer/ExoDiBosonAnalysis/forSystematics/histosForShapeUnc/"+signal+"_13TeV_"+str(int(m))+"GeV_CV.root"
                    
                    
                    plotEffectOnShape(fname,fname2,m,category,sys)
                    
                    
                    r = doFit(fname2,fname,category,m,signal)
                    if fname.find("JESup")!=-1:
                        JESup.append(r[0])
                        JESup_peak.append(r[1])
                    if fname.find("JESdown")!=-1:
                        JESdown.append(r[0])
                        JESdown_peak.append(r[1])
                    if fname.find("JERup")!=-1:
                        JERup.append(r[0])
                        JERup_peak.append(r[1])
                    if fname.find("JERdown")!=-1:
                        JERdown.append(r[0])
                        JERdown_peak.append(r[1])
            i=0 
            outfile.write( "==========================================\n")
            outfile.write( "=======" + signal +"================\n")
            outfile.write( "==========================================\n")
            outfile.write( "width: \n")
            outfile.write( "mass:      JESup/JESdown       JERup/JERdown\n")
            for m in mass:
                outfile.write( str(m)+"   "+str(round(JESup[i],2))+"/"+str(round(JESdown[i],2))+"   "+str(round(JERup[i],2))+"/"+str(round(JERdown[i],2))+"\n")
                i+=1
                
            outfile.write( "peak position: \n")
            i=0
            outfile.write( "mass:      JESup/JESdown       JERup/JERdown\n")
            for m in mass:
                outfile.write( str(m)+"   "+str(round(JESup_peak[i],2))+"/"+str(round(JESdown_peak[i],2))+"   "+str(round(JERup_peak[i],2))+"/"+str(round(JERdown_peak[i],2))+"\n")
                i+=1
                        
            maxJES =0
            maxJER =0
            maxJES_peak =0
            maxJER_peak =0
            i=0
            for m in mass:
                if TMath.Abs(JESup[i]) >= maxJES:
                    maxJES = TMath.Abs(JESup[i])
                if TMath.Abs(JESdown[i]) >= maxJES:
                    maxJES = TMath.Abs(JESdown[i])
                if TMath.Abs(JERup[i]) >= maxJER:
                    maxJER = TMath.Abs(JERup[i])
                if TMath.Abs(JERdown[i]) >= maxJER:
                    maxJER = TMath.Abs(JERdown[i])
                    
                if TMath.Abs(JESup_peak[i]) >= maxJES_peak:
                    maxJES_peak = TMath.Abs(JESup_peak[i])
                if TMath.Abs(JESdown_peak[i]) >= maxJES_peak:
                    maxJES_peak = TMath.Abs(JESdown_peak[i])
                if TMath.Abs(JERup_peak[i]) >= maxJER_peak:
                    maxJER_peak = TMath.Abs(JESup_peak[i])
                if TMath.Abs(JERdown_peak[i]) >= maxJER_peak:
                    maxJER_peak = TMath.Abs(JERdown_peak[i])
                i+=1
                
            outfile.write( "maximum rel. diff width: JES " +str(round(maxJES,2))+"   JER  "+str(round(maxJER,2))+"\n")
            outfile.write( "maximum rel. diff peak : JES " +str(round(maxJES_peak,2))+"   JER  "+str(round(maxJER_peak,2))+"\n")
            
    else:
            print "bla"
            mass = [1200,2000,3000,4000,5000,6000,7000]
            #mass = [1200,2000,3500,4500]
            #mass = [6000]
            width=[]
            peak =[]
            resW=[]
            resP=[]
            pdfsetIndex =[]
            category = "qVHP"
            #category = "VVLPHP"
            for signal in signals:
                for m in mass:
                    filename = "../results/Signal_QstarQW_M"+str(m)+"_PDF.root"
                    #filename = "../results/Signal_BulkWW_M"+str(m)+"_PDF.root"
                    f = TFile.Open(filename,'READ')
                    print f
                    res = doFitPDF(f,category,m)
                    print res
                    for l in res:
                        resW.append(l[0])
                        resP.append(l[1])
                    nres = numpy.array(resW)
                    mean = numpy.mean(nres)
                    std  = numpy.std(nres)
                    width.append([mean,std])
                    
                    
                    nresP = numpy.array(resP)
                    meanP = numpy.mean(nresP)
                    stdP  = numpy.std(nresP)
                    peak.append([meanP,stdP])
                    #maxW=0
                    #maxP=0
                    #pdfset=0
                    #i=0
                    #for l in res:
                        #if TMath.Abs(l[0])>=maxW:
                            #maxW=TMath.Abs(l[0])
                            #pdfset = i
                        #if TMath.Abs(l[1])>=maxP:
                            #maxP=TMath.Abs(l[1])
                        #i+=1
                    #print "maximum variance of width "+str(maxW)+" %" 
                    #print "maximum variance of peak  "+str(maxP)+" %"
                    #print pdfset
                    #pdfsetIndex.append(pdfset)
                    #width.append(maxW)
                    #peak.append(maxP)
                    
                i=0
                #print pdfsetIndex
                #for m in mass:
                    #print "mass: "+str(m)+" "+str(round(width[i][0],2))+" "+str(round(width[i][1],2))+"  "+str(round(peak[i][0],2))+"  "+str(round(peak[i][1],2))
                    
                for m in mass:
                    print "mass: "+str(m)+" "+str(round(width[i][1],2))+"  "+str(round(peak[i][1],2))
                    i+=1
                
                        
            
        
    
    
