void AFTER_P_mx_my_COL() {
    
    ifstream in1[5];
    Double_t par1[5];

    TCanvas *c1 = new TCanvas("Canvas1", "Canvas", 1280, 720);
    in1[0].open("../AFTER_TARGET/P_MX.dat");
    in1[1].open("../AFTER_TARGET/P_MY.dat");
    in1[2].open("../AFTER_TARGET/P_MZ.dat");
    in1[3].open("../AFTER_TARGET/P_X.dat");
    in1[4].open("../AFTER_TARGET/P_Y.dat");
    assert(in1[0].is_open());
    assert(in1[1].is_open());
    assert(in1[2].is_open());
    assert(in1[3].is_open());
    assert(in1[4].is_open());

    TH2F *h1 = new TH2F("After Target X MX","Momentum projection (X)",200,-20,20,200,-1,1);
    h1->GetXaxis()->SetTitle("X, mm");
    h1->GetXaxis()->SetTitleOffset(1.5);
    h1->GetYaxis()->SetTitle("Px/P");
    h1->GetYaxis()->SetTitleOffset(1.5);
    h1->SetLineColor(kAzure+10);
    
    TH2F *h2 = new TH2F("After Target Y MY","Momentum projection (Y)",200,-20,20,200,-1,1);
    h2->GetXaxis()->SetTitle("Y, mm");
    h2->GetXaxis()->SetTitleOffset(1.5);
    h2->GetYaxis()->SetTitle("Py/P");
    h2->GetYaxis()->SetTitleOffset(1.5);
    h2->SetLineColor(kAzure+10);

    while (1)
    {
        in1[0]>>par1[0];
        in1[1]>>par1[1];
        in1[2]>>par1[2];
        in1[3]>>par1[3];
        in1[4]>>par1[4];
        if(!in1[0].good())
            break;
        h1->Fill(par1[3], par1[0]/sqrt(par1[0]*par1[0] + par1[1]*par1[1] + par1[2]*par1[2]));
        h2->Fill(par1[4], par1[1]/sqrt(par1[0]*par1[0] + par1[1]*par1[1] + par1[2]*par1[2]));
    }
    in1[0].close();
    in1[1].close();
    in1[2].close();
    in1[3].close();
    in1[4].close();
    h1->Draw("SURF3");
    c1->SaveAs("../PNG/AFTER_P_X_MX_COL_T.png");
    h2->Draw("SURF3");
    c1->SaveAs("../PNG/AFTER_P_Y_MY_COL_T.png");
    
    h1->Delete();
    h2->Delete();
    
    in1[0].open("../AFTER_MAGNET/P_MX.dat");
    in1[1].open("../AFTER_MAGNET/P_MY.dat");
    in1[2].open("../AFTER_MAGNET/P_MZ.dat");
    in1[3].open("../AFTER_MAGNET/P_X.dat");
    in1[4].open("../AFTER_MAGNET/P_Y.dat");
    assert(in1[0].is_open());
    assert(in1[1].is_open());
    assert(in1[2].is_open());
    assert(in1[3].is_open());
    assert(in1[4].is_open());
    
    h1 = new TH2F("After Magnet X MX","Momentum projection (X)",200,-20,20,200,-1,1);
    h1->GetXaxis()->SetTitle("X, mm");
    h1->GetXaxis()->SetTitleOffset(1.5);
    h1->GetYaxis()->SetTitle("Px/P");
    h1->GetYaxis()->SetTitleOffset(1.5);
    h1->SetLineColor(kAzure+10);
    
    h2 = new TH2F("After Magnet Y MY","Momentum projection (Y)",200,-20,20,200,-1,1);
    h2->GetXaxis()->SetTitle("Y, mm");
    h2->GetXaxis()->SetTitleOffset(1.5);
    h2->GetYaxis()->SetTitle("Py/P");
    h2->GetYaxis()->SetTitleOffset(1.5);
    h2->SetLineColor(kAzure+10);
    
    while (1)
    {
        in1[0]>>par1[0];
        in1[1]>>par1[1];
        in1[2]>>par1[2];
        in1[3]>>par1[3];
        in1[4]>>par1[4];
        if(!in1[0].good())
            break;
        h1->Fill(par1[3], par1[0]/sqrt(par1[0]*par1[0] + par1[1]*par1[1] + par1[2]*par1[2]));
        h2->Fill(par1[4], par1[1]/sqrt(par1[0]*par1[0] + par1[1]*par1[1] + par1[2]*par1[2]));
    }
    in1[0].close();
    in1[1].close();
    in1[2].close();
    in1[3].close();
    in1[4].close();
    h1->Draw("SURF3");
    c1->SaveAs("../PNG/AFTER_P_X_MX_COL_M.png");
    h2->Draw("SURF3");
    c1->SaveAs("../PNG/AFTER_P_Y_MY_COL_M.png");
    
    c1->Close();
}



