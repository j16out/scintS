#ifndef GPT_INCLUDED
#define GPT_INCLUDED
//g++ macro.cpp GPT.cpp mroot.cpp -Wall -o2 -o test1 `root-config --cflags --glibs` -std=c++0x -pthread


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




//project loader
void load_geometry(vector< vector <vector <double> > > & surfvec, string cadfile);

void load_sensors(vector< vector <vector <double> > > & surfvec, string cadfile);

//Photon Path Generator
void getphoton(vector< vector< vector <double> > > & AFpath, vector<double> & pathtime, vector< vector <vector <double> > > scintsurf, vector< vector <vector <double> > > sensorsurf, vector< vector <double> > scintillation, vector <int> & sensindex);

//Random Start Points/Directions for photons/positron animation
vector< vector <double> > getscintpath(vector< vector <vector <double> > > surf1, float num, double x, double y, double z, vector < vector < double> > & points);
bool cadpath(vector< vector <vector <double> > > Gpaths, const char* filename);

//Generate random points for laser pulse inside scintillator
vector< vector <double> > getlaserpulse(vector< vector <vector <double> > > surf1, float num, double x, double y, double z, vector < vector < double> > & points);
bool cadpath(vector< vector <vector <double> > > Gpaths, const char* filename);

//Generated points between reflected points for animation purposes
void Tanimate(vector< vector <vector <double> > > & AFpath);

//math functions
void cyltocart(double & r, double & theta, double & z);
vector<double> normalize(vector<double> v1);

#endif
