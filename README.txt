photon simulations using cuda/root/opengl

Before compiling make appropriate changes for multicore threading (in GPD.cxx) as is set up for 8-core cpu
Too compile simulation:

	make sure latest g++/gcc installed
	source your root of choice, im using v5.34.32
	run comp.sh ie 
	
	$ sh comp.sh
	
	done!

	macro.cpp contains all changable parameters, and is the highest level (user interface) which uses both standard root and opengl for visualization,	
	macro2.cpp shows what else can be done with functions

	edit comp.sh to change executable


Too compile opengl interface:

	cd visopengl/build

	open Makefile and CMakeCach.txt files in build and change and edit the home directory to match your own ie search for "jerin" and replace with your own.
	then make sure you have requisits for opengl ie:
			-libglew-dev
			-libglm-dev
			-libassimp-dev
			-glew-utils
			-x11-xserver-utils
			-libxrandr-dev
			-libxi-dev

	then make: 
	$ make -j(number of cores)

	then 
	$ cd../visualizer1/

	then 
	$ ./visualizer to run

