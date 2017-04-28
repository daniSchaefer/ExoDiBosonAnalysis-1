#!/bin/bash

# python extractMjj.py --filename ../../Bkg/QCD_Spring16_Ptbinned_pythia8_VVdijet_Mjj995.root --isMC True --s QCD_pythia8_forEff_VVdijet --region SR

masses=(1200 1400 1600 1800 2000 2500 3000 3500 4000 4500)

for m in ${masses[@]}
do 
        python extractMjj.py --filename ExoDiBosonAnalysis.ZprimeWW_13TeV_${m}GeV.CV.root --isMC True --s Zprime_M${m} --region SR --mode Mjj

done


masses=(1200 1400 1600 1800 2000 2500 3500 4000 4500)

for m in ${masses[@]}
do 
        python extractMjj.py --filename ExoDiBosonAnalysis.BulkWW_13TeV_${m}GeV.CV.root --isMC True --s BulkWW_M${m} --region SR --mode Mjj

done


masses=(1200 1400 1600 1800 2000 2500 3000 3500 4000)

for m in ${masses[@]}
do 
        python extractMjj.py --filename ExoDiBosonAnalysis.BulkZZ_13TeV_${m}GeV.CV.root --isMC True --s BulkZZ_M${m} --region SR --mode Mjj

done


masses=(1200 1400 1600 1800 2000 2500 3000 3500 4000 4500)

for m in ${masses[@]}
do 
        python extractMjj.py --filename ExoDiBosonAnalysis.WprimeWZ_13TeV_${m}GeV.CV.root --isMC True --s WprimeWZ_M${m} --region SR --mode Mjj

done

# masses=(1200 1400 1600 1800 2000 2500 3000 3500 4000 4500 5000 6000)
# masses=(1200 1400 1600 1800 2500 3500 4000)
# masses=(1200 2000 3500 4500)
# 
# for m in ${masses[@]}
# do 
#          #python extractMjj.py --filename ExoDiBosonAnalysis.QstarQW_13TeV_${m}GeV.qV.root --isMC True --s QstarQW_M${m} --region qV_SR --mode Mjj
#          #python extractMjj.py --filename Sys/ExoDiBosonAnalysis.QstarQZ_13TeV_${m}GeV.PDF.root --isMC True --s QstarQZ_M${m}_PDF --region qV_SR --mode MjjPDF
#          
#          python extractMjj.py --filename Sys/ExoDiBosonAnalysis.BulkWW_13TeV_${m}GeV.PDF.root --isMC True --s BulkWW_M${m}_PDF --region VV_SR --mode MjjPDF
#         #python extractMjj.py --filename ExoDiBosonAnalysis.QstarQZ_13TeV_${m}GeV.qV.root --isMC True --s QstarQZ_M${m} --region qV_SR --mode Mjj
# 
# done
