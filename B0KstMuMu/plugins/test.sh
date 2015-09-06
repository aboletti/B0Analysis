#!/bin/bash

cd /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/

source  /cvmfs/cms.cern.ch/cmsset_default.sh
pwd
eval `scram runtime -sh`

mkdir Closure_bin_${1}
cd Closure_bin_${1}
export ANALYPATH=../../
#../ComputeEfficiencyKE  ${1} 1 1
ln -s ../eff3DOutputFile.root .
ln -s ../effKEpdf.root .
../ClosureTest  ${1} 1 1
