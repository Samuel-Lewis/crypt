

#include <string>

#include "ResourcePath.hpp"
#include "TileManager.hpp"

#include "lbLog.h"

#include "Entity.h"

// Empty entity, treat as "air"
Entity::Entity()
{
	_displayName = "";
	_solid = false;
}


Entity::Entity(std::string entityName)
{
	// Load entity data from external file
	TileManager *tm = &TileManager::getInstance();

	// Empty entity, move along now.
	if (entityName == "")
	{
		_displayName = "";
		_tileName = "";
		_solid = false;
		return;
	}
	
	// Actual entity
	if (tm->tileDict->get(entityName) != nullptr)
	{
		_displayName = tm->getString(entityName, "display");
		_tileName = entityName;
		_solid = (bool)tm->getInt(entityName, "solid");
		_connected = NONE;
		
		std::string givenConnected = tm->getString(entityName, "connected");
		
		if (givenConnected == "self")
		{
			_connected = SELF;
		} else if (givenConnected == "solid")
		{
			_connected = SOLID;
		} else {
			_connected = NONE;
		}
		
	} else {
		// Failed to find entity.
		WARN("Could not find tile '"<< entityName <<"'. Default to 'air'.");
		_displayName = "";
		_tileName = "";
		_solid = false;
		_connected = NONE;
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

// CONNECTED TILES MAGIC HERE PLZ

std::string Entity::getTileName()
{
	if (_connected == SELF)
	{
		
	} else if (_connected == SOLID) {
		
	} else {
		return _tileName;
	}
	
	return _tileName;
}