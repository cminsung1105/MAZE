#include <ics46/factory/DynamicFactory.hpp>
#include "MyMazeGenerator.hpp"
#include "Maze.hpp"
#include <iostream>
#include <random>
#include <vector>
#include <utility>
#include <string>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, MyMazeGenerator, "My Maze (Required)");

std::random_device device;
std::default_random_engine engine{device()};

MyMazeGenerator::MyMazeGenerator(){}

void MyMazeGenerator::generateMaze(Maze& maze)
{
	maze.addAllWalls();
	
	std::vector<std::vector<bool>> grid(maze.getWidth(), 
		std::vector<bool>(maze.getHeight(), false));

	std::pair location(0,0);

	dig_tunnel(maze, grid, location);

}

std::vector<std::string> MyMazeGenerator::check_possible_ways(const Maze& maze,
	const std::pair<int, int>& location)
{
	std::vector<std::string> ways;

	if (location.first == 0 && location.second == 0)
	{
		ways.insert(ways.begin(), {"down", "right"});
		return ways;
	}
	else if (location.first == maze.getWidth() - 1 && 
		location.second == maze.getHeight() - 1)
	{
		ways.insert(ways.begin(), {"up", "left"});
		return ways;
	}
	else if (location.first == 0 && location.second == maze.getHeight() - 1)
	{
		ways.insert(ways.begin(), {"up", "right"});
		return ways;
	}
	else if (location.first == maze.getWidth()-1 && location.second == 0)
	{
		ways.insert(ways.begin(), {"down", "left"});
		return ways;
	}
	else if(location.first == 0)
	{
		ways.insert(ways.begin(), {"up", "down", "right"});
		return ways;
	}
	else if(location.first == maze.getWidth()-1)
	{
		ways.insert(ways.begin(), {"up", "down", "left"});
		return ways;
	}
	else if (location.second == 0)
	{
		ways.insert(ways.begin(), {"down", "right", "left"});
		return ways;
	}
	else if (location.second == maze.getHeight()-1)
	{
		ways.insert(ways.begin(), {"up", "right", "left"});
		return ways;
	}
	else
	{
		ways.insert(ways.begin(), {"up", "down", "right", "left"});
		return ways;
	}
}

void MyMazeGenerator::dig_tunnel(Maze& maze, 
	std::vector<std::vector<bool>>& grid, std::pair<int, int>& location)
{
	grid[location.first][location.second] = true;

	std::vector<std::string> ways = check_possible_ways(maze, location);

	while (!ways.empty())
	{
		int length = ways.size() - 1;

		std::uniform_int_distribution<int> distribution{0, length};

		int i = distribution(engine);

		std::string d = ways[i];

		if (d == "up")
		{
			if (maze.wallExists(location.first, location.second, 
				Direction::up) == false)
			{
				ways.erase(ways.begin()+i);
			}
			else
			{
				std::pair new_location(location.first, location.second-1);

				if (grid[new_location.first][new_location.second] == false)
				{
					maze.removeWall(location.first, location.second, 
						Direction::up);

					dig_tunnel(maze, grid, new_location);

					ways = check_possible_ways(maze, location);
				}
				else
				{
					ways.erase(ways.begin()+i);
				}

			}
		}
		else if (d == "down")
		{
			if (maze.wallExists(location.first, location.second, 
				Direction::down) == false)
			{
				ways.erase(ways.begin()+i);
			}
			else
			{
				std::pair new_location(location.first, location.second+1);

				if (grid[new_location.first][new_location.second] == false)
				{
					maze.removeWall(location.first, location.second, 
						Direction::down);

					dig_tunnel(maze, grid, new_location);

					ways = check_possible_ways(maze, location);
				}
				else
				{
					ways.erase(ways.begin()+i);
				}
			}
		}
		else if (d == "right")
		{
			if (maze.wallExists(location.first, location.second, 
				Direction::right) == false)
			{
				ways.erase(ways.begin()+i);
			}
			else
			{
				std::pair new_location(location.first+1, location.second);

				if (grid[new_location.first][new_location.second] == false)
				{
					maze.removeWall(location.first, location.second, 
						Direction::right);

					dig_tunnel(maze, grid, new_location);

					ways = check_possible_ways(maze, location);
				}
				else
				{
					ways.erase(ways.begin()+i);
				}

			}
		}
		else 
		{
			if (maze.wallExists(location.first, location.second, 
				Direction::left) == false)
			{
				ways.erase(ways.begin()+i);
			}
			else
			{
				std::pair new_location(location.first-1, location.second);

				if (grid[new_location.first][new_location.second] == false)
				{
					maze.removeWall(location.first, location.second, 
						Direction::left);

					dig_tunnel(maze, grid, new_location);

					ways = check_possible_ways(maze, location);
				}
				else
				{
					ways.erase(ways.begin()+i);
				}
			}
		}
	}
}