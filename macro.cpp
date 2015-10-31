//g++ macro.cpp GPT.cpp mroot.cpp -Wall -o2 -o test1 `root-config --cflags --glibs` -std=c++0x -pthread

#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <math.h> 
#include "TApplication.h"
#include <thread>
#include "mROOT/mroot.hpp"
#include "gPT/GPT.hpp"



using namespace std;



int main(int argc, char **argv)
{
bool res = false;  

//vectors for data
vector< vector< vector <double> > > AFpath;
vector<double> pathtime;
vector< vector< vector <double> > > scintsurf;//main geometry
vector< vector< vector <double> > > sensorsurf;//sensors + main geometry
vector< vector <double> > points;
vector< vector <double> > scintillation; // scintillation.at(n) is start point and scintillation.at(n+1) is random direction for increments of n = n+2
vector<int> sensindex;


//------------------------------------------loading model-----------------------------------------------//
load_geometry(scintsurf, "Project1");//geometry
load_sensors(sensorsurf, "Project1");//sensors





//-------------------------------------------Generating Scintillation-----------------------------------//

//scintillation = getlaserpulse(scintsurf, 100, 1.0, 1.0, 0.00000001, points);//laser path in scintillator
scintillation = getscintpath(scintsurf, 5000, 1.0, 1.0, 2.0, points);//positron path through scintillator 





//----------------------------------------Propagating/Detecting Photons---------------------------------//
if(scintillation.size() > 0)
{
	getphoton(AFpath, pathtime, scintsurf, sensorsurf, scintillation, sensindex);//generated multithreaded photon path data	     	

}
else
return 0;



//---------------------------------------OpenGl visualization------------------------------------------//

if(AFpath.size() > 0)
{
	Tanimate(AFpath);//reorganize for fancy animation
	res = cadpath(AFpath, "visopengl/visualizer1/pdata.txt");//generate file for opengl
}
else
return 0;
 
 
 
//---------------------------------------ROOT analysis--------------------------------------------------// 
	
if(AFpath.size() > 0)
{ 
	TApplication theApp("App", &argc, argv);
	SignalTime(pathtime, sensindex);//display singal timings in root
	visroot(scintillation,sensorsurf,scintsurf,AFpath,pathtime);
	theApp.Run();

}
else
return 0;
 
 
 
 
 
 
return 1; 
}
