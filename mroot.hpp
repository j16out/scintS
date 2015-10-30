#ifndef MROOT_INCLUDED
#define MROOT_INCLUDED

#include "TF1.h"
#include <TAxis.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph2D.h>
#include <TGraph.h>
#include "TF1.h"
#include "TH2F.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TFile.h"
#include "TApplication.h"
#include <TLatex.h>
#include <TImage.h>
#include <TRandom3.h>
#include <TMultiGraph.h>
#include <TLegend.h>
#include <TPad.h>
#include <TFrame.h>
#include "TH3.h"
#include "TNtuple.h"

#include <TRandom3.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <math.h> 
#include <thread>
#include <stdio.h>
#include <iterator>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

extern vector< int> sensorindex1;

struct lopi
{
  double i, m, x, y, z;
};

template <typename T> string tostr(const T& t) { 
   ostringstream os; 
   os<<t; 
   return os.str();
}


TH1D * SensHist(vector<double> pathtime);
void SensHist2(vector<double> pathtime, double & mean);
void SignalTime(vector<double> pathtime, double & time);
void SignalTime(vector<double> pathtime, vector<int> sensindex);
void scat4d(vector< lopi> ftime);

void visroot(vector< vector <double> > scintillation,vector< vector< vector <double> > > sensorsurf,vector< vector< vector <double> > > scintsurf,vector< vector< vector <double> > > AFpath, vector<double> pathtime);

#endif
