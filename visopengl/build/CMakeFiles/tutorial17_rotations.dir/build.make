# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jerin/opengl3/visopengl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jerin/opengl3/visopengl/build

# Include any dependencies generated for this target.
include CMakeFiles/tutorial17_rotations.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tutorial17_rotations.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tutorial17_rotations.dir/flags.make

CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.o: CMakeFiles/tutorial17_rotations.dir/flags.make
CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.o: ../tutorial17_rotations/tutorial17.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jerin/opengl3/visopengl/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.o -c /home/jerin/opengl3/visopengl/tutorial17_rotations/tutorial17.cpp

CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jerin/opengl3/visopengl/tutorial17_rotations/tutorial17.cpp > CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.i

CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jerin/opengl3/visopengl/tutorial17_rotations/tutorial17.cpp -o CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.s

CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.o.requires:
.PHONY : CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.o.requires

CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.o.provides: CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.o.requires
	$(MAKE) -f CMakeFiles/tutorial17_rotations.dir/build.make CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.o.provides.build
.PHONY : CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.o.provides

CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.o.provides.build: CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.o

CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.o: CMakeFiles/tutorial17_rotations.dir/flags.make
CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.o: ../common/shader.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jerin/opengl3/visopengl/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.o -c /home/jerin/opengl3/visopengl/common/shader.cpp

CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jerin/opengl3/visopengl/common/shader.cpp > CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.i

CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jerin/opengl3/visopengl/common/shader.cpp -o CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.s

CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.o.requires:
.PHONY : CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.o.requires

CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.o.provides: CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.o.requires
	$(MAKE) -f CMakeFiles/tutorial17_rotations.dir/build.make CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.o.provides.build
.PHONY : CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.o.provides

CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.o.provides.build: CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.o

CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.o: CMakeFiles/tutorial17_rotations.dir/flags.make
CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.o: ../common/controls.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jerin/opengl3/visopengl/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.o -c /home/jerin/opengl3/visopengl/common/controls.cpp

CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jerin/opengl3/visopengl/common/controls.cpp > CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.i

CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jerin/opengl3/visopengl/common/controls.cpp -o CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.s

CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.o.requires:
.PHONY : CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.o.requires

CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.o.provides: CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.o.requires
	$(MAKE) -f CMakeFiles/tutorial17_rotations.dir/build.make CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.o.provides.build
.PHONY : CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.o.provides

CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.o.provides.build: CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.o

CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.o: CMakeFiles/tutorial17_rotations.dir/flags.make
CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.o: ../common/texture.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jerin/opengl3/visopengl/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.o -c /home/jerin/opengl3/visopengl/common/texture.cpp

CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jerin/opengl3/visopengl/common/texture.cpp > CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.i

CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jerin/opengl3/visopengl/common/texture.cpp -o CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.s

CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.o.requires:
.PHONY : CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.o.requires

CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.o.provides: CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.o.requires
	$(MAKE) -f CMakeFiles/tutorial17_rotations.dir/build.make CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.o.provides.build
.PHONY : CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.o.provides

CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.o.provides.build: CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.o

CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.o: CMakeFiles/tutorial17_rotations.dir/flags.make
CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.o: ../common/objloader.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jerin/opengl3/visopengl/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.o -c /home/jerin/opengl3/visopengl/common/objloader.cpp

CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jerin/opengl3/visopengl/common/objloader.cpp > CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.i

CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jerin/opengl3/visopengl/common/objloader.cpp -o CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.s

CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.o.requires:
.PHONY : CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.o.requires

CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.o.provides: CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.o.requires
	$(MAKE) -f CMakeFiles/tutorial17_rotations.dir/build.make CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.o.provides.build
.PHONY : CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.o.provides

CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.o.provides.build: CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.o

CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.o: CMakeFiles/tutorial17_rotations.dir/flags.make
CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.o: ../common/vboindexer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jerin/opengl3/visopengl/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.o -c /home/jerin/opengl3/visopengl/common/vboindexer.cpp

CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jerin/opengl3/visopengl/common/vboindexer.cpp > CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.i

CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jerin/opengl3/visopengl/common/vboindexer.cpp -o CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.s

CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.o.requires:
.PHONY : CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.o.requires

CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.o.provides: CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.o.requires
	$(MAKE) -f CMakeFiles/tutorial17_rotations.dir/build.make CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.o.provides.build
.PHONY : CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.o.provides

CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.o.provides.build: CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.o

CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.o: CMakeFiles/tutorial17_rotations.dir/flags.make
CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.o: ../common/quaternion_utils.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jerin/opengl3/visopengl/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.o -c /home/jerin/opengl3/visopengl/common/quaternion_utils.cpp

CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jerin/opengl3/visopengl/common/quaternion_utils.cpp > CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.i

CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jerin/opengl3/visopengl/common/quaternion_utils.cpp -o CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.s

CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.o.requires:
.PHONY : CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.o.requires

CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.o.provides: CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.o.requires
	$(MAKE) -f CMakeFiles/tutorial17_rotations.dir/build.make CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.o.provides.build
.PHONY : CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.o.provides

CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.o.provides.build: CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.o

# Object files for target tutorial17_rotations
tutorial17_rotations_OBJECTS = \
"CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.o" \
"CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.o" \
"CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.o" \
"CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.o" \
"CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.o" \
"CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.o" \
"CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.o"

# External object files for target tutorial17_rotations
tutorial17_rotations_EXTERNAL_OBJECTS =

tutorial17_rotations: CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.o
tutorial17_rotations: CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.o
tutorial17_rotations: CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.o
tutorial17_rotations: CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.o
tutorial17_rotations: CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.o
tutorial17_rotations: CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.o
tutorial17_rotations: CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.o
tutorial17_rotations: CMakeFiles/tutorial17_rotations.dir/build.make
tutorial17_rotations: /usr/lib/x86_64-linux-gnu/libGLU.so
tutorial17_rotations: /usr/lib/x86_64-linux-gnu/libGL.so
tutorial17_rotations: /usr/lib/x86_64-linux-gnu/libSM.so
tutorial17_rotations: /usr/lib/x86_64-linux-gnu/libICE.so
tutorial17_rotations: /usr/lib/x86_64-linux-gnu/libX11.so
tutorial17_rotations: /usr/lib/x86_64-linux-gnu/libXext.so
tutorial17_rotations: external/glfw-3.0.3/src/libglfw3.a
tutorial17_rotations: external/libGLEW_190.a
tutorial17_rotations: external/libANTTWEAKBAR_116_OGLCORE_GLFW.a
tutorial17_rotations: /usr/lib/x86_64-linux-gnu/libGLU.so
tutorial17_rotations: /usr/lib/x86_64-linux-gnu/libXrandr.so
tutorial17_rotations: /usr/lib/x86_64-linux-gnu/libXi.so
tutorial17_rotations: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
tutorial17_rotations: /usr/lib/x86_64-linux-gnu/librt.so
tutorial17_rotations: /usr/lib/x86_64-linux-gnu/libm.so
tutorial17_rotations: /usr/lib/x86_64-linux-gnu/libGL.so
tutorial17_rotations: /usr/lib/x86_64-linux-gnu/libSM.so
tutorial17_rotations: /usr/lib/x86_64-linux-gnu/libICE.so
tutorial17_rotations: /usr/lib/x86_64-linux-gnu/libX11.so
tutorial17_rotations: /usr/lib/x86_64-linux-gnu/libXext.so
tutorial17_rotations: CMakeFiles/tutorial17_rotations.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable tutorial17_rotations"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tutorial17_rotations.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -E copy /home/jerin/opengl3/visopengl/build/./tutorial17_rotations /home/jerin/opengl3/visopengl/tutorial17_rotations/

# Rule to build all files generated by this target.
CMakeFiles/tutorial17_rotations.dir/build: tutorial17_rotations
.PHONY : CMakeFiles/tutorial17_rotations.dir/build

CMakeFiles/tutorial17_rotations.dir/requires: CMakeFiles/tutorial17_rotations.dir/tutorial17_rotations/tutorial17.cpp.o.requires
CMakeFiles/tutorial17_rotations.dir/requires: CMakeFiles/tutorial17_rotations.dir/common/shader.cpp.o.requires
CMakeFiles/tutorial17_rotations.dir/requires: CMakeFiles/tutorial17_rotations.dir/common/controls.cpp.o.requires
CMakeFiles/tutorial17_rotations.dir/requires: CMakeFiles/tutorial17_rotations.dir/common/texture.cpp.o.requires
CMakeFiles/tutorial17_rotations.dir/requires: CMakeFiles/tutorial17_rotations.dir/common/objloader.cpp.o.requires
CMakeFiles/tutorial17_rotations.dir/requires: CMakeFiles/tutorial17_rotations.dir/common/vboindexer.cpp.o.requires
CMakeFiles/tutorial17_rotations.dir/requires: CMakeFiles/tutorial17_rotations.dir/common/quaternion_utils.cpp.o.requires
.PHONY : CMakeFiles/tutorial17_rotations.dir/requires

CMakeFiles/tutorial17_rotations.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tutorial17_rotations.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tutorial17_rotations.dir/clean

CMakeFiles/tutorial17_rotations.dir/depend:
	cd /home/jerin/opengl3/visopengl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jerin/opengl3/visopengl /home/jerin/opengl3/visopengl /home/jerin/opengl3/visopengl/build /home/jerin/opengl3/visopengl/build /home/jerin/opengl3/visopengl/build/CMakeFiles/tutorial17_rotations.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tutorial17_rotations.dir/depend

