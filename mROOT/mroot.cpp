#include "mroot.hpp"

using namespace std;



const Double_t tempLowEdge = 0.01;

Double_t transfer_function(Double_t *x, Double_t * /*param*/)
{
   //This function is required to suppress
   //boxes for empty bins - make them transparent.
   if (x)
      return *x > tempLowEdge ? 1. : 0.;
   
   return 0.;
}



void scat4d(vector< lopi> ftime)
{ 
lopi lop;
TFile* outfile = new TFile("results/test3.root", "new");
TList* hList = new TList();
gROOT->Reset();
const unsigned nBins = 50;
double time;
double x, y, z;	

TH3F * const hist = new TH3F("", "", nBins, 0., 50., nBins, 0., 50., nBins, -60., 60.);

TList * const lof = hist->GetListOfFunctions();
lof->Add(new TF1("TransferFunction", transfer_function, 0., 1000., 0));

gStyle->SetCanvasPreferGL(true); 
gStyle->SetPalette(55);  

  for(int i = 0; i < ftime.size(); ++i)
 {
  lop = ftime.at(i);
  time = lop.m;
  x= lop.x;
  y =  lop.y;
  z = lop.z;
 hist->Fill(x,y,z,time);
  printf( "\n x: %f y: %f z: %f mean: %f", x,y,z,time);
  }

 
  for (unsigned i = 0; i < nBins; ++i) {
      for (unsigned j = 0; j < nBins; ++j) {
         for (unsigned k = 0; k < nBins; ++k) {
            if (!hist->GetBinContent(i + 1, j + 1, k + 1))
               hist->SetBinContent(i + 1, j + 1, k + 1, tempLowEdge);
         }
      }
   }
 
 
   

hist->Draw("glcolz");
  hList->Add(hist);
  hList->Write();
}


void SignalTime(vector<double> pathtime, double & time)
{ 
         
    
     
     
     
     
     // TCanvas *c1 = new TCanvas("c1","The FillRandom example",500,10,500,500);
      vector<float> graphs1A (20000), graphs1B (20000);
      float tomp, x, y;
      float PEthres = 1;
      
      
      for(int i = 0; i < graphs1A.size(); ++i)
	{
	graphs1A.at(i) = -5*PEthres;
	}
	
      for(int n = 0; n < pathtime.size(); ++n)
	{
	for(int i = 0; i < graphs1A.size(); ++i)
		{  
	          tomp = -(11.94)*(exp(-((i*.001)-pathtime.at(n))/2.341)-exp(-((i*.001)-pathtime.at(n))/9.526));
	          if (tomp > 0)
		   graphs1A.at(i) = tomp + graphs1A.at(i);
		  else
		   graphs1A.at(i) = 0 + graphs1A.at(i);
		 } 
	}
	
	
	for(int i = 0; i < graphs1A.size(); ++i)
		{
		graphs1B.at(i) = abs(graphs1A.at(i));
		}
	float lo = 100;
         int loi = 0;
        for(int i = 0; i < 9000; ++i)
		{
		tomp = graphs1B.at(i);
			if(tomp < lo)
			{lo = tomp;
			loi = i;
			}
			
		}
	time = loi*.001;
	
	/*TGraph *fsum = new TGraph();
for (float i = 0; i < graphs1A.size(); ++i)
	{
	x = i*.001;
	tomp = graphs1A.at(i);
	y = tomp;
	fsum->SetPoint(i,x,y);
	}
   fsum->SetLineColor(4);
   fsum->SetLineWidth(2);
//fsum->GetYaxis()->SetRangeUser(0,6000); 
   fsum->GetXaxis()->SetRangeUser(0,100);
   fsum->SetTitle("SiPM Array 1;Time (ns);Amplitude (mV)");
   fsum->Draw("AL");
   c1->Update();*/			 	
		
}

