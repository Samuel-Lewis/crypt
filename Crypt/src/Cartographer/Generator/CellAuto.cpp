
#include <vector>
#include <string>

#include "lbLog.h"
#include "lbRNG.h"

#include "CellAuto.h"
#include "../Tile.h"

CellAuto::CellAuto() {}
CellAuto::~CellAuto() {}

TILEGRID CellAuto::generate(std::string wall, std::string ground, std::string regName, Options opt)
{
	DEBUG("Generating new CellAuto map...");
	std::vector< std::vector<bool> > map;
	populateMap(map, opt);

	// Apply rules
	for (int i = 0; i < opt.iterations; i++)
	{
		map = step(map, opt);
	}

	//Convert to tiles
	TILEGRID returnMap;
	returnMap.resize(opt.width, std::vector<Tile*>(opt.height));

	for (int x = 0; x < opt.width; x++)
	{
		for (int y = 0; y < opt.height; y++)
		{
			Tile* nextTile = map[x][y] ? new Tile(ground,wall) : new Tile(ground);
			nextTile->setRegionName(regName);
			
			returnMap[x][y] = nextTile;
		}
	}

	DEBUG("Generated CellAuto Map!");

	return returnMap;
}

TILEGRID CellAuto::generate(std::string wall, std::string ground, Options opt)
{
	return generate(wall, ground, "", opt);
}


// Randomly assign wall or ground to all cells
void CellAuto::populateMap(std::vector< std::vector<bool> >& map, Options opt)
{
	DEBUG("Populating map...");
	map.resize(opt.width, std::vector<bool>(opt.height));
	for (int x = 0; x < opt.width; x++)
	{
		for (int y = 0; y < opt.height; y++)
		{
			// If success chance (less than aliveChance), make it a wall
			map[x][y] = lbRNG::linear(0.0,1.0) < opt.aliveChance;
		}
	}
	DEBUG("Populated map");
}

int CellAuto::countAliveAdj(std::vector< std::vector<bool> > map, int xPos, int yPos, Options opt)
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
			} else if (x < 0 || x >= opt.width || y < 0 || y > opt.height) {
				//Counts edges as walls 
				if (opt.borders)
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
std::vector< std::vector<bool> > CellAuto::step(std::vector< std::vector<bool> > map, Options opt)
{
	// Mutable map, so we don't check a changed map
	std::vector< std::vector<bool> > mutMap = map;

	int aliveAdj = 0;
	for (int x = 0; x < opt.width; x++)
	{
		for (int y = 0; y < opt.height; y++)
		{
			// Apply semi-game of life rules
			aliveAdj = countAliveAdj(map, x,y, opt);
			if (map[x][y])
			{
				if (aliveAdj < opt.deathLimit)
				{
					// Tile is 'starved'
					mutMap[x][y] = false;
				} else {
					// Alive and staying alive
					mutMap[x][y] = true;
				}
			} else {
				if (aliveAdj > opt.birthLimit)
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

	DEBUG("Applied step rules");

	return mutMap;
}
