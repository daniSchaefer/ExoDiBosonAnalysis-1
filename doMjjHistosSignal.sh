#!bin/bash

# do histos for the input of the shape interpolation for the limit setting
# output is written to: results/ZprimeWW_13TeV_1200GeV.root etc. if used with option --noLumiScale it is imediatly written in the right folder (input of DijetCombinedLimitCode) also it is not scaled to lumi since in the limits the signal gets scaled to the luminosity!!!!
option="--noLumiScale"
masses=(1000 1200 1400 1600 1800 2000 2500 3000 3500 4000 4500)

for m in ${masses[@]}
do
    python do-mjj-histos_SR.py --signal ZprimeWW --mass $m $option
done


masses=(1000 1200 1400 1600 1800 2000 2500 3000 3500 4000)

for m in ${masses[@]}
do
    python do-mjj-histos_SR.py --signal BulkZZ --mass $m $option
done

masses=(1000 1200 1400 1600 1800 2000 2500 3500 4000 4500)

for m in ${masses[@]}
do
    python do-mjj-histos_SR.py --signal BulkWW --mass $m $option
done


masses=(1000 1200 1400 1600 1800 2000 2500 3000 3500 4000 4500)

for m in ${masses[@]}
do
    python do-mjj-histos_SR.py --signal WprimeWZ --mass $m $option
done


masses=(1000 1200 1400 1600 1800 2000 2500 3000 3500 4000 4500 5000 6000 7000)

for m in ${masses[@]}
do
    python do-mjj-histos_SR.py --signal QstarQW --mass $m $option
done

masses=(1000 1200 1400 1600 1800 2000 2500 3000 4500 6000)

for m in ${masses[@]}
do
    python do-mjj-histos_SR.py --signal QstarQZ --mass $m $option
done

# produce histos for shape uncertainty studies

option="--noLumiScale"
options=("JESup" "JESdown" "CV" "JERdown")
options=("JERup")

#for option in ${options[@]}
#do
    # masses=(1000 1200 1400 1600 1800 2000 2500 3000 3500 4000 4500)
    # 
    # for m in ${masses[@]}
    # do
    #     python do-mjj-histos_SR.py --signal ZprimeWW --mass #m --doSmeared $option
    # done


#     masses=(1000 1200 1400 1600 1800 2000 2500 3000 3500 4000)
# 
#     for m in ${masses[@]}
#     do
#         python do-mjj-histos_SR.py --signal BulkZZ --mass $m --doSmeared $option
#     done
# 
#     masses=(1000 1200 1400 1600 1800 2000 2500 3500 4000 4500)
# 
#     for m in ${masses[@]}
#     do
#         python do-mjj-histos_SR.py --signal BulkWW --mass $m --doSmeared $option
#     done
# 
# 
#     masses=(1000 1200 1400 1600 1800 2000 2500 3000 3500 4000 4500)
# 
#     for m in ${masses[@]}
#     do
#         python do-mjj-histos_SR.py --signal WprimeWZ --mass $m --doSmeared $option
#     done


#     masses=(1000 1200 1400 1600 1800 2000 2500 3000 3500 4000 4500 5000 6000 7000)
# 
#     for m in ${masses[@]}
#     do
#         python do-mjj-histos_SR.py --signal QstarQW --mass $m --doSmeared $option
#     done
# 
#     masses=(1000 1200 1400 1600 1800 2000 2500 3000 4500 6000)
# 
#     for m in ${masses[@]}
#     do
#         python do-mjj-histos_SR.py --signal QstarQZ --mass $m --doSmeared $option
#     done
# done
