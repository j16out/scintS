photon simulations using cuda/root/opengl

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

	open Make and CMakeCach.txt files and edit the home directory to match your own.

	then make: 
	$ make -j(number of cores)

	then 
	$ cd../visualizer1/

	then 
	$ ./visualizer to run

