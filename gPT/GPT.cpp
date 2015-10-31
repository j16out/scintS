//g++ macro.cpp GPT.cpp -Wall -o2 -o test1 `root-config --cflags --glibs` -std=c++0x -pthread
#include "GPT.hpp"

using namespace std;

vector< int> sensorindex1;


#define SMALL_NUM   0.00000001 // anything that avoids division overflow

//convert variabes to string
template <typename T> string tostr(const T& t) { 
   ostringstream os; 
   os<<t; 
   return os.str();
}

//quaternion stuff
struct quaternion
{
  double x, y, z, w;
};

vector< double> View (3);
vector< double> View2 (3);
vector< double> Axis (3);




//quarternion functions
quaternion mult(quaternion A, quaternion B);
quaternion conjugate(quaternion quat);
quaternion normalizeq(quaternion quat);
void Rotate(double Angle, double x, double y, double z);
double length(quaternion quat);

//vector operations functions
vector<double> cross(vector<double> v1, vector<double> v2);
double dot(vector<double> v1, vector<double> v2);
vector<double> addvec(vector<double> v1, vector<double> v2);
vector<double> subvec(vector<double> v1, vector<double> v2);
vector<double> refvec(vector<double> v1, vector<double> v2, double sub);
vector<double> vecaddnum(vector<double> v1, double f1, double f2, double f3);
vector<double> trans(vector<double> v1, vector<double> v2, vector<double> v3, double n1, double n2, vector<double> ddir, vector<double> & I);



//random generator from root
TRandom *gRandom = new TRandom3();


//main function declarations
int triangledetect(vector< vector<double> > T, vector< vector<double> > P, vector<double> & I, vector<double> & R,  vector<double> & nnn, vector<double> & ddir, double & theta);

void gen(vector< vector< vector <double> > > & AFpath, vector<double> & pathtime, vector< vector <vector <double> > > surf1, vector< vector <vector <double> > > surfFinal, vector< vector <double> > scint, vector <int> & sensindex, string mode, int start, int stop);

void animate(vector< vector <vector <double> > > & AFpath, int start, int last);

void getcad(vector< vector <vector <double> > > & surfvec, string cadfile, string mode1);
bool file_exists(string& name);


bool file_exists(string& name)
{
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}



//****************************************************************************************************//
//*************************************start of main functions****************************************//
//****************************************************************************************************//
//---------------------------Load Sensors-------------------------------------------------------------//
void load_sensors(vector< vector <vector <double> > > & surfvec, string cadfile)
{ 
 bool run = true;
 sensorindex1.push_back(0);
 float k = 1;
 while(run)
  {string temp = cadfile;
  temp.append("/sensors/s");
  temp.append(tostr(k));
  temp.append(".ast");
	  if(file_exists(temp))
	  {
	  getcad(surfvec, temp,"V");
	  sensorindex1.push_back(surfvec.size());
	  //cout << "\n" << surfvec.size();
	  }
	  else
	  run = false;
  ++k;
  }
}

//----------------------------load geometry-------------------------------------------------------//
void load_geometry(vector< vector <vector <double> > > & surfvec, string cadfile)
{
 bool run = true;
 
 float k = 1;
 while(run)
  {string temp = cadfile;
  temp.append("/geometry/g");
  temp.append(tostr(k));
  temp.append(".ast");
	  if(file_exists(temp))
	  {
	  getcad(surfvec, temp,"V");
	  //cout << "\n" << surfvec.size();
	  }
	  else
	  run = false;
  ++k;
  }
}

//----------------------------Photon path generation threading-------------------------------------//

void getphoton(vector< vector< vector <double> > > & AFpath, vector<double> & pathtime, vector< vector <vector <double> > > scintsurf, vector< vector <vector <double> > > sensorsurf, vector< vector <double> > scintillation, vector <int> & sensindex)
{
cout << "\n\nStarting Photon Path Generation\n";
vector< vector< vector <double> > > AFpath1;
vector< vector< vector <double> > > AFpath2;
vector< vector< vector <double> > > AFpath3;
vector< vector< vector <double> > > AFpath4;
vector< vector< vector <double> > > AFpath5;
vector< vector< vector <double> > > AFpath6;
vector< vector< vector <double> > > AFpath7;
vector<double> pathtime1;
vector<double> pathtime2;
vector<double> pathtime3;
vector<double> pathtime4;
vector<double> pathtime5;
vector<double> pathtime6;
vector<double> pathtime7;
vector<int> sensindex1;
vector<int> sensindex2;
vector<int> sensindex3;
vector<int> sensindex4;
vector<int> sensindex5;
vector<int> sensindex6;
vector<int> sensindex7;
int jobsize = scintillation.size();
//cout << "\n jobsize: " << jobsize;

int range1 = jobsize*0.14;
int range2 = jobsize*0.28;
int range3 = jobsize*0.42;
int range4 = jobsize*0.56;
int range5 = jobsize*0.70;
int range6 = jobsize*0.84;

if(range1%2 != 0)
{++range1;
}
if(range2%2 != 0)
{++range2;
}
if(range3%2 != 0)
{++range3;
}
if(range4%2 != 0)
{++range4;
}
if(range5%2 != 0)
{++range5;
}
if(range6%2 != 0)
{++range6;
}

thread t1(gen, ref(AFpath1), ref(pathtime1), scintsurf, sensorsurf, scintillation, ref(sensindex1),"RT", 0, range1);
thread t2(gen, ref(AFpath2), ref(pathtime2), scintsurf, sensorsurf, scintillation, ref(sensindex2),"RT", range1,range2 );
thread t3(gen, ref(AFpath3), ref(pathtime3), scintsurf, sensorsurf, scintillation, ref(sensindex3),"RT", range2, range3);
thread t4(gen, ref(AFpath4), ref(pathtime4), scintsurf, sensorsurf, scintillation, ref(sensindex4),"RT", range3, range4);
thread t5(gen, ref(AFpath5), ref(pathtime5), scintsurf, sensorsurf, scintillation, ref(sensindex5),"RT", range4, range5);
thread t6(gen, ref(AFpath6), ref(pathtime6), scintsurf, sensorsurf, scintillation, ref(sensindex6),"RT", range5,range6 );
thread t7(gen, ref(AFpath7), ref(pathtime7), scintsurf, sensorsurf, scintillation, ref(sensindex7),"RT", range6, jobsize);


t1.join();
t2.join();
t3.join();
t4.join();
t5.join();
t6.join();
t7.join();




AFpath.reserve( AFpath1.size() + AFpath2.size() + AFpath3.size() + AFpath4.size() + AFpath5.size() + AFpath6.size() + AFpath7.size()); // preallocate memory
AFpath.insert( AFpath.end(), AFpath1.begin(), AFpath1.end() );
AFpath.insert( AFpath.end(), AFpath2.begin(), AFpath2.end() );
AFpath.insert( AFpath.end(), AFpath3.begin(), AFpath3.end() );
AFpath.insert( AFpath.end(), AFpath4.begin(), AFpath4.end() );
AFpath.insert( AFpath.end(), AFpath5.begin(), AFpath5.end() );
AFpath.insert( AFpath.end(), AFpath6.begin(), AFpath6.end() );
AFpath.insert( AFpath.end(), AFpath7.begin(), AFpath7.end() );



pathtime.reserve( pathtime1.size() + pathtime2.size() + pathtime3.size() + pathtime4.size() + pathtime5.size() + pathtime6.size() + pathtime7.size()); // preallocate memory
pathtime.insert( pathtime.end(), pathtime1.begin(), pathtime1.end() );
pathtime.insert( pathtime.end(), pathtime2.begin(), pathtime2.end() );
pathtime.insert( pathtime.end(), pathtime3.begin(), pathtime3.end() );
pathtime.insert( pathtime.end(), pathtime4.begin(), pathtime4.end() );
pathtime.insert( pathtime.end(), pathtime5.begin(), pathtime5.end() );
pathtime.insert( pathtime.end(), pathtime6.begin(), pathtime6.end() );
pathtime.insert( pathtime.end(), pathtime7.begin(), pathtime7.end() );


sensindex.reserve( sensindex1.size() + sensindex2.size() + sensindex3.size() + sensindex4.size() + sensindex5.size() + sensindex6.size() + sensindex7.size()); // preallocate memory
sensindex.insert( sensindex.end(), sensindex1.begin(), sensindex1.end() );
sensindex.insert( sensindex.end(), sensindex2.begin(), sensindex2.end() );
sensindex.insert( sensindex.end(), sensindex3.begin(), sensindex3.end() );
sensindex.insert( sensindex.end(), sensindex4.begin(), sensindex4.end() );
sensindex.insert( sensindex.end(), sensindex5.begin(), sensindex5.end() );
sensindex.insert( sensindex.end(), sensindex6.begin(), sensindex6.end() );
sensindex.insert( sensindex.end(), sensindex7.begin(), sensindex7.end() );

float detected = pathtime.size();
float nump = jobsize;
cout  << "\n\nDetected:  %" << (100*(2*detected/nump));
        cout << "\nEnd of photon Generation\n\n\n";
}





