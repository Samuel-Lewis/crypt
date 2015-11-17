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
	_height = height;
	_width = width;
	
	// Resize to given size, and fill with empty tiles
	tiles.resize(_width, std::vector<Tile*>(_height));
	
	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			tiles[x][y] = new Tile("air");
		}
		
	}
}

Feature::~Feature()
{
	// Yep, more deletions
}

// Swap tiles around, so we can delete the old one
void Feature::setGround(int x, int y, Entity* newGround)
{
	if (x >= 0 && x < _width && y >=0 && y <_height)
	{
//		delete tiles[x][y];
		tiles[x][y]->setGround(newGround);
	} else {
		WARN("Tried to swap an out of bounds tile ["<<x<<","<<y<<"]");
	}
}

// Swap tiles around, so we can delete the old one
void Feature::setProp(int x, int y, Entity* newProp)
{
	if (x >= 0 && x < _width && y >=0 && y <_height)
	{
		//		delete tiles[x][y];
		tiles[x][y]->setProp(newProp);
	} else {
		WARN("Tried to swap an out of bounds tile ["<<x<<","<<y<<"]");
	}
}

void Feature::setBorderGround(std::string wallTile)
{
	// Prop and bottom
	for (int i = 0; i < _width; i++)
	{
		setGround(i,0, new Entity(wallTile));
		setGround(i,_height-1, new Entity(wallTile));
	}
	
	// Sides
	for (int i = 0; i < _height; i++)
	{
		setGround(0,i, new Entity(wallTile));
		setGround(_width-1, i, new Entity(wallTile));
	}
}

void Feature::setBorderProp(std::string wallTile)
{
	// Prop and bottom
	for (int i = 0; i < _width; i++)
	{
		setProp(i,0, new Entity(wallTile));
		setProp(i,_height-1, new Entity(wallTile));
	}
	
	// Sides
	for (int i = 0; i < _height; i++)
	{
		setProp(0,i, new Entity(wallTile));
		setProp(_width-1, i, new Entity(wallTile));
	}
}

void Feature::setAllGround(std::string floorTile)
{
	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			setGround(x,y,new Entity(floorTile));
		}
	}
}

void Feature::setAllProp(std::string floorTile)
{
	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			setProp(x,y,new Entity(floorTile));
		}
	}
}

void Feature::addDoor(std::string nonActName, std::string actName, DIRECTION dir)
{
	int doorPos = 0;
	if (dir == N || dir == S)
	{
		doorPos = lbRNG::linear(1,_width-1);
		if (dir == N)
		{
			setProp(doorPos,0, new Switch(nonActName, actName));
		} else {
			setProp(doorPos,_height-1, new Switch(nonActName, actName));
		}
	} else if (dir == E || dir == W) {
		doorPos = lbRNG::linear(1,_height-1);
		if (dir == W)
		{
			setProp(0, doorPos, new Switch(nonActName, actName));
		} else {
			setProp(_width-1, doorPos, new Switch(nonActName, actName));
		}
	} else {
		WARN("Tried to add door with an invalid direction");
		addDoor(nonActName, actName);
	}
}

void Feature::addDoor(std::string nonActName, std::string actName)
{
	switch(lbRNG::linear(0,4))
	{
		case 0: addDoor(nonActName, actName, N); return;
		case 1: addDoor(nonActName, actName, E); return;
		case 2: addDoor(nonActName, actName, S); return;
		case 3: addDoor(nonActName, actName, W); return;
	}
}


// Super simple one, just to keep things spicy
void Feature::generate()
{
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