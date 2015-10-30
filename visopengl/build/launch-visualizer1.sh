#!/bin/sh
bindir=$(pwd)
cd /home/jerin/scintS/visopengl/visualizer1/
export LD_LIBRARY_PATH=:$LD_LIBRARY_PATH

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		 -batch -command=$bindir/gdbscript  /home/jerin/scintS/visopengl/build/visualizer1 
	else
		"/home/jerin/scintS/visopengl/build/visualizer1"  
	fi
else
	"/home/jerin/scintS/visopengl/build/visualizer1"  
fi
