void TARGET_P_x_y_z() {
    
    ifstream in1[3];
    in1[0].open("../TARGET/P_X.dat");
    in1[1].open("../TARGET/P_Y.dat");
    in1[2].open("../TARGET/P_Z.dat");
    assert(in1[0].is_open());
    assert(in1[1].is_open());
    assert(in1[2].is_open());
    Double_t par1[3];
    
    TCanvas *c1 = new TCanvas("Canvas1", "Canvas", 1280, 720);
    gStyle->SetOptStat(false);
    TH3F *h1 = new TH3F("XYZ", "Birthplace of the positrons", 14, 0, 14, 70, -35, 35, 70, -35, 35);
    h1->SetTitle("Birthplace of the positrons");
    h1->GetXaxis()->SetTitle("Z, mm");
    h1->GetXaxis()->SetTitleOffset(1.5);
    h1->GetYaxis()->SetTitle("Y, mm");
    h1->GetYaxis()->SetTitleOffset(1.5);
    h1->GetZaxis()->SetTitle("X, mm");
    h1->SetMarkerColor(kAzure+10);

    while (1)
    {
        in1[0]>>par1[0];
        in1[1]>>par1[1];
        in1[2]>>par1[2];
        if(!in1[0].good())
            break;
        h1->Fill(par1[2] - 93., par1[1], par1[0]);
    }
    in1[0].close();
    in1[1].close();
    in1[2].close();
    h1->Draw();
    c1->SaveAs("../PNG/TARGET_P_X_Y_Z.png");
    c1->Close();

    TCanvas *c2 = new TCanvas("Canvas2", "Canvas", 1280, 720);
    gStyle->SetOptStat(true);
    TH1F *h2 = new TH1F("Z", "Z projection", 140, 0, 14);
    h2->SetFillStyle(3001);
    h2->SetFillColorAlpha(kAzure+10, 0.4);
    h2->SetLineColor(kAzure);
    h2->GetXaxis()->SetTitle("Z, mm");
    h2->GetYaxis()->SetTitle("Number of the positrons");

    TH1F *h3 = new TH1F("Y", "Y projection", 280, -35, 35);
    h3->SetFillStyle(3001);
    h3->SetFillColorAlpha(kAzure+10, 0.4);
    h3->SetLineColor(kAzure);
    h3->GetXaxis()->SetTitle("Y, mm");
    h3->GetYaxis()->SetTitle("Number of the positrons");

    TH1F *h4 = new TH1F("X", "X projection", 280, -35, 35);
    h4->SetFillStyle(3001);
    h4->SetFillColorAlpha(kAzure+10, 0.4);
    h4->SetLineColor(kAzure);
    h4->GetXaxis()->SetTitle("X, mm");
    h4->GetYaxis()->SetTitle("Number of the positrons");

    TH2F *h5 = new TH2F("XY", "XY projection", 280, -35, 35, 280, -35, 35);
    h5->GetXaxis()->SetTitle("X, mm");
    h5->GetXaxis()->SetTitleOffset(1.5);
    h5->GetYaxis()->SetTitle("Y, mm");
    h5->GetYaxis()->SetTitleOffset(1.5);
    h5->SetLineColor(kAzure+10);

    TH2F *h6 = new TH2F("ZX", "ZX projection", 140, 0, 14, 280, -35, 35);
    h6->GetXaxis()->SetTitle("Z, mm");
    h6->GetXaxis()->SetTitleOffset(1.5);
    h6->GetYaxis()->SetTitle("X, mm");
    h6->GetYaxis()->SetTitleOffset(1.5);
    h6->SetLineColor(kAzure+10);

    TH2F *h7 = new TH2F("ZY", "ZY projection", 140, 0, 14, 280, -35, 35);
    h7->GetXaxis()->SetTitle("Z, mm");
    h7->GetXaxis()->SetTitleOffset(1.5);
    h7->GetYaxis()->SetTitle("Y, mm");
    h7->GetYaxis()->SetTitleOffset(1.5);
    h7->SetLineColor(kAzure+10);

    in1[0].open("../TARGET/P_X.dat");
    in1[1].open("../TARGET/P_Y.dat");
    in1[2].open("../TARGET/P_Z.dat");
    assert(in1[0].is_open());
    assert(in1[1].is_open());
    assert(in1[2].is_open());
    while (1)
    {
        in1[0]>>par1[0];
        in1[1]>>par1[1];
        in1[2]>>par1[2];
        if(!in1[0].good())
            break;
        h2->Fill(par1[2] - 93.);
        h3->Fill(par1[1]);
        h4->Fill(par1[0]);
        h5->Fill(par1[0], par1[1]);
        h6->Fill(par1[2] - 93., par1[0]);
        h7->Fill(par1[2] - 93., par1[1]);
    }
    in1[0].close();
    in1[1].close();
    in1[2].close();

    h2->Draw();
    c2->SaveAs("../PNG/TARGET_P_Z.png");
    h3->Draw();
    c2->SaveAs("../PNG/TARGET_P_Y.png");
    h4->Draw();
    c2->SaveAs("../PNG/TARGET_P_X.png");
    c2->Clear();
    h5->Draw("SURF3");
    c2->SaveAs("../PNG/TARGET_P_X_Y.png");
    h6->Draw("SURF3");
    c2->SaveAs("../PNG/TARGET_P_Z_X.png");
    h7->Draw("SURF3");
    c2->SaveAs("../PNG/TARGET_P_Z_Y.png");
    c2->Close();


    in1[0].open("../TARGET/P_Z.dat");
    in1[1].open("../TARGET/P_E.dat");
    assert(in1[0].is_open());
    assert(in1[1].is_open());
    TCanvas *c3 = new TCanvas("Canvas1", "Canvas", 1280, 720);
    TH2F *h8 = new TH2F("Positron beam", "Positrons energy vs. Z-coordinate", 210, 0, 14, 200, 0, 6000);
    h8->GetXaxis()->SetTitle("Z, mm");
    h8->GetYaxis()->SetTitle("Energy, MeV");
    h8->SetMarkerColor(kAzure+10);

    while (1)
    {
        in1[0]>>par1[0];
        in1[1]>>par1[1];
        if(!in1[0].good())
            break;
        h8->Fill(par1[0] - 93., par1[1]);
    }
    in1[0].close();
    in1[1].close();
    h8->Draw();
    c3->SaveAs("../PNG/TARGET_P_Z_E.png");
    c3->Close();
}



