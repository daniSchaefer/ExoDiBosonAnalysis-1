import ROOT
from ROOT import *
import time
import CMS_lumi, tdrstyle
#!/usr/bin/python
from array import *
from optparse import OptionParser


parser = OptionParser()
parser.add_option('--signal',dest="signal", default="BulkWW", action="store", help="Use signal samples model specified with --signal")
parser.add_option('--region',dest="region", default="VV", action="store", help="Use VV,WW,WZ or ZZ mass window (for VV dijet samples)")
parser.add_option('--bkg',dest="background",default='', action="store",help="calculate efficiency for QCD background samples")
parser.add_option('--ALL',dest="ALL",default=False, action="store_true",help="make efficiency*acceptance plot for all models instead")


(options, args) = parser.parse_args()

tdrstyle.setTDRStyle()
gStyle.SetOptFit(0) 
CMS_lumi.lumi_13TeV = ""
CMS_lumi.writeExtraText = 1
CMS_lumi.extraText = "Simulation"
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

def get_palette(mode):

 palette = {}
 palette['gv'] = [] 
 
 colors = ['#1b7837','#00441b','#92c5de','#4393c3','#2166ac','#053061']
 colors = ['#1b7837','#053061','#2166ac','#92c5de','#92c5de','#4393c3','#4393c3','#2166ac','#2166ac','#053061','#053061']

 for c in colors:
  palette['gv'].append(c)
 
 return palette[mode]
 
channel = options.region

palette = get_palette('gv')
col = TColor()
markerStyle = [20,24,22,26,33,27,20]
legend = [channel+" HP,HP",channel+" HP,LP",channel+" LP,LP"]
if options.region.find("q")!=-1:
    legend = [channel+" HP",channel+"LP",channel+"NP"]
path = "../results/"




def printDiff(g1,g2,masses):
    print "difference in % "
    for m in masses:
        diff = (g1.Eval(m)-g2.Eval(m))/g1.Eval(m)
        diff = diff*100
        print diff
    print "graph 1 : "
    for m in masses:
        print g1.Eval(m)
    print "graph 2 : "
    for m in masses:
        print g2.Eval(m)
        
        










