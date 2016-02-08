#!/bin/bash

#cd /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/
cd /lustre/cmswork/boletti/Kstmumu/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/

source  /cvmfs/cms.cern.ch/cmsset_default.sh
pwd
eval `scram runtime -sh`

mkdir Closure_rt_ada_${2}
cd Closure_rt_ada_${2}
export ANALYPATH=../../
../ComputeEfficiencyKE  ${1} 1 1 0 ${2}

#./PlotPdf ${1}