void SignalTime(vector<double> pathtime, vector<int> sensindex)
{ 
         
     	TGraph *fsum1 = new TGraph();
	TGraph *fsum2 = new TGraph();
	TGraph *fsum3 = new TGraph();
	TGraph *fsum4 = new TGraph();
     
     
   TCanvas *c9 = new TCanvas("c9","The FillRandom example",500,10,500,500);
     c9->cd();
		TH1D * OutHist = new TH1D("data", "", 500, 0, 50);
		TF1 *mfit1 = new TF1("mfit1","gaus");

		float ftime;
		if(pathtime.size() > 0)
		{
		for (float i = 0; i < pathtime.size(); ++i)
			{	    	    
				ftime = pathtime.at(i);
				OutHist->Fill(ftime);
		
			}

		OutHist->SetLineColor(1);     
			OutHist->SetFillStyle(3005);
			OutHist->SetFillColor(4);//blue
	
		OutHist->SetTitle("Photon Arrival Times; Time (ns); N");
		OutHist->Fit("mfit1","LL","",-3,15);
		gStyle->SetOptFit();
		OutHist->Draw(); 
		}
		else
		cout <<"\n nothing in pathtime";   
     
     
for(int q = 0; q < sensorindex1.size()-1; ++q)
{   
     
     // TCanvas *c1 = new TCanvas("c1","The FillRandom example",500,10,500,500);
      vector<float> graphs1A (100000), graphs1B (100000);
      float tomp, x, y;
      float PEthres = 1;
      float time;
      
      for(int i = 0; i < graphs1A.size(); ++i)
	{
	graphs1A.at(i) = -5*PEthres;
	}
	
      for(int n = 0; n < pathtime.size(); ++n)
	{
	
	if(q+1 == sensindex.at(n))
	{
		for(int i = 0; i < graphs1A.size(); ++i)
			{  
			  tomp = -(11.94)*(exp(-((i*.001)-pathtime.at(n))/2.341)-exp(-((i*.001)-pathtime.at(n))/9.526));
			  if (tomp > 0)
			   graphs1A.at(i) = tomp + graphs1A.at(i);
			  else
			   graphs1A.at(i) = 0 + graphs1A.at(i);
			 } 
		}
	}
	
	
	for(int i = 0; i < graphs1A.size(); ++i)
		{
		graphs1B.at(i) = abs(graphs1A.at(i));
		}
	float lo = 100;
         int loi = 0;
        for(int i = 0; i < 9000; ++i)
		{
		tomp = graphs1B.at(i);
			if(tomp < lo)
			{lo = tomp;
			loi = i;
			}
			
		}
	time = loi*.001;
	
for (float i = 0; i < graphs1A.size(); ++i)
	{
	x = i*.001;
	tomp = graphs1A.at(i);
	y = tomp;
	if(q == 0)
	fsum1->SetPoint(i,x,y);
	if(q == 1)
	fsum2->SetPoint(i,x,y);
	if(q == 2)
	fsum3->SetPoint(i,x,y);
	if(q == 3)
	fsum4->SetPoint(i,x,y);

	}
		
	
}
double max1, q1, q2, q3;
double max2;
double max3;
double max4;
fsum1->ComputeRange(q1,q2, q3, max1);
fsum2->ComputeRange(q1,q2, q3, max2);
fsum3->ComputeRange(q1,q2, q3, max3);
fsum4->ComputeRange(q1,q2, q3, max4);

max1 = (max1+max2+max3+max4)/2;
cout << "\n max1  " << max1;	
	
TCanvas *c4= new TCanvas("c4","The FillRandom example",500,10,900,900);
c4->cd();	

   fsum1->SetLineColor(4);
   fsum2->SetLineColor(3);
   fsum3->SetLineColor(6);
   fsum4->SetLineColor(2);

//fsum->GetYaxis()->SetRangeUser(0,6000); 
  fsum1->GetXaxis()->SetRangeUser(0,100);
  fsum1->GetYaxis()->SetRangeUser(0,max1);
TF1 *myfit = new TF1("myfit","(x-[3]>0)*(-([2])*(exp(-(x-[3])/[0])-exp(-(x-[3])/[1])))", 0,100);
TF1 *myfit1 = new TF1("myfit1","(x-[3]>0)*(-([2])*(exp(-(x-[3])/[0])-exp(-(x-[3])/[1])))", 0,100);
TF1 *myfit2 = new TF1("myfit2","(x-[3]>0)*(-([2])*(exp(-(x-[3])/[0])-exp(-(x-[3])/[1])))", 0,100);
TF1 *myfit3 = new TF1("myfit3","(x-[3]>0)*(-([2])*(exp(-(x-[3])/[0])-exp(-(x-[3])/[1])))", 0,100);
myfit->SetParameter(0, 5);
myfit->SetParameter(1, 10);
myfit->SetParameter(2, 1000);
myfit->SetParameter(3, 0);

myfit1->SetParameter(0, 5);
myfit1->SetParameter(1, 10);
myfit1->SetParameter(2, 1000);
myfit1->SetParameter(3, 0);

myfit2->SetParameter(0, 5);
myfit2->SetParameter(1, 10);
myfit2->SetParameter(2, 1000);
myfit2->SetParameter(3, 0);

myfit3->SetParameter(0, 5);
myfit3->SetParameter(1, 10);
myfit3->SetParameter(2, 1000);
myfit3->SetParameter(3, 0);

myfit->SetParNames("#tau_{Rise}", "#tau_{Fall}", "V_{max}", "t_{o}");
myfit->SetLineWidth(2);
myfit->SetLineColor(1);
gStyle->SetOptFit();

myfit1->SetParNames("#tau_{Rise}", "#tau_{Fall}", "V_{max}", "t_{o}");
myfit1->SetLineWidth(2);
myfit1->SetLineColor(1);
gStyle->SetOptFit();

myfit2->SetParNames("#tau_{Rise}", "#tau_{Fall}", "V_{max}", "t_{o}");
myfit2->SetLineWidth(2);
myfit2->SetLineColor(1);
gStyle->SetOptFit();

myfit3->SetParNames("#tau_{Rise}", "#tau_{Fall}", "V_{max}", "t_{o}");
myfit3->SetLineWidth(2);
myfit3->SetLineColor(1);
gStyle->SetOptFit();
   
fsum1->Fit("myfit","M","",0, 100); 
fsum2->Fit("myfit1","M","",0, 100); 
fsum3->Fit("myfit2","M","",0, 100); 
fsum4->Fit("myfit3","M","",0, 100);   
   fsum1->SetTitle("SiPM Signal Array 1;Time (ns);Amplitude (mV)");
   fsum1->Draw("AL");
    fsum2->Draw("sameL");
     fsum3->Draw("sameL");
      fsum4->Draw("sameL");
  fsum1->GetYaxis()->SetRangeUser(0,max1);
   c4->Update();			 	
		
}