//------------------------------------Animation Threading---------------------------------//

void Tanimate(vector< vector <vector <double> > > & AFpath)
{
vector< vector< vector <double> > > AFpath1 = AFpath;
vector< vector< vector <double> > > AFpath2 = AFpath;
vector< vector< vector <double> > > AFpath3 = AFpath;
vector< vector< vector <double> > > AFpath4 = AFpath;
vector< vector< vector <double> > > AFpath5 = AFpath;
vector< vector< vector <double> > > AFpath6 = AFpath;
vector< vector< vector <double> > > AFpath7 = AFpath;
vector< vector< vector <double> > > FFpath;

int jobsize = AFpath.size();
cout << "\n jobsize: " << jobsize;

int range1 = jobsize*0.14;
int range2 = jobsize*0.28;
int range3 = jobsize*0.42;
int range4 = jobsize*0.56;
int range5 = jobsize*0.70;
int range6 = jobsize*0.84;


thread t1(animate, ref(AFpath1), 0, range1);
thread t2(animate, ref(AFpath2), range1,range2 );
thread t3(animate, ref(AFpath3), range2, range3);
thread t4(animate, ref(AFpath4), range3, range4);
thread t5(animate, ref(AFpath5), range4, range5);
thread t6(animate, ref(AFpath6), range5,range6 );
thread t7(animate, ref(AFpath7), range6, jobsize);


t1.join();
t2.join();
t3.join();
t4.join();
t5.join();
t6.join();
t7.join();

FFpath.reserve( AFpath1.size() + AFpath2.size() + AFpath3.size() + AFpath4.size()+ AFpath5.size() + AFpath6.size() + AFpath7.size()); // preallocate memory
FFpath.insert( FFpath.end(), AFpath1.begin(), AFpath1.end() );
FFpath.insert( FFpath.end(), AFpath2.begin(), AFpath2.end() );
FFpath.insert( FFpath.end(), AFpath3.begin(), AFpath3.end() );
FFpath.insert( FFpath.end(), AFpath4.begin(), AFpath4.end() );
FFpath.insert( FFpath.end(), AFpath5.begin(), AFpath5.end() );
FFpath.insert( FFpath.end(), AFpath6.begin(), AFpath6.end() );
FFpath.insert( FFpath.end(), AFpath7.begin(), AFpath7.end() );

AFpath = FFpath;
}





//----------------------------------------positron generation-----------------------------------------//

