

#include <string>

#include "ResourcePath.hpp"
#include "TileManager.hpp"

#include "lbLog.h"

#include "Entity.h"

Entity::Entity()
{
	_displayName = "";
	_solid = false;
}

Entity::Entity(std::string entityName)
{
	TileManager *tm = &TileManager::getInstance();
	
	if (tm->tileDict->get(entityName) != nullptr)
	{
		_displayName = tm->getString(entityName, "display");
		_tileName = entityName;
		_solid = (bool)tm->getInt(entityName, "solid");
	} else {
		WARN("Could not find tile '"<< entityName <<"'");
		_displayName = "";
		_tileName = "";
		_solid = false;
	}
}

Entity::~Entity()
{
	
}

// Getters
bool Entity::isSolid()
{
	return _solid;
}

std::string Entity::getDisplayName()
{
	return _displayName;
}

std::string Entity::getTileName()
{
	return _tileName;
}