def getEfficiencyAcceptance(signal,channel):
        filename = "Signal_"+signal+"_M"  #Signal_BulkWW_13TeV_1000GeV.VV.root
        #filename2 = "QCD_HTbinned_"+channel+"_SB.root"
        if options.background!='':
            filename = "Signal_QCD_pythia8_forEff_VVdijet.root"


        fBins =[1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607, 1687, 1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010]

                
        mg =  []
        masses=[1200,1400,1800,2000,2500,3500,4000]
        histos = [channel+"HPHP",channel+"LPHP",channel+"LPLP"]
        if options.region.find("qV")!=-1:
            histos = [channel+"HP",channel+"LP",channel+"NP"]
            masses=[1200,1400,1800,2000,2500,3000,4500,6000]

        i = -1 

       
        #masses=[1000,1200,2000,2500,3000] #for BulkWW
        HPHP=[]
        LPHP=[]
        LPLP=[]
        HPHP_err=[]
        LPHP_err=[]
        LPLP_err=[]
        m_err=[]
        HPplusLP =[]
        HPplusLPplusLPLP =[]
        HPplusLPLP =[]
        HPplusLP_err =[]
        HPplusLPplusLPLP_err =[]
        HPplusLPLP_err =[]
        acc = []
        acc_err = []

        if options.background=="":
            for m in masses:
                filename1=filename+str(int(m))+".root"
                f = ROOT.TFile(path+filename1)
                #print f
                nEvents =[]
                for h in histos:
                    numtmp = f.Get(h)
                    nEvents.append(numtmp.Integral())
                    #print numtmp
                dentmp =  f.Get('Mjj')
                print nEvents
                #gentmp =  f.Get("Mjj_allHadGen")
                #print gentmp
                #del f
                den = dentmp.Integral()
                #print signal+"   "+str( den)+"    "+str(dentmp.GetEntries())+ "   acc "+str(den/30000.)
                #den = 30000.
                numberGenEvents = 30000.#float(gentmp.GetEntries())
                if signal.find("BulkWW")!=-1 or signal.find("Zprime")!=-1:
                    numberGenEvents = numberGenEvents*0.66*0.66
                    
                print numberGenEvents
                acc.append(dentmp.GetEntries()/numberGenEvents)
                acc_err.append(ROOT.TMath.Sqrt(den)/numberGenEvents+ ROOT.TMath.Sqrt(numberGenEvents)*den/pow(numberGenEvents,2))
                HPHP.append(nEvents[0]/den)
                LPHP.append(nEvents[1]/den)
                LPLP.append(nEvents[2]/den)
                HPHP_err.append(ROOT.TMath.Sqrt(nEvents[0])/den+ ROOT.TMath.Sqrt(den)*nEvents[0]/(den*den))
                LPHP_err.append(ROOT.TMath.Sqrt(nEvents[1])/den+ ROOT.TMath.Sqrt(den)*nEvents[1]/(den*den))
                LPLP_err.append(ROOT.TMath.Sqrt(nEvents[2])/den+ ROOT.TMath.Sqrt(den)*nEvents[2]/(den*den))
            
                HPplusLP.append((nEvents[0]+nEvents[1])/den)
                HPplusLPplusLPLP.append((nEvents[1]+nEvents[0]+nEvents[2])/den)
                HPplusLPLP.append((nEvents[0]+nEvents[2])/den)
                HPplusLP_err.append((ROOT.TMath.Sqrt(nEvents[0]+nEvents[1]))/den+ ROOT.TMath.Sqrt(den)*nEvents[0]/(den*den))
                HPplusLPplusLPLP_err.append(ROOT.TMath.Sqrt(nEvents[1]+nEvents[0]+nEvents[2])/den+ ROOT.TMath.Sqrt(den)*nEvents[1]/(den*den))
                HPplusLPLP_err.append(ROOT.TMath.Sqrt(nEvents[2]+nEvents[0])/den+ ROOT.TMath.Sqrt(den)*nEvents[2]/(den*den))
            
                print nEvents[2]/((nEvents[0]+nEvents[1])/100.)
                m_err.append(0.)
        else:
            masses = [1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500]
            m_err = [0,0,0,0,0,0,0,0,0,0,0]
            massBins = array('d',masses)
            f = ROOT.TFile(path+filename)
            for h in histos:
                dentmp = f.Get("Mjj")
                numtmp = f.Get(h)
                dentmp.Sumw2()
                numtmp.Sumw2()
                # dentmp.Scale(1./dentmp.Integral())
                # numtmp.Scale(1./numtmp.Integral())
                den = dentmp.Rebin(len(massBins)-1,"den_rebinned",massBins)
                num = numtmp.Rebin(len(massBins)-1,"num_rebinned",massBins)
                for b in range(1,num.GetNbinsX()+1):
                    if h.find("HPHP")!=-1:
                        nt = num.GetBinContent(b)
                        dt = den.GetBinContent(b)
                        HPHP.append(nt/dt)
                        err = nt/pow(dt,2)+ pow(nt,2)/pow(dt,3)
                        HPHP_err.append(err)
                    if h.find("LPHP")!=-1:
                        LPHP.append(num.GetBinContent(b)/den.GetBinContent(b))
                        nt = num.GetBinContent(b)
                        dt = den.GetBinContent(b)
                        err = nt/pow(dt,2)+ pow(nt,2)/pow(dt,3)
                        LPHP_err.append(err)
                    if h.find("LPLP")!=-1:
                        nt = num.GetBinContent(b)
                        dt = den.GetBinContent(b)
                        err = nt/pow(dt,2)+ pow(nt,2)/pow(dt,3)
                        LPLP.append(num.GetBinContent(b)/den.GetBinContent(b))
                        LPLP_err.append(err)
        return [masses, m_err,HPHP,LPHP, LPLP, HPHP_err, LPHP_err, LPLP_err, HPplusLP, HPplusLPplusLPLP , HPplusLPLP, HPplusLP_err,  HPplusLPplusLPLP_err ,HPplusLPLP_err ,acc ,acc_err]
        

