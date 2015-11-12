#include <string>
#include <vector>
#include <map>

#include "lbCSV.h"
#include "lbLog.h"

#include "ResourcePath.hpp"
#include "TileManager.hpp"

#include "Tile.h"
#include "Entity.h"


Tile::Tile(std::string groundName, std::string topName)
{
	_ground = new Entity(groundName);
	_top = new Entity(topName);
	
	_special = 0;
	_regionName = "";
}

Tile::Tile(std::string groundName) : Tile(groundName, "")
{}

Tile::Tile() : Tile("","")
{}

Tile::~Tile() {}


// Setters
void Tile::setRegionName(std::string newRegionName)
{
	_regionName = newRegionName;
}

// Getters
int Tile::getSpecial()
{
	return _special;
}

bool Tile::isSolid()
{
	return _ground->isSolid() || _top->isSolid();
}

Entity* Tile::getTop()
{
	return _top;
}

Entity* Tile::getGround()
{
	return _ground;
}

