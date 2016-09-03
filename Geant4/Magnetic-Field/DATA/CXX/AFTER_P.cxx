void AFTER_P() {
    
    ifstream in1, in10;
    in1.open("../AFTER_TARGET/P_E.dat");
    in10.open("../AFTER_MAGNET/P_E.dat");
    assert(in1.is_open());
    assert(in10.is_open());
    Double_t par1;
    Double_t par10;
    TPaveStats *ps1;
    TPaveStats *ps10;

    TCanvas *c1 = new TCanvas("Canvas1", "Canvas", 1280, 720);
    c1->SetLogy(1);
    TH1F *h1 = new TH1F("AFTER_TARGET_E","Energy spectrum of the positrons",90,0,6000);
    h1->GetXaxis()->SetTitle("Energy, MeV");
    h1->GetYaxis()->SetTitle("Number of the positrons");
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
            c1->Print("../PNG/AFTER_P_E.png");
            c1->Clear();
            ps1->Clear();
            ps10->Clear();
            break;
        }
        h10->Fill(par10);
    }

    in1.open("../AFTER_TARGET/P_P.dat");
    in10.open("../AFTER_MAGNET/P_P.dat");
    assert(in1.is_open());
    assert(in10.is_open());

    c1->SetLogy(1);
    TH1F *h2 = new TH1F("AFTER_TARGET_P","Angular distribution of the positrons (Phi)",60,-180,180);
    h2->GetXaxis()->SetTitle("Phi, deg");
    h2->GetYaxis()->SetTitle("Number of the positrons");
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
            c1->Print("../PNG/AFTER_P_P.png");
            c1->Clear();
            ps1->Clear();
            ps10->Clear();
            break;
        }
        h20->Fill(par10);
    }
    
    in1.open("../AFTER_TARGET/P_T.dat");
    in10.open("../AFTER_MAGNET/P_T.dat");
    assert(in1.is_open());
    assert(in10.is_open());
    
    c1->SetLogy(1);
    TH1F *h3 = new TH1F("AFTER_TARGET_T","Angular distribution of the positrons (Theta)",60,0,90);
    h3->GetXaxis()->SetTitle("Theta, deg");
    h3->GetYaxis()->SetTitle("Number of the positrons");
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
            c1->Print("../PNG/AFTER_P_T.png");
            c1->Clear();
            ps1->Clear();
            ps10->Clear();
            break;
        }
        h30->Fill(par10);
    }
    
    ifstream in2, in20;
    in1.open("../AFTER_TARGET/P_MX.dat");
    in10.open("../AFTER_MAGNET/P_MX.dat");
    in2.open("../AFTER_TARGET/P_MY.dat");
    in20.open("../AFTER_MAGNET/P_MY.dat");
    assert(in1.is_open());
    assert(in10.is_open());
    assert(in2.is_open());
    assert(in20.is_open());
    Double_t par2;
    Double_t par20;
    
    c1->SetLogy(1);
    TH1F *h4 = new TH1F("AFTER_TARGET_MT","Transverse momentum of the positrons",100,0,200);
    h4->GetXaxis()->SetTitle("Transverse momentum, MeV/c");
    h4->GetYaxis()->SetTitle("Number of the positrons");
    h4->SetLineColor(kBlue);
    h4->SetFillColorAlpha(kBlue, 0.1);
    h4->SetFillStyle(3001);
    TH1F *h40 = new TH1F("AFTER_MAGNET_MT"," ",100,0,200);
    h40->SetLineColor(kRed);
    h40->SetFillColorAlpha(kRed, 0.1);
    h40->SetFillStyle(3001);
    
    i = 0;
    while (1)
    {
        while(i == 0)
        {
            in1>>par1;
            in2>>par2;
            if(!in1.good() && !in2.good())
            {
                i = 1;
                in1.close();
                in2.close();
                h4->Draw();
                c1->Update();
                ps1 = (TPaveStats*)h4->GetListOfFunctions()->FindObject("stats");
                ps1->SetX1NDC(0.4);
                ps1->SetX2NDC(0.6);
                ps1->SetTextColor(kBlue);
                c1->cd();
                break;
            }
            h4->Fill(sqrt(par1*par1 + par2*par2));
        }
        in10>>par10;
        in20>>par20;
        if(!in10.good() && !in20.good())
        {
            in10.close();
            in20.close();
            h40->Draw("][sames");
            c1->Update();
            ps10 = (TPaveStats*)h40->GetListOfFunctions()->FindObject("stats");
            ps10->SetX1NDC(0.65);
            ps10->SetX2NDC(0.85);
            ps10->SetTextColor(kRed);
            c1->Update();
            c1->Print("../PNG/AFTER_P_MT.png");
            c1->Clear();
            ps1->Clear();
            ps10->Clear();
            break;
        }
        h40->Fill(sqrt(par10*par10 + par20*par20));
    }

    in1.open("../AFTER_TARGET/P_X.dat");
    in10.open("../AFTER_MAGNET/P_X.dat");
    assert(in1.is_open());
    assert(in10.is_open());
    
    c1->SetLogy(0);
    TH1F *h5 = new TH1F("AFTER_TARGET_X","Positron beam",100,-20,20);
    h5->GetXaxis()->SetTitle("X, mm");
    h5->GetYaxis()->SetTitle("Number of the positrons");
    h5->SetLineColor(kBlue);
    h5->SetFillColorAlpha(kBlue, 0.1);
    h5->SetFillStyle(3001);
    TH1F *h50 = new TH1F("AFTER_MAGNET_X"," ",100,-20,20);
    h50->SetLineColor(kRed);
    h50->SetFillColorAlpha(kRed, 0.1);
    h50->SetFillStyle(3001);
    
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
                h5->Draw();
                c1->Update();
                ps1 = (TPaveStats*)h5->GetListOfFunctions()->FindObject("stats");
                ps1->SetX1NDC(0.15);
                ps1->SetX2NDC(0.35);
                ps1->SetTextColor(kBlue);
                c1->cd();
                break;
            }
            h5->Fill(par1);
        }
        in10>>par10;
        if(!in10.good())
        {
            in10.close();
            h50->Draw("][sames");
            c1->Update();
            ps10 = (TPaveStats*)h50->GetListOfFunctions()->FindObject("stats");
            ps10->SetX1NDC(0.65);
            ps10->SetX2NDC(0.85);
            ps10->SetTextColor(kRed);
            c1->Update();
            c1->Print("../PNG/AFTER_P_X.png");
            c1->Clear();
            ps1->Clear();
            ps10->Clear();
            break;
        }
        h50->Fill(par10);
    }
    
    in1.open("../AFTER_TARGET/P_Y.dat");
    in10.open("../AFTER_MAGNET/P_Y.dat");
    assert(in1.is_open());
    assert(in10.is_open());
    
    c1->SetLogy(0);
    TH1F *h6 = new TH1F("AFTER_TARGET_Y","Positron beam",100,-20,20);
    h6->GetXaxis()->SetTitle("Y, mm");
    h6->GetYaxis()->SetTitle("Number of the positrons");
    h6->SetLineColor(kBlue);
    h6->SetFillColorAlpha(kBlue, 0.1);
    h6->SetFillStyle(3001);
    TH1F *h60 = new TH1F("AFTER_MAGNET_Y"," ",100,-20,20);
    h60->SetLineColor(kRed);
    h60->SetFillColorAlpha(kRed, 0.1);
    h60->SetFillStyle(3001);
    
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
                h6->Draw();
                c1->Update();
                ps1 = (TPaveStats*)h6->GetListOfFunctions()->FindObject("stats");
                ps1->SetX1NDC(0.15);
                ps1->SetX2NDC(0.35);
                ps1->SetTextColor(kBlue);
                c1->cd();
                break;
            }
            h6->Fill(par1);
        }
        in10>>par10;
        if(!in10.good())
        {
            in10.close();
            h60->Draw("][sames");
            c1->Update();
            ps10 = (TPaveStats*)h60->GetListOfFunctions()->FindObject("stats");
            ps10->SetX1NDC(0.65);
            ps10->SetX2NDC(0.85);
            ps10->SetTextColor(kRed);
            c1->Update();
            c1->Print("../PNG/AFTER_P_Y.png");
            c1->Clear();
            ps1->Clear();
            ps10->Clear();
            break;
        }
        h60->Fill(par10);
    }
    c1->Close();
}



