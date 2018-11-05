#ifndef MYMAZESOLVER_HPP
#define MYMAZESOLVER_HPP

#include "MazeSolver.hpp"
#include "Maze.hpp"
#include "MazeSolution.hpp"
#include "Direction.hpp"
#include <vector>
#include <string>

class MyMazeSolver : public MazeSolver
{
public:
	virtual void solveMaze(const Maze& maze, MazeSolution& mazeSolution);

	std::vector<Direction> check_possible_ways(const Maze& maze,
		const MazeSolution& mazeSolution, const std::pair<int, int>& location,
		std::vector<std::pair<int,int>> visited);

	void find_way(const Maze& maze, MazeSolution& mazeSolution, 
		std::pair<int, int>& location, std::vector<std::pair<int,int>>& visited);

	std::pair<int,int> new_coordinates(const std::pair<int,int>& location, 
		Direction direction); 
};

#endif