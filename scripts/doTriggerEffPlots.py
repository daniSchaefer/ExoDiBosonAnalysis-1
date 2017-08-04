# run with : python doTriggerEffPlots.py --filename ExoDiBosonAnalysis.Datatest_noTrigger_data_sideband_doubleTag.root --isMC False -s True
# python doTriggerEffPlots.py --filename Data_VVsideband_All_noTrigger.root --isMC False -s True --run All
# python doTriggerEffPlots.py --filename ExoDiBosonAnalysis.JetHT_Run2016C_noTrigger_data_sideband_doubleTag.root --isMC False -s True --run C+B --plot SD/all/turnOn
from subprocess import Popen
from optparse import OptionParser
from array import array
import ROOT
import time
import CMS_lumi, tdrstyle
from ROOT import gROOT, TPaveLabel, gStyle, gSystem, TGaxis, TStyle, TLatex, TString, TF1,TFile,TLine, TLegend, TH1D,TH1F,TH2D,THStack,TChain, TCanvas, TMatrixDSym, TMath, TText, TPad, TPaveText, TMultiGraph, TGraphAsymmErrors, TGraph, TH1, TH2, TH2F, TLine, TColor

from array import array

gROOT.SetBatch(True)
parser = OptionParser()

parser.add_option('--filename', action="store",type="string",dest = "filename",default="../config/BulkWW_M1000.xml")
parser.add_option('--outdir',action="store",type="string",dest="outdir",default="../results/")
parser.add_option('--s',action="store",type="string",dest="suffix",default="")
parser.add_option('--isMC',action="store",type="string",dest="isMC",default="True")
parser.add_option("-s", "--save", dest="save", default=False, action="store_true",help="save canvas")
parser.add_option("-t","--time",dest="time",default=5,action="store_true")
parser.add_option("--run",dest="run",type="string",default="all",action="store")
parser.add_option("--plot",dest="plot",type="string",default="all",action="store")
parser.add_option("--lumi",dest="lumi",type="string",default="",action="store")
(options, args) = parser.parse_args()

tdrstyle.setTDRStyle()
gStyle.SetOptFit(0)
lumi =""
if options.run =="All":
    lumi="36.5 fb^{-1}"
else:
    lumi = options.run
    
if options.lumi !="":
    lumi = options.lumi+" fb^{-1}"
CMS_lumi.lumi_13TeV = lumi#"36.4 fb^{-1}"
CMS_lumi.writeExtraText = 1
CMS_lumi.extraText = ""
CMS_lumi.lumi_sqrtS = "13 TeV"
iPos = 10
if( iPos==0 ): CMS_lumi.relPosX = 0.12
iPeriod = 4

def openRootFile(filename,inputdir):
    f = ROOT.TFile(inputdir+filename)
    print inputdir+filename
    #print f
    return f


def get_palette(mode):
 palette = {}
 palette['gv'] = [] 
 colors = ['#40004b','#762a83','#9970ab','#de77ae','#a6dba0','#5aae61','#1b7837','#00441b','#92c5de','#4393c3','#2166ac','#053061']
 colors = ['#762a83','#de77ae','#a6dba0','#4393c3','#4393c3']
 colors = ['#000000','#0000CD','#228b22']
 for c in colors:
  palette['gv'].append(c)
 return palette[mode]
 
def sigmoid(x,p):
    max_eff = 1.
    return max_eff/(1+math.exp(-p[1]*(x[0]-p[0])))
    # return max_eff/(p[1]+math.exp(-p[0]*x[0]))
    return sigmoid
    # k == 1/sigma*Ethres, x0 = EThreshold

def getLegend():
  l = TLegend(0.4304361,0.263552,0.808124,0.5624967)
  l.SetTextSize(0.038)
  l.SetLineColor(0)
  l.SetShadowColor(0)
  l.SetTextFont(42)
  #l.SetLineStyle(1)
  #l.SetLineWidth(1)
  l.SetFillColor(0)
  l.SetFillStyle(0)
  l.SetMargin(0.35)
  l.SetHeader("")#options.run)
  return l

def getPave():
  addInfo = TPaveText(0.4604027,0.846131,0.8288591,0.9419643,"NDC")
  addInfo.SetFillColor(0)
  addInfo.SetLineColor(0)
  addInfo.SetFillStyle(0)
  addInfo.SetBorderSize(0)
  addInfo.SetTextFont(42)
  addInfo.SetTextSize(0.042)
  addInfo.SetTextAlign(12)
  return addInfo

