#!/bin/bash

g++ -std=c++0x `pkg-config --cflags libglfw` -g -o the_maze_2 the_maze_2.cpp models/player.cpp model.cpp models/wall_segment.cpp `pkg-config --static --libs libglfw` /usr/lib64/libGLEW.a
if [ $? -eq 0 ]; then
	./the_maze_2
fi
