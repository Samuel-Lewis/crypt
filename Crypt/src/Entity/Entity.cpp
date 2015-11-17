

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
	_entityName = "";
	_textureName = "";
	_textureSuffix = "";
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
		_entityName = "";
		_textureName = "";
		_textureSuffix = "";
		_solid = false;
		_connected = NONE;
		
		return;
	}
	
	// Actual entity
	if (tm->tileDict->get(entityName) != nullptr)
	{
		_displayName = tm->getString(entityName, "display");
		_entityName = entityName;
		_textureName = _entityName;
		_textureSuffix = ""; // Will be determined later
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
		WARN("Could not find texture '"<< entityName <<"'. Default to 'air'.");
		_displayName = "";
		_entityName = "";
		_textureName = "";
		_textureSuffix = ""; // Will be determined later
		_solid = false;
		_connected = NONE;
		
	}
}

Entity::~Entity() { }


bool Entity::use()
{
	// "Nothing happens"
	return false;
}

bool Entity::canUse()
{
	return false;
}

// Setters
void Entity::setTextureName(std::string newTName)
{
	_textureName = newTName;
}

void Entity::setTextureSuffix(std::string newSuffix)
{
	_textureSuffix = newSuffix;
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

std::string Entity::getEntityName()
{
	return _entityName;
}

std::string Entity::getTextureName()
{
	return _textureName;
}

std::string Entity::getTextureSuffix()
{
	return _textureSuffix;
}

Entity::contType Entity::getContType()
{
	return _connected;
}