def getCanvas():
  c = TCanvas("c","TriggerEff",800,800)
  c.GetWindowHeight()
  c.GetWindowWidth()
  c.SetTitle("")
  #c.SetGridx()
  #c.SetGridy()
  return c

def formatGraph(c,mg,label,bin1,bin2):
  mg.SetMinimum(0.)
  mg.SetMaximum(1.2)
  mg.GetXaxis().SetTitleSize(0.06)
  mg.GetXaxis().SetTitleOffset(0.95)
  mg.GetXaxis().SetLabelSize(0.05)
  mg.GetYaxis().SetTitleSize(0.06)
  mg.GetYaxis().SetLabelSize(0.05)
  mg.GetXaxis().SetTitle(label)
  mg.GetYaxis().SetTitle("Efficiency")
  mg.GetXaxis().SetRangeUser(bin1,bin2)
  mg.GetYaxis().SetNdivisions(408)
  CMS_lumi.CMS_lumi(c, iPeriod, iPos)
  c.Update()

def setEffStyle(eff,color,marker):
  eff.SetMarkerStyle(marker)
  eff.SetMarkerSize(1.5)
  eff.SetMarkerColor(color)
  eff.SetLineColor( color)
  
def doFit(eff,l,histtmp,end):
  #fit_x3 = TF1("fit_x3",sigmoid, 0., 2000., 2)
  fit_x3 = TF1("fit_x3","1./(1+exp(-[1]*(x-[0])))",0.,2000.)
  fit_x3.SetLineColor(ROOT.kBlue)
  trans = TColor.GetColorTransparent(ROOT.kWhite, 0.00001);
  fit_x3.SetLineColor(trans)
  
  #print fit_x3.Eval(1000)
  fit_x3.SetParameters(1.0,0.01)
  start = histtmp.GetBinCenter(histtmp.FindFirstBinAbove(0.75))
  print "Starting point = %s" %start
  eff.Fit(fit_x3, "+","",start,end)
  fit = eff.GetFunction("fit_x3")
  print fit
  mass = fit.GetX(0.9900, start, end, 1.E-10, 100, False)
  print "99 percent efficient at mass:"
  print mass
  print "######"
  #l.AddEntry(eff, "%s: >99 %% : M_{jj} > %.0f GeV" %(histtmp.GetTitle(),mass), "lep" )
  l.AddEntry(0, ">99%%: m_{jj} > %.0f GeV" %(mass), "" )
  return fit
    


def getTriggerEff(trigger,f):
    denom = f.Get("PFHT650_VV");
    num = f.Get(trigger);
    eff = ROOT.TEfficiency(num,denom);
    return eff;

