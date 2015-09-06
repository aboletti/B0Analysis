#!/bin/sh

export LSF_WORKING_DIR=$PWD

for i in {1..9..1}
do
  #bsub -q local-cms-long -o Bin${i}.log -J Bin${i} /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test.sh ${i}
  bsub -o Bin${i}.log -J Bin${i} /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test.sh ${i}
done

