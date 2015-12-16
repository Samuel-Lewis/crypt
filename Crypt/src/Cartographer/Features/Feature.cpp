#include <vector>
#include <string>

#include "Config.h"

#include "lbLog.h"
#include "lbRNG.h"

#include "Tile.h"

#include "Feature.h"

#include "Entity.h"
#include "Switch.h"


Feature::Feature(int width, int height)
{
	// Initial bounds
	_height = height;
	_width = width;
	
	// Resize to given size, and fill with empty tiles
	tiles.resize(_width, std::vector<Tile*>(_height));
	
		// Need to iterate over it like this, otherwise every tile will be the same new Tile
	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			tiles[x][y] = new Tile();
		}
		
	}
}

Feature::~Feature()
{
	// TODO: Proper deletes
}

// MUTs
void Feature::mutAll(int startX, int startY, int width, int height, std::function<void(Tile*)> act)
{
	for (int x = startX; x < startX + width; x++)
	{
		for (int y = startY; y < startY + height; y++)
		{
			if (x >= 0 && x < _width && y >= 0 && y < _height)
			{
				act(tiles[x][y]);
			}
		}
	}
}

void Feature::mutBorder(int startX, int startY, int width, int height, std::function<void(Tile*)> act)
{
	// Note, this could be quicker, but this is just the more verbose way to break it up
	
	// Top
	for (int t = startX; t < startX + width; t++)
	{
		if (t >= 0 && t < _width && startY >= 0 && startY < _height)
		{
			act(tiles[t][startY]);
		}
	}
	
	// Bottom
	for (int b = startX; b < startX + width; b++)
	{
		if (b >= 0 && b < _width && startY + height -1 >= 0 && startY + height -1 < _height)
		{
			act(tiles[b][startY + height - 1]);
		}
	}
	
	// Sides ignore corners, just so there is no double up.
	
	// Left
	for (int l = startY+1; l < startY + height-1; l++)
	{
		if (l >= 0 && l < _height && startX >= 0 && startX < _width)
		{
			act(tiles[startX][l]);
		}
	}
	
	// Right
	for (int r = startY+1; r < startY + height-1; r++)
	{
		if (r >= 0 && r < _height && startX + width -1 >= 0 && startX + width -1 < _width)
		{
			act(tiles[startX + width -1][r]);
		}
	}
}


// Simple mut's
void Feature::addAll(std::string entName)
{
	addAll(entName,0,0,_width,_height);
}

void Feature::addAll(std::string entName, int startX, int startY, int width, int height)
{
	mutAll(startX, startY, width, height, [&](Tile* tile)->void
		   {
			   tile->addEntTop(new Entity(entName));
		   });
}

void Feature::addBorder(std::string entName)
{
	addBorder(entName,0,0,_width,_height);
}

void Feature::addBorder(std::string entName, int startX, int startY, int width, int height)
{
	mutBorder(startX, startY, width, height, [&](Tile* tile)->void
		   {
			   tile->addEntTop(new Entity(entName));
		   });
}

void Feature::addEntity(int x, int y, Entity* newEnt)
{
	if (x >= 0 && x < _width && y >= 0 && y < _height)
	{
		tiles[x][y]->addEntTop(newEnt);
	}
}

void Feature::clearAll(int startX, int startY, int width, int height)
{
	mutAll(startX, startY, width, height, [&](Tile* tile)->void
		   {
			   tile->clearEntities();
		   });
}

void Feature::clearAll()
{
	clearAll(0,0,_width,_height);
}

void Feature::clearBorder(int startX, int startY, int width, int height)
{
	mutBorder(startX, startY, width, height, [&](Tile* tile)->void
		   {
			   tile->clearEntities();
		   });
}

void Feature::clearBorder()
{
	clearBorder(0,0, _width,_height);
}

// DOOR

// TODO: Add sub-cardinals (NW,NE,SW,SE)

void Feature::addDoor(std::string nonActName, std::string actName, DIRECTION dir)
{
	int doorPos = 0;

	if (dir == N || dir == S)
	{
		
		// random position along the width of the area
		doorPos = lbRNG::linear(1,_width-1);
		int x = doorPos;
		int y = 0;
		if (dir == N)
		{
			// North
			y = 0;
		} else {
			// South
			y = _height-1;
		}
		
		// Actually set the door
		if (x >= 0 && x < _width && y >= 0 && y < _height)
		{
			tiles[x][y]->removeEntSolid();
			addEntity(x,y,new Switch(nonActName, actName));
		} else {
			// Something went wrong. Just try again
			WARN("Door positioning was out of bounds. Please check alg");
			addDoor(nonActName, actName, dir);
		}
		
		
	} else if (dir == E || dir == W) {
		// random position along the height of the area
		doorPos = lbRNG::linear(1,_height-1);
		int x = 0;
		int y = doorPos;
		if (dir == W)
		{
			// West
			x = 0;
		} else {
			// East
			x = _width-1;
		}
		// Actually set the door
		if (x >= 0 && x < _width && y >= 0 && y < _height)
		{
			tiles[x][y]->removeEntSolid();
			addEntity(x,y,new Switch(nonActName, actName));
		} else {
			// Something went wrong. Just try again
			WARN("Door positioning was out of bounds. Please check alg");
			addDoor(nonActName, actName, dir);
		}
		
	} else {
		WARN("Tried to add door with an invalid direction");
		addDoor(nonActName, actName);
	}
}

void Feature::addDoor(std::string nonActName, std::string actName)
{
	// Pick a random side
	switch(lbRNG::linear(0,4))
	{
		case 0: addDoor(nonActName, actName, N); return;
		case 1: addDoor(nonActName, actName, E); return;
		case 2: addDoor(nonActName, actName, S); return;
		case 3: addDoor(nonActName, actName, W); return;
	}
}

// GENERATE

// Super simple one, just to keep things spicy
void Feature::generate()
{
	// Plain background with occasional tree. Just magic.
	addAll("grass-light");
	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			if (lbRNG::decision(0.1))
			{
				addEntity(x,y, new Entity("tree-light"));
			}
		}
		
	}
}
