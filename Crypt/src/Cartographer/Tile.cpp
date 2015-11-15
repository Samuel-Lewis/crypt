#include <string>
#include <vector>
#include <map>

#include "Config.h"

#include "lbCSV.h"
#include "lbLog.h"
#include "ResourcePath.hpp"

#include "TileManager.hpp"

#include "Tile.h"
#include "Entity.h"


Tile::Tile(std::string groundName, std::string propName)
{
	_ground = new Entity(groundName);
	_prop = new Entity(propName);
	
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
	return _ground->isSolid() || _prop->isSolid();
}

Entity* Tile::getProp()
{
	return _prop;
}

Entity* Tile::getGround()
{
	return _ground;
}

