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

using namespace RooFit ;
#include <TApplication.h>
#include "TCanvas.h"
#include "TFile.h"
#include "TH2D.h"
#include "TMath.h"

// ####################
// # Global variables #
// ####################
Utils* Utility;

void loadHisto() {
  // These are the 2D histogram of the efficiency. Try to save them somewhere
  TFile* effHistoFile=TFile::Open("effHisto2DFile.root","READ");
  cout << "Loading histos" ;
  TH2D* H2Deff_0_q2Bin_Org_1=(TH2D*) effHistoFile->Get("H2Deff_0_q2Bin_Org_1");
  TH2D* H2Deff_1_q2Bin_Org_1=(TH2D*) effHistoFile->Get("H2Deff_1_q2Bin_Org_1");
  TH2D* H2Deff_2_q2Bin_Org_1=(TH2D*) effHistoFile->Get("H2Deff_2_q2Bin_Org_1");
  cout << " done " << endl;
  effHistoFile->Close();

  // Define variables
  RooRealVar ctK("ctK","cos#theta_K",-1,1);
  RooRealVar ctL("ctL","cos#theta_L",-1,1);
  RooRealVar phi("phi","#phi",-TMath::Pi(),TMath::Pi());

  RooArgSet ctKctLS(ctK,ctL);
  RooArgList ctKctL(ctKctLS);

  cout << "creating RooDataHist" ;
  // Create a RooDataHist from a TH2D: how?
  RooDataHist pippo("pippo","pippo", ctKctL, H2Deff_0_q2Bin_Org_1);
  cout << " done " << endl;

  // // Represent data in dh as pdf in x
  // RooHistPdf histpdf1("histpdf1","histpdf1", ctKctL, pippo, 0);

  // Make plot of binned dataset showing Poisson error bars (RooFit default)
  // RooPlot* frame = x.frame(Title("Imported TH1 with Poisson error bars")) ;
  // dh.plotOn(frame) ;
  TH2* hh21 = (TH2*)pippo.createHistogram("hh21",ctK,Binning(10,-1,1),YVar(ctL,Binning(10,-1,1)));

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
  framex->Draw("") ;
  c->cd(2);
  gPad->SetLeftMargin(0.15) ;
  framey->GetYaxis()->SetTitleOffset(1.4) ;
  framey->Draw("") ;
  c->cd(3);
  pippo.Draw("lego");
  c->cd(4);
  hh21->Draw("lego");
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
      loadHisto();
    }
  else
    {
      cout << "Parameter missing: " << endl;
      cout << "./" << argv[0] << endl;

      
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}
