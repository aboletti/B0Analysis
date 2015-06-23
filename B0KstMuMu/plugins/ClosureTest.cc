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
#include "RooProdPdf.h"
#include "RooPlot.h"
#include "RooBinning.h"
using namespace RooFit ;

#include <TROOT.h>
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

#define doInterpolation 4

// ####################
// # Global variables #
// ####################
Utils* Utility;

vector<double> q2Bins;
double* q2Bins_ ;
double* cosThetaKBins_ ;
double* cosThetaLBins_ ;
double* phiBins_ ;
RooBinning cosThetaLBinning;
RooBinning cosThetaKBinning;
RooBinning phiBinning;
RooRealVar ctK("ctK","cos#theta_{K}",-1.,1.);
RooRealVar ctL("ctL","cos#theta_{L}",-1.,1.);
RooRealVar phi("phi","#phi",-1.*TMath::Pi(),1.*TMath::Pi());
RooArgSet ctKctL(ctK,ctL);
RooArgSet ctKphi(ctK,phi);
RooArgSet ctLphi(ctL,phi);
RooArgSet ctKctLphi(ctK,ctL,phi);

TFile* effHistoFile=0;
TFile* pdf2DOutputFile;
TH2D* H2Deff_ctK_ctL;
TH2D* H2Deff_ctL_phi;
TH2D* H2Deff_ctK_phi;

void loadEffHisto(unsigned int q2bin) {
  if (!effHistoFile) { 
    cout << "Loading effHistoFile.root " << endl;
    effHistoFile=TFile::Open("effHisto2DFile.root","READ");
  }

  H2Deff_ctK_ctL=(TH2D*) effHistoFile->Get(Form("H2Deff_0_q2Bin_Org_%d",q2bin));
  H2Deff_ctL_phi=(TH2D*) effHistoFile->Get(Form("H2Deff_1_q2Bin_Org_%d",q2bin));
  H2Deff_ctK_phi=(TH2D*) effHistoFile->Get(Form("H2Deff_2_q2Bin_Org_%d",q2bin));
}

void plot3DHisto(unsigned int q2bin, const RooAbsPdf& xyzEff) {
  TCanvas* c3D = new TCanvas("c3D","3D Pdf",800,800) ;
  c3D->Divide(2,2);
  c3D->cd(1);
  TH2* hh21Pdf = (TH2*)xyzEff.createHistogram("hh21Pdf",ctK,Binning(cosThetaKBinning),YVar(ctL,Binning(cosThetaLBinning)));
  hh21Pdf->DrawCopy("lego2 fp");
  c3D->cd(2);
  TH2* hh22Pdf = (TH2*)xyzEff.createHistogram("hh22Pdf",ctL,Binning(cosThetaLBinning),YVar(phi,Binning(phiBinning)));
  hh22Pdf->DrawCopy("lego2 fp");
  c3D->cd(3);
  TH2* hh23Pdf = (TH2*)xyzEff.createHistogram("hh23Pdf",ctL,Binning(cosThetaKBinning),YVar(phi,Binning(phiBinning)));
  hh23Pdf->DrawCopy("lego2 fp");
  c3D->cd(4);
  TH3* hh24Pdf = (TH3*)xyzEff.createHistogram("hh24Pdf",ctK,Binning(cosThetaKBinning),YVar(ctL,Binning(cosThetaKBinning)),ZVar(phi,Binning(phiBinning)));
  hh24Pdf->DrawCopy("box2 fp");
}

