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


Tile::Tile(std::string ent1, std::string ent2)
{
	_entities.push_back(new Entity(ent1));
	_entities.push_back(new Entity(ent2));
	_mob = nullptr;
	
	_regionName = "";
}

Tile::Tile(std::string ent1) : Tile(ent1,"")
{}

Tile::Tile() : Tile("","")
{}

Tile::~Tile() {}

// Use. Top entity takes priortiy
bool Tile::use()
{
	if (hasMob())
	{
		//use on mob
	} else {
		// Search from top to bottom
		for (int i = (int)_entities.size()-1; i >= 0; i--)
		{
			if (_entities[i]->canUse())
			{
				return _entities[i]->use();
			}
		}
	}
	
	return false;
}

bool Tile::canUse()
{
	if (hasMob())
	{
		return true;
	} else {
		// Search top to bottom
		for (int i = (int)_entities.size()-1; i >= 0; i--)
		{
			if (_entities[i]->canUse())
			{
				return true;
			}
		}
	}
	
	return false;
}

bool Tile::hasMob()
{
	return _mob != nullptr;
}

// Setters
void Tile::setRegionName(std::string newRegionName)
{
	_regionName = newRegionName;
}

// _entities Manipulations
void Tile::addEntTop(Entity* newEnt)
{
	if (newEnt->getEntityName() != "" || newEnt->getEntityName() != "air")
	{
		_entities.push_back(newEnt);
	}
}

void Tile::addEntBottom(Entity* newEnt)
{
	if (newEnt->getEntityName() != "" || newEnt->getEntityName() != "air")
	{
		// Insert to front of vector
		_entities.insert(_entities.begin(), newEnt);
	}
}

void Tile::removeEntTop()
{
	// delete _entities.back();
	_entities.pop_back();
}

void Tile::removeEntBottom()
{
	// Remove first ent
	// delete _entities.begin() ??
	_entities.erase(_entities.begin());
}

void Tile::removeEntSolid()
{
	for (int i = 0; i < (int)_entities.size(); i++)
	{
		if (_entities[i]->isSolid())
		{
			_entities.erase(_entities.begin() + i);
		}
	}
}

void Tile::clearEntities()
{
	_entities.clear();
}

// Getters
bool Tile::isSolid()
{
	// Don't include hasMob for this. As mobs are temp
	for (int i = (int)_entities.size()-1; i >= 0; i--)
	{
		if (_entities[i]->isSolid())
		{
			return true;
		}
	}
	
	return false;
}

std::vector<Entity*> Tile::getEntities()
{
	return _entities;
}
