void AFTER_P_x_y_COL() {
    
    ifstream in1, in10, in2, in20;
    Double_t par1, par10, par2, par20;

    TCanvas *c1 = new TCanvas("Canvas1", "Canvas", 1280, 720);
    in1.open("../AFTER_TARGET/P_X.dat");
    in10.open("../AFTER_TARGET/P_Y.dat");
    assert(in1.is_open());
    assert(in10.is_open());
    
    c1->SetLogy(0);
    TH2F *h1 = new TH2F("After Target X Y","Positron beam",200,-20,20,200,-20,20);
    h1->GetXaxis()->SetTitle("X, mm");
    h1->GetXaxis()->SetTitleOffset(1.5);
    h1->GetYaxis()->SetTitle("Y, mm");
    h1->GetYaxis()->SetTitleOffset(1.5);
    h1->SetLineColor(kAzure+10);

    while (1)
    {
        in1>>par1;
        in10>>par10;
        if(!in1.good() && !in10.good())
            break;
        h1->Fill(par1, par10);
    }
    in1.close();
    in10.close();
    h1->Draw("SURF3");
    c1->SaveAs("../PNG/AFTER_P_X_Y_COL_T.png");
    c1->Clear();
    h1->Delete();
    
    in1.open("../AFTER_MAGNET/P_X.dat");
    in10.open("../AFTER_MAGNET/P_Y.dat");
    assert(in1.is_open());
    assert(in10.is_open());
    
    h1 = new TH2F("After Magnet X Y","Positron beam",200,-20,20,200,-20,20);
    c1->SetLogy(0);
    h1->GetXaxis()->SetTitle("X, mm");
    h1->GetXaxis()->SetTitleOffset(1.5);
    h1->GetYaxis()->SetTitle("Y, mm");
    h1->GetYaxis()->SetTitleOffset(1.5);
    h1->SetLineColor(kAzure+10);
    
    while (1)
    {
        in1>>par1;
        in10>>par10;
        if(!in1.good() && !in10.good())
            break;
        h1->Fill(par1, par10);
    }
    in1.close();
    in10.close();
    h1->Draw("SURF3");
    c1->SaveAs("../PNG/AFTER_P_X_Y_COL_M.png");
    c1->Close();
}