//Returns scintillation vector---- > layout: scintillation.at(n) is start point and scintillation.at(n+1) is random direction for increments of n = n+2 ie start and direction alternate --> allows for a kind of memory of events
vector< vector <double> > getscintpath(vector< vector <vector <double> > > surf1, float num, double x, double y, double z, vector < vector < double> > & points)
{ vector<double>  ddir, nnn;
  vector<double> I(3);
    vector<double> R(3);
    points.clear();
   

	vector< vector< double > > T(3);
	vector< vector< double > > P(2);
	vector< vector< double > > intercepts;
	vector< vector< double > > Sintercepts;
	vector< vector< double > > scintstart;
	vector<double> pp0(3);//initial position
	vector<double> pp1(3);
	vector<double> ppf(3);
	vector<double> ppf2(3);//direction vector
	float tomp;
	double theta;
	pp0.at(0) = 0;//x
	pp0.at(1) = 0;//y
	pp0.at(2) = 0;//z;//z
	//cout << "\n" << pos.at(0) << "  &  " << pos.at(1) << "  &rad:   " << sqrt(pow(pos.at(0),2)+pow(pos.at(1),2));
	//random starting direction of photon
	pp1.at(0) = x;
	pp1.at(1) = y;
	pp1.at(2) = z;
	
	//generate positron path in .ast
	
	 std::ofstream myfile4;
	  myfile4.open ("cadd/positron/new");
	  
	vector< vector< vector <double> > > posobj;
	vector< vector< vector <double> > > facobj;
	vector< vector <double> > posvert;
	getcad(posobj, "cadd/positron/positron.ast", "V");
	getcad(facobj, "cadd/positron/positron.ast", "F");
	View.at(0) = 0;
        View.at(1) = 0;
        View.at(2) = -1;
        
        View2.at(0) = x;
        View2.at(1) = y;
        View2.at(2) = -z;
        
        if (View.at(0) == View2.at(0) && View.at(1) == View2.at(1) && View.at(2) == View2.at(2))
        { 
        }
        else
        {
		Axis = cross(View, View2);
		theta = acos( dot(View,View2)/(sqrt(dot(View,View))*sqrt(dot(View2,View2))));
		Axis = normalize(Axis);
		
		
		for(unsigned int i = 0; i < posobj.size(); ++i)
		{posvert = posobj.at(i);
			 for(unsigned int ii = 0; ii < posvert.size(); ++ii)
			 {View = posvert.at(ii);
			  Rotate(theta, Axis.at(0), Axis.at(1), Axis.at(2));
			  myfile4 << "\n      vertex " << View.at(0) << " " << View.at(1) << " " << View.at(2);
			  
			 }
		 
		 
		 
		 }
		 
		 for(unsigned int i = 0; i < facobj.size(); ++i)
		{posvert = facobj.at(i);
			 View = posvert.at(0);
			  Rotate(theta, Axis.at(0), Axis.at(1), Axis.at(2));
			  myfile4 << "\n  facet normal " << View.at(0) << " " << View.at(1) << " " << View.at(2);
			   
		 
		 }
	 
	}
        
	
	
	  myfile4.close();
	
	
	
	//*******
	
	int o;

		P.at(0) = pp0;
		P.at(1) = pp1;
	//find geomtry that positron intercepts
		 for(int gg = 0; gg < surf1.size(); ++gg)
		 { 
			  T = surf1.at(gg);
			  o = triangledetect(T, P, I , R , nnn, ddir, theta);
			  
			  if(o == -1){
			  cout << "triangle error at " << gg;
			  }
			  if(o == 2)
			  cout << "same plane";
		if(o == 1)
			  {
			  intercepts.push_back(I);
			  }
			  
		  }
	//cout << "\n int size " << intercepts.size();
	//check for duplicates
	bool odd = false;

int jj = 0;
int pp = 0;	

	
for(int i = 0; i < 1; ++i)//
{

int fpsize = intercepts.size();
int nn =0;
bool simhit = true;
	while(simhit)
	{
	pp0 = intercepts.at(nn);
	pp = 0;
	bool simhit2 = true;	
		while(simhit2)
			{ I = intercepts.at(pp);
			bool a, b, c;
			 a = (trunc(10000. * pp0.at(0)) == trunc(10000. * I.at(0))); 
		         b = (trunc(10000. * pp0.at(1)) == trunc(10000. * I.at(1)));
		         c = (trunc(10000. * pp0.at(2)) == trunc(10000. * I.at(2)));
			if((nn!=pp) && a && b && c) 
				{
 
					intercepts.erase (intercepts.begin() + nn);
					--nn;
					++jj;
		
				simhit2 = false;
				}
			if((pp+1) == (fpsize -jj))
			simhit2 = false;
			++pp;
			}
	++nn;
	if(nn == (fpsize -jj) || (fpsize-jj) == 1)
	simhit = false;
	}
}
	
	//cout << "\n After int size " << intercepts.size();
	
	//now reorganize in terms of distance
	float pathtime4;
	float lowest = 10000000;
	float lowest2 = 0;
	int dd = 0;
	
	odd = true;
	while(odd)
	{pp0.at(0) = 0;
	pp0.at(1) = 0;
	pp0.at(2) = 0;
		for(int i = 0; i < intercepts.size(); ++i)
			{I = intercepts.at(i);
			pathtime4 = ( sqrt( pow( (pp0.at(0)-I.at(0)),2 )+pow( (pp0.at(1)-I.at(1)),2 )+pow( (pp0.at(2)-I.at(2)),2))/300.0);
				if(pathtime4 < lowest && pathtime4 > lowest2)
				{
				dd = i;
				lowest = pathtime4;
				}

			}
		if(intercepts.size() > Sintercepts.size())
			{
			//cout << "\n pushbakc";
			Sintercepts.push_back(intercepts.at(dd));
			I = intercepts.at(dd);
			lowest = 100000000;
			lowest2 = ( sqrt( pow( (pp0.at(0)-I.at(0)),2 )+pow( (pp0.at(1)-I.at(1)),2 )+pow( (pp0.at(2)-I.at(2)),2))/300.0);
			}
		else
		{
		odd = false;
		}
	}
	points = Sintercepts;
	for(int i = 0; i < Sintercepts.size(); ++i)
	{
	 I = Sintercepts.at(i);
	 pathtime4 = ( sqrt( pow( (pp0.at(0)-I.at(0)),2 )+pow( (pp0.at(1)-I.at(1)),2 )+pow( (pp0.at(2)-I.at(2)),2))/300.0);
	 //printf("\ntime after sort %f", pathtime4);
	}
		 
	if(Sintercepts.size()%2 == 0 && Sintercepts.size() > 0)
	{
		for(int f = 0; f < Sintercepts.size(); f = f+2)
		{
	         pp0 = Sintercepts.at(0+f); 
	         pp1 = Sintercepts.at(1+f); 
	         I = subvec(pp1, pp0);
		       for (double i = 0; i < num; ++i)
		       {
			ppf = I;
			tomp = gRandom->Uniform(2,98);
			ppf2.at(0) = (tomp/100) * ppf.at(0);
			ppf2.at(1) = (tomp/100) * ppf.at(1);
			ppf2.at(2) = (tomp/100) * ppf.at(2);
			ppf = addvec(ppf2, pp0);
			scintstart.push_back(ppf);
		        tomp = gRandom->Uniform(-100,100);
		        ppf.at(0) = tomp;
		        tomp = gRandom->Uniform(-100,100);
		        ppf.at(1) = tomp;
		        tomp = gRandom->Uniform(-100,100);
		        ppf.at(2) = tomp;
			scintstart.push_back(ppf);	
		
		        }
		        num = num*0.60;
		}
		
	}		
	else
	{cout << "\n **ERROR either position dosen't intercept surface or intercepts to many solids";
	}		
                    



return scintstart;
}


//----------------------------------------Laser Pulse generation-----------------------------------------//

