#ifndef MYMAZEGENERATOR_HPP
#define MYMAZEGENERATOR_HPP

#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include <vector>
#include <utility>

class MyMazeGenerator : public MazeGenerator
{
public:
	MyMazeGenerator();

	virtual void generateMaze(Maze& maze);

	void dig_tunnel(Maze & maze, std::vector<std::vector<bool>>& grid, 
		std::pair<int, int>& location);

	std::vector<std::string> check_possible_ways(const Maze& maze,
		const std::pair<int, int>& location);

};

#endif 