if __name__== '__main__':
    
    line = TLine(1050,0,1050,1.2)
    line.SetLineWidth(2)
    line.SetLineColor(ROOT.kRed)

    fname  = options.filename
    outdir = options.outdir
    suffix = options.suffix
    isMC   = True;
    if options.isMC=="False":
        isMC = False;
    print isMC
    
    inputdir = "../../AnalysisOutput/80X/Data/"
    inputdir = "/storage/jbod/dschaefer/AnalysisOutput/80X/Data/SingleMuon/"
    f = openRootFile(fname,inputdir)
    
    #e = getTriggerEff("HT800_noTag",f)
    
    #denom = f.Get("PFHT650_noTag");
    #num = f.Get("HT800_noTag");
    
    
    
    
    
    
    
    #c = TCanvas("c1","c1",800,800)
    #c.Divide(2,2)
    #c.cd(1)
    #denom.Draw()
    #c.cd(2)
    #num.Draw()
    #c.cd(3)
    #e.Draw()
    #c.cd(4)
    #num.Divide(denom)
    #num.Draw()
    #time.sleep(10)
    
    outpath="../results/plots/trigger/"
    outpath="../results/plots/trigger/SingleMuon/BaseHLT_Mu50/"
    file = TFile.Open(inputdir+fname, 'READ')   
    palette = get_palette('gv')
    col = ROOT.TColor()
    markerStyles = [20,21,22]

    colorcodes = [18,17,16,15,11,20,23,29,30,32]
    pal = array('i', colorcodes)
    gStyle.SetPalette(10,pal)
    
    # #-------------------------Pt vs SD-------------------------------#

    #histoname = 'PtvsMSD_num'

    #rbin = 2
    #bin1 = 200
    #bin2 = 850
    #label = 'p_{T} (GeV)'
    #addInfo1 = "p_{T} > 200 GeV, |#eta| < 2.5"
    #addInfo2 = 'NUM = PF360TrimMass30'
    #addInfo3 = 'DEN = PF320'
    #hnum = TH2F(file.Get('PtvsMSD_num')) #PtvsMPR_den
    #hden = TH2F(file.Get('PtvsMSD_den')) #PtvsMPR_den
    #hden.GetXaxis().SetRangeUser(bin1,bin2)
    #l=getLegend()
    #hnum.Divide(hden)

    #c = getCanvas()
    #hnum.Draw("COLZ")

    #turnon = hnum.FindFirstBinAbove(0.9999,2)
    #print turnon
    #print turnon
    #turnon = hnum.FindFirstBinAbove(0.9999,1)
    #print turnon
    #print turnon
    #turnon = hnum.FindFirstBinAbove(0.9999)
    #print turnon
    #print turnon
    #formatGraph(c,hnum,label,bin1,bin2)
    #hnum.GetYaxis().SetTitle("PUPPI softdrop mass (GeV)")
    #hnum.GetYaxis().SetRangeUser(0.,150.)
    #hnum.GetYaxis().SetNdivisions(308)
    #addInfo = getPave()
    #addInfo.AddText(addInfo1)
    #addInfo.AddText(addInfo2)
    #addInfo.AddText(addInfo3)
    #addInfo.Draw()
    #hnum.SetMaximum(1.0)
    #c.Update()

    #if options.save:
        #canvasname ="%striggereff-2DsdmassVSpt.pdf"%outpath
        #print "saving to Canvas  %s" %canvasname
        #c.Print(canvasname,"pdf")
        #c.Print(canvasname.replace(".pdf",".root"),"root")
    #time.sleep(options.time)
    #del c, l, hden, hnum

#-------------------------HT vs SD-------------------------------#
    #histonames = ['HT800_vsSD']

    #rbin = 2
    #bin1 = 0
    #bin2 = 210
    #label = 'PUPPI softdrop mass (GeV)'
    #addInfo1 = "p_{T} > 200 GeV, |#eta| < 2.5"
    #addInfo2 = ''
    #hden = TH1F(file.Get('PFHT650_vsSD'))
    #hden.GetXaxis().SetRangeUser(bin1,bin2)
    #hden.Rebin(rbin)
    #l=getLegend()

    #i=0
    #mg =  TMultiGraph()
    #for h in histonames:
        #histtmp = TH1F(file.Get(h))
        #histtmp.GetXaxis().SetRangeUser(bin1,bin2)
        #name = 'hnew%i'%i
        #histtmp.Rebin(rbin)
        #eff =  TGraphAsymmErrors()
        #eff.Divide(histtmp,hden)
        #histtmp.Divide(hden)
        #setEffStyle(eff,col.GetColor(palette[i]),markerStyles[i])
        ## myfit = doFit(eff,l,histtmp,100)
        #mg.Add(eff)
        #l.AddEntry(0,"","")
        #l.AddEntry(eff, histtmp.GetTitle(), "lep" )
        #l.AddEntry(0,"","")
        #i += 1

    #c = getCanvas()
    #mg.Draw("AP")
    #l.Draw("same")

    #formatGraph(c,mg,label,bin1,bin2)
    #mg.SetMinimum(0.90)
    #mg.SetMaximum(1.10)
    #addInfo = getPave()
    #addInfo.AddText(addInfo1)
    #addInfo.AddText(addInfo2)
    #addInfo.Draw()
    #c.Update()
    #if options.save:
        #canvasname ="%striggereff-HTvssdmass.pdf"%outpath
        #print "saving to Canvas  %s" %canvasname
        #c.Print(canvasname,"pdf")
        #c.Print(canvasname.replace(".pdf",".root"),"root")
    #time.sleep(options.time)
    #del c, l, mg, addInfo, hden, histtmp

