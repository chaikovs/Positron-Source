void TARGET_P_x_y_z_e_COL()
{
    ifstream in, in1;
    in.open("../TARGET/B_DE.dat");
    in1.open("../TARGET/B_ijk.dat");
    assert(in.is_open());
    assert(in1.is_open());
    double edep;
    int I, J, K;
    double EDXY[70][70], EDZX[14][70], EDZY[14][70];
    for(int i = -35; i < 35; ++i)
    {
        for(int j = -35; j < 35; ++j)
        {
            EDXY[i+35][j+35] = 0;
        }
    }
    for(int k = 0; k < 14; ++k)
    {
        for(int i = -35; i < 35; ++i)
        {
            EDZX[k][i+35] = 0;
        }
    }
    for(int k = 0; k < 14; ++k)
    {
        for(int j = -35; j < 35; ++j)
        {
            EDZY[k][j+35] = 0;
        }
    }

    while(1)
    {
        in1 >> I >> J >> K;
        in >> edep;
        EDXY[I+35][J+35] += edep;
        EDZX[K][I+35] += edep;
        EDZY[K][J+35] += edep;
        if(!in.good()) break;
    }
    in.close();
    in1.close();

    TCanvas *c1 = new TCanvas("Canvas1", "Canvas", 1280, 720);
    TH2F *h2 = new TH2F("XY", "Energy distribution of the positrons in target", 70, -35, 35, 70, -35, 35);
    h2->GetXaxis()->SetTitle("X, mm");
    h2->GetYaxis()->SetTitle("Y, mm");
    for(int i = -35; i < 35; ++i)
    {
        for(int j = -35; j < 35; ++j)
        {
            h2->Fill(i, j, EDXY[i+35][j+35]);
        }
    }
    h2->Draw("SURF3");
    c1->SaveAs("../PNG/TARGET_B_X_Y_E.png");

    TH2F *h3 = new TH2F("ZX", "Energy distribution of the positrons in target", 14, 0, 14, 70, -35, 35);
    h3->GetXaxis()->SetTitle("Z, mm");
    h3->GetYaxis()->SetTitle("X, mm");
    for(int k = 0; k < 14; ++k)
    {
        for(int i = -35; i < 35; ++i)
        {
            h3->Fill(k, i, EDZX[k][i+35]);
        }
    }
    h3->Draw("SURF3");
    c1->SaveAs("../PNG/TARGET_B_Z_X_E.png");

    TH2F *h1 = new TH2F("ZY", "Energy distribution of the positrons in target", 14, 0, 14, 70, -35, 35);
    h1->GetXaxis()->SetTitle("Z, mm");
    h1->GetYaxis()->SetTitle("Y, mm");
    for(int k = 0; k < 14; ++k)
    {
        for(int j = -35; j < 35; ++j)
        {
            h1->Fill(k, j, EDZY[k][j+35]);
        }
    }
    h1->Draw("SURF3");
    c1->SaveAs("../PNG/TARGET_B_Z_Y_E.png");
    c1->Close();
}
