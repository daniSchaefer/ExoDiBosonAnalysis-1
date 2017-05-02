# ExoDiBosonAnalysis

You first need to set up the SFrame Framework as described here:
  https://wiki-zeuthen.desy.de/ATLAS/Projects/TopPhysicsInternal/AnalysisFramework/Tutorial 
  (current tag is SFrame-04-00-01/)
In order to run SFrame you need a working version ROOT (setting up the CMSSW enviroment will do, CMSSW_7_4_X with X>1)
After sourcing SFrame 

  cd SFrame
  source setup.sh

You need to create a new package

  sframe_new_package.sh ExoDiBosonAnalysis

in order to let SFrame now about the directory. Your package needs to have the same name as the repository your checking out 
(ExoDiBosonAnalysis). You can then move on to checking out the code.
Then you should be able to compile

  make clean && make 

and run

  sframe_main config/VV_HP.xml. 

with respect to theas version added the following:

        1) if Channel = "PU" or "PUreweighting" then running the framework will just fill the histos nPUVtxTrue that is needed do do a proper PU reweighting (and           nPUVtx) this can then be done using calculate-puweights.py in scripts
        2) for the calculation of PDF uncertainties on the cross section and the acceptance add <Item Name="PDFSET" Value="263400" />  and  
            <Item Name="wPDFname" Value="wpdf_M1200_BulkZZ" />  to the .xml file. the first is the number of the PDFSET that should be used for reweighting and the second is the name of a .txt file containing the outcome that will be generated. a list of PDFSets available can be found under LHAPDF pdfsets.
        3) when you want to look at the sideband region put "jetmassSideband" before the usual option in Channel i.e. "jetmassSidebandqVdijet" or "jetmassSidebandVVdijet"
        

        
Pile-Up reweighting:

    pileup distribution in data has to be inserted in the variable: PUdata in the config file old one from thea in data/biasXsec_69200.root
    for pileup distributions i fill now four histograms in MC: 
                    nPUVtxTrue  -> true vertex distribution (as expected from momentary luminosity
                    nPUVtx      -> number of PU vertices measured in detector (as per the mc simulation)
                    nPUVtxTrue_rew  -> true vertex distribution reweighted to the true data distribution -> these two distributions should look the same now
                    nPUVtx_rew      -> reco dist. reweighted according to the true number of vertices of the event -> this and the corresponding data distribution can still differ for example due to reconstruction inefficiencies of the runs
                    
    -> these histos get filled in data and mc (exept for true and reweighted in data which of course makes no sense) when using either PU of VVdijet qVdijet as Channel
    for summer16 samples right reweighting if in the filename is summer16 anywhere
            

Cross sections for MC samples:
    find  the cross sections for 2015 here: https://github.com/CERN-PH-CMG/cmgtools-lite/blob/80X/RootTools/python/samples/samples_13TeV_RunIISpring16MiniAODv2.py#L377

to examine the shape uncertainties due to PDF:

    add the option <Item Name="PDFSET" Value="263400" /> in order to choose the PDFset to evaluate.
    then put PDF as "scaleUncPar". the output tree will have a variable called pdfweights with the weights corresponding to the different PDFsets normalised to the central value (odf PDF used for generation of sample).