#-------------------------vs SD-------------------------------#
    if (options.plot).find("SD")!=-1 or (options.plot).find("all")!=-1:
        histonames = ['PFJet360_Trim_SD']#['Substructure_SD','PFJet360_Trim_SD','HT700_Trim_SD']

        rbin = 2
        bin1 = 0
        bin2 = 210
        label = 'PUPPI softdrop mass (GeV)'
        addInfo1 = "p_{T} > 200 GeV, |#eta| < 2.5"
        addInfo2 = ''
        hden = TH1F(file.Get('PFJet320_SD'))
        hden.GetXaxis().SetRangeUser(bin1,bin2)
        hden.Rebin(rbin)
        l=getLegend()

        i=0
        mg =  TMultiGraph()
        for h in histonames:
            histtmp = TH1F(file.Get(h))
            histtmp.GetXaxis().SetRangeUser(bin1,bin2)
            name = 'hnew%i'%i
            histtmp.Rebin(rbin)
            eff =  TGraphAsymmErrors()
            eff.Divide(histtmp,hden)
            histtmp.Divide(hden)
            setEffStyle(eff,col.GetColor(palette[i]),markerStyles[i])
            if options.run.find("H")!=-1:
                if i==2:
                    myfit = doFit(eff,l,histtmp,110) 
                else:
                    myfit = doFit(eff,l,histtmp,90)
            else:
                myfit = doFit(eff,l,histtmp,100)
            mg.Add(eff)
            #l.AddEntry(0,"","")
            if histtmp.GetTitle().find("HT700_Trim")!=-1:
                l.AddEntry(eff,"AK8HT700_TrimMass50", "lep" )
            else:
                l.AddEntry(eff, histtmp.GetTitle(), "lep" )
            #l.AddEntry(0,"","")
            i += 1

        c = getCanvas()
        mg.Draw("AP")
        l.Draw("same")

        formatGraph(c,mg,label,bin1,bin2)
        addInfo = getPave()
        addInfo.AddText(addInfo1)
        addInfo.AddText(addInfo2)
        addInfo.Draw()
        c.Update()
        if options.save:
            canvasname ="%striggereff-sdmass_run%s.pdf"%(outpath,options.run)
            print "saving to Canvas  %s" %canvasname
            c.Print(canvasname,"pdf")
            c.Print(canvasname.replace(".pdf",".root"),"root")
        time.sleep(options.time)
        del c, l, mg, addInfo, hden, histtmp

    
    #ctmp =TCanvas("ctmp","ctmp",400,400)
    #htmp = TH1F(file.Get('Substructure_SD'))
    #htmp.Draw();
    
    #============================ NO V tag ==================================================================
    if (options.plot).find("turnOn")!=-1 or (options.plot).find("all")!=-1:
        label = 'Dijet invariant mass (GeV)'
        addInfo1 = "No V tag"
        addInfo2 = ''

        bins1 = range (700,1100,20)
        bins2 = range (1100,1300,50)
        bins3 = range (1300,2100,100)
        bins = []
        bins = bins1
        bins += bins2
        bins += bins3
        # bins = [650.,675., 720., 800.,850., 900.,950.,975., 1000.,1025.,1050.,1075.,1100.,1150., 1200.,1300.,1400.,1500,1600., 2000.]
        runArray = array('d',bins)
        binnum = len(bins)-1

        
        #denom = f.Get("PFHT650_noTag");
        #num = f.Get("HT800_noTag");
        
        #denom.Rebin(binnum,"denom",runArray)
        #num.Rebin(binnum,"num",runArray)
        #bla = num.Clone("bla")
        
        
        
        
        
        #c = TCanvas("c1","c1",800,800)
        #c.Divide(2,2)
        #c.cd(1)
        #denom.Draw("HIST")
        #c.cd(2)
        #num.Draw("HIST")
        #c.cd(3)
        ##e.Draw("HIST")
        #c.cd(4)
        #bla.Divide(denom)
        #bla.Draw("HIST")
        #time.sleep(10)
    
    
    #============================ No tag =========================================================================================
        hden = TH1F(file.Get('PFHT650_noTag'))
        hden = hden.Rebin(binnum,"hden",runArray)

        histonames1 = ['HT800_noTag','HT650_MJJ900_noTag','HT_noTag']
        histonames2 = ['PFJet360_Trim_noTag', 'HT700_Trim_noTag','Substructure_noTag']
        histonames3 = ['ALL_noTag','HT_noTag','Substructure_noTag']

        addInfo = getPave()
        addInfo.AddText(addInfo1)
        addInfo.AddText(addInfo2)


        bin1 = 600
        bin2 = 2200

        #-------ALL-------
        l=getLegend()
        i=0
        mg =  TMultiGraph()
        print hden
        for h in histonames3:
            print h
            print  TH1F(file.Get(h))
            
        
        for h in histonames3:
            print h
            histtmp = TH1F(file.Get(h))
            histtmp.GetXaxis().SetRangeUser(bin1,bin2)
            name = 'hnew%i'%i
            histtmp = histtmp.Rebin(binnum,name,runArray)
            eff =  TGraphAsymmErrors()
            eff.Divide(histtmp,hden)
            histtmp.Divide(hden)
            setEffStyle(eff,col.GetColor(palette[i]),markerStyles[i])
            if i==1:
                histtmp.SetTitle("OR H_{T}")
            if i==2:
                histtmp.SetTitle("OR trimmed mass")
            myfit = doFit(eff,l,histtmp,1300.)
            mg.Add(eff)
            l.AddEntry(eff, histtmp.GetTitle(), "lep" )
            i += 1

        c = getCanvas()
        mg.Draw("AP")
        l.Draw("same")

        formatGraph(c,mg,label,bin1,bin2)
        mg.GetXaxis().SetNdivisions(404)
        addInfo.Draw()
        c.Update()
        if options.save:
            canvasname ="%striggereffMjj-ALL_noTag_run%s.pdf"%(outpath, options.run)
            print "saving to Canvas  %s" %canvasname
            c.Print(canvasname,"pdf")
            c.Print(canvasname.replace(".pdf",".root"),"root")
            time.sleep(options.time) 
            del c, l, mg, histtmp
        

    
     # #-------HT based-------
        l=getLegend()
        i=0
        mg =  TMultiGraph()
        for h in histonames1:
                histtmp = TH1F(file.Get(h))
                histtmp.GetXaxis().SetRangeUser(bin1,bin2)
                name = 'hnew%i'%i
                histtmp = histtmp.Rebin(binnum,name,runArray)
                eff =  TGraphAsymmErrors()
                eff.Divide(histtmp,hden)
                histtmp.Divide(hden)
                setEffStyle(eff,col.GetColor(palette[i]),markerStyles[i])
                myfit = doFit(eff,l,histtmp,1250)
                mg.Add(eff)
                if options.run =="H" and histtmp.GetTitle().find("HT800")!=-1:
                    l.AddEntry(eff, "HT900", "lep" )
                else:
                    l.AddEntry(eff, histtmp.GetTitle(), "lep" )
                i += 1
        
        c = getCanvas()
        mg.Draw("AP")
        l.Draw("same")
     
        formatGraph(c,mg,label,bin1,bin2)
        mg.GetXaxis().SetNdivisions(404)
        addInfo.Draw()
        c.Update()
        if options.save:
                canvasname ="%striggereffMjj-HT_noTag_run%s.pdf"%(outpath,options.run)
                print "saving to Canvas  %s" %canvasname
                c.Print(canvasname,"pdf")
                c.Print(canvasname.replace(".pdf",".root"),"root")
        time.sleep(options.time)
        del c, l, mg, histtmp
     
     #-------SUBSTRUCTURE based-------
        l=getLegend()
        i=0
        mg =  TMultiGraph()
        for h in histonames2:
                histtmp = TH1F(file.Get(h))
                histtmp.GetXaxis().SetRangeUser(bin1,bin2)
                name = 'hnew%i'%i
                histtmp = histtmp.Rebin(binnum,name,runArray)
                eff =  TGraphAsymmErrors()
                eff.Divide(histtmp,hden)
                histtmp.Divide(hden)
                setEffStyle(eff,col.GetColor(palette[i]),markerStyles[i])
                #myfit = doFit(eff,l,histtmp,1250.)
                mg.Add(eff)
                if histtmp.GetTitle().find("HT700_Trim")!=-1:
                    l.AddEntry(eff,"AK8HT700_TrimMass50", "lep" )
                else:
                    l.AddEntry(eff, histtmp.GetTitle(), "lep" )
                #l.AddEntry(eff, histtmp.GetTitle(), "lep" )
                i += 1
        time.sleep(options.time)
        c = getCanvas()
        mg.Draw("AP")
        l.Draw("same")
        
        formatGraph(c,mg,label,bin1,bin2)
        mg.GetXaxis().SetNdivisions(404)
        addInfo.Draw()
        c.Update()
        if options.save:
            canvasname ="%striggereffMjj-SUBST_noTag_run%s.pdf"%(outpath,options.run)
            print "saving to Canvas  %s" %canvasname
            c.Print(canvasname,"pdf")
            c.Print(canvasname.replace(".pdf",".root"),"root")
            time.sleep(options.time)
        del c, l, mg, hden, histtmp


    
    # #-------------------------vs Mjj, Double V tag-------------------------------#
        label = 'Dijet invariant mass (GeV)'
        addInfo1 = "Double V tag"
        addInfo2 = '65 < m_{jet,1/2} < 105 GeV'
        
        bins1 = range (700,1100,40)
        bins2 = range (1100,1300,60)
        bins3 = range (1300,2100,120)
        bins = []
        bins = bins1
        bins += bins2
        bins += bins3
        # bins = [650.,675., 720., 800.,850., 900.,950.,975., 1000.,1025.,1050.,1075.,1100.,1150., 1200.,1300.,1400.,1500,1600., 2000.]
        runArray = array('d',bins)
        binnum = len(bins)-1
        
        hden = TH1F(file.Get('PFHT650_VV'))
        hden = hden.Rebin(binnum,"hden",runArray)
        
        histonames1 = ['HT800_VV','HT650_MJJ900_VV','HT_VV']
        histonames2 = ['PFJet360_Trim_VV', 'HT700_Trim_VV','Substructure_VV']
        histonames3 = ['ALL_VV','HT_VV','Substructure_VV']
        
        addInfo = getPave()
        addInfo.AddText(addInfo1)
        addInfo.AddText(addInfo2)
    
    # #-------HT based-------
        l=getLegend()
        i=0
        mg =  TMultiGraph()
        for h in histonames1:
            histtmp = TH1F(file.Get(h))
            histtmp.GetXaxis().SetRangeUser(bin1,bin2)
            name = 'hnew%i'%i
            histtmp = histtmp.Rebin(binnum,name,runArray)
            eff =  TGraphAsymmErrors()
            eff.Divide(histtmp,hden)
            histtmp.Divide(hden)
            setEffStyle(eff,col.GetColor(palette[i]),markerStyles[i])
            myfit = doFit(eff,l,histtmp,1250.)
            mg.Add(eff)
            if options.run =="H" and histtmp.GetTitle().find("HT800")!=-1:
                    l.AddEntry(eff, "HT900", "lep" )
            else:
                    l.AddEntry(eff, histtmp.GetTitle(), "lep" )
            #l.AddEntry(eff, histtmp.GetTitle(), "lep" )
            i += 1
        
        c = getCanvas()
        mg.Draw("AP")
        l.Draw("same")
    
        formatGraph(c,mg,label,bin1,bin2)
        mg.GetXaxis().SetNdivisions(404)
        line2 = TLine(650,1,2050,1)
        line2.SetLineStyle(2)
        line2.Draw('same')
        
        addInfo.Draw()
        c.Update()
        if options.save:
            canvasname ="%striggereffMjj-HT_DoubleTag_run%s.pdf"%(outpath,options.run)
            print "saving to Canvas  %s" %canvasname
            c.Print(canvasname,"pdf")
            c.Print(canvasname.replace(".pdf",".root"),"root")
            time.sleep(options.time)
        del c, l, mg, hden, histtmp
    #
    # #-------SUBSTRUCTURE based-------
        hden = TH1F(file.Get('PFHT650_VV'))
        hden = hden.Rebin(binnum,"hden",runArray)
        l=getLegend()
        i=0
        mg =  TMultiGraph()
        for h in histonames2:
                histtmp = TH1F(file.Get(h))
                histtmp.GetXaxis().SetRangeUser(bin1,bin2)
                name = 'hnew%i'%i
                histtmp = histtmp.Rebin(binnum,name,runArray)
                eff =  TGraphAsymmErrors()
                eff.Divide(histtmp,hden)
                histtmp.Divide(hden)
                setEffStyle(eff,col.GetColor(palette[i]),markerStyles[i])
                myfit = doFit(eff,l,histtmp,1250.)
                mg.Add(eff)
                if histtmp.GetTitle().find("HT700_Trim")!=-1:
                    l.AddEntry(eff,"AK8HT700_TrimMass50", "lep" )
                else:
                    l.AddEntry(eff, histtmp.GetTitle(), "lep" )
                #l.AddEntry(eff, histtmp.GetTitle(), "lep" )
                i += 1
        
        c = getCanvas()
        mg.Draw("AP")
        l.Draw("same")
        
        formatGraph(c,mg,label,bin1,bin2)
        mg.GetXaxis().SetNdivisions(404)
        addInfo.Draw()
        c.Update()
        if options.save:
            canvasname ="%striggereffMjj-SUBST_DoubleTag_run%s.pdf"%(outpath,options.run)
            print "saving to Canvas  %s" %canvasname
            c.Print(canvasname,"pdf")
            time.sleep(options.time)
        del c, l, mg, hden, histtmp

    #-------ALL-------
        hden = TH1F(file.Get('PFHT650_VV'))
        hden = hden.Rebin(binnum,"hden",runArray)
        l=getLegend()
        i=0
        mg =  TMultiGraph()
        for h in histonames3:
                histtmp = TH1F(file.Get(h))
                histtmp.GetXaxis().SetRangeUser(bin1,bin2)
                name = 'hnew%i'%i
                histtmp = histtmp.Rebin(binnum,name,runArray)
                eff =  TGraphAsymmErrors()
                eff.Divide(histtmp,hden)
                histtmp.Divide(hden)
                setEffStyle(eff,col.GetColor(palette[i]),markerStyles[i]) 
                if i==0:
                    histtmp.SetTitle("All triggers")
                if i==1:
                    histtmp.SetTitle("H_{T}-based triggers")
                if i==2:
                    histtmp.SetTitle("Substructure triggers")
                l.AddEntry(eff, histtmp.GetTitle(), "lep" )    
                myfit = doFit(eff,l,histtmp,1250.)
                mg.Add(eff)
                i += 1

        c = getCanvas()
        mg.Draw("AP")
        l.Draw("same")
        line.Draw("same")

        formatGraph(c,mg,label,bin1,bin2)
        mg.GetXaxis().SetNdivisions(404)
        addInfo.Draw()
        line2 = TLine(650,1,2050,1)
        line2.SetLineStyle(2)
        line2.Draw('same')

        c.Update()
        if options.save:
            canvasname ="%striggereffMjj-ALL_DoubleTag_run%s.pdf"%(outpath,options.run)
            print "saving to Canvas  %s" %canvasname
            c.Print(canvasname,"pdf")
            c.Print(canvasname.replace(".pdf",".root"),"root")
        del c, l, mg, hden, histtmp

        time.sleep(options.time)
    
    
    # #-------------------------vs Mjj, Single V-tag-------------------------------#
        label = 'Dijet invariant mass (GeV)'
        addInfo1 = "Single V tag"
        addInfo2 = '65 < m_{jet} < 105 GeV'
        
        bins1 = range (700,1100,20)
        bins2 = range (1100,1300,50)
        bins3 = range (1300,2100,100)
        bins = []
        bins = bins1
        bins += bins2
        bins += bins3
        # bins = [650.,675., 720., 800.,850., 900.,950.,975., 1000.,1025.,1050.,1075.,1100.,1150., 1200.,1300.,1400.,1500,1600., 2000.]
        runArray = array('d',bins)
        binnum = len(bins)-1
        
        hden = TH1F(file.Get('PFHT650'))
        hden = hden.Rebin(binnum,"hden",runArray)
        
        histonames1 = ['HT800','HT650_MJJ900','HT']
        histonames2 = ['PFJet360_Trim', 'HT700_Trim','Substructure']
        histonames3 = ['ALL','HT','Substructure']
        
        addInfo = getPave()
        addInfo.AddText(addInfo1)
        addInfo.AddText(addInfo2)
        
        # #-------HT based-------
        l=getLegend()
        i=0
        mg =  TMultiGraph()
        for h in histonames1:
            histtmp = TH1F(file.Get(h))
            histtmp.GetXaxis().SetRangeUser(bin1,bin2)
            name = 'hnew%i'%i
            histtmp = histtmp.Rebin(binnum,name,runArray)
            eff =  TGraphAsymmErrors()
            eff.Divide(histtmp,hden)
            histtmp.Divide(hden)
            setEffStyle(eff,col.GetColor(palette[i]),markerStyles[i])
            myfit = doFit(eff,l,histtmp,1250)
            mg.Add(eff)
            if options.run =="H" and histtmp.GetTitle().find("HT800")!=-1:
                    l.AddEntry(eff, "HT900", "lep" )
            else:
                    l.AddEntry(eff, histtmp.GetTitle(), "lep" )
            #l.AddEntry(eff, histtmp.GetTitle(), "lep" )
            i += 1
    
        c = getCanvas()
        mg.Draw("AP")
        l.Draw("same")
        
        formatGraph(c,mg,label,bin1,bin2)
        mg.GetXaxis().SetNdivisions(404)
        addInfo.Draw()
        c.Update()
        if options.save:
            canvasname ="%striggereffMjj-HT_SingleTag_run%s.pdf"%(outpath,options.run)
            print "saving to Canvas  %s" %canvasname
            c.Print(canvasname,"pdf")
            c.Print(canvasname.replace(".pdf",".root"),"root")
        time.sleep(options.time)
        del c, l, mg, histtmp
    
    #-------SUBSTRUCTURE based-------
        l=getLegend()
        i=0
        mg =  TMultiGraph()
        for h in histonames2:
            histtmp = TH1F(file.Get(h))
            histtmp.GetXaxis().SetRangeUser(bin1,bin2)
            name = 'hnew%i'%i
            histtmp = histtmp.Rebin(binnum,name,runArray)
            eff =  TGraphAsymmErrors()
            eff.Divide(histtmp,hden)
            histtmp.Divide(hden)
            setEffStyle(eff,col.GetColor(palette[i]),markerStyles[i])
            myfit = doFit(eff,l,histtmp,1250.)
            mg.Add(eff)
            if histtmp.GetTitle().find("HT700_Trim")!=-1:
                l.AddEntry(eff,"AK8HT700_TrimMass50", "lep" )
            else:
                l.AddEntry(eff, histtmp.GetTitle(), "lep" )
            #l.AddEntry(eff, histtmp.GetTitle(), "lep" )
            i += 1
        time.sleep(options.time)
        c = getCanvas()
        mg.Draw("AP")
        l.Draw("same")
        
        formatGraph(c,mg,label,bin1,bin2)
        mg.GetXaxis().SetNdivisions(404)
        addInfo.Draw()
        line2 = TLine(650,1,2050,1)
        line2.SetLineStyle(2)
        line2.Draw('same')
        c.Update()
        if options.save:
            canvasname ="%striggereffMjj-SUBST_SingleTag_run%s.pdf"%(outpath,options.run)
            print "saving to Canvas  %s" %canvasname
            c.Print(canvasname,"pdf")
            c.Print(canvasname.replace(".pdf",".root"),"root")
        time.sleep(options.time)
        del c, l, mg, histtmp
    
    #-------ALL-------
        l=getLegend()
        i=0
        mg =  TMultiGraph()
        for h in histonames3:
            histtmp = TH1F(file.Get(h))
            histtmp.GetXaxis().SetRangeUser(bin1,bin2)
            name = 'hnew%i'%i
            histtmp = histtmp.Rebin(binnum,name,runArray)
            eff =  TGraphAsymmErrors()
            eff.Divide(histtmp,hden)
            histtmp.Divide(hden)
            setEffStyle(eff,col.GetColor(palette[i]),markerStyles[i])
            if i==0:
                histtmp.SetTitle("All triggers")
            if i==1:
                histtmp.SetTitle("H_{T}-based triggers")
            if i==2:
                histtmp.SetTitle("Substructure triggers")
            l.AddEntry(eff, histtmp.GetTitle(), "lep" )
            myfit = doFit(eff,l,histtmp,1250.)
            mg.Add(eff)
            i += 1
    
        c = getCanvas()
        mg.Draw("AP")
        l.Draw("same")
        line.Draw("same")
        
        formatGraph(c,mg,label,bin1,bin2)
        mg.GetXaxis().SetNdivisions(404)
        addInfo.Draw()
        line2.Draw('same')
        c.Update()
        if options.save:
            canvasname ="%striggereffMjj-ALL_SingleTag_run%s.pdf"%(outpath,options.run)
            print "saving to Canvas  %s" %canvasname
            c.Print(canvasname,"pdf")
            c.Print(canvasname.replace(".pdf",".root"),"root")
        time.sleep(options.time) 
        del c, l, mg, hden, histtmp
    
    
    
    time.sleep(40)
    
