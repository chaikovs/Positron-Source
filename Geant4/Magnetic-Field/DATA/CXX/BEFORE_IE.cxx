void BEFORE_IE() {
    
    ifstream in1[2];
    in1[0].open("../BEFORE_TARGET/IE_X.dat");
    in1[1].open("../BEFORE_TARGET/IE_Y.dat");
    assert(in1[0].is_open());
    assert(in1[1].is_open());
    Double_t par1[2];
    
    TCanvas *c1 = new TCanvas("Canvas1", "Canvas", 1280, 720);
    
    TH1F *h1 = new TH1F("Initial X","Initial electron beam",200,-20,20);
    h1->GetXaxis()->SetTitle("X, mm");
    h1->GetYaxis()->SetTitle("Number of the initial electrons");
    h1->SetLineColor(kAzure+10);
    h1->SetFillColorAlpha(kAzure+10, 0.4);
    h1->SetFillStyle(3001);
    
    TH1F *h2 = new TH1F("Initial Y","Initial electron beam",200,-20,20);
    h2->GetXaxis()->SetTitle("Y, mm");
    h2->GetYaxis()->SetTitle("Number of the initial electrons");
    h2->SetLineColor(kAzure+10);
    h2->SetFillColorAlpha(kAzure+10, 0.4);
    h2->SetFillStyle(3001);
    
    TH2F *h3 = new TH2F("Initial X Y","Initial electron beam",200,-20,20,200,-20,20);
    h3->GetXaxis()->SetTitle("X, mm");
    h3->GetXaxis()->SetTitleOffset(1.5);
    h3->GetYaxis()->SetTitle("Y, mm");
    h3->GetYaxis()->SetTitleOffset(1.5);
    h3->SetLineColor(kAzure+10);
    
    while (1)
    {
        in1[0]>>par1[0];
        in1[1]>>par1[1];
        if(!in1[0].good())
            break;
        h1->Fill(par1[0]);
        h2->Fill(par1[1]);
        h3->Fill(par1[0], par1[1]);
    }
    in1[0].close();
    in1[1].close();
    h1->Draw();
    c1->SaveAs("../PNG/BEFORE_IE_X.png");
    h2->Draw();
    c1->SaveAs("../PNG/BEFORE_IE_Y.png");
    h3->Draw("SURF3");
    c1->SaveAs("../PNG/BEFORE_IE_X_Y_COL.png");
    c1->Close();
}



