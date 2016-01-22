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
	
	INFO("Added " << mobName);
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
	
	if ((dir == N && _parentTile->y() <= 0) ||
		(dir == W && _parentTile->x() <= 0) ||
		(dir == S && _parentTile->y() >= REGIONSIZE-1) ||
		(dir == E && _parentTile->x() >= REGIONSIZE-1))
	{
//		INFO("Tried to move out of bounds (" << _parentTile->x() << "," << _parentTile->y() << ").");
		return false;
	}
	
	// No move
	if (dir == DIRECTION::NONE)
	{
		INFO("NONE");
		return false;
	}
	
	if (_parentTile->neighbours[dir] != nullptr)
	{
		Tile* dest = _parentTile->neighbours[dir];
		
		if (dest->isSolid())
		{
			INFO("Tried to move into a solid tile");
			return false;
		}
		
		if (dest->hasMob())
		{
			INFO("Tried to move into a tile with a mob");
			return false;
		}
		
		// Move sucessful
		_parentTile->leaveMob();
		_parentTile->neighbours[dir]->setMob(this);

		return true;
		
		
	} else {
		INFO("Mob " << getEntityName() << " tried to move into a nullptr tile");
		return false;
	}
	
	WARN("No conditions met in move().");
	return false;
}

bool Mob::_thinkCoolDown()
{
	_coolDown--;
	
	if (_coolDown < 0)
	{
		_coolDown = TICKSPEED / _speed;
		return true;
	} else {
		return false;
	}
	
}