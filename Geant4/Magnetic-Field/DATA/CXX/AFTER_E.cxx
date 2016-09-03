void AFTER_E() {
    
    ifstream in1, in10;
    in1.open("../AFTER_TARGET/E_E.dat");
    in10.open("../AFTER_MAGNET/E_E.dat");
    assert(in1.is_open());
    assert(in10.is_open());
    Double_t par1;
    Double_t par10;
    TPaveStats *ps1;
    TPaveStats *ps10;

    TCanvas *c1 = new TCanvas("Canvas1", "Canvas", 1280, 720);
    c1->SetLogy(1);
    TH1F *h1 = new TH1F("AFTER_TARGET_E","Energy spectrum of the electrons",90,0,6000);
    h1->GetXaxis()->SetTitle("Energy, MeV");
    h1->GetYaxis()->SetTitle("Number of the electrons");
    h1->SetLineColor(kBlue);
    h1->SetFillColorAlpha(kBlue, 0.4);
    h1->SetFillStyle(3001);
    TH1F *h10 = new TH1F("AFTER_MAGNET_E"," ",90,0,6000);
    h10->SetLineColor(kRed);
    h10->SetFillColorAlpha(kRed, 0.4);
    h10->SetFillStyle(3001);

    int i = 0;
    while (1)
    {
        while(i == 0)
        {
            in1>>par1;
            if(!in1.good())
            {
                i = 1;
                in1.close();
                h1->Draw();
                c1->Update();
                ps1 = (TPaveStats*)h1->GetListOfFunctions()->FindObject("stats");
                ps1->SetX1NDC(0.4);
                ps1->SetX2NDC(0.6);
                ps1->SetTextColor(kBlue);
                c1->cd();
                break;
            }
            h1->Fill(par1);
        }
        in10>>par10;
        if(!in10.good())
        {
            in10.close();
            h10->Draw("][sames");
            c1->Update();
            ps10 = (TPaveStats*)h10->GetListOfFunctions()->FindObject("stats");
            ps10->SetX1NDC(0.65);
            ps10->SetX2NDC(0.85);
            ps10->SetTextColor(kRed);
            c1->Update();
            c1->Print("../PNG/AFTER_E_E.png");
            c1->Clear();
            ps1->Clear();
            ps10->Clear();
            break;
        }
        h10->Fill(par10);
    }

    in1.open("../AFTER_TARGET/E_P.dat");
    in10.open("../AFTER_MAGNET/E_P.dat");
    assert(in1.is_open());
    assert(in10.is_open());

    c1->SetLogy(1);
    TH1F *h2 = new TH1F("AFTER_TARGET_P","Angular distribution of the electrons (Phi)",60,-180,180);
    h2->GetXaxis()->SetTitle("Phi, deg");
    h2->GetYaxis()->SetTitle("Number of the electrons");
    h2->GetYaxis()->SetRangeUser(5000, 50000);
    h2->SetLineColor(kBlue);
    h2->SetFillColorAlpha(kBlue, 0.1);
    h2->SetFillStyle(3001);
    TH1F *h20 = new TH1F("AFTER_MAGNET_P"," ",60,-180,180);
    h20->GetYaxis()->SetRangeUser(5000, 50000);
    h20->SetLineColor(kRed);
    h20->SetFillColorAlpha(kRed, 0.1);
    h20->SetFillStyle(3001);
    
    i = 0;
    while (1)
    {
        while(i == 0)
        {
            in1>>par1;
            if(!in1.good())
            {
                i = 1;
                in1.close();
                h2->Draw();
                c1->Update();
                ps1 = (TPaveStats*)h2->GetListOfFunctions()->FindObject("stats");
                ps1->SetX1NDC(0.4);
                ps1->SetX2NDC(0.6);
                ps1->SetTextColor(kBlue);
                c1->cd();
                break;
            }
            h2->Fill(par1);
        }
        in10>>par10;
        if(!in10.good())
        {
            in10.close();
            h20->Draw("][sames");
            c1->Update();
            ps10 = (TPaveStats*)h20->GetListOfFunctions()->FindObject("stats");
            ps10->SetX1NDC(0.65);
            ps10->SetX2NDC(0.85);
            ps10->SetTextColor(kRed);
            c1->Update();
            c1->Print("../PNG/AFTER_E_P.png");
            c1->Clear();
            ps1->Clear();
            ps10->Clear();
            break;
        }
        h20->Fill(par10);
    }
    
    in1.open("../AFTER_TARGET/E_T.dat");
    in10.open("../AFTER_MAGNET/E_T.dat");
    assert(in1.is_open());
    assert(in10.is_open());
    
    c1->SetLogy(1);
    TH1F *h3 = new TH1F("AFTER_TARGET_T","Angular distribution of the electrons (Theta)",60,0,90);
    h3->GetXaxis()->SetTitle("Theta, deg");
    h3->GetYaxis()->SetTitle("Number of the electrons");
    h3->SetLineColor(kBlue);
    h3->SetFillColorAlpha(kBlue, 0.1);
    h3->SetFillStyle(3001);
    TH1F *h30 = new TH1F("AFTER_MAGNET_T"," ",60,0,90);
    h30->SetLineColor(kRed);
    h30->SetFillColorAlpha(kRed, 0.1);
    h30->SetFillStyle(3001);
    
    i = 0;
    while (1)
    {
        while(i == 0)
        {
            in1>>par1;
            if(!in1.good())
            {
                i = 1;
                in1.close();
                h3->Draw();
                c1->Update();
                ps1 = (TPaveStats*)h3->GetListOfFunctions()->FindObject("stats");
                ps1->SetX1NDC(0.4);
                ps1->SetX2NDC(0.6);
                ps1->SetTextColor(kBlue);
                c1->cd();
                break;
            }
            h3->Fill(par1);
        }
        in10>>par10;
        if(!in10.good())
        {
            in10.close();
            h30->Draw("][sames");
            c1->Update();
            ps10 = (TPaveStats*)h30->GetListOfFunctions()->FindObject("stats");
            ps10->SetX1NDC(0.65);
            ps10->SetX2NDC(0.85);
            ps10->SetTextColor(kRed);
            c1->Update();
            c1->Print("../PNG/AFTER_E_T.png");
            c1->Clear();
            ps1->Clear();
            ps10->Clear();
            break;
        }
        h30->Fill(par10);
    }
    c1->Close();
}