//Returns scintillation vector---- > layout: scintillation.at(n) is start point and scintillation.at(n+1) is random direction for increments of n = n+2 ie start and direction alternate --> allows for a kind of memory of events
vector< vector <double> > getlaserpulse(vector< vector <vector <double> > > surf1, float num, double x, double y, double z, vector < vector < double> > & points)
{ vector<double>  ddir, nnn;
  vector<double> I(3);
    vector<double> R(3);
    points.clear();
   

	vector< vector< double > > T(3);
	vector< vector< double > > P(2);
	vector< vector< double > > intercepts;
	vector< vector< double > > Sintercepts;
	vector< vector< double > > scintstart;
	vector<double> pp0(3);//initial position
	vector<double> pp1(3);
	vector<double> ppf(3);
	vector<double> ppf2(3);//direction vector
	float tomp;
	double theta;
	pp0.at(0) = 0;//x
	pp0.at(1) = 0;//y
	pp0.at(2) = 0;//z;//z
	//cout << "\n" << pos.at(0) << "  &  " << pos.at(1) << "  &rad:   " << sqrt(pow(pos.at(0),2)+pow(pos.at(1),2));
	//starting direction of positron
	pp1.at(0) = x;
	pp1.at(1) = y;
	pp1.at(2) = z;
	
	//generate positron path in .ast
	
	 std::ofstream myfile4;
	  myfile4.open ("cadd/positron/new");
	  
	vector< vector< vector <double> > > posobj;
	vector< vector< vector <double> > > facobj;
	vector< vector <double> > posvert;
	getcad(posobj, "cadd/positron/positron.ast", "V");
	getcad(facobj, "cadd/positron/positron.ast", "F");
	View.at(0) = 0;
        View.at(1) = 0;
        View.at(2) = -1;
        
        View2.at(0) = x;
        View2.at(1) = y;
        View2.at(2) = -z;
        
        if (View.at(0) == View2.at(0) && View.at(1) == View2.at(1) && View.at(2) == View2.at(2))
        { 
        }
        else
        {
		Axis = cross(View, View2);
		theta = acos( dot(View,View2)/(sqrt(dot(View,View))*sqrt(dot(View2,View2))));
		Axis = normalize(Axis);
		
		
		for(unsigned int i = 0; i < posobj.size(); ++i)
		{posvert = posobj.at(i);
			 for(unsigned int ii = 0; ii < posvert.size(); ++ii)
			 {View = posvert.at(ii);
			  Rotate(theta, Axis.at(0), Axis.at(1), Axis.at(2));
			  myfile4 << "\n      vertex " << View.at(0) << " " << View.at(1) << " " << View.at(2);
			  
			 }
		 
		 
		 
		 }
		 
		 for(unsigned int i = 0; i < facobj.size(); ++i)
		{posvert = facobj.at(i);
			 View = posvert.at(0);
			  Rotate(theta, Axis.at(0), Axis.at(1), Axis.at(2));
			  myfile4 << "\n  facet normal " << View.at(0) << " " << View.at(1) << " " << View.at(2);
			   
		 
		 }
	 
	}
        
	
	
	  myfile4.close();
	
	
	
	//*******
	
	int o;

		P.at(0) = pp0;
		P.at(1) = pp1;
	//find geomtry that positron intercepts
		 for(int gg = 0; gg < surf1.size(); ++gg)
		 { 
			  T = surf1.at(gg);
			  o = triangledetect(T, P, I , R , nnn, ddir, theta);
			  
			  if(o == -1){
			  cout << "triangle error at " << gg;
			  }
			  if(o == 2)
			  cout << "same plane";
		if(o == 1)
			  {
			  intercepts.push_back(I);
			  }
			  
		  }
	//cout << "\n int size " << intercepts.size();
	//check for duplicates
	bool odd = false;

int jj = 0;
int pp = 0;	
	
for(int i = 0; i < 2; ++i)
{

int fpsize = intercepts.size();
int nn =0;
bool simhit = true;
	while(simhit)
	{
	pp0 = intercepts.at(nn);
	pp = 0;
	bool simhit2 = true;	
		while(simhit2)
			{ I = intercepts.at(pp);
			bool a, b, c;
			 a = (trunc(10000. * pp0.at(0)) == trunc(10000. * I.at(0))); 
		         b = (trunc(10000. * pp0.at(1)) == trunc(10000. * I.at(1)));
		         c = (trunc(10000. * pp0.at(2)) == trunc(10000. * I.at(2)));
			if((nn!=pp) && a && b && c) 
				{
 
					intercepts.erase (intercepts.begin() + nn);
					--nn;
					++jj;
		
				simhit2 = false;
				}
			if((pp+1) == (fpsize -jj))
			simhit2 = false;
			++pp;
			}
	++nn;
	if(nn == (fpsize -jj) || (fpsize-jj) == 1)
	simhit = false;
	}
}
	
	
	//cout << "\n After int size " << intercepts.size();
	
	//now reorganize in terms of distance
	float pathtime4;
	float lowest = 10000000;
	float lowest2 = 0;
	int dd = 0;
	
	odd = true;
	while(odd)
	{pp0.at(0) = 0;
	pp0.at(1) = 0;
	pp0.at(2) = 0;
		for(int i = 0; i < intercepts.size(); ++i)
			{I = intercepts.at(i);
			pathtime4 = ( sqrt( pow( (pp0.at(0)-I.at(0)),2 )+pow( (pp0.at(1)-I.at(1)),2 )+pow( (pp0.at(2)-I.at(2)),2))/300.0);
				if(pathtime4 < lowest && pathtime4 > lowest2)
				{
				dd = i;
				lowest = pathtime4;
				}

			}
		if(intercepts.size() > Sintercepts.size())
			{
			//cout << "\n pushbakc";
			Sintercepts.push_back(intercepts.at(dd));
			I = intercepts.at(dd);
			lowest = 100000000;
			lowest2 = ( sqrt( pow( (pp0.at(0)-I.at(0)),2 )+pow( (pp0.at(1)-I.at(1)),2 )+pow( (pp0.at(2)-I.at(2)),2))/300.0);
			}
		else
		{
		odd = false;
		}
	}
	points = Sintercepts;
	for(int i = 0; i < Sintercepts.size(); ++i)
	{
	 I = Sintercepts.at(i);
	 pathtime4 = ( sqrt( pow( (pp0.at(0)-I.at(0)),2 )+pow( (pp0.at(1)-I.at(1)),2 )+pow( (pp0.at(2)-I.at(2)),2))/300.0);
	 //printf("\ntime after sort %f", pathtime4);
	}
		 
	if(Sintercepts.size()%2 == 0 && Sintercepts.size() > 0)
	{
		for(int f = 0; f < Sintercepts.size(); f = f+2)
		{
	         pp0 = Sintercepts.at(0+f); 
	         pp1 = Sintercepts.at(1+f); 
	         I = subvec(pp1, pp0);
		       for (double i = 0; i < num; ++i)
		       {
			ppf = I;
			tomp = gRandom->Uniform(20,80);
			ppf2.at(0) = (tomp/100) * ppf.at(0);
			ppf2.at(1) = (tomp/100) * ppf.at(1);
			ppf2.at(2) = (tomp/100) * ppf.at(2);
			ppf = addvec(ppf2, pp0);
			scintstart.push_back(ppf);
		        tomp = gRandom->Uniform(-100,100);
		        ppf.at(0) = x+(tomp/500);
		        tomp = gRandom->Uniform(-100,100);
		        ppf.at(1) = y+ (tomp/500);
		        tomp = gRandom->Uniform(-100,100);
		        ppf.at(2) = z + (tomp/500);
			scintstart.push_back(ppf);	
		
		        }
		        num = num*0.60;
		}
		
	}		
	else
	{cout << "\n **ERROR either position dosen't intercept surface or intercepts to many solids";
	}		
                    



return scintstart;
}