if __name__=="__main__":
    if options.ALL == False:
        signal  = options.signal
        sigchannel="WW"
        model = "G_{Bulk} to WW"
        if signal.find("Zprime")!=-1:
            model = "Z' to WW"
            
        if signal.find("BulkZZ")!=-1:
            model = "G_{Bulk} to ZZ"
        if signal.find("Wprime")!=-1:
            model = "W' to WZ"
        if signal.find("RS")!=-1:
            model = "G_{RS}"
        
        l = TLegend(0.6,0.7215026,0.9296482,0.9093264)
        l.SetTextSize(0.033)
        l.SetLineColor(0)
        l.SetShadowColor(0)
        l.SetLineStyle(1)
        l.SetLineWidth(1)
        l.SetFillColor(0)
        l.SetFillStyle(0)
        l.SetMargin(0.35)
        # addInfo = TPaveText(0.6984925,0.5854922,0.9886935,0.7020725,"NDC")
        addInfo = TPaveText(0.16,0.7914508,0.7072864,0.9080311,"NDC")
        addInfo.SetFillColor(0)
        addInfo.SetLineColor(0)
        addInfo.SetFillStyle(0)
        addInfo.SetBorderSize(0)
        addInfo.SetTextFont(42)
        addInfo.SetTextSize(0.030)
        addInfo.SetTextAlign(12)
        # addInfo.AddText("W-jet")
        if options.background!='':
            addInfo.AddText("QCD pythia8")
        else:
            addInfo.AddText("model: "+model+", mass region: "+channel)

        #addInfo.AddText("p_{T} > 200 GeV, |#eta| < 2.5 GeV")
        #addInfo.AddText("M_{jj} > 1.055 TeV")
        
        result = getEfficiencyAcceptance(options.signal,sigchannel)
        
        a= array('f',result[0])
        b= array('f')
        b.fromlist(result[2])
        c= array('f')
        c.fromlist(result[1])
        d= array('f')
        d.fromlist(result[5])
        n = len(result[0])

        gHPHP = TGraphErrors(n,a,b,c,d)
        gLPHP = TGraphErrors(n,array('f',result[0]),array('f',result[3]),array('f',result[1]),array('f',result[6]))
        gLPLP = TGraphErrors(n,array('f',result[0]),array('f',result[4]),array('f',result[1]),array('f',result[7]))

        canvas = TCanvas("c","c",W,H)

        #canvas.SetLogy()

        gHPHP.SetMarkerColor(col.GetColor(palette[0]))
        gHPHP.SetLineColor(col.GetColor(palette[0]))
        gHPHP.SetLineWidth(2)
        gHPHP.SetMarkerSize(2)
        gHPHP.SetMarkerStyle(markerStyle[0])

        gLPHP.SetMarkerColor(col.GetColor(palette[1]))
        gLPHP.SetLineColor(col.GetColor(palette[1]))
        gLPHP.SetLineWidth(2)
        gLPHP.SetMarkerSize(2)
        gLPHP.SetMarkerStyle(markerStyle[1])

        gLPLP.SetMarkerColor(col.GetColor(palette[2]))
        gLPLP.SetLineColor(col.GetColor(palette[2]))
        gLPLP.SetLineWidth(2)
        gLPLP.SetMarkerSize(2)
        gLPLP.SetMarkerStyle(markerStyle[2])

        gHPHP.SetMinimum(0.0)
        gHPHP.SetMaximum(0.6)
        if options.background!="":
                gHPHP.SetMaximum(0.02)
        gHPHP.GetXaxis().SetTitleSize(0.06)
        gHPHP.GetXaxis().SetTitleOffset(0.95)
        gHPHP.GetXaxis().SetLabelSize(0.05)
        gHPHP.GetYaxis().SetTitleSize(0.06)
        gHPHP.GetYaxis().SetLabelSize(0.05)
        gHPHP.GetXaxis().SetTitle("M_{VV} (GeV)")
        gHPHP.GetYaxis().SetTitle("MC efficiency")
        gHPHP.GetYaxis().SetNdivisions(304)
        gHPHP.GetXaxis().SetNdivisions(308)

        gHPHP.GetXaxis().SetNdivisions(5)
        gHPHP.Draw("ALP")
        gLPHP.Draw("sameLP")
        gLPLP.Draw("sameLP")

        CMS_lumi.CMS_lumi(canvas, iPeriod, iPos)
        l2 = TLegend(0.65,0.7215026,0.8596482,0.87093264)
        l2.SetTextSize(0.033)
        l2.SetLineColor(0)
        l2.SetShadowColor(0)
        l2.SetLineStyle(1)
        l2.SetLineWidth(1)
        l2.SetFillColor(0)
        l2.SetFillStyle(0)
        #l2.SetMargin(0.35)
        l2.AddEntry(gHPHP,"%s"%(legend[0]), "pl" )
        l2.AddEntry(gLPHP,"%s"%(legend[1]), "pl" )
        l2.AddEntry(gLPLP,"%s"%(legend[2]), "pl" )
        SetOwnership( l2, 1 )
        addInfo.Draw("same")
        l2.Draw("same")
        canvas.Update()
        canvas.SaveAs("../../AnalysisOutput/figures/"+signal+"_efficiency_perCat_overMass_"+channel+".pdf")

        del canvas
        del l2
        #cname = "../AnalysisOutput/figures/MjjSRvsSB_MVVdist%s_pythia8Madgraph.pdf"%h
        #if options.herwig:
            #cname = "../AnalysisOutput/figures/MjjSRvsSB_MVVdist%s_herwig.pdf"%h
        #if options.ptBinned:
            #cname = "../AnalysisOutput/figures/MjjSRvsSB_MVVdist%s_pythia8.pdf"%h
        #canvas.SaveAs(cname)
        
        time.sleep(10)      

        if options.background=='':
            gacc  = TGraphErrors(n,array('f',result[0]),array('f',result[14]),array('f',result[1]),array('f',result[15]))
            gHPplusLP  = TGraphErrors(n,array('f',result[0]),array('f',result[8]),array('f',result[1]),array('f',result[11]))
            gHPplusLPplusLPLP = TGraphErrors(n,array('f',result[0]),array('f',result[9]),array('f',result[1]),array('f',result[12]))
            gHPplusLPLP       = TGraphErrors(n,array('f',result[0]),array('f',result[10]),array('f',result[1]),array('f',result[13]))
            canvas = TCanvas("c","c",W,H)
            #canvas.SetLogy()

            gHPplusLP.SetMarkerColor(col.GetColor(palette[3]))
            gHPplusLP.SetLineColor(col.GetColor(palette[3]))
            gHPplusLP.SetLineWidth(2)
            gHPplusLP.SetMarkerSize(2)
            gHPplusLP.SetMarkerStyle(markerStyle[3])

            gHPplusLPplusLPLP.SetMarkerColor(col.GetColor(palette[1]))
            gHPplusLPplusLPLP.SetLineColor(col.GetColor(palette[1]))
            gHPplusLPplusLPLP.SetLineWidth(2)
            gHPplusLPplusLPLP.SetMarkerSize(2)
            gHPplusLPplusLPLP.SetMarkerStyle(markerStyle[1])

            gHPplusLPLP.SetMarkerColor(col.GetColor(palette[2]))
            gHPplusLPLP.SetLineColor(col.GetColor(palette[2]))
            gHPplusLPLP.SetLineWidth(2)
            gHPplusLPLP.SetMarkerSize(2)
            gHPplusLPLP.SetMarkerStyle(markerStyle[2])

            gHPHP.SetMinimum(0.0)
            gHPHP.SetMaximum(0.9)
            #gHPHP.GetXaxis().SetTitleSize(0.06)
            #gHPHP.GetXaxis().SetTitleOffset(0.95)
            #gHPHP.GetXaxis().SetLabelSize(0.05)
            #gHPHP.GetYaxis().SetTitleSize(0.06)
            #gHPHP.GetYaxis().SetLabelSize(0.05)
            #gHPHP.GetXaxis().SetTitle("M_{VV} (GeV)")
            #gHPHP.GetYaxis().SetTitle("MC efficiency")
            #gHPHP.GetYaxis().SetNdivisions(304)
            #gHPHP.GetXaxis().SetNdivisions(308)
            gHPHP.GetXaxis().SetNdivisions(5)
            gHPHP.Draw("ALP")
            gHPplusLP.Draw("sameLP")
            gHPplusLPLP.Draw("sameLP")
            gHPplusLPplusLPLP.Draw("sameLP")

            CMS_lumi.CMS_lumi(canvas, iPeriod, iPos)
            l2 = TLegend(0.65,0.7215026,0.8596482,0.87093264)
            l2.SetTextSize(0.033)
            l2.SetLineColor(0)
            l2.SetShadowColor(0)
            l2.SetLineStyle(1)
            l2.SetLineWidth(1)
            l2.SetFillColor(0)
            l2.SetFillStyle(0)
            #l2.SetMargin(0.35)
            l2.AddEntry(gHPHP,"HP", "pl" )
            l2.AddEntry(gHPplusLP,"HP+LP", "pl" )
            l2.AddEntry(gHPplusLPLP,"HP+LPLP", "pl" )
            l2.AddEntry(gHPplusLPplusLPLP,"HP+LP+LPLP", "pl" )
            #SetOwnership( l2, 1 )
            l2.Draw("same")
            addInfo.Draw("same")
            canvas.SaveAs("../../AnalysisOutput/figures/"+signal+"_Addefficiency_perCat_overMass_"+channel+".pdf")

            time.sleep(10)
            del canvas, l2

        #============= plot acceptance: (preselections)/(all gen events)==================================================================

            canvas = TCanvas("c","c",W,H)
            #canvas.SetLogy()

            gacc.SetMarkerColor(col.GetColor(palette[1]))
            gacc.SetLineColor(col.GetColor(palette[1]))
            gacc.SetLineWidth(2)
            gacc.SetMarkerSize(2)
            gacc.SetMarkerStyle(markerStyle[1])

            gacc.SetMinimum(0.0)
            gacc.SetMaximum(0.7)
            if signal.find("Wprime")!=-1 or signal.find("BulkZZ")!=-1:
                gacc.SetMaximum(1.2)
                gacc.SetMinimum(0.6)
            #gHPHP.GetXaxis().SetTitleSize(0.06)
            #gHPHP.GetXaxis().SetTitleOffset(0.95)
            #gHPHP.GetXaxis().SetLabelSize(0.05)
            #gHPHP.GetYaxis().SetTitleSize(0.06)
            #gHPHP.GetYaxis().SetLabelSize(0.05)
            #gHPHP.GetXaxis().SetTitle("M_{VV} (GeV)")
            gacc.GetYaxis().SetTitle("MC acceptance")
            gacc.GetYaxis().SetNdivisions(304)
            gacc.GetXaxis().SetNdivisions(5)
            gacc.Draw("ALP")

            CMS_lumi.CMS_lumi(canvas, iPeriod, iPos)
            l2 = TLegend(0.65,0.7215026,0.8596482,0.87093264)
            l2.SetTextSize(0.033)
            l2.SetLineColor(0)
            l2.SetShadowColor(0)
            l2.SetLineStyle(1)
            l2.SetLineWidth(1)
            l2.SetFillColor(0)
            l2.SetFillStyle(0)
            #l2.SetMargin(0.35)
            l2.AddEntry(gacc,"acceptance", "pl" )
            l2.Draw("same")
            addInfo.Draw("same")
            canvas.SaveAs("../../AnalysisOutput/figures/"+signal+"_acceptance_overMass.pdf")

            time.sleep(10)

    else:
        signals = ["BulkWW","BulkZZ","Zprime",'WprimeWZ']
        sigchannel = "ZZ"
        #signals = ["BulkWW","Zprime","BulkZZ",'WprimeWZ']
        #signals=  ["QstarQW","QstarQZ"]
        
        lentries =[]
        
        
        l = TLegend(0.6,0.7215026,0.9296482,0.9093264)
        l.SetTextSize(0.033)
        l.SetLineColor(0)
        l.SetShadowColor(0)
        l.SetLineStyle(1)
        l.SetLineWidth(1)
        l.SetFillColor(0)
        l.SetFillStyle(0)
        l.SetMargin(0.35)
        
        geff = []
        gacc = []
        geffXacc=[]
        for signal in signals:
            model = "G_{Bulk} to WW"
            if signal.find("Zprime")!=-1:
                model = "Z' to WW"
                
            if signal.find("BulkZZ")!=-1:
                model = "G_{Bulk} to ZZ"
            if signal.find("Wprime")!=-1:
                model = "W' to WZ"
            if signal.find("RS")!=-1:
                model = "G_{RS}"
            lentries.append(model)
        
            result = getEfficiencyAcceptance(signal,sigchannel)
            
            n = len(result[0])
            geff.append(TGraphErrors(n,array('f',result[0]),array('f',result[8]),array('f',result[1]),array('f',result[11])))
            gacc.append(TGraphErrors(n,array('f',result[0]),array('f',result[14]),array('f',result[1]),array('f',result[15])))
            effXacc=[]
            effXacc_err=[]
            for i in range(0,len(result[14])):
                effXacc.append(result[14][i]*result[8][i])
                effXacc_err.append(result[15][i]*result[11][i])
            geffXacc.append(TGraphErrors(n,array('f',result[0]),array('f',effXacc),array('f',result[1]),array('f',effXacc_err)))

        colorlist=[kRed,kRed+2,kRed+4,kBlue,kBlue+2,kBlue+4, kGreen,kGreen+2 ]
        canvas = TCanvas("c","c",W,H)
        geff[0].SetMaximum(1.)
        geff[0].SetMinimum(0.)
        geff[0].SetMarkerStyle(20)
        geff[0].SetMarkerColor(kRed)
        geff[0].SetLineColor(kRed)
        geff[0].SetLineWidth(2)
        geff[0].Draw("ALP")
        geff[0].GetXaxis().SetTitle("mass [GeV]")
        geff[0].GetYaxis().SetTitle("efficiency")
        l.AddEntry(geff[0],lentries[0],"lp" )
        
        for i in range(1,len(geff)):
           l.AddEntry(geff[i],lentries[i],"lp" )
           #geff[i].SetMarkerStyle(20+i)
           geff[i].SetMarkerColor(colorlist[i])
           geff[i].SetMarkerSize(1)
           geff[i].SetLineWidth(2)
           geff[i].SetLineColor(colorlist[i])
           geff[i].Draw("LPsame")
        l.Draw("same")
        canvas.SaveAs("../../AnalysisOutput/figures/efficiecy_overMass.pdf")
        masses=[1200,1400,1600,1800,2000,2500,3000,3500]
        printDiff(geff[0],geff[1],masses)
        time.sleep(10)

       
        del canvas
        
        canvas = TCanvas("c","c",W,H)
        gacc[0].SetMaximum(1.5)
        gacc[0].SetMinimum(0.)
        gacc[0].SetMarkerStyle(20)
        gacc[0].SetMarkerColor(kRed)
        gacc[0].SetLineColor(kRed)
        gacc[0].SetLineWidth(2)
        gacc[0].Draw("AL")
        gacc[0].GetXaxis().SetTitle("mass (GeV)")
        gacc[0].GetYaxis().SetTitle("Nominal acceptance")
        #l.AddEntry(gacc[0],signals[0],"lp" )
        for i in range(1,len(gacc)):
           #l.AddEntry(gacc[i],signals[i],"lp" )
           #gacc[i].SetMarkerStyle(20+i)
           gacc[i].SetMarkerColor(colorlist[i])
           gacc[i].SetMarkerSize(1)
           gacc[i].SetLineWidth(2)
           gacc[i].SetLineColor(colorlist[i])
           gacc[i].Draw("Lsame")
        l.Draw("same")
        canvas.SaveAs("../../AnalysisOutput/figures/acceptance_overMass.pdf")
        masses=[1200,1400,1600,1800,2000,2500,3000,3500]
        printDiff(gacc[0],gacc[1],masses)
        time.sleep(10)

       
        del canvas
        
        
        canvas = TCanvas("c","c",W,H)
        geffXacc[0].SetMaximum(1.)
        geffXacc[0].SetMinimum(0.)
        geffXacc[0].SetMarkerStyle(20)
        geffXacc[0].SetMarkerColor(kRed)
        geffXacc[0].SetLineColor(kRed)
        geffXacc[0].SetLineWidth(2)
        geffXacc[0].Draw("ALP")
        geffXacc[0].GetXaxis().SetTitle("mass [GeV]")
        geffXacc[0].GetYaxis().SetTitle("efficiency")
        #l.AddEntry(geffXacc[0],signals[0],"lp" )
        for i in range(1,len(geffXacc)):
           #l.AddEntry(geffXacc[i],signals[i],"lp" )
           geffXacc[i].SetMarkerStyle(20+i)
           geffXacc[i].SetMarkerColor(colorlist[i])
           geffXacc[i].SetMarkerSize(1)
           geffXacc[i].SetLineWidth(2)
           geffXacc[i].SetLineColor(colorlist[i])
           geffXacc[i].Draw("LPsame")
        l.Draw("same")
        canvas.SaveAs("../../AnalysisOutput/figures/efficiecyXacceptance_overMass.pdf")
        time.sleep(10)
        masses=[1200,1400,1600,1800,2000,2500,3000,3500]
        printDiff(geffXacc[0],geffXacc[1],masses)
       
        del canvas
        
        
