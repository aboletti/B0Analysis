rootlogon(){
  gROOT->SetStyle("Plain"); // remove gray background from plots
  gInterpreter->AddIncludePath("/cvmfs/cms.cern.ch/slc6_amd64_gcc472/lcg/roofit/5.32.03-cms/include");
  gSystem->Load("libMinuit.so") ;
  gSystem->Load("/cvmfs/cms.cern.ch/slc6_amd64_gcc472/lcg/roofit/5.32.03-cms/lib/libRooFitCore.so") ;
  using namespace RooFit ;
}
