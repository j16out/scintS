#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <glm/glm.hpp>

#include "objloader.hpp"

using namespace std;
// Very, VERY simple OBJ loader.
// Here is a short list of features a real function would provide : 
// - Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
// - Animations & bones (includes bones weights)
// - Multiple UVs
// - All attributes should be optional, not "forced"
// - More stable. Change a line in the OBJ file and it crashes.
// - More secure. Change another line and you can inject code.
// - Loading from memory, stream, etc
#ifdef USE_ASSIMP 
bool loadOBJ(
	const char * path, 
	std::vector<glm::vec3> & out_vertices, 
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals
){
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices; 
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;
	
	

		FILE * file = fopen(path, "r");
		if( file == NULL ){
			printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
			getchar();
			return false;
		}

		while( 1 ){

			char lineHeader[128];
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break; // EOF = End Of File. Quit the loop.

			// else : parse lineHeader
		
			if ( strcmp( lineHeader, "v" ) == 0 ){
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
				temp_vertices.push_back(vertex);
		
			}else if ( strcmp( lineHeader, "vn" ) == 0 ){
				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
				temp_normals.push_back(normal);
			}else if ( strcmp( lineHeader, "f" ) == 0 ){
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2] );
				if (matches != 6){
					printf("File can't be read by our simple parser :-( Try exporting with other options\n");
					return false;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}else{
				// Probably a comment, eat up the rest of the line
				char stupidBuffer[1000];
				fgets(stupidBuffer, 1000, file);
			}

		}
	}

	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		
		glm::vec3 normal = temp_normals[ normalIndex-1 ];
		
		// Put the attributes in buffers
		glm::vec2 uv;
			uv.x = 0.7; 
			uv.y = 0.8;
	        out_vertices.push_back(vertex);
		out_uvs     .push_back(uv);
		out_normals .push_back(normal);
	
	}

	return true;
}

#endif
//#ifdef USE_ASSIMP 

bool loadOBJ(
	const char * path, 
	std::vector<glm::vec3> & out_vertices, 
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals,
	std::vector<int> & out_Vindex,
	float color1,
	float color2,
	int type
){
	printf("Loading file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices; 
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;
	out_Vindex.push_back(0);
        char norm;
        
        
        
        
        if(type == 2)
	{//std::cout << "\n did this one";
	float scale = 30;
	 int count = 0;
	 	vector< vector <vector <double> > > Gpaths;
	 	vector< vector < double > > vin (1);
		 vector< vector < double > > Event;
		 vector< double > point0 (3);
		 vector< double > point1 (3);
		 
		 
		    ifstream is("bindata.dat", ios::binary);
		    int size2;
		    is.read((char*)&size2, sizeof(size2));
		    vin.resize(size2);

		     // Is it safe to read a whole array of structures directly into the vector?
		    is.read((char*)&vin[0], size2 * sizeof(point1));
		    
		    int c = 0;
		    /*for(int i = 0; i < vin.size(); ++i)
		    {point0 = vin.at(i);
		     if(point0.at(0) == 100000 && point0.at(1) == 100000 && c > 0)
		     {
		      Gpaths.push_back(Event);
		      Event.clear();
		     }
		     else
		     {
		      Event.push_back(point0);
		     }
		    
		    }*/
		cout << "\n did this here";    
		glm::vec3 vertex;

		int w =0;
		bool run6 = true;
		/* while(run6)
		 {int ddd = 0;
			for(unsigned int q = 0; q < Gpaths.size(); ++q)
			{cout << "\n did this here2";
		  	Event = Gpaths.at(q);
		  	
			
				if(Event.size() > w + 1)
				{
				cout << "\n did this here";
				point0 = Event.at(w);
			  	point1 = Event.at(w+1);
				
				vertex.x = point0.at(0); 
				vertex.y = point0.at(1);
				vertex.z = point0.at(2);
				glm::vec2 uv;
				uv.x = color1; 
				uv.y = color2;
				vertex.x = vertex.x/scale;
				vertex.y = vertex.y/scale;
				vertex.z = vertex.z/scale;
				out_vertices.push_back(vertex);
				out_uvs.push_back(uv);
				
				++count;
		    	        vertex.x = point1.at(0); 
				vertex.y = point1.at(1);
				vertex.z = point1.at(2);
				vertex.x = vertex.x/scale;
				vertex.y = vertex.y/scale;
				vertex.z = vertex.z/scale;
				out_vertices.push_back(vertex);
				out_uvs.push_back(uv);
				
				
		    	        ++count;
				}
				else
				++ddd;
			}//end of for
	
		++w;
		out_Vindex.push_back(count);
		if(ddd >= Gpaths.size())
		run6 = false;
		}//end of while
		glm::vec3 normal;
		for(unsigned int i = 0; i < count; ++i)
		{
		normal.x = 0;
		normal.y = 0;
		normal.z = 0;
		out_normals .push_back(normal);
	
		}*/
	
	}//end of if
	else
	{std::cout << "\nRegular .ast Import: ";
	
		FILE * file = fopen(path, "r");
		if( file == NULL ){
			printf("File not found with path given\n");
			getchar();
			return false;
		}
		float scale = 30;
		while( 1 ){

			char lineHeader[500];
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break; // EOF = End Of File. Quit the loop.

			// else : parse lineHeader
		
			if ( strcmp( lineHeader, "vertex" ) == 0 ){
				glm::vec3 vertex;
				int matches = fscanf(file, " %e %e %e \n", &vertex.x, &vertex.y, &vertex.z );
			
				if (matches != 3){
					printf("File can't be read by our simple parser :-( problem with vertices\n");
					return false;
				}
			
		
				//printf("   vertex: %f %f %f\n", vertex.x, vertex.y, vertex.z);
				glm::vec2 uv;
				uv.x = color1; 
				uv.y = color2;
				vertex.x = vertex.x/scale;
				vertex.y = vertex.y/scale;
				vertex.z = vertex.z/scale;
				out_vertices.push_back(vertex);
				out_uvs     .push_back(uv);
			}
		
			if ( strcmp( lineHeader, "facet" ) == 0 ){
				glm::vec3 normal;
				int matches = fscanf(file, "%s %e %e %e \n", &norm, &normal.x, &normal.y, &normal.z );
				if (matches != 4){
					printf("File can't be read by our simple parser :-( problem with normals\n");
					return false;
				}
				for(unsigned int i = 0; i < 3; i++)
				out_normals .push_back(normal);
			
				//printf("normal: %f %f %f\n", normal.x, normal.y, normal.z);
			}
			if ( strcmp( lineHeader, "Cluster" ) == 0 ){
				int ind = 0;
				int matches = fscanf(file, "%d \n", &ind);
				if (matches != 1){
					printf("File can't be read by our simple parser :-( problem with index\n");
					return false;
				}
				out_Vindex.push_back(ind);	
				//printf("normal: %f %f %f\n", normal.x, normal.y, normal.z);
			}

		}
       }
	
	float vecsize = out_vertices.size();
	printf("number of vertices:  %f \n", vecsize);
	
	if(out_vertices.size() != out_uvs.size() || out_vertices.size() != out_normals.size())
	{
		printf("File can't be read by our simple parser :-( number of vertices don't match number of normals\n");
		return false;
	}	
	
	

	return true;
}
//#endif 
