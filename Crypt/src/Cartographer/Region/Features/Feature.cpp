#include <vector>
#include <string>

#include "Config.h"

#include "lbLog.h"
#include "lbRNG.h"

#include "Tile.h"

#include "Feature.h"


Feature::Feature(int width, int height)
{
	_height = height;
	_width = width;
	
	// Resize to given size, and fill with empty tiles
	tiles.resize(_width, std::vector<Tile*>(_height, new Tile()));
}

Feature::~Feature()
{
	// Yep, more deletions
}

// Swap tiles around, so we can delete the old one
void Feature::swapGround(int x, int y, std::string groundTile)
{
	if (x >= 0 && x < _width && y >=0 && y <_height)
	{
//		delete tiles[x][y];
		tiles[x][y] = new Tile(groundTile, tiles[x][y]->getTop()->getTileName());
	} else {
		WARN("Tried to swap an out of bounds tile ["<<x<<","<<y<<"]");
	}
}

// Swap tiles around, so we can delete the old one
void Feature::swapTop(int x, int y, std::string topTile)
{
	if (x >= 0 && x < _width && y >=0 && y <_height)
	{
		//		delete tiles[x][y];
		tiles[x][y] = new Tile(tiles[x][y]->getGround()->getTileName(), topTile);
	} else {
		WARN("Tried to swap an out of bounds tile ["<<x<<","<<y<<"]");
	}
}

void Feature::addBorder(std::string groundTile, std::string wallTile)
{
	// Top and bottom
	for (int i = 0; i < _width; i++)
	{
		swapTop(i,0, wallTile);
		swapTop(i,_height-1, wallTile);
	}
	
	// Sides
	for (int i = 0; i < _height; i++)
	{
		swapTop(0,i, wallTile);
		swapTop(_width-1, i, wallTile);
	}
}

void Feature::addFloor(std::string floorTile)
{
	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			swapGround(x,y,floorTile);
		}
	}
		
}

// Super simple one, just to keep things spicy
void Feature::generate()
{
	addFloor("grass-light");
	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			float decorChance = lbRNG::linear(0.0,1.0);
			
			if (decorChance < 0.025)
			{
				swapTop(x,y,"flower-" + std::to_string(lbRNG::linear(2,4)));
			} else if (decorChance < 0.1) {
				swapTop(x,y,"tree-light");
			}
		}
		
	}
}