//------------------------------------------Photon Generator----------------------------------------------//

void gen(vector< vector< vector <double> > > & AFpath, vector<double> & pathtime, vector< vector <vector <double> > > surf1, vector< vector <vector <double> > > surfFinal, vector< vector <double> > scint, vector <int> & sensindex, string mode, int start, int stop)
{ 
float crit = 40; 
bool type1;
if(mode == "R")
type1 = false;
if(mode == "RT")
type1 = true;

vector<double>  ddir, nnn;
double theta;
    vector<double> I(3);
    vector<double> R(3);




	//cout << "\n\nStarting Photon Path Generation";
	vector<int> reftrispot;
	float senslim = 0;
	float nump = scint.size()/2;


	senslim = surfFinal.size();
	//cout << "\nsenslim  " << senslim;
	//cout << "\n scintsurf size" << surf1.size();


	for (int i = 0; i < surf1.size(); ++i)
	{
	surfFinal.push_back(surf1.at(i));
	}

	//cout << "\nfinal size  " << surfFinal.size();


	vector< vector<double> > Fpath;
	vector<double> lpath;


	int p =0;
	double tomp;

	AFpath.clear();
	pathtime.clear();
	int detected = 0;



	for(int n = start; n < stop; n = n+2)
		{
		//generate vectors
		vector<double> pp0(3);//initial position
		vector<double> pp1(3);//direction vector
		vector<vector <double> > refpoints;
		pp0 = scint.at(n);

		//starting point of photon 
		//pp0.at(0) = 28.2;//x
		//pp0.at(1) = 28.2;//y
		//pp0.at(2) = 0;//z;//z
		//cout << "\n" << pos.at(0) << "  &  " << pos.at(1) << "  &rad:   " << sqrt(pow(pos.at(0),2)+pow(pos.at(1),2));
		//random starting direction of photon
		pp1 = scint.at(n+1);
	        pp1 = addvec(pp1, pp0);


		refpoints.push_back(pp0);
	

		bool run = true;
		bool sensArea = true;
		bool critical = true;
		double pathtime1 = 0;
		double sumtime = 0;
		vector< vector< double > > T(3);
		vector< vector< double > > P(2);
		vector< double > ggvalue;
		int o;
		while(sensArea)
		{
			int gg = 0;
			run = true;
			P.at(0) = pp0;
			P.at(1) = pp1;
			while(run)
			{
			  
			 for(int gg = 0; gg < surfFinal.size(); ++gg)
			 { 
				  T = surfFinal.at(gg);
				  o = triangledetect(T, P, I , R , nnn, ddir, theta);
				  
				  if(o == -1){
				  cout << "triangle error at " << gg;
				  }
				  if(o == 2)
				  cout << "same plane";
			if(o == 1 && trunc(10000. * pp0.at(0)) != trunc(10000. * I.at(0)) && trunc(10000. * pp0.at(1)) != trunc(10000. * I.at(1)) && trunc(10000. * pp0.at(2)) != trunc(10000. * I.at(2)))
				  {
				  ggvalue.push_back(gg);//index of triangles the path intersects
				  }
				 
			  }
		
		
				  if(ggvalue.size() < 1)//A complete miss of structure
				  {
					  
					  run = false;
					  sensArea = false;
					  cout << "M";
				  }
			     
			  //cout << "\n ggvalue size " << ggvalue.size();
			  
			  if(ggvalue.size() > 0 && run && sensArea)//now find closest triangle
			  {  float shortest = 100000000000000;
			     float finalgg = 0;
			  
			  
			    for(int i = 0; i < ggvalue.size(); ++i)
			    {gg = ggvalue.at(i);		
			     T = surfFinal.at(gg);
			     o = triangledetect(T, P, I , R , nnn, ddir, theta);
			     pathtime1 = ( sqrt( pow( (pp0.at(0)-I.at(0)),2 )+pow( (pp0.at(1)-I.at(1)),2 )+pow( (pp0.at(2)-I.at(2)),2))/300.0);
			    // cout << "\n pathtime  " << pathtime1 << "   gg " << gg;
			     if(pathtime1 < shortest)
				     {
				     finalgg = gg;
				     shortest = pathtime1;
				     }
			     }
			  //cout << "\n Boundary encountered";
			  //cout << "\n final gg " << finalgg;
			     T = surfFinal.at(finalgg);
			     o = triangledetect(T, P, I , R , nnn, ddir, theta);
			     //printf("\ntheta: %f finalgg: %f senslim: %f", theta, finalgg, senslim); 
			    if(finalgg < senslim)
			    {
				    
				    int wsens = 0;
				    for(int i = 0; i < sensorindex1.size()-1; ++i)
				    {
				     float range1 = sensorindex1.at(i);
				     float range2 = sensorindex1.at(i+1);
				     if(finalgg <= range2 && finalgg > range1)
				     wsens = (i+1);
				    }
				    //cout << "\npp0: " << pp0.at(0) << "   " << pp0.at(1) << "  " << pp0.at(2);
				    //cout << "\npp1: " << pp1.at(0) << "   " << pp1.at(1) << "  " << pp1.at(2);	
				    //cout << "\nintercept: " << I.at(0) << "  " << I.at(1) << "   " << I.at(2);
				    refpoints.push_back(I);
				    pathtime1 = ( sqrt( pow( (pp0.at(0)-pp1.at(0)),2 )+pow( (pp0.at(1)-pp1.at(1)),2 )+pow( (pp0.at(2)-pp1.at(2)),2))/300.0);
				    sumtime = sumtime+pathtime1;
				    pp0 = I;
				    pp1 = addvec(pp0, R);
				    //cout << "\nafter\npp0: " << pp0.at(0) << "   " << pp0.at(1) << "  " << pp0.at(2);
				    //cout << "\npp1: " << pp1.at(0) << "   " << pp1.at(1) << "  " << pp1.at(2);
				                   if(theta <= 45.0)
                                                   {
						    cout << "\nHit Sensor #" << wsens;
						    detected++;
						    pathtime.push_back(sumtime);
						    sensindex.push_back(wsens);
						    cout << "\n pathtime " << sumtime;
						    sumtime = 0;
						    sensArea = false;
						    }
						    else
						    {sumtime = 0;
						    sensArea = false;
						    }
				
				    ggvalue.clear();
				    run = false;
			  } 
			     
			    if(theta >= crit)//reflection if crit degrees or more from normal
			    {
				     //cout << "\npp0: " << pp0.at(0) << "   " << pp0.at(1) << "  " << pp0.at(2);
				    //cout << "\npp1: " << pp1.at(0) << "   " << pp1.at(1) << "  " << pp1.at(2);	
				    //cout << "\nintercept: " << I.at(0) << "  " << I.at(1) << "   " << I.at(2);
				    refpoints.push_back(I);
				    pathtime1 = ( sqrt( pow( (pp0.at(0)-pp1.at(0)),2 )+pow( (pp0.at(1)-pp1.at(1)),2 )+pow( (pp0.at(2)-pp1.at(2)),2))/300.0);
				    sumtime = sumtime+pathtime1;
				    pp0 = I;
				    pp1 = addvec(pp0, R);
				    //cout << "\nafter\npp0: " << pp0.at(0) << "   " << pp0.at(1) << "  " << pp0.at(2);
				    //cout << "\npp1: " << pp1.at(0) << "   " << pp1.at(1) << "  " << pp1.at(2);
				   // cout << "r";

				    ggvalue.clear();
				    run = false;
			  }
			  
			  if(theta < crit && sensArea)
			  { 
			  
				    if(type1)
				    {
				    refpoints.push_back(I);
				    R = trans(nnn, pp0, pp1, 1.52,1.00, ddir, I);
				    //printf("\npoints here: %f %f %f", R.at(0), R.at(1), R.at(2));
				    refpoints.push_back(R);
				    cout << "*";
				    run = false;
				    sensArea = false;
				    critical = true;
				    sumtime = 0;
				    }
				    else
				    {
				    cout << "*";
				    run = false;
				    sensArea = false;
				    critical = false;
				    }
			    
			    
			  }
			  
			  if(sumtime > 50)
			  {
			  cout << "#";
		          run = false;
		          sensArea = false;
			  critical = false;
			  sumtime = 0;
			  }
			  
			  }
	
			  
			 }
			 //cout << "\nrun end";
			 }
			   

		//if(sensArea == true)
		//cout << "\n push back vector";
		if(critical)
		AFpath.push_back(refpoints);
		
	  
		

	Fpath.clear();
	++p;
	}//end of for


	


   	
}//end of getphoton