void plotHisto(unsigned int q2bin, const RooHistPdf& xyEff, const RooDataHist& xyHisto) {
  // These are the 2D histogram of the efficiency. Try to save them somewhere

  TCanvas* cOrig = new TCanvas("cOrig","Original histo",800,800) ;
  cOrig->Divide(2,2);
  cOrig->cd(1);
  H2Deff_ctK_ctL->DrawCopy("lego2 fp");
  cOrig->cd(2);
  H2Deff_ctK_phi->DrawCopy("lego2 fp");
  cOrig->cd(3);
  H2Deff_ctL_phi->DrawCopy("lego2 fp");

  //xyEff.Print();
  bool isCtK=false, isCtL=false, isPhi=false;
  if (xyEff.dependsOn(ctK)) isCtK=true;
  if (xyEff.dependsOn(ctL)) isCtL=true;
  if (xyEff.dependsOn(phi)) isPhi=true;

  TH2* h2Orig=0;
  TH2* hh21Histo=0;
  TH2* hh21Pdf=0;
  TString caName("EffPlot");
  TString caTitle("Eff Plot vs ");
  RooPlot* framex=0;
  RooPlot* framey=0;
  if (isCtK && isCtL) {
    h2Orig=H2Deff_ctK_ctL;
    hh21Histo = (TH2*)xyHisto.createHistogram("hh21Histo",ctK,Binning(cosThetaKBinning),YVar(ctL,Binning(cosThetaLBinning)));
    hh21Pdf = (TH2*)xyEff.createHistogram("hh21Pdf",ctK,Binning(cosThetaKBinning),YVar(ctL,Binning(cosThetaLBinning)));
    framex = ctK.frame(Title("cos#theta_{K} projection")) ;
    framey = ctL.frame(Title("cos#theta_{L} projection")) ;
    caName+=TString("CtkCtl");
    caTitle+=TString(" cos#theta_{K},cos#theta_{L}");
  }
  else if (isCtK && isPhi) {
    h2Orig=H2Deff_ctK_phi;
    //phiBinning.Print();
    hh21Histo = (TH2*)xyHisto.createHistogram("hh21Histo",ctK,Binning(cosThetaKBinning),YVar(phi,Binning(phiBinning)));
    hh21Pdf = (TH2*)xyEff.createHistogram("hh21Pdf",ctK,Binning(cosThetaKBinning),YVar(phi,Binning(phiBinning)));
    framex = ctK.frame(Title("cos#theta_{K} projection")) ;
    framey = phi.frame(Title("#phi projection")) ;
    caName+=TString("CtkPhi");
    caTitle+=TString(" cos#theta_{K},#phi");
  }
  else if (isCtL && isPhi) {
    h2Orig=H2Deff_ctL_phi;
    hh21Histo = (TH2*)xyHisto.createHistogram("hh21Histo",ctL,Binning(cosThetaLBinning),YVar(phi,Binning(phiBinning)));
    hh21Pdf = (TH2*)xyEff.createHistogram("hh21Pdf",ctL,Binning(cosThetaLBinning),YVar(phi,Binning(phiBinning)));
    framex = ctL.frame(Title("cos#theta_{L} projection")) ;
    framey = phi.frame(Title("#phi projection")) ;
    caName+=TString("CtlPhi");
    caTitle+=TString(" cos#theta_{L},#phi");
  }

  // P l o t   a n d   f i t   a   R o o D a t a P d f
  // ---------------------------------------------------
  xyEff.plotOn(framex) ; 
  xyEff.plotOn(framey) ; 

  TCanvas* c = new TCanvas(caName,caTitle,800,800) ;
  c->Divide(3,2);
  c->cd(1);
  gPad->SetLeftMargin(0.15) ;
  framex->GetYaxis()->SetTitleOffset(1.4) ;
  framex->DrawClone() ;
  c->cd(2);
  gPad->SetLeftMargin(0.15) ;
  framey->GetYaxis()->SetTitleOffset(1.4) ;
  framey->DrawClone() ;
  c->cd(3);
  h2Orig->DrawCopy("lego2 fp");
  c->cd(4);
  hh21Histo->DrawCopy("lego2 fp");
  c->cd(5);
  hh21Pdf->DrawCopy("lego2 fp");

  c->Print(caName+Form("_q2bin_%d.pdf",q2bin));
}

