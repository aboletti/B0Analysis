using namespace RooFit ;

void readToyDataset() {
  TFile *_file0 = TFile::Open("toyDatasets.root");
  RooWorkspace* w=_file0->Get("ws");

  w->Print("v");

  RooRealVar* B0mass = w->var("B0mass") ;
  RooRealVar* ctK = w->var("ctK") ;
  RooRealVar* ctL = w->var("ctL") ;
  RooRealVar* phi = w->var("phi") ;

  for (int q2Bin=1; q2Bin<=9; ++q2Bin) {
    if (q2Bin==5 || q2Bin==7) continue;
    RooDataSet* sig1 = (RooDataSet*)w->data(Form("toy0_sig%d",q2Bin)) ;
    RooDataSet* bkg1 = (RooDataSet*)w->data(Form("toy0_bkg%d",q2Bin)) ;

    RooDataSet* all1 = sig1;
    all1->append(*bkg1);

    RooPlot* B0massFrame = B0mass->frame() ;
    RooPlot* ctLFrame = ctK->frame() ;
    RooPlot* ctKFrame = ctL->frame() ;
    RooPlot* phiFrame = phi->frame() ;

    // // Overlay the background component of model with a dashed line
    // sig1->plotOn(B0massFrame,MarkerStyle(20),MarkerColor(kRed)) ;

    // // Overlay the background+sig2 components of model with a dotted line
    // bkg1->plotOn(B0massFrame,MarkerStyle(24),MarkerColor(kBlue)) ;

    // Overlay the background+sig2 components of model with a dotted line
    all1->plotOn(B0massFrame,MarkerStyle(20),MarkerColor(kBlack)) ;
    all1->plotOn(ctLFrame,MarkerStyle(20),MarkerColor(kBlack)) ;
    all1->plotOn(ctKFrame,MarkerStyle(20),MarkerColor(kBlack)) ;
    all1->plotOn(phiFrame,MarkerStyle(20),MarkerColor(kBlack)) ;

    // Draw the frame on the canvas
    TCanvas* c1=new TCanvas(Form("toyBin%d",q2Bin),Form("cocktail toy MC Bin %d",q2Bin),600,600) ;
    c1->Divide(2,2);
    c1->cd(1);
    // gPad->SetLeftMargin(0.12) ;
    B0massFrame->GetYaxis()->SetTitleOffset(1) ; 
    B0massFrame->Draw() ;
    c1->cd(2);
    ctLFrame->GetYaxis()->SetTitleOffset(1) ; 
    ctLFrame->Draw() ;
    c1->cd(3);
    ctKFrame->GetYaxis()->SetTitleOffset(1) ; 
    ctKFrame->Draw() ;
    c1->cd(4);
    phiFrame->GetYaxis()->SetTitleOffset(1) ; 
    phiFrame->Draw() ;
    c1->Print((c1->GetName())+TString(".pdf"));
  }
}