//-------------------------------------------Animate---------------------------------------------//

void animate(vector< vector <vector <double> > > & AFpath, int start, int last)
{//cout<< "\nstart animate"; 

vector< vector < double > > Event;
vector< vector < double > > EventF;
	 vector< double > point0 (3);
	 vector< double > point1 (3);
	 vector< vector <vector <double> > > Gpaths;
	 
	  vector<double> I(3);
	vector<double> pp0(3);//initial position
	vector<double> pp1(3);
	vector<double> ppf(3);
	vector<double> ppf2(3);
	float tomp, tump, slice;
	float step = 0.5;

        for(unsigned int q = start; q < last; ++q)
	 {
	  	Event = AFpath.at(q);
		for(int f = 0; f < Event.size()-1; ++f)
		{
	         pp0 = Event.at(0+f);
	         EventF.push_back(pp0); 
	         pp1 = Event.at(1+f); 
	         I = subvec(pp1, pp0);
	         slice = step/( sqrt( pow( (pp0.at(0)-pp1.at(0)),2 )+pow( (pp0.at(1)-pp1.at(1)),2 )+pow( (pp0.at(2)-pp1.at(2)),2)));
	          
	         tomp = slice;
	         
		       while(tomp <= 1)
		       {
			ppf = I;
			ppf2.at(0) = (tomp) * ppf.at(0);
			ppf2.at(1) = (tomp) * ppf.at(1);
			ppf2.at(2) = (tomp) * ppf.at(2);
			ppf = addvec(ppf2, pp0);
			EventF.push_back(ppf);
				
		        tomp = tomp + slice;
		        }
		        EventF.push_back(pp1);
		        
		        
		}
          Gpaths.push_back(EventF);
          EventF.clear();
         }
AFpath = Gpaths;
}






//------------------------------------------Generate CADpaths-------------------------------------------//


bool cadpath(vector< vector <vector <double> > > Gpaths, const char* filename)
{	printf("\nWriting data to file...."); 
	 int count = 0;
	 std::ofstream myfile;
	  myfile.open (filename);
	 	 
	 vector< vector < double > > Event;
	 vector< double > point0 (3);
	 vector< double > point1 (3);
	 /*
	 for(unsigned int q = 0; q < Gpaths.size(); ++q)
	 {
	  	Event = Gpaths.at(q);
	  	for(unsigned int w = 0; w < (Event.size()-1); ++w)
	  	{
	  		point0 = Event.at(w);
	  		point1 = Event.at(w+1);
	
        myfile << "\n      vertex " << point0.at(0) << " " << point0.at(1) << " " << point0.at(2);
        ++count;
    	myfile << "\n      vertex " << point1.at(0) << " " << point1.at(1) << " " << point1.at(2);
    	++count;

		}
	}*/
	int w =0;
	bool run6 = true;
	 while(run6)
	 {int ddd = 0;
		for(unsigned int q = 0; q < Gpaths.size(); ++q)
		{
	  	Event = Gpaths.at(q);
	  	
	        
			if(Event.size() > w + 1)
			{
			point0 = Event.at(w);
		  	point1 = Event.at(w+1);
	
		        myfile << "\n      vertex " << point0.at(0) << " " << point0.at(1) << " " << point0.at(2);
		        ++count;
	    	        myfile << "\n      vertex " << point1.at(0) << " " << point1.at(1) << " " << point1.at(2);
	    	        ++count;
			}
			else
			++ddd;
		}
	
	++w;
	myfile << "\nCluster " << count;
	if(ddd >= Gpaths.size())
	run6 = false;
	}
	
	for(unsigned int i = 0; i < count; ++i)
	{
	myfile << "\nfacet normal 0 0 0";
	
	}
	
	
	  myfile.close();
	  printf("Done");
	  return true;
}








//-----------------------------------------------CAD Loader------------------------------------------------//