TH1D * SensHist(vector<double> pathtime)
{ 
                TH1D * OutHist = new TH1D("data", "", 500, 0, 15);
		TF1 *mfit1 = new TF1("mfit1","gaus");

		float ftime;
		if(pathtime.size() > 0)
		{
		for (float i = 0; i < pathtime.size(); ++i)
			{	    	    
				ftime = pathtime.at(i);
				OutHist->Fill(ftime);
		
			}

		OutHist->SetLineColor(1);     
			OutHist->SetFillStyle(3005);
			OutHist->SetFillColor(4);//blue
	
		OutHist->SetTitle("Photon Arrival Times; Time (ns); N");
		OutHist->Fit("mfit1","LL","",-3,15);
		gStyle->SetOptFit();
		}
		else
		cout <<"\n nothing in pathtime";
		return OutHist;
}

void SensHist2(vector<double> pathtime, double & mean)
{ 
                TCanvas *c1 = new TCanvas("c1","The FillRandom example",500,10,900,900);
                TH1D * OutHist = new TH1D("data", "", 500, 0, 15);
		TF1 *mfit1 = new TF1("mfit1","gaus");

		float ftime;
		if(pathtime.size() > 0)
		{
		for (float i = 0; i < pathtime.size(); ++i)
			{	    	    
				ftime = pathtime.at(i);
				OutHist->Fill(ftime);
		
			}

		OutHist->SetLineColor(1);     
			OutHist->SetFillStyle(3005);
			OutHist->SetFillColor(4);//blue
	
		OutHist->SetTitle("Photon Arrival Times; Time (ns); N");
		OutHist->Fit("mfit1","LL","",0,15);
		mean = mfit1->GetParameter("Mean");
		//gStyle->SetOptFit();
		}
		else
		cout <<"\n nothing in pathtime";
		
}




