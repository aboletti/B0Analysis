RooRealVar ctK("ctK","cos#theta_{K}",-1.,1.);
RooRealVar ctL("ctL","cos#theta_{L}",-1.,1.);
RooRealVar phi("phi","#phi",-1.*TMath::Pi(),1.*TMath::Pi());
TFile* file=TFile::Open("pdf2DOutputFile.root","READ");

void plotPdf(unsigned int q2bin) {


  TCanvas* c1=new TCanvas(Form("canProjection%d",q2bin),"",800,800);
  c1->Divide(4,2);
  c1->cd(1);
  RooHistPdf* pdf_ctKctL=(RooHistPdf*)file->Get(Form("pdf_ctKctL_q2bin%d",q2bin));
  TH2* h2_pdf_ctKctL=pdf_ctKctL->createHistogram("ctK,ctL");
  h2_pdf_ctKctL->Draw("surf3 fp");
  c1->cd(2);
  RooHistPdf* pdf_ctKphi=(RooHistPdf*)file->Get(Form("pdf_ctKphi_q2bin%d",q2bin));
  TH2* h2_pdf_ctKphi=pdf_ctKphi->createHistogram("ctK,phi");
  h2_pdf_ctKphi->Draw("surf3 fp");
  c1->cd(3);
  RooHistPdf* pdf_ctLphi=(RooHistPdf*)file->Get(Form("pdf_ctLphi_q2bin%d",q2bin));
  TH2* h2_pdf_ctLphi=pdf_ctLphi->createHistogram("ctL,phi");
  h2_pdf_ctLphi->Draw("surf3 fp");
  c1->cd(4);
  RooHistPdf* pdf_ctKctLphi=(RooHistPdf*)file->Get(Form("pdf_ctKctLphi_q2bin%d",q2bin));
  TH2* h2_pdf_ctKctLphi=pdf_ctKctLphi->createHistogram("ctK,ctL,phi");
  h2_pdf_ctKctLphi->Draw("box2");

  c1->cd(5);
  RooPlot* frameCtK=ctK.frame();
  pdf_ctKctLphi->plotOn(frameCtK);
  frameCtK->Draw();
  c1->cd(6);
  RooPlot* frameCtL=ctL.frame();
  pdf_ctKctLphi->plotOn(frameCtL);
  frameCtL->Draw();
  c1->cd(7);
  RooPlot* framePhi=phi.frame();
  pdf_ctKctLphi->plotOn(framePhi);
  framePhi->Draw();
  c1->Print(Form("canProjection%d.pdf",q2bin));
}

void plotPdf() {
  for (unsigned int q2bin=1; q2bin<9; ++q2bin) plotPdf(q2bin);
}
