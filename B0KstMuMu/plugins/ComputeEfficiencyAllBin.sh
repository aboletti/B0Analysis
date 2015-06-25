#!/bin/bash

# Compute efficiency for all q2 bins, and save the histogram in a file.
# NB requires that SETBATCH is defined as TRUE in the ComputeEfficiency.cc file
#
# 23-Jun-2015
# Stefano Lacaprara  <lacaprara@pd.infn.it>  INFN Padova

case "$1" in
  2d)
    what=Test2DEff
    mv -f effHisto2DFile.root effHisto2DFile.root_old
    ;;
  3d)
    what=Test3DEff
    mv -f effHisto3DFile.root effHisto3DFile.root_old
    ;;
  *)
    echo $"Usage: $0 [2d|3d]"
    exit 2
esac


for q2bin in {1..8}
do
  ./ComputeEfficiency ${what} 1 ../efficiency/Efficiency4D_B0ToKstMuMu_GoodTag.txt ANALY ${q2bin}
done


