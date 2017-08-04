
#! /usr/bin/python
import sys
import os
import optparse
import numpy
import tempfile
import platform
from scipy import stats
from copy import deepcopy
import subprocess

# check for python version
if platform.python_version() < "2.5.1":
  print "FATAL: you need a newer python version"
  sys.exit()

from multiprocessing import Process
import thread
import subprocess
import time
import shutil
import socket


# if ntuplizer trees are to be put into trees: python batchsubmission.py --sframe -j SignalMC_Summer16.py 
# or better yet: nohup python batchsubmission.py --sframe -j SignalMC_Summer16.py & 


class ConfigReader:
    def __init__(self,filename):
        #self.Reset
        self.par = [[],[]]
        self.width = []
        self.peak = []
        self.category= (filename.split("y")[1]).split(".")[0]
       # #print self.width
        #print len(self.width)
        config = open(filename,'r')
        setpar = 0
        setpar2 =2
        for i in config.readlines():
            if '#' in i: continue
            if '=' in i: continue
            if 'maximum' in i: continue
            if 'width:' in i:
                setpar=0
                setpar2 =2
                continue
            if 'peak position:' in i:
                setpar=1
                setpar2=1
                continue
            if 'mass' in i:
                continue
            #print i.split("   ")
            #self.par[setpar].append(  (i.split("   ")[setpar2]).split("\n")[0])
            self.par[setpar].append(  (i.split("   ")[1]).split("\n")[0])
            self.par[setpar].append(  (i.split("   ")[2]).split("\n")[0])
        for i in self.par[0]:
            a,b = i.split("/")
            self.width.append(float(a))
            self.width.append(float(b))
        for i in self.par[1]:
            a,b = i.split("/")
            self.peak.append(float(a))
            self.peak.append(float(b))
        config.close()

    def Reset(self):
        print "reset"
        self.width =[]
        self.peak =[]
        self.par =[[],[]]
        print self.width
        print self.par
            
  
  
  
if __name__ == "__main__":
    conf = ["ShapeUncertaintyHPVV.txt","ShapeUncertaintyWWHP.txt","ShapeUncertaintyWZHP.txt","ShapeUncertaintyZZHP.txt","ShapeUncertaintyLPVV.txt","ShapeUncertaintyWWLP.txt","ShapeUncertaintyWZLP.txt","ShapeUncertaintyZZLP.txt"]
    i=0
    
    for config in conf:
        r = ConfigReader(config)

        #print r.par
        #print r.width
        #print r.peak
        s=0
        for w in r.width:
            s += w**2
        s = numpy.sqrt(s/(len(r.width)-1))
        #print r.width
        print "standard deviation width "+r.category+"   "+str(round(s,0))
        
        peak=0
        for p in r.peak:
            peak += p**2
        #print peak
        peak = numpy.sqrt(peak/(len(r.peak)-1))
        print "standard deviation peak "+r.category+"   "+str(round(peak,0))
        i+=1
    
        
    print " ============================================================="   
    conf = ["ShapeUncertaintyHPqV.txt","ShapeUncertaintyHPqW.txt","ShapeUncertaintyHPqZ.txt","ShapeUncertaintyLPqV.txt","ShapeUncertaintyLPqW.txt","ShapeUncertaintyLPqZ.txt"]
    for config in conf:
    
        r = ConfigReader(config)
        #print r.par
        #print r.width
        #print r.peak
        s=0
        for w in r.width:
            s += w**2
        s = numpy.sqrt(s/(len(r.width)-1))
        print "standard deviation width "+r.category+"   "+str(round(s,0))
        
        peak=0
        for p in r.peak:
            peak += p**2
        peak = numpy.sqrt(peak/(len(r.peak)-1))
        print "standard deviation peak "+r.category+"   "+str(round(peak,0))
        