void getcad(vector< vector <vector <double> > > & surfvec, string cadfile, string mode1)
{  
cout << "\n" << "loading cadd file: " << cadfile;
const char * c;
string search;
if(mode1 == "V");
search = "vertex";
if(mode1 == "F");
search = "facet";
vector<string> lines, lines2;
vector<double> x, y, z;	

        //enter .txt and .wfi files to be used
	string wfifile= cadfile;
	c = wfifile.c_str();

ifstream file(c);
		string str, temp, tomp; 
		string::size_type sz;
if(mode1 == "V");
{
		while (getline(file, str))
		{	if(str.find("vertex") == 6)
			{
			str.erase (str.begin(), str.begin()+13);
			lines.push_back(str);
			}
		}
}
if(mode1 == "F");
{
		while (getline(file, str))
		{	if(str.find("facet") == 2)
			{
			str.erase (str.begin(), str.begin()+15);
			lines.push_back(str);
			}
		}
}		
		
	cout << "\ndone";
	
	for(int i = 0; i < lines.size(); ++i)
	{ 		
		lines2.push_back(lines.at(i));		
	}
	
	string current;
	int f = 0;
	for(int i = 0; i < lines2.size(); ++i)
	{ //cout << "\n" << lines2.at(i) << "\n";
		current = lines2.at(i);
		
		f = current.find(" ");
		//cout << "\n f: " << f;
		current.erase (current.begin() + f, current.end());
  		
 		x.push_back(atof(current.c_str()));
 		
 		current = lines2.at(i);
		
		f = current.find(" ");
		current.erase (current.begin(), current.begin()+f+1);
		 
		f = current.find(" ");
		current.erase (current.begin()+f, current.end());
		 
		y.push_back(atof(current.c_str()));
		
		current = lines2.at(i);
		
		f = current.find(" ");
		current.erase (current.begin(), current.begin()+f+1);
		 
		f = current.find(" ");
		current.erase (current.begin(), current.begin()+f+1);
		
		z.push_back(atof(current.c_str()));
			
	}
	
//cout << "\nxsize" << z.size();
//cout << "\nysize" << y.size();
//cout << "\nzsize" << z.size();

	file.close();
	
	vector<vector<double> > set(3);
	vector<double> point0(3);
	vector<double> point1(3);
	vector<double> point2(3);
	
int p = 0;
if(mode1 == "V")
{
	for(int k = 0; k < x.size(); k = k+3)
	{
		double x0,y0,z0,x1,y1,z1,x2,y2,z2;
		x0 = x.at(k);
		y0 = y.at(k);
		z0 = z.at(k);	
		x1 = x.at(k+1);
		y1 = y.at(k+1);
		z1 = z.at(k+1);	
		x2 = x.at(k+2);
		y2 = y.at(k+2);
		z2 = z.at(k+2);
	
		 point0.at(0) = x0;
		 point0.at(1) = y0;
		 point0.at(2) = z0;
		 point1.at(0) = x1;
		 point1.at(1) = y1;
		 point1.at(2) = z1;
		 point2.at(0) = x2;
		 point2.at(1) = y2;
		 point2.at(2) = z2;
		 
		++p;
		set.at(0) = point0; 
		set.at(1) = point1; 
		set.at(2) = point2; 
	
		surfvec.push_back(set);
	}
}
if(mode1 == "F")
{
	for(int k = 0; k < x.size(); k = k+3)
	{
		double x0,y0,z0;
		x0 = x.at(k);
		y0 = y.at(k);
		z0 = z.at(k);	
	
		 point0.at(0) = x0;
		 point0.at(1) = y0;
		 point0.at(2) = z0;
		 point1.at(0) = 0;
		 point1.at(1) = 0;
		 point1.at(2) = 0;
		 point2.at(0) = 0;
		 point2.at(1) = 0;
		 point2.at(2) = 0;
		 
		++p;
		set.at(0) = point0; 
		set.at(1) = point1; 
		set.at(2) = point2; 
	
		surfvec.push_back(set);
	}
}

cout << "  size:" << surfvec.size();		
}	





//-----------------------------------------Triangle Detection-----------------------------------------// 



int triangledetect(vector< vector<double> > T, vector< vector<double> > P, vector<double> & I, vector<double> & R,  vector<double> & nnn, vector<double> & ddir, double & theta)
{   vector< double>  uuu, vvv;              // triangle vectors
    vector<double> ww0, ww;           // ray vectors
    double     rrr, aaa, bbb;  
    vector<double> V0(3);
    vector<double> V1(3);
    vector<double> V2(3);
    vector<double> null(3); 
    double    uu1, uv1, vv1, wu1, wv1, D1;
double sss, ttt;

    I.at(0) = 0;
    I.at(1) = 0;
    I.at(2) = 0;
    
    R.at(0) = 0;
    R.at(1) = 0;
    R.at(2) = 0;
    
    null.at(0) = 0;
    null.at(1) = 0;
    null.at(2) = 0;	
    
    vector<double> P0(3);
    vector<double> P1(3);
    V0 = T.at(0);
    V1 = T.at(1);
    V2 = T.at(2); 

    P0 = P.at(0);
    P1 = P.at(1);
       
 //start of detect 
    // get triangle edge vectors and plane normal
    uuu = subvec(V1, V0);
    vvv = subvec(V2, V0);
    nnn = cross(uuu,vvv);            // cross product nnn is plane normal
    
    
    if (nnn == null)             // triangle is degenerate
        return -1;                  // do not deal with this case

    ddir = subvec(P1,P0);              // ray direction vector
    ww0 = subvec(P0 , V0);
    aaa = -dot(nnn,ww0);
    bbb = dot(nnn,ddir);  
    
    if (fabs(bbb) < SMALL_NUM) {     // ray is  parallel to triangle plane
        if (aaa == 0)  
                       // ray lies in triangle plane
            return 2;
        else return 0;              // ray disjoint from plane
    }

    // get intersect point of ray with triangle plane
    rrr = aaa / bbb;
    if (rrr < 0.0)                    // ray goes away from triangle
        return 0;                   // => no intersect
    // for a segment, also test if (r > 1.0) => no intersect

    I.at(0) = P0.at(0) + rrr * ddir.at(0);            // intersect point of ray and plane
    I.at(1) = P0.at(1) + rrr * ddir.at(1);
    I.at(2) = P0.at(2) + rrr * ddir.at(2);
    // is I inside T?
    
    uu1 = dot(uuu,uuu);
    uv1 = dot(uuu,vvv);
    vv1 = dot(vvv,vvv);
    ww = subvec(I , V0);
    wu1 = dot(ww,uuu);
    wv1 = dot(ww,vvv);
    D1 = uv1 * uv1 - uu1 * vv1;

    // get and test parametric coords
    
    sss = (uv1 * wv1 - vv1 * wu1) / D1;
    if (sss < 0.0000000 || sss > 1.0000000)         // I is outside T
        return 0;
    ttt = (uv1 * wu1 - uu1 * wv1) / D1;
    if (ttt < 0.0000000 || (sss + ttt) > 1.0000000)  // I is outside T
        return 0;

    double sub = (2*dot(ddir, nnn))/dot(nnn,nnn);
    
	R = refvec(ddir, nnn, sub);
	
	//angle between reflected and normal vector
	
	theta = 360*(acos( dot(nnn,R)/(sqrt(dot(nnn,nnn))*sqrt(dot(R,R))))/(2*3.14159265359));
	if(theta > 90)
	theta = 180-theta;


    return 1;                       // I is in T
    
   
}




