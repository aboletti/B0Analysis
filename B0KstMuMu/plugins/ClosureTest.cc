// ################################################################################
// # Program to perform the a closure test for efficiency for angular analysis
// of the decay B0 --> K*0 mu+ mu- 
// Author: Stefano Lacaprara  <lacaprara@pd.infn.it>  INFN Padova
// #
// ################################################################################
// # Search for @TMP@ to look for temporary code options                          #
// ################################################################################
#include "Utils.h"

#include <RooGenericPdf.h>
#include "RooHistPdf.h"
#include "RooRealVar.h"
#include "RooDataHist.h"
#include "RooPlot.h"
#include "RooBinning.h"

using namespace RooFit ;
#include <TApplication.h>
#include "TCanvas.h"
#include "TFile.h"
#include "TH2D.h"
#include "TMath.h"

// ####################
// # Global constants #
// ####################
#define SETBATCH        false
#define PARAMETERFILEIN "/python/ParameterFile.txt"
#define ordinateRange   1e-2

// ####################
// # Global variables #
// ####################
Utils* Utility;

vector<double> q2Bins;
vector<double> cosThetaKBins;
vector<double> cosThetaLBins;
vector<double> phiBins;

void loadHisto() {
  // These are the 2D histogram of the efficiency. Try to save them somewhere
  TFile* effHistoFile=TFile::Open("effHisto2DFile.root","READ");
  cout << "Loading histos" ;
  TH2D* H2Deff_0_q2Bin_Org_2=(TH2D*) effHistoFile->Get("H2Deff_0_q2Bin_Org_2");
  TH2D* H2Deff_1_q2Bin_Org_2=(TH2D*) effHistoFile->Get("H2Deff_1_q2Bin_Org_2");
  TH2D* H2Deff_2_q2Bin_Org_2=(TH2D*) effHistoFile->Get("H2Deff_2_q2Bin_Org_2");
  cout << " done " << endl;
  //effHistoFile->Close();

  // Define variables
  RooRealVar ctK("ctK","cos#theta_K",-1.,1.);
  RooRealVar ctL("ctL","cos#theta_L",-1.,1.);
  RooRealVar phi("phi","#phi",1.*TMath::Pi(),1.*TMath::Pi());

  RooArgSet ctKctLS(ctK,ctL);
  RooArgList ctKctL(ctKctLS);

  cout << "creating RooDataHist " << H2Deff_0_q2Bin_Org_2 << endl ;
  // Create a RooDataHist from a TH2D: how?
  RooDataHist pippo("pippo","pippo", ctKctL, Import(*H2Deff_0_q2Bin_Org_2,kFALSE));
  cout << " done " << endl;

  // Represent data in dh as pdf in x
  RooHistPdf histpdf1("histpdf1","histpdf1", ctKctL, pippo, 0);

  // Make plot of binned dataset showing Poisson error bars (RooFit default)
  // RooPlot* frame = x.frame(Title("Imported TH1 with Poisson error bars")) ;
  // dh.plotOn(frame) ;
  
  double* q2Bins_        = Utility->MakeBinning(&q2Bins);
  double* cosThetaKBins_ = Utility->MakeBinning(&cosThetaKBins);
  double* cosThetaLBins_ = Utility->MakeBinning(&cosThetaLBins);
  double* phiBins_       = Utility->MakeBinning(&phiBins);

  cout << "cosThetaL binning " << endl;
  for (vector<double>::const_iterator xlow= cosThetaLBins.begin(); xlow!=cosThetaLBins.end(); xlow++ ) cout << (*xlow) << " " << endl;

  RooBinning cosThetaLBinning(cosThetaLBins.size()-1,cosThetaLBins_);

  cout << "RooBinning L: " << cosThetaLBinning.lowBound() << " H: " << cosThetaLBinning.highBound() << " N " << cosThetaLBinning.numBoundaries() << endl;
  // RooBinning cosThetaKBinning;
  // for (vector<double>::const_iterator xlow= cosThetaKBins.begin(); xlow!=cosThetaKBins.end(); xlow++ ) cosThetaKBinning.addBoundary(*xlow);

  cout << "cosThetaK binning " << endl;
  for (vector<double>::const_iterator xlow= cosThetaKBins.begin(); xlow!=cosThetaKBins.end(); xlow++ ) cout << (*xlow) << " " << endl;

  RooBinning cosThetaKBinning(cosThetaKBins.size()-1,cosThetaKBins_);
  cout << "RooBinning L: " << cosThetaKBinning.lowBound() << " H: " << cosThetaKBinning.highBound() << " N " << cosThetaKBinning.numBoundaries() << endl;

  TH2* hh21 = (TH2*)pippo.createHistogram("hh21",ctK,Binning(cosThetaKBinning),YVar(ctL,Binning(cosThetaLBinning)));

  // P l o t   a n d   f i t   a   R o o D a t a H i s t
  // ---------------------------------------------------
  RooPlot* framex = ctK.frame(Title("Imported TH1 with Poisson error bars")) ;
  pippo.plotOn(framex) ; 
  RooPlot* framey = ctL.frame(Title("Imported TH1 with Poisson error bars")) ;
  pippo.plotOn(framey) ; 

  TCanvas* c = new TCanvas("rf102_dataimport","rf102_dataimport",800,800) ;
  c->Divide(2,2);
  c->cd(1);
  gPad->SetLeftMargin(0.15) ;
  framex->GetYaxis()->SetTitleOffset(1.4) ;
  framex->Draw() ;
  c->cd(2);
  gPad->SetLeftMargin(0.15) ;
  framey->GetYaxis()->SetTitleOffset(1.4) ;
  framey->Draw() ;
  c->cd(3);
  H2Deff_0_q2Bin_Org_2->Draw("lego2 fp");
  c->cd(4);
  hh21->Draw("lego2 fp");
  //effHistoFile->Close();
}

int main(int argc, char** argv)
{
  if (argc >= 0)
    {
      // ##################
      // # Main variables #
      // ##################

	TApplication theApp ("Applications", &argc, argv);
	Utility = new Utils(false);
	Utility->ReadAllBins(Utility->MakeAnalysisPATH(PARAMETERFILEIN).c_str(),&q2Bins,&cosThetaKBins,&cosThetaLBins,&phiBins,"goodTag");
      loadHisto();
      theApp.Run ();
    }
  else
    {
      cout << "Parameter missing: " << endl;
      cout << "./" << argv[0] << endl;

      
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}
