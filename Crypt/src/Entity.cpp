

#include <string>

#include "Config.h"

#include "ResourcePath.hpp"
#include "TileManager.hpp"

#include "lbLog.h"

#include "Entity.h"

// Empty entity, treat as "air"
Entity::Entity()
{
	_displayName = "";
	_tileName = "";
	_textureName = "";
	_solid = false;
	_connected = NONE;
	
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
		_textureName = "";
		_solid = false;
		_connected = NONE;
		
		return;
	}
	
	// Actual entity
	if (tm->tileDict->get(entityName) != nullptr)
	{
		_displayName = tm->getString(entityName, "display");
		_tileName = entityName;
		_textureName = _tileName;
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
		_textureName = "";
		_solid = false;
		_connected = NONE;
		
	}
}

Entity::~Entity()
{
	
}

// Setters
void Entity::setTextureName(std::string newTName)
{
	_textureName = newTName;
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

std::string Entity::getTextureName()
{
	return _textureName;
}

Entity::contType Entity::getContType()
{
	return _connected;
}