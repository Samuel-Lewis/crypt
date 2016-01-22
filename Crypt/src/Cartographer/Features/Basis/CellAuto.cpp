
#include <vector>
#include <string>

#include "Config.h"

#include "lbLog.h"
#include "lbRNG.h"

#include "Feature.h"
#include "CellAuto.h"

CellAuto::CellAuto(int width, int height) : Feature(width,height), options(2,0.4,4,4,false)
{}

CellAuto::~CellAuto()
{}

void CellAuto::generate(std::string wall, std::string ground)
{
	
	INFO("Generating new CellAuto");
	std::vector< std::vector<bool> > map;
	populateMap(map);

	// Apply rules
	for (int i = 0; i < options.iterations; i++)
	{
		map = step(map);
	}

	//Convert to tiles
	TILEGRID returnMap;
	tiles.resize(_width, std::vector<Tile*>(_height));

	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			tiles[x][y] = map[x][y] ? new Tile(ground,wall) : new Tile(ground);
		}
	}

	INFO("Generated CellAuto Map!");
}

// Randomly assign wall or ground to all cells
void CellAuto::populateMap(std::vector< std::vector<bool> >& map)
{
	map.resize(_width, std::vector<bool>(_height));
	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			// If success chance (less than aliveChance), make it a wall
			map[x][y] = lbRNG::decision(options.aliveChance);
		}
	}
	INFO("Populated map");
}

int CellAuto::countAliveAdj(std::vector< std::vector<bool> > map, int xPos, int yPos)
{
	int numAlive = 0;

	// Go over 3x3 around cell
	for (int x = xPos-1; x < xPos+2; x++)
	{
		for (int y = yPos-1; y < yPos+2; y++)
		{
			if (x == xPos && y == yPos)
			{
				// Doesn't count itself
			} else if (x < 0 || x >= _width || y < 0 || y > _height) {
				//Counts edges as walls 
				if (options.borders)
				{
					numAlive++;
				}
			} else if (map[x][y]) {
				// Check if name matches the wall tile
				numAlive++;
			}
		}
	}

	return numAlive;
}

// Apply rules over whole map
std::vector< std::vector<bool> > CellAuto::step(std::vector< std::vector<bool> > map)
{
	// Mutable map, so we don't check a changed map
	std::vector< std::vector<bool> > mutMap = map;

	int aliveAdj = 0;
	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			// Apply semi-game of life rules
			aliveAdj = countAliveAdj(map, x,y);
			if (map[x][y])
			{
				if (aliveAdj < options.deathLimit)
				{
					// Tile is 'starved'
					mutMap[x][y] = false;
				} else {
					// Alive and staying alive
					mutMap[x][y] = true;
				}
			} else {
				if (aliveAdj > options.birthLimit)
				{
					// Tile is surrounded by enough to be 'born'
					mutMap[x][y] = true;
				} else {
					// Dead, and staying dead
					mutMap[x][y] = false;
				}
			}
		}
	}

	return mutMap;
}