//-------------------------------------Transmission Calculator--------------------------------------//

vector<double> trans(vector<double> v1, vector<double> v2, vector<double> v3, double n1, double n2, vector<double> ddir, vector<double> & I)//v1 normal 
{ vector<double> vcross(3);
vector<double> vecP;
vecP = normalize(ddir);
v1 = normalize(v1);
//printf("\nvecP here: %f %f %f", vecP.at(0), vecP.at(1), vecP.at(2)); 
//printf("\nv1 here: %f %f %f", v1.at(0), v1.at(1), v1.at(2));  
vector<double> vectemp (3);
vector<double> vectemp1 (3);
vector<double> vectemp2 (3);
vector<double> vectempN (3);
double hhh11 = dot(cross(v1, vecP),cross(v1,vecP));
//printf( "\nhhh11 here: %f", hhh11);
double hhh22;

       vectempN.at(0) = -v1.at(0);
       vectempN.at(1) = -v1.at(1);
       vectempN.at(2) = -v1.at(2);

       vectemp = cross(v1, cross(vectempN,vecP));
        //printf("\nvectemp here: %f %f %f", vectemp.at(0), vectemp.at(1), vectemp.at(2));
       vectemp1.at(0) = (n1/n2)*vectemp.at(0);
       vectemp1.at(1) = (n1/n2)*vectemp.at(1);
       vectemp1.at(2) = (n1/n2)*vectemp.at(2);
       //printf("\nvectemp1 here: %f %f %f", vectemp1.at(0), vectemp1.at(1), vectemp1.at(2));
       //printf("\nsqr: %f",(pow((n1/n2),2)*hhh11)); 
       hhh22 = sqrt(1-(pow((n1/n2),2)*hhh11));
       //printf( "\nhhh22 here: %f", hhh22);
       vectemp2.at(0) = hhh22*v1.at(0);
       vectemp2.at(1) = hhh22*v1.at(1);
       vectemp2.at(2) = hhh22*v1.at(2);
       //printf("\nvectemp2 here: %f %f %f", vectemp2.at(0), vectemp2.at(1), vectemp2.at(2));
       vcross = subvec(vectemp1,vectemp2);
       vcross.at(0) = 15* vcross.at(0);
       vcross.at(1) = 15* vcross.at(1);
       vcross.at(2) = 15* vcross.at(2);
       vcross = addvec(vcross, I);
       
     
return vcross;
}




//---------------------------------------------Quartionion Rotations----------------------------------------//

double length(quaternion quat)
{
  return sqrt(quat.x * quat.x + quat.y * quat.y +
              quat.z * quat.z + quat.w * quat.w);
}

quaternion normalizeq(quaternion quat)
{
  double L = length(quat);

  quat.x /= L;
  quat.y /= L;
  quat.z /= L;
  quat.w /= L;

  return quat;
}

quaternion conjugate(quaternion quat)
{
  quat.x = -quat.x;
  quat.y = -quat.y;
  quat.z = -quat.z;
  return quat;
}

quaternion mult(quaternion A, quaternion B)
{
  quaternion C;

  C.x = A.w*B.x + A.x*B.w + A.y*B.z - A.z*B.y;
  C.y = A.w*B.y - A.x*B.z + A.y*B.w + A.z*B.x;
  C.z = A.w*B.z + A.x*B.y - A.y*B.x + A.z*B.w;
  C.w = A.w*B.w - A.x*B.x - A.y*B.y - A.z*B.z;
  return C;
}


void Rotate(double Angle, double x, double y, double z)
{
  quaternion temp, quat_view, result;

  temp.x = x * sin(Angle/2);
  temp.y = y * sin(Angle/2);
  temp.z = z * sin(Angle/2);
  temp.w = cos(Angle/2);

  quat_view.x = View.at(0);
  quat_view.y = View.at(1);
  quat_view.z = View.at(2);
  quat_view.w = 0;

  result = mult(mult(temp, quat_view), conjugate(temp));

  View.at(0) = result.x;
  View.at(1) = result.y;
  View.at(2) = result.z;
}


//----------------------------------------------Math Operations---------------------------------------//

vector<double> cross(vector<double> v1, vector<double> v2)
{vector<double> vcross(3);
	vcross.at(0) = (v2.at(1)*v1.at(2))-(v2.at(2)*v1.at(1));
	vcross.at(1) = (v2.at(2)*v1.at(0))-(v2.at(0)*v1.at(2));
	vcross.at(2) = (v2.at(0)*v1.at(1))-(v2.at(1)*v1.at(0));
return vcross;
}

double dot(vector<double> v1, vector<double> v2)
{vector<double> vcross(3);
        double dotp;
	dotp = v1.at(0)*v2.at(0) +v1.at(1)*v2.at(1) +v1.at(2)*v2.at(2);
	
return dotp;
}

vector<double> addvec(vector<double> v1, vector<double> v2)
{vector<double> vcross(3);
	vcross.at(0) = v1.at(0) + v2.at(0);
	vcross.at(1) = v1.at(1) + v2.at(1);
	vcross.at(2) = v1.at(2) + v2.at(2);
return vcross;
}

vector<double> subvec(vector<double> v1, vector<double> v2)
{vector<double> vcross(3);
	vcross.at(0) = v1.at(0) - v2.at(0);
	vcross.at(1) = v1.at(1) - v2.at(1);
	vcross.at(2) = v1.at(2) - v2.at(2);
return vcross;
}

vector<double> vecaddnum(vector<double> v1, double f1, double f2, double f3)
{ vector<double> vcross(3);
	vcross.at(0) = v1.at(0) + f1;
	vcross.at(1) = v1.at(1) + f2;
	vcross.at(2) = v1.at(2) + f3;
return vcross;
}

  
vector<double> refvec(vector<double> v1, vector<double> v2, double sub)
{vector<double> vcross(3);
	vcross.at(0) = v1.at(0) - sub*v2.at(0);
	vcross.at(1) = v1.at(1) - sub*v2.at(1);
	vcross.at(2) = v1.at(2) - sub*v2.at(2);
return vcross;
}

void cyltocart(double & r, double & theta, double & z)
{double x, y;
x = r*cos(theta);
y = r*sin(theta);
r = x;
theta = y;

}

vector<double> normalize(vector<double> v1)//v1 normal 
{ vector<double> vcross(3);
double hhh33 = sqrt(pow(v1.at(0),2)+ pow(v1.at(1),2) + pow(v1.at(2),2));
vcross.at(0) = v1.at(0)/hhh33;
vcross.at(1) = v1.at(1)/hhh33;
vcross.at(2) = v1.at(2)/hhh33;

return vcross;
}

