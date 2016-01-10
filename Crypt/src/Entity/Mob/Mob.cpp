#include <string>

#include "Config.h"

#include "ResourcePath.hpp"
#include "Manager.h"

#include "lbLog.h"

#include "Tile.h"
#include "Entity.h"
#include "Mob.h"

Mob::Mob(std::string mobName) : Entity(mobName)
{
	_canUse = true;
}

Mob::~Mob()
{}

void Mob::setParentTile(Tile* newParent)
{
	// Do NOT want to delete what ever the old parent is. Tiles are very important.
	
	// So just override the new parent
	_parentTile = newParent;
}