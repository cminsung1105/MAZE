#include <ics46/factory/DynamicFactory.hpp>
#include "MyMazeSolver.hpp"
#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include "Maze.hpp"
#include "Direction.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, MyMazeSolver, "My Maze Solver (Required)");

std::random_device machine;
std::default_random_engine e{machine()};

void MyMazeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
	mazeSolution.restart();

	std::pair<int, int> location = mazeSolution.getStartingCell();

	std::vector<std::pair<int,int>> visited;

	find_way(maze, mazeSolution, location, visited);

}

void MyMazeSolver::find_way(const Maze& maze, MazeSolution& mazeSolution, 
	std::pair<int, int>& location, std::vector<std::pair<int,int>>& visited)
{
	Direction d;

	location = mazeSolution.getCurrentCell();

	std::vector<Direction> ways = check_possible_ways(maze, mazeSolution, 
		location, visited);

	if (mazeSolution.isComplete())
	{
		return;
	}

	if (ways.size() > 0)
	{
		for(int i = 0; i < ways.size(); ++i)
		{
			d = ways[i];

			std::pair<int,int> new_location = new_coordinates(location, d);


			if(std::find(visited.begin(),visited.end(),new_location) 
				== visited.end())
			{

				if(!mazeSolution.isComplete())
				{
					mazeSolution.extend(d);
				}
				location = mazeSolution.getCurrentCell();
				visited.push_back(location);
				find_way(maze, mazeSolution, new_location, visited);
			}
		}
	}
	else if (ways.size() == 0)
	{
		mazeSolution.backUp();
		location = mazeSolution.getCurrentCell();


		if(location == mazeSolution.getStartingCell())
		{
			return;
		}
		find_way(maze, mazeSolution, location, visited);
	}



}

std::vector<Direction> MyMazeSolver::check_possible_ways(const Maze& maze,
	const MazeSolution& mazeSolution, const std::pair<int, int>& location,
	std::vector<std::pair<int,int>> visited)
{
	std::vector<Direction> ways;

	if (location.first - 1 >= 0 && 
		!maze.wallExists(location.first, location.second, Direction::left))
	{
		std::pair<int,int> new_location = new_coordinates(location,Direction::left);

		if(std::find(visited.begin(),visited.end(),new_location)==visited.end())
		{
			ways.insert(ways.begin(), Direction::left);
		}
	
	}
	if (location.first + 1 < mazeSolution.getWidth() &&
		!maze.wallExists(location.first, location.second, Direction::right)) 
	{
		std::pair<int,int> new_location = new_coordinates(location,Direction::right);

		if(std::find(visited.begin(),visited.end(),new_location)==visited.end())
		{
			ways.insert(ways.begin(), Direction::right);
		}
	}
	if (location.second - 1 >= 0 &&
		!maze.wallExists(location.first,location.second,Direction::up))
	{
		std::pair<int,int> new_location = new_coordinates(location,Direction::up);

		if(std::find(visited.begin(),visited.end(),new_location)==visited.end())
		{
			ways.insert(ways.begin(), Direction::up);
		}
	}
	if (location.second + 1 < mazeSolution.getHeight() &&
		!maze.wallExists(location.first,location.second,Direction::down))
	{
		std::pair<int,int> new_location = new_coordinates(location,Direction::down);

		if(std::find(visited.begin(),visited.end(),new_location)==visited.end())
		{
			ways.insert(ways.begin(), Direction::down);
		}
	}
	return ways;

}

std::pair<int,int> MyMazeSolver::new_coordinates(
	const std::pair<int,int>& location, Direction direction)
{
	std::pair<int,int> new_location = location;

	if (direction == Direction::right)
	{
		new_location.first += 1;
	}
	else if (direction == Direction::left)
	{
		new_location.first -= 1;
	}
	else if (direction == Direction::up)
	{
		new_location.second -= 1;
	}
	else
	{
		new_location.second += 1;
	}
	return new_location;
}

