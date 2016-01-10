#include <string>

#include "Config.h"

#include "ResourcePath.hpp"
#include "Manager.h"

#include "lbLog.h"

#include "Tile.h"
#include "Entity.h"
#include "Mob.h"

Mob::Mob(std::string mobName, Tile* parTile) : Entity(mobName)
{
	_canUse = true;
	
	_parentTile = parTile;
	_path = new Path(_parentTile);
}

Mob::~Mob()
{}

void Mob::setParentTile(Tile* newParent)
{
	// Do NOT want to delete what ever the old parent is. Tiles are very important.
	
	// So just override the new parent
	_parentTile = newParent;
}

bool Mob::move(DIRECTION dir)
{
	if (_parentTile->neighbours[dir] != nullptr)
	{
		Tile* dest = _parentTile->neighbours[dir];
		
		if (dest->isSolid())
		{
			INFO("Tried to move into a solid Tile");
			return false;
		}
		
		if (dest->hasMob())
		{
			//TODO: Add auto 'use' or something maybe
			INFO("Tried to move into a Tile with a mob");
			return false;
		}
		
		
		// Successfull move
		dest->setMob(this);
		_parentTile = dest;
		
		_path->setCurrentTile(_parentTile);
		
		return true;
	}
	
	return false;
}