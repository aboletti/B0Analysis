#!/bin/sh

export LSF_WORKING_DIR=$PWD

for i in {1..9..1}
do
    #bsub -q local-cms-long -o CT${i}_cc_rt.log -J CT${i}_cc_rt /lustre/cmswork/boletti/Kstmumu/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test_clos_cc.sh ${i} rt_0.5 0 0
    #bsub -q local-cms-long -o CT${i}_cc_wt.log -J CT${i}_cc_wt /lustre/cmswork/boletti/Kstmumu/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test_clos_cc.sh ${i} wt_1.0 1 0
    bsub -q local-cms-long -o Bin${i}_ada1_rt.log -J Bin${i}_ada1_rt /lustre/cmswork/boletti/Kstmumu/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test.sh ${i} 0.5
    bsub -q local-cms-long -o Bin${i}_ada2_rt.log -J Bin${i}_ada2_rt /lustre/cmswork/boletti/Kstmumu/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test.sh ${i} 1.0
    bsub -q local-cms-long -o Bin${i}_ada_wt.log -J Bin${i}_ada_wt /lustre/cmswork/boletti/Kstmumu/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test_wt.sh ${i} 1.0
done
for i in {4..5..1}
do
    bsub -q local-cms-long -o Bin${i}_ada1_rt_jp.log -J Bin${i}_ada1_rt_jp /lustre/cmswork/boletti/Kstmumu/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test_jp.sh ${i} 0.5
    bsub -q local-cms-long -o Bin${i}_ada2_rt_jp.log -J Bin${i}_ada2_rt_jp /lustre/cmswork/boletti/Kstmumu/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test_jp.sh ${i} 1.0
    bsub -q local-cms-long -o Bin${i}_ada_wt_jp.log -J Bin${i}_ada_wt_jp /lustre/cmswork/boletti/Kstmumu/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test_wt_jp.sh ${i} 1.0
    #bsub -q local-cms-long -o CT${i}_cc_jp_rt.log -J CT${i}_cc_jp_rt /lustre/cmswork/boletti/Kstmumu/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test_clos_cc.sh ${i} rt_jp_0.5 0 1
done
#bsub -q local-cms-long -o CT5_cc_jp_wt.log -J CT5_cc_jp_wt /lustre/cmswork/boletti/Kstmumu/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test_clos_cc.sh 5 wt_jp_1.0 1 1
for i in {6..7..1}
do
    bsub -q local-cms-long -o Bin${i}_ada1_rt_p2.log -J Bin${i}_ada1_rt_p2 /lustre/cmswork/boletti/Kstmumu/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test_p2.sh ${i} 0.5
    bsub -q local-cms-long -o Bin${i}_ada2_rt_p2.log -J Bin${i}_ada2_rt_p2 /lustre/cmswork/boletti/Kstmumu/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test_p2.sh ${i} 1.0
    bsub -q local-cms-long -o Bin${i}_ada_wt_p2.log -J Bin${i}_ada_wt_p2 /lustre/cmswork/boletti/Kstmumu/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test_wt_p2.sh ${i} 1.0
    #bsub -q local-cms-long -o CT${i}_cc_p2_rt.log -J CT${i}_cc_p2_rt /lustre/cmswork/boletti/Kstmumu/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test_clos_cc.sh ${i} rt_p2_0.5 0 2
    #bsub -q local-cms-long -o CT${i}_cc_p2_wt.log -J CT${i}_cc_p2_wt /lustre/cmswork/boletti/Kstmumu/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test_clos_cc.sh ${i} wt_p2_1.0 1 2
done

#bsub -q local-cms-long -o PP.log -J PP /lustre/cmswork/boletti/Kstmumu/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test.sh 0
#bsub -q local-cms-long -o PP_jp.log -J PP_jp /lustre/cmswork/boletti/Kstmumu/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test.sh 1
#bsub -q local-cms-long -o PP_p2.log -J PP_p2 /lustre/cmswork/boletti/Kstmumu/CMSSW_5_3_28/src/B0Analysis/B0KstMuMu/plugins/test.sh 2

