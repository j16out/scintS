#!/bin/bash
 
###########################################################
#
#
# M9 sim setup
#
#
###########################################################
 
# compile m9 sim
echo "Starting compilation"
echo "Reminder: Make sure root is sourced"
#rm mtest2

rm test1
#macro2
#g++ macro2.cpp GPT.cpp mroot.cpp -o2 -o mtest2 `root-config --cflags --glibs` -std=c++0x -pthread
#macro1
g++ macro.cpp GPT.cpp mroot.cpp -o2 -o test1 `root-config --cflags --glibs` -std=c++0x -pthread

echo "done!"
 

