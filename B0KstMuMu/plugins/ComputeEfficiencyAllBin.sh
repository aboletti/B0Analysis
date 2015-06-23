#!/bin/bash

# Compute efficiency for all q2 bins, and save the histogram in a file.
# NB requires that SETBATCH is defined as TRUE in the ComputeEfficiency.cc file
#
# 23-Jun-2015
# Stefano Lacaprara  <lacaprara@pd.infn.it>  INFN Padova

mv -f effHisto2DFile.root effHisto2DFile.root_old
for q2bin in {1..8}
do
  ./ComputeEfficiency Test2DEff 1 ../efficiency/Efficiency4D_B0ToKstMuMu_GoodTag.txt ANALY ${q2bin}
done


