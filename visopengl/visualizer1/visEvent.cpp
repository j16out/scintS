// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>
#include <sstream>
 
// Include GLEW
#include <GL/glew.h>
 
// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
using namespace glm;
 
// Include AntTweakBar
#include <AntTweakBar.h>
 
 
#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/quaternion_utils.hpp> // See quaternion_utils.cpp for RotationBetweenVectors, LookAt and RotateTowards

vec3 gPosition1(-1.5f, 0.0f, 0.0f);
vec3 gOrientation1;
 
vec3 gPosition2( 1.5f, 0.0f, 0.0f);
quat gOrientation2;
 
bool gLookAtOther = true;


std::string int_to_string(int a);



bool file_texists(std::string& name)
{
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

std::string int_to_string(int a)
{
std::stringstream ss;
ss << a;
std::string str = ss.str();
return str;
}

 
int main( void )
{ float windsize = 1.2;
 const char* c; 
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}
 
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024*windsize, 768*windsize, "Scintillation Visualization", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
 
	// Initialize the GUI
	TwInit(TW_OPENGL_CORE, NULL);
	TwWindowSize(1024*windsize, 768*windsize);
	//TwBar * EulerGUI = TwNewBar("Euler settings");
	TwBar * QuaternionGUI = TwNewBar("Quaternion settings");
	//TwSetParam(EulerGUI, NULL, "refresh", TW_PARAM_CSTRING, 1, "0.1");
	TwSetParam(QuaternionGUI, NULL, "position", TW_PARAM_CSTRING, 1, "0.1");

	/*TwAddVarRW(EulerGUI, "Euler X", TW_TYPE_FLOAT, &gOrientation1.x, "step=0.01");
	TwAddVarRW(EulerGUI, "Euler Y", TW_TYPE_FLOAT, &gOrientation1.y, "step=0.01");
	TwAddVarRW(EulerGUI, "Euler Z", TW_TYPE_FLOAT, &gOrientation1.z, "step=0.01");
	TwAddVarRW(EulerGUI, "Pos X"  , TW_TYPE_FLOAT, &gPosition1.x, "step=0.1");
	TwAddVarRW(EulerGUI, "Pos Y"  , TW_TYPE_FLOAT, &gPosition1.y, "step=0.1");
	TwAddVarRW(EulerGUI, "Pos Z"  , TW_TYPE_FLOAT, &gPosition1.z, "step=0.1");*/
 
	TwAddVarRW(QuaternionGUI, "Quaternion", TW_TYPE_QUAT4F, &gOrientation2, "showval=true open=true ");
	TwAddVarRW(QuaternionGUI, "Use LookAt", TW_TYPE_BOOL8 , &gLookAtOther, "help?'");
 
	// Set GLFW event callbacks. I removed glfwSetWindowSizeCallback for conciseness
	glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)TwEventMouseButtonGLFW); // - Directly redirect GLFW mouse button events to AntTweakBar
	glfwSetCursorPosCallback(window, (GLFWcursorposfun)TwEventMousePosGLFW);          // - Directly redirect GLFW mouse position events to AntTweakBar
	glfwSetScrollCallback(window, (GLFWscrollfun)TwEventMouseWheelGLFW);    // - Directly redirect GLFW mouse wheel events to AntTweakBar
	glfwSetKeyCallback(window, (GLFWkeyfun)TwEventKeyGLFW);                         // - Directly redirect GLFW key events to AntTweakBar
	glfwSetCharCallback(window, (GLFWcharfun)TwEventCharGLFW);                      // - Directly redirect GLFW char events to AntTweakBar
 
 
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetCursorPos(window, (1024*windsize)/2, (768*windsize)/2);
 
	// Dark blue background
	glClearColor(0.4f, 0.6f, 0.9f, 0.4f);
 
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 
 
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
 	
	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "StandardShading.vertexshader", "StandardTransparentShading.fragmentshader" );
        GLuint programID2 = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );
	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID2, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID2, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID2, "M");
	
 
	// Get a handle for our buffers
	GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID2, "vertexPosition_modelspace");
	GLuint vertexUVID = glGetAttribLocation(programID2, "vertexUV");
	GLuint vertexNormal_modelspaceID = glGetAttribLocation(programID2, "vertexNormal_modelspace");
 
	// Load the texture
	GLuint Texture = loadDDS("uvmap.DDS");
	//lines
	glLineWidth(0.4); 
	glColor3f(0.0, 0.5, 0.1);
	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
 
        std::vector< int > VindexT;
 
	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	
	//two has to be the lines
	std::vector<glm::vec3> vertices2;
	std::vector<glm::vec2> uvs2;
	std::vector<glm::vec3> normals2;
	std::vector< int > Vindex;
	
	
	std::vector<glm::vec3> vertices3;
	std::vector<glm::vec2> uvs3;
	std::vector<glm::vec3> normals3;
	
	std::vector<glm::vec3> vertices4;
	std::vector<glm::vec2> uvs4;
	std::vector<glm::vec3> normals4;
	
	
	//------------------------------------------Load Geometry and Sensors---------------------------------------------//
	
	std::string cadfile = "../../Project1";
	 bool run1 = true;
	 bool res;
 	std::string temp;
 	
		 float k = 1;
		 while(run1)
		  {temp = cadfile;
		  temp.append("/geometry/g");
		  temp.append(int_to_string(k));
		  temp.append(".ast");
		  c = temp.c_str();
			  if(file_texists(temp))
			  {
			  res = loadOBJ(c, vertices, uvs, normals, VindexT, 0.95, 0.25, 0);
			  run1 = false;
			  }
			  else
			  {
			  printf("Geometry file: %s Doesn't Exist", c);
			  return 0;
			  }
		  ++k;
		  }
	k = 1;
	run1 = true;
		 while(run1)
		  {temp = cadfile;
		  temp.append("/sensors/s");
		  temp.append(int_to_string(k));
		  temp.append(".ast");
		   c = temp.c_str();
			  if(file_texists(temp))
			  {
			  res = loadOBJ(c, vertices3, uvs3, normals3, VindexT,0.5, 0.01, 0);
			  }
			  else
			  {
			  run1 = false;
				   if(k ==1)
				   {
				   printf("Sensor file: %s Doesn't Exist", c);
				   return 0;
				   }
			   
			  }
		  ++k;
		  }
	temp = cadfile;
	temp.append("/positron/pdata.txt");
	 c = temp.c_str();
			  if(file_texists(temp))
			  {
			  res = loadOBJ(c, vertices2, uvs2, normals2, Vindex, 1, 1, 0);
			  }
			  else
			  {
			  run1 = false;
				   if(k ==1)
				   {
				   printf("Positron file: %s Doesn't Exist", c);
				   return 0;
				   }
			   
			  }
			  
	  temp = cadfile;
	  temp.append("/positron/new");
	  c = temp.c_str();
			  if(file_texists(temp))
			  {
			  res = loadOBJ(c, vertices4, uvs4, normals4, VindexT, 0.7, 0.7, 0);
			  }
			  else
			  {
			  run1 = false;
				   if(k ==1)
				   {
				   printf("Positron file: %s Doesn't Exist", c);
				   return 0;
				   }
			   
			  }
	//bool res = loadOBJ("../../cadd/sim45/sim45cone.ast", vertices, uvs, normals, VindexT, 0.95, 0.25, 0);
	//res = loadOBJ("../../cadd/sim45/ssim45.ast", vertices3, uvs3, normals3, VindexT,0.5, 0.01, 0);
	//res = loadOBJ("pdata.txt", vertices2, uvs2, normals2, Vindex, 1, 1, 0);
	//res = loadOBJ("../../cadd/positron/new", vertices4, uvs4, normals4, VindexT, 0.7, 0.7, 0);
	
 

 
	// Load it into a VBO
 
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	//second
	GLuint vertexbuffer2;
	glGenBuffers(1, &vertexbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
	glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(glm::vec3), &vertices2[0], GL_STATIC_DRAW);

	GLuint uvbuffer2;
	glGenBuffers(1, &uvbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer2);
	glBufferData(GL_ARRAY_BUFFER, uvs2.size() * sizeof(glm::vec2), &uvs2[0], GL_STATIC_DRAW);
	
	GLuint normalbuffer2;
	glGenBuffers(1, &normalbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer2);
	glBufferData(GL_ARRAY_BUFFER, normals2.size() * sizeof(glm::vec3), &normals2[0], GL_STATIC_DRAW);
	//sensors
	GLuint vertexbuffer3;
	glGenBuffers(1, &vertexbuffer3);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer3);
	glBufferData(GL_ARRAY_BUFFER, vertices3.size() * sizeof(glm::vec3), &vertices3[0], GL_STATIC_DRAW);

	GLuint uvbuffer3;
	glGenBuffers(1, &uvbuffer3);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer3);
	glBufferData(GL_ARRAY_BUFFER, uvs3.size() * sizeof(glm::vec2), &uvs3[0], GL_STATIC_DRAW);
	
	GLuint normalbuffer3;
	glGenBuffers(1, &normalbuffer3);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer3);
	glBufferData(GL_ARRAY_BUFFER, normals3.size() * sizeof(glm::vec3), &normals3[0], GL_STATIC_DRAW);
	
	GLuint vertexbuffer4;
	glGenBuffers(1, &vertexbuffer4);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer4);
	glBufferData(GL_ARRAY_BUFFER, vertices4.size() * sizeof(glm::vec3), &vertices4[0], GL_STATIC_DRAW);

	GLuint uvbuffer4;
	glGenBuffers(1, &uvbuffer4);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer4);
	glBufferData(GL_ARRAY_BUFFER, uvs4.size() * sizeof(glm::vec2), &uvs4[0], GL_STATIC_DRAW);
	
	GLuint normalbuffer4;
	glGenBuffers(1, &normalbuffer4);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer4);
	glBufferData(GL_ARRAY_BUFFER, normals4.size() * sizeof(glm::vec3), &normals4[0], GL_STATIC_DRAW);

	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
 
	// For speed computation
	double lastTime = glfwGetTime();
	double lastFrameTime = lastTime;
	int nbFrames = 0;
	
		// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	float vz = 7, vx = 0, vy = 0;
	int prop = 0;
	bool flop = false;
	bool bflop = true;
	int Vindexcount = 0;
	int prop2 = vertices.size();
	
	printf("\n**************************************\nP = start/stop animation\nG = reset \nO = reverse \nF = step backwards \nz = turn on/off scintillator \n**************************************\n**************************************");
 
	do{ 
	
	//controls
	        if(glfwGetKey(window, GLFW_KEY_SPACE ) == GLFW_PRESS && flop == false && prop < Vindex.size()-2)
		{
		if(bflop)
		++prop;
		else
		{if(prop > 1)
		--prop;
		}
		}
	
	
		if(glfwGetKey(window, GLFW_KEY_MINUS ) == GLFW_PRESS)
		{vz= vz + 0.05;
		}
		
		if(glfwGetKey(window, GLFW_KEY_EQUAL ) == GLFW_PRESS && vz > 0)
		{vz= vz - 0.05;
		}
		
		if(glfwGetKey(window, GLFW_KEY_UP ) == GLFW_PRESS)
		{vy= vy + 0.05;
		}
		
		if(glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS)
		{vy= vy - 0.05;
		}
		
		if(glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS)
		{
		 vx= vx + 0.05;
		}
		
		if(glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS)
		{vx= vx - 0.05;
		}
 		//disable blender for non-transparent objects
 		glDisable(GL_BLEND);
		// Measure speed
		double currentTime = glfwGetTime();
		float deltaTime = (float)(currentTime - lastFrameTime); 
		lastFrameTime = currentTime;
		nbFrames++;
		
 
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
		// Use our shader
		glUseProgram(programID2);
 
		glm::mat4 ProjectionMatrix = glm::perspective(450.0f, 40.0f / 30.0f, 1.0f, 1000.0f);
		glm::mat4 ViewMatrix = glm::lookAt(
			glm::vec3( vx, vy, vz ), // Camera is here
			glm::vec3( vx, vy, 0 ), // and looks here
			glm::vec3( 0, 1, 0 )  // Head is up (set to 0,-1,0 to look upside-down)
		);
		 
        //****************************************Render sensors
                 // 1rst attribute buffer : 
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer3);
		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE,0,(void*)0);
		//LAYOUT: glVertexAttribPointer(attribute, size, type, normalized?, stride, array buffer offset)
		
		
                // 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer3);
		glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,(void*)0);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer3);
		glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE, 0,(void*)0);
		
		
		//lighting
                glm::vec3 lightPos = glm::vec3(0,0,9);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		{ // Quaternion
 
			// It the box is checked...
			if (gLookAtOther){
				vec3 desiredDir = gPosition1-gPosition2;
				vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f); // +Y
 
				// Compute the desired orientation
				quat targetOrientation = normalize(LookAt(desiredDir, desiredUp));
 
				// And interpolate
				gOrientation2 = RotateTowards(gOrientation2, targetOrientation, 1.0f*deltaTime);
			}
 
			glm::mat4 RotationMatrix = mat4_cast(gOrientation2);
			glm::mat4 TranslationMatrix = translate(mat4(), gPosition2); // A bit to the right
			glm::mat4 ScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
			glm::mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;
 
			glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
 
			// Send our transformation to the currently bound shader, 
			// in the "MVP" uniform
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
 
 
			// Draw the triangles !
			glDrawArrays(GL_TRIANGLES, 0, vertices3.size() );
				
		}
	//*******************************************Now Render Photon paths
  		glColor3f(0.0, 0.5, 0.1);
                 // 1rst attribute buffer : lines
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(4);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer2);
		glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,(void*)0);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(5);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer2);
		glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,(void*)0);
		
		//state light position for this object
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		{ // Quaternion
 
			// It the box is checked...
			if (gLookAtOther){
				vec3 desiredDir = gPosition1-gPosition2;
				vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f); // +Y
 
				// Compute the desired orientation
				quat targetOrientation = normalize(LookAt(desiredDir, desiredUp));
 
				// And interpolate
				gOrientation2 = RotateTowards(gOrientation2, targetOrientation, 1.0f*deltaTime);
			}
 
			glm::mat4 RotationMatrix = mat4_cast(gOrientation2);
			glm::mat4 TranslationMatrix = translate(mat4(), gPosition2); // A bit to the right
			glm::mat4 ScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
			glm::mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;
 
			glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
 
			// Send our transformation to the currently bound shader, 
			// in the "MVP" uniform
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
 
                       
			// Draw the triangles
			glDrawArrays(GL_LINES, 0, Vindexcount);
			//glDrawArrays(GL_LINES, 0, vertices2.size() );
			
			if(glfwGetKey(window, GLFW_KEY_P ) == GLFW_PRESS)
		        { if(flop)
		          flop = false;
		          else
		          flop = true;
		        }
		        if(glfwGetKey(window, GLFW_KEY_O ) == GLFW_PRESS)
		        { if(bflop)
		          bflop = false;
		          else
		          bflop = true;
		        }
		        
		         if(glfwGetKey(window, GLFW_KEY_F ) == GLFW_PRESS)
		        { 
		          prop = Vindex.size()-2;
		        }
		        
		           if(glfwGetKey(window, GLFW_KEY_G ) == GLFW_PRESS)
		        { 
		          prop = 0;
		        }
		        
			
			if(flop)
			{
				if(prop < Vindex.size()-2 && bflop)
				++prop;
				if(bflop == false && prop > 0)
				--prop;
			}
			
			Vindexcount = Vindex.at(prop);
				
		}
		
		//P = start/stop animation
		//G = reset
		//O = reverse
		//F = step backwards
		//z = turn on/off scintillator
		//************************************************positron
		glColor3f(0.0, 0.5, 0.1);
                 // 1rst attribute buffer : lines
		glEnableVertexAttribArray(9);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer4);
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(10);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer4);
		glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,(void*)0);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(11);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer4);
		glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,(void*)0);
		
		//state light position for this object
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		{ // Quaternion
 
			// It the box is checked...
			if (gLookAtOther){
				vec3 desiredDir = gPosition1-gPosition2;
				vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f); // +Y
 
				// Compute the desired orientation
				quat targetOrientation = normalize(LookAt(desiredDir, desiredUp));
 
				// And interpolate
				gOrientation2 = RotateTowards(gOrientation2, targetOrientation, 1.0f*deltaTime);
			}
 
			glm::mat4 RotationMatrix = mat4_cast(gOrientation2);
			glm::mat4 TranslationMatrix = translate(mat4(), gPosition2); // A bit to the right
			glm::mat4 ScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
			glm::mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;
 
			glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
 
			// Send our transformation to the currently bound shader, 
			// in the "MVP" uniform
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
 
 
			// Draw the triangles !
			glDrawArrays(GL_TRIANGLES, 0, vertices4.size() );
				
		}
		//**********************************************Start of scintillator
		glUseProgram(programID);
		//re-enable blending for transparent objects
		glEnable(GL_BLEND);
		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(6);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(7);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,(void*)0);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(8);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,(void*)0);
 
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
		
 
		{ // Quaternion
 
			// It the box is checked...
			if (gLookAtOther){
				vec3 desiredDir = gPosition1-gPosition2;
				vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f); // +Y
 
				// Compute the desired orientation
				quat targetOrientation = normalize(LookAt(desiredDir, desiredUp));
 
				// And interpolate
				gOrientation2 = RotateTowards(gOrientation2, targetOrientation, 1.0f*deltaTime);
			}
 
			glm::mat4 RotationMatrix = mat4_cast(gOrientation2);
			glm::mat4 TranslationMatrix = translate(mat4(), gPosition2); // A bit to the right
			glm::mat4 ScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
			glm::mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;
 
			glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
 
			// Send our transformation to the currently bound shader, 
			// in the "MVP" uniform
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
 
                        if(glfwGetKey(window, GLFW_KEY_Z ) == GLFW_PRESS)
		{if(prop2 == 0)
		prop2 = vertices.size();
		else
		prop2 = 0;
		}
			// Draw the triangles !
			glDrawArrays(GL_TRIANGLES, 0, prop2 );
				
		}
                
                 //******************************************8
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
 
		// Draw GUI
		TwDraw();
 
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
 
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );
 
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	//glDeleteBuffers(1, &elementbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);
 
	// Close GUI and OpenGL window, and terminate GLFW
	TwTerminate();
	glfwTerminate();
 
	return 0;
}
 
