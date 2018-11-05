// expmain.cpp
//
// ICS 46 Spring 2018
// Project #1: Dark at the End of the Tunnel
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with the given classes in the darkmaze library, or with your own
// algorithm implementations, outside of the context of the GUI or
// Google Test.

#include <memory>
#include "MazeFactory.hpp"
#include "MyMazeGenerator.hpp"

int main()
{
    std::unique_ptr<Maze> maze = MazeFactory().create(10, 10);
	MyMazeGenerator generator;
	generator.generateMaze(*maze);




    return 0;
}