void createHistPdf(unsigned int q2bin, bool doPlot=false) {
  cout << "createHistPdf " << q2bin << endl;
  // Define variables

  // ctK.setVal(0.1);
  // ctL.setVal(0.1);
  // phi.setVal(0.1);


  RooArgList ctKctL(ctK,ctL);
  RooDataHist hist_ctKctL("hist_ctKctL","hist_ctKctL", ctKctL, Import(*H2Deff_ctK_ctL,kTRUE));
  RooHistPdf pdf_ctKctL("pdf_ctKctL","pdf_ctKctL", ctKctL, hist_ctKctL, doInterpolation);
  //cout << "pdf_ctKctL( " << ctK.getVal() << "," << ctL.getVal() << " ) = " << pdf_ctKctL.getVal() << endl;
  if (doPlot) plotHisto(q2bin, pdf_ctKctL,hist_ctKctL);
  pdf2DOutputFile->cd();
  pdf_ctKctL.Write(Form("pdf_ctKctL_q2bin%d",q2bin));

  RooArgList ctKphi(ctK,phi);
  RooDataHist hist_ctKphi("hist_ctKphi","hist_ctKphi", ctKphi, Import(*H2Deff_ctK_phi,kTRUE));
  RooHistPdf pdf_ctKphi("pdf_ctKphi","pdf_ctKphi", ctKphi, hist_ctKphi, doInterpolation);
  //cout << "pdf_ctKphi( " << ctK.getVal() << "," << phi.getVal() << " ) = " << pdf_ctKphi.getVal() << endl;
  if (doPlot) plotHisto(q2bin, pdf_ctKphi,hist_ctKphi);
  pdf2DOutputFile->cd();
  pdf_ctKphi.Write(Form("pdf_ctKphi_q2bin%d",q2bin));

  RooArgList ctLphi(ctL,phi);
  RooDataHist hist_ctLphi("hist_ctLphi","hist_ctLphi", ctLphi, Import(*H2Deff_ctL_phi,kTRUE));
  RooHistPdf pdf_ctLphi("pdf_ctLphi","pdf_ctLphi", ctLphi, hist_ctLphi, doInterpolation);
  //cout << "pdf_ctLphi( " << ctL.getVal() << "," << phi.getVal() << " ) = " << pdf_ctLphi.getVal() << endl;
  if (doPlot) plotHisto(q2bin, pdf_ctLphi,hist_ctLphi);
  pdf2DOutputFile->cd();
  pdf_ctLphi.Write(Form("pdf_ctLphi_q2bin%d",q2bin));

  // Try a 3d pdf
  RooProdPdf pdf_ctKctLphi("pdf_ctKctLphi","pdf cos#theta_{K},cos#theta_{L},#phi",RooArgSet(pdf_ctKctL,pdf_ctKphi,pdf_ctLphi));
  pdf_ctKctLphi.Print();
  pdf_ctKctLphi.Print("T");
  if (doPlot) plot3DHisto(q2bin,pdf_ctKctLphi);
  pdf_ctKctLphi.Write(Form("pdf_ctKctLphi_q2bin%d",q2bin));

}

void createHistPdfCtKCtL() {

  //cout << "creating RooDataHist " << H2Deff_ctK_ctL << endl ;
  // Create a RooDataHist from a TH2D: how?
  RooDataHist pippo("pippo","pippo", ctKctL, Import(*H2Deff_ctK_ctL,kTRUE));
  //cout << " done " << endl;

  // Represent data in dh as pdf in x
  RooHistPdf histpdf1("histpdf1","histpdf1", ctKctL, pippo, 0);
  histpdf1.setUnitNorm(kFALSE);

  TH2* hh21 = (TH2*)pippo.createHistogram("hh21",ctK,Binning(cosThetaKBinning),YVar(ctL,Binning(cosThetaLBinning)));

  TH2* hh21Pdf = (TH2*)histpdf1.createHistogram("hh21Pdf",ctK,Binning(cosThetaKBinning),YVar(ctL,Binning(cosThetaLBinning)));

  // P l o t   a n d   f i t   a   R o o D a t a H i s t
  // ---------------------------------------------------
  RooPlot* framex = ctK.frame(Title("Imported TH1 with Poisson error bars")) ;
  pippo.plotOn(framex) ; 
  RooPlot* framey = ctL.frame(Title("Imported TH1 with Poisson error bars")) ;
  pippo.plotOn(framey) ; 
  // RooPlot* framePdf = new RooPlot(ctK,ctL) ;
  // histpdf1.plotOn(framePdf) ;

  TCanvas* c = new TCanvas("CosThetaKVsCosThetaL","CosThetaKVsCosThetaL",800,800) ;
  c->Divide(3,2);
  c->cd(1);
  gPad->SetLeftMargin(0.15) ;
  framex->GetYaxis()->SetTitleOffset(1.4) ;
  framex->Draw() ;
  c->cd(2);
  gPad->SetLeftMargin(0.15) ;
  framey->GetYaxis()->SetTitleOffset(1.4) ;
  framey->Draw() ;
  c->cd(3);
  H2Deff_ctK_ctL->Draw("lego2 fp");
  c->cd(4);
  hh21->Draw("lego2 fp");
  c->cd(5);
  hh21Pdf->Draw("lego2 fp");

  
}

