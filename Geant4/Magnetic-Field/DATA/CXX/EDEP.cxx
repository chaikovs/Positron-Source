void EDEP() {
    
    ifstream in1;
    in1.open("../EDEP.dat");
    assert(in1.is_open());
    Double_t par1;

    TCanvas *c1 = new TCanvas("Canvas1", "Canvas", 1280, 720);
    TH1F *h1 = new TH1F("EDEP","Deposited Energy",100,0,2000);
    h1->GetXaxis()->SetTitle("Energy, MeV");
    h1->GetYaxis()->SetTitle("Number of the particles");
    h1->SetLineColor(kAzure+10);
    h1->SetFillColorAlpha(kAzure+10, 0.4);
    h1->SetFillStyle(3001);

    while (1)
    {
        in1>>par1;
        if(!in1.good())
            break;
        h1->Fill(par1);
    }
    in1.close();
    h1->Draw();
    c1->SaveAs("../PNG/EDEP.png");
    c1->Close();
}



