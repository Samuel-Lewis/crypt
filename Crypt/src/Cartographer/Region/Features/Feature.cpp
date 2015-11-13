#include <vector>

#include "Config.h"

#include "lbLog.h"

#include "Tile.h"

#include "Feature.hpp"


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
void Feature::swap(int x, int y, std::string groundTile, std::string topTile)
{
	if (x >= 0 && x < _width && y >=0 && y <_height)
	{
//		delete tiles[x][y];
		tiles[x][y] = new Tile(groundTile, topTile);
	} else {
		WARN("Tried to swap an out of bounds tile ["<<x<<","<<y<<"]");
	}
}

void Feature::addBorder(std::string groundTile, std::string topTile)
{
	// Top and bottom
	for (int i = 0; i < _width; i++)
	{
		swap(i,0, groundTile, topTile);
		swap(i,_height-1, groundTile, topTile);
	}
	
	// Sides
	for (int i = 0; i < _height; i++)
	{
		swap(0,i, groundTile, topTile);
		swap(_width-1, i, groundTile, topTile);
	}
}