void createHistPdfCtKPhi() {

  //cout << "creating RooDataHist " << H2Deff_ctK_ctL << endl ;
  // Create a RooDataHist from a TH2D: how?
  RooDataHist pippo("pippo","pippo", ctKphi, Import(*H2Deff_ctK_phi,kTRUE));
  //cout << " done " << endl;

  // Represent data in dh as pdf in x
  RooHistPdf histpdf1("histpdf1","histpdf1", ctKphi, pippo, 0);
  histpdf1.setUnitNorm(kFALSE);

  TH2* hh21 = (TH2*)pippo.createHistogram("hh21",ctK,Binning(cosThetaKBinning),YVar(phi,Binning(phiBinning)));

  TH2* hh21Pdf = (TH2*)histpdf1.createHistogram("hh21Pdf",ctK,Binning(cosThetaKBinning),YVar(phi,Binning(phiBinning)));

  // P l o t   a n d   f i t   a   R o o D a t a H i s t
  // ---------------------------------------------------
  RooPlot* framex = ctK.frame(Title("Imported TH1 with Poisson error bars")) ;
  pippo.plotOn(framex) ; 
  RooPlot* framey = phi.frame(Title("Imported TH1 with Poisson error bars")) ;
  pippo.plotOn(framey) ; 
  // RooPlot* framePdf = new RooPlot(ctK,ctL) ;
  // histpdf1.plotOn(framePdf) ;

  TCanvas* c = new TCanvas("CosThetaKVsPhi","CosThetaKVsPhi",800,800) ;
  c->Divide(3,2);
  c->cd(1);
  gPad->SetLeftMargin(0.15) ;
  framex->GetYaxis()->SetTitleOffset(1.4) ;
  framex->Draw() ;
  c->cd(2);
  gPad->SetLeftMargin(0.15) ;
  framey->GetYaxis()->SetTitleOffset(1.4) ;
  framey->Draw() ;
  c->cd(3);
  H2Deff_ctK_phi->Draw("lego2 fp");
  c->cd(4);
  hh21->Draw("lego2 fp");
  c->cd(5);
  hh21Pdf->Draw("lego2 fp");

  
}

void createHistPdfCtLPhi() {
  //cout << "creating RooDataHist " << H2Deff_ctK_ctL << endl ;
  // Create a RooDataHist from a TH2D: how?
  RooDataHist pippo("pippo","pippo", ctLphi, Import(*H2Deff_ctL_phi,kTRUE));
  //cout << " done " << endl;

  // Represent data in dh as pdf in x
  RooHistPdf histpdf1("histpdf1","histpdf1", ctLphi, pippo, 0);
  histpdf1.setUnitNorm(kFALSE);

  TH2* hh21 = (TH2*)pippo.createHistogram("hh21",ctL,Binning(cosThetaLBinning),YVar(phi,Binning(phiBinning)));

  TH2* hh21Pdf = (TH2*)histpdf1.createHistogram("hh21Pdf",ctL,Binning(cosThetaLBinning),YVar(phi,Binning(phiBinning)));

  // P l o t   a n d   f i t   a   R o o D a t a H i s t
  // ---------------------------------------------------
  RooPlot* framex = ctL.frame(Title("Imported TH1 with Poisson error bars")) ;
  pippo.plotOn(framex) ; 
  RooPlot* framey = phi.frame(Title("Imported TH1 with Poisson error bars")) ;
  pippo.plotOn(framey) ; 
  // RooPlot* framePdf = new RooPlot(ctK,ctL) ;
  // histpdf1.plotOn(framePdf) ;

  TCanvas* c = new TCanvas("CosThetaLVsPhi","CosThetaLVsPhi",800,800) ;
  c->Divide(3,2);
  c->cd(1);
  gPad->SetLeftMargin(0.15) ;
  framex->GetYaxis()->SetTitleOffset(1.4) ;
  framex->Draw() ;
  c->cd(2);
  gPad->SetLeftMargin(0.15) ;
  framey->GetYaxis()->SetTitleOffset(1.4) ;
  framey->Draw() ;
  c->cd(3);
  H2Deff_ctL_phi->Draw("lego2 fp");
  c->cd(4);
  hh21->Draw("lego2 fp");
  c->cd(5);
  hh21Pdf->Draw("lego2 fp");

  
}

void loadBinning() {
  vector<double> cosThetaKBins;
  vector<double> cosThetaLBins;
  vector<double> phiBins;
  Utility->ReadAllBins(Utility->MakeAnalysisPATH(PARAMETERFILEIN).c_str(),&q2Bins,&cosThetaKBins,&cosThetaLBins,&phiBins,"goodTag");
  q2Bins_        = Utility->MakeBinning(&q2Bins);
  cosThetaKBins_ = Utility->MakeBinning(&cosThetaKBins);
  cosThetaLBins_ = Utility->MakeBinning(&cosThetaLBins);
  phiBins_       = Utility->MakeBinning(&phiBins);
  cosThetaLBinning=RooBinning (cosThetaLBins.size()-1,cosThetaLBins_);
  cosThetaLBinning.Print();
  cosThetaKBinning=RooBinning (cosThetaKBins.size()-1,cosThetaKBins_);
  cosThetaKBinning.Print();
  phiBinning=RooBinning(phiBins.size()-1,phiBins_);
  phiBinning.Print();

}

int main(int argc, char** argv)
{
  if (argc > 0)
    {
      // ##################
      // # Main variables #
      // ##################

	TApplication theApp ("Applications", &argc, argv);
	Utility = new Utils(false);
      loadBinning();

      unsigned int q2BinIndx=2;
      bool doPlot=false;
      bool doBatch=false;
      if ( argc > 1 ) q2BinIndx = atoi(argv[1]);
      if ( argc > 2 ) doPlot = atoi(argv[2]);
      if ( argc > 3 ) doBatch = atoi(argv[3]);


      // createHistPdfCtKCtL();
      // createHistPdfCtKPhi();
      // createHistPdfCtLPhi();

      if (doBatch) {
        cout << "\n[" << argv[0] << "::main]\t@@@ Setting batch mode @@@" << endl;
        gROOT->SetBatch(doBatch);
      }

      // Open output file
      pdf2DOutputFile = new TFile("pdf2DOutputFile.root", "RECREATE");

      // do all q2Bins at once
      if (q2BinIndx==0) {
        for (q2BinIndx=1; q2BinIndx<9; ++q2BinIndx) {
          // Open input file
          loadEffHisto(q2BinIndx);
          createHistPdf(q2BinIndx,doPlot);
        }
      }
      else {
        // do only one q2 bin
        loadEffHisto(q2BinIndx);
        createHistPdf(q2BinIndx,doPlot);
      }

      pdf2DOutputFile->Close();
      theApp.Run();
    }
  else
    {
      cout << "Parameter missing: " << endl;
      cout << "./" << argv[0] << " <q2Bin (0 for all)> " << " <plot histo (decfault=0/no)> " << " <batch running (default=0/no) " << endl;

      
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}
