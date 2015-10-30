//g++ macro2.cpp GPT.cpp mroot.cpp -Wall -o2 -o mtest2 `root-config --cflags --glibs` -std=c++0x -pthread

#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <math.h> 
#include <thread>

#include "mroot.hpp"
#include "GPT.hpp"



using namespace std;

template <typename T> string tostr(const T& t) { 
   ostringstream os; 
   os<<t; 
   return os.str();
}


int main(int argc, char **argv)
{
bool res = false;  
const char* c; 
double mean;
double x, y, z;




vector< vector< vector <double> > > scintsurf;//main geometry
vector< vector< vector <double> > > sensorsurf;
vector<double> v1(3);
	
vector< lopi> ftime;
lopi lop;//see mroot for def of lopi struct
	
load_geometry(scintsurf, "Project1");//geometry
load_sensors(sensorsurf, "Project1");//sensors
int count = 0;

for(double h = -30; h < 30; ++h)
{
	for(double f = 10; f < 80; ++f)
	{
		//loading model
		printf("\n****Current Place*****       h: %f f: %f", h, f);
		vector< vector <double> > points;
		vector< double> point(3); 
		vector< vector< vector <double> > > AFpath;
		vector<double> pathtime;
		vector< vector <double> > scintillation; // scintillation.at(n) is start point and scintillation.at(n+1) is random direction for increments of n = n+2
		vector<int> sensindex;
		
		double r = 50, theta;
		
		z = h;
		theta = (f/360)*(2*3.14159265359);
		
		
		cyltocart(r, theta, z);
		v1.at(0) = r;
		v1.at(1) = theta;
		v1.at(2) = z;
		v1 = normalize(v1);
		
		r = v1.at(0);
		theta = v1.at(1);
		z = v1.at(2);
		printf("\n r: %f theta: %f z:  %f", r, theta, z);  
	
		scintillation = getscintpath(scintsurf, 100, r, theta, z, points);//positron path through scintillator 

		if(scintillation.size() > 0)
		{
			getphoton(AFpath, pathtime, scintsurf, sensorsurf, scintillation, sensindex);//generated multithreaded photon path data	     

		}
		else
		return 0;
	
		 if(AFpath.size() > 0 && pathtime.size() > 0)
		 { 
		  
		 // if(pathtime.size() > 0)
		  SignalTime(pathtime, mean);
		  
		  for(int i = 0; i < 1; i++)
		  {
		  point = points.at(i);
		  lop.i = count;
		  lop.m = mean;
		  lop.x = point.at(0);
		  lop.y = point.at(1);
		  lop.z = point.at(2);
		  ftime.push_back(lop);
		 
		  ++count;
		  }

		   
		 }
	 }
 }

TApplication theApp("App", &argc, argv);

scat4d(ftime);

theApp.Run();
  //nt->SetMarkerStyle(21);
   //nt->Draw("x:y:z:m","","glcolz");
   
  
   

   
 
return 0; 
}//end of macro