void visroot(vector< vector <double> > scintillation,vector< vector< vector <double> > > sensorsurf,vector< vector< vector <double> > > scintsurf,vector< vector< vector <double> > > AFpath, vector<double> pathtime)
{
	cout << "\nsize" << sensorindex1.size();
	if(AFpath.size() > 0)
	{
	
	        
	        double xx1, yy1, zz1;
	        
		TCanvas *c1 = new TCanvas("c1","The FillRandom example",500,10,900,900);
		TCanvas *c2 = new TCanvas("c2","The FillRandom example",500,10,700,700);
		//TCanvas *c3 = new TCanvas("c3","The FillRandom example",250,10,700,700);

		
		TGraph2D *gr = new TGraph2D();
		TGraph2D *gr2 = new TGraph2D();
		TGraph2D *gr3 = new TGraph2D();
		TGraph2D *gr4 = new TGraph2D();
		c1->cd();

		//TGraph *gr3 = new TGraph();
		vector< vector<double> > tpath;
		vector<double> tpos(3);
		cout << "\n size: " << AFpath.size();
		int ksie = 0;
		
		if(AFpath.size() > 0)
		{
			for(int n = 0; n < AFpath.size(); ++n)
			{
				tpath = AFpath.at(n);
				bool grun = true;
				bool back = false;
				int k = 0;

				while(grun)
				{
				tpos = tpath.at(k);		
				xx1 = tpos.at(0);
				yy1 = tpos.at(1);
				zz1 = tpos.at(2);
				//cout << "\n"<< i << " : "<< x << " & "<< y << " & " << z;  
				gr->SetPoint((ksie),xx1,yy1,zz1);
				++ksie;
	
				if(back)
				--k;
				else
				++k;
	
				if(k == tpath.size()-1)
				back = true;
	
				if(back && k == 0)
				grun = false;

				}
	
			}	
		AFpath.clear();
		}
		else
		cout << "\n AFpath is zero";
			vector<vector<double> > set(3);
			vector<double> point0(3);
			vector<double> point1(3);
			vector<double> point2(3);
			double xf, yf, zf;//out	
			
		if(scintillation.size() > 0)
		{int p = 0;	
			for(int n = 0; n < scintillation.size(); n = n+2)
			{
			     point0 = scintillation.at(n);
				xf = point0.at(0);
				yf = point0.at(1);
				zf = point0.at(2);
				gr4->SetPoint(p,xf,yf,zf);				
				++p;
			}
		}
				
		if(scintsurf.size() > 0)
		{	
			for(int n = 0; n < scintsurf.size(); ++n)
			{++ksie;

			     set = scintsurf.at(n);
			     point0 = set.at(0);
			     point1 = set.at(1);
			     point2 = set.at(2);
				xf = point0.at(0);
				yf = point0.at(1);
				zf = point0.at(2);		
				gr2->SetPoint(3*n,xf,yf,zf);
				xf = point1.at(0);
				yf = point1.at(1);
				zf = point1.at(2);
				gr2->SetPoint(3*n+1,xf,yf,zf);
				xf = point2.at(0);
				yf = point2.at(1);
				zf = point2.at(2);
				gr2->SetPoint(3*n+2,xf,yf,zf);

			}
		}

		for(int n = 0; n < sensorsurf.size(); ++n)
		{++ksie;

		     set = sensorsurf.at(n);
		     point0 = set.at(0);
		     point1 = set.at(1);
		     point2 = set.at(2);

			xf = point0.at(0);
			yf = point0.at(1);
			zf = point0.at(2);
			gr3->SetPoint(3*n,xf,yf,zf);
			xf = point1.at(0);
			yf = point1.at(1);
			zf = point1.at(2);
			gr3->SetPoint(3*n+1,xf,yf,zf);
			xf = point2.at(0);
			yf = point2.at(1);
			zf = point2.at(2);
			gr3->SetPoint(3*n+2,xf,yf,zf);

		}
		
		float ax = 70;
		//gr->GetXaxis()->SetRangeUser(-ax,ax); 
		//gr->GetYaxis()->SetRangeUser(-ax,ax); 
		gr->GetZaxis()->SetRangeUser(-ax,ax);
		//gr2->GetXaxis()->SetRangeUser(-ax,ax); 
		//gr2->GetYaxis()->SetRangeUser(-ax,ax); 
		gr2->GetZaxis()->SetRangeUser(-ax,ax);
		gr->SetTitle("Photon Scintillation Trajectory");
		gr2->SetMarkerStyle(10);
		gr4->SetLineWidth(1);

		gr3->SetLineWidth(1);
		gr3->SetLineColor(2);

		gr->SetLineWidth(1.5);
		gr->SetLineColor(4);

		gr2->Draw("pcolz");
		gr3->Draw("sameline");
		gr->Draw("sameline");
		gr4->Draw("sameline");

		//***************************************************histogram

		c2->cd();
		TH1D * OutHist = new TH1D("data", "", 500, 0, 15);
		TF1 *mfit1 = new TF1("mfit1","gaus");

		float ftime;
		if(pathtime.size() > 0)
		{
		for (float i = 0; i < pathtime.size(); ++i)
			{	    	    
				ftime = pathtime.at(i);
				OutHist->Fill(ftime);
		
			}

		OutHist->SetLineColor(1);     
			OutHist->SetFillStyle(3005);
			OutHist->SetFillColor(4);//blue
	
		OutHist->SetTitle("Photon Arrival Times; Time (ns); N");
		OutHist->Fit("mfit1","LL","",-3,15);
		gStyle->SetOptFit();
		OutHist->Draw(); 
		}
		else
		cout <<"\n nothing in pathtime";

}
else
cout << "\n positron missed surface";

}//end of main

