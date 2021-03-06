OS            := $(shell uname)
.DEFAULT_GOAL := all

ifeq ($(OS), Darwin)
CXX           := clang++
DEBUG         :=
endif

ifeq ($(OS), Linux)
CXX           := g++
DEBUG         := -g
endif

CXXFLAGS      := $(DEBUG) -ansi -Wall -Wextra -m64 -O3

SOURCEDIR     := ../src
SOURCES       := $(filter-out $(SOURCEDIR)/B0KstMuMu.cc,$(wildcard $(SOURCEDIR)/*.cc))

INCLUDEDIR    := ../interface
INCLUDES      := -I $(INCLUDEDIR)

XERCESINFLAGS := -I $(HOME)/xerces/include
BOOSTINFLAGS  := -I $(HOME)/boost
GSLINCFLAGS   := -I $(HOME)/gsl/include

XERCESFLAGS   := -L $(HOME)/xerces/lib -lxerces-c
BOOSTFLFLAGS  := -L $(HOME)/boost/stage/lib
GSLFLAGS      := -L $(HOME)/gsl/lib -lgsl

ROOTFLAGS     := `root-config --cflags --glibs` -lMinuit
ROOFITFLAGS   := $(ROOTFLAGS) -lRooFit -lRooFitCore -lFoam -I/cvmfs/cms.cern.ch/slc6_amd64_gcc472/lcg/roofit/5.32.03-cms/include -L/cvmfs/cms.cern.ch/slc6_amd64_gcc472/lcg/roofit/5.32.03-cms/lib


SingleCandB0KstMuMu: $(SOURCEDIR) $(INCLUDEDIR) SingleCandB0KstMuMu.cc
	$(CXX) $(CXXFLAGS) -o $@ $(ROOTFLAGS) $(INCLUDES) $(SOURCES) $@.cc

AddVarsToCandidates: $(SOURCEDIR) $(INCLUDEDIR) AddVarsToCandidates.cc
	$(CXX) $(CXXFLAGS) -o $@ $(ROOTFLAGS) $(INCLUDES) $(SOURCES) $@.cc

B0KstMuMuScanCuts: $(SOURCEDIR) $(INCLUDEDIR) B0KstMuMuScanCuts.cc
	$(CXX) $(CXXFLAGS) -o $@ $(ROOTFLAGS) $(INCLUDES) $(SOURCES) $@.cc

ComputeEfficiency: $(SOURCEDIR) $(INCLUDEDIR) ComputeEfficiency.cc
	$(CXX) $(CXXFLAGS) -o $@ $(ROOTFLAGS) $(INCLUDES) $(SOURCES) $@.cc

MakePlots: $(SOURCEDIR) $(INCLUDEDIR) $(ROOTFITINC) MakePlots.cc
	$(CXX) $(CXXFLAGS) -o $@ $(ROOFITFLAGS) $(INCLUDES) $(SOURCES) -D"ROOFIT" $@.cc

ExtractYield: $(SOURCEDIR) $(INCLUDEDIR) ExtractYield.cc
	$(CXX) $(CXXFLAGS) -o $@ $(ROOFITFLAGS) $(INCLUDES) $(SOURCES) -D"ROOFIT" $@.cc

ComputeEfficiency3D: $(SOURCEDIR) $(INCLUDEDIR) ComputeEfficiency3D.cc
	$(CXX) $(CXXFLAGS) -o $@ $(ROOFITFLAGS) $(ROOTFLAGS) $(INCLUDES) $(SOURCES) $@.cc

ComputeEfficiencyKE: $(SOURCEDIR) $(INCLUDEDIR) ComputeEfficiencyKE.cc
	$(CXX) $(CXXFLAGS) -o $@ $(ROOFITFLAGS) $(INCLUDES) $(SOURCES) -D"ROOFIT" $@.cc

ComputeEfficiencyKE_jp: $(SOURCEDIR) $(INCLUDEDIR) ComputeEfficiencyKE_jp.cc
	$(CXX) $(CXXFLAGS) -o $@ $(ROOFITFLAGS) $(INCLUDES) $(SOURCES) -D"ROOFIT" $@.cc

ComputeEfficiencyKE_p2: $(SOURCEDIR) $(INCLUDEDIR) ComputeEfficiencyKE_p2.cc
	$(CXX) $(CXXFLAGS) -o $@ $(ROOFITFLAGS) $(INCLUDES) $(SOURCES) -D"ROOFIT" $@.cc

ComputeEfficiencyKE_wt: $(SOURCEDIR) $(INCLUDEDIR) ComputeEfficiencyKE_wt.cc
	$(CXX) $(CXXFLAGS) -o $@ $(ROOFITFLAGS) $(INCLUDES) $(SOURCES) -D"ROOFIT" $@.cc

ComputeEfficiencyKE_wt_jp: $(SOURCEDIR) $(INCLUDEDIR) ComputeEfficiencyKE_wt_jp.cc
	$(CXX) $(CXXFLAGS) -o $@ $(ROOFITFLAGS) $(INCLUDES) $(SOURCES) -D"ROOFIT" $@.cc

ComputeEfficiencyKE_wt_p2: $(SOURCEDIR) $(INCLUDEDIR) ComputeEfficiencyKE_wt_p2.cc
	$(CXX) $(CXXFLAGS) -o $@ $(ROOFITFLAGS) $(INCLUDES) $(SOURCES) -D"ROOFIT" $@.cc

ComputeEfficiencyKE_test1: $(SOURCEDIR) $(INCLUDEDIR) ComputeEfficiencyKE_test1.cc
	$(CXX) $(CXXFLAGS) -o $@ $(ROOFITFLAGS) $(INCLUDES) $(SOURCES) -D"ROOFIT" $@.cc

ComputeEfficiencyKE_test2: $(SOURCEDIR) $(INCLUDEDIR) ComputeEfficiencyKE_test2.cc
	$(CXX) $(CXXFLAGS) -o $@ $(ROOFITFLAGS) $(INCLUDES) $(SOURCES) -D"ROOFIT" $@.cc

ClosureTest: $(SOURCEDIR) $(INCLUDEDIR) ClosureTest.cc
	$(CXX) $(CXXFLAGS) -o $@ $(ROOFITFLAGS) $(INCLUDES) $(SOURCES) -D"ROOFIT" $@.cc

Hist2pdf: $(SOURCEDIR) $(INCLUDEDIR) Hist2pdf.cc
	$(CXX) $(CXXFLAGS) -o $@ $(ROOFITFLAGS) $(INCLUDES) $(SOURCES) -D"ROOFIT" $@.cc

PlotPdf: $(SOURCEDIR) $(INCLUDEDIR) PlotPdf.cc
	$(CXX) $(CXXFLAGS) -o $@ $(ROOFITFLAGS) $(INCLUDES) $(SOURCES) -D"ROOFIT" $@.cc

LOCALCC := $(wildcard *.cc)
clean:
	$(RM) $(LOCALCC:%.cc=%) Macros_C.*

all: $(LOCALCC:%.cc=%)
