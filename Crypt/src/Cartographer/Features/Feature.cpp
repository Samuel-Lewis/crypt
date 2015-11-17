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

// Utils

// Set the new entity of the tile ground
void Feature::setGround(int x, int y, Entity* newGround)
{
	// Bounds check
	if (x >= 0 && x < _width && y >=0 && y <_height)
	{
		tiles[x][y]->setGround(newGround);
	} else {
		WARN("Tried to swap an out of bounds tile ["<<x<<","<<y<<"]");
	}
}

// Set the new entity of the tile prop
void Feature::setProp(int x, int y, Entity* newProp)
{
	// Bounds check
	if (x >= 0 && x < _width && y >=0 && y <_height)
	{
		tiles[x][y]->setProp(newProp);
	} else {
		WARN("Tried to swap an out of bounds tile ["<<x<<","<<y<<"]");
	}
}


// ALLS

void Feature::setAllGround(std::string groundName)
{
	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			setGround(x,y,new Entity(groundName));
		}
	}
}

void Feature::setAllProp(std::string propName)
{
	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			setProp(x,y,new Entity(propName));
		}
	}
}

// BORDERS

void Feature::setBorderGround(std::string borderName)
{
	// Top and bottom
	for (int i = 0; i < _width; i++)
	{
		setGround(i,0, new Entity(borderName)); // Top
		setGround(i,_height-1, new Entity(borderName)); // Bottom
	}
	
	// Sides
	for (int i = 0; i < _height; i++)
	{
		setGround(0,i, new Entity(borderName)); // Left
		setGround(_width-1, i, new Entity(borderName)); // Right
	}
	
	INFO("Added border (ground) using '" << borderName << "'");
}

void Feature::setBorderProp(std::string borderName)
{
	// Top and bottom
	for (int i = 0; i < _width; i++)
	{
		setProp(i,0, new Entity(borderName)); // Top
		setProp(i,_height-1, new Entity(borderName)); // Bottom
	}
	
	// Sides
	for (int i = 0; i < _height; i++)
	{
		setProp(0,i, new Entity(borderName)); // Left
		setProp(_width-1, i, new Entity(borderName)); // Right
	}
	
	INFO("Added border (prop) using '" << borderName << "'");
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
		if (dir == N)
		{
			// North
			setProp(doorPos,0, new Switch(nonActName, actName));
		} else {
			// South
			setProp(doorPos,_height-1, new Switch(nonActName, actName));
		}
	} else if (dir == E || dir == W) {
		// random position along the height of the area
		doorPos = lbRNG::linear(1,_height-1);
		if (dir == W)
		{
			// West
			setProp(0, doorPos, new Switch(nonActName, actName));
		} else {
			// East
			setProp(_width-1, doorPos, new Switch(nonActName, actName));
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
	setAllGround("grass-light");
	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			if (lbRNG::linear(0.0,1.0) < 0.1)
			{
				setProp(x,y, new Entity("tree-light"));
			}
		}
		
	}
}
