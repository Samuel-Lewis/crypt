#include <string>

#include "Config.h"

#include "ResourcePath.hpp"
#include "TileManager.hpp"

#include "lbLog.h"

#include "Entity.h"

// New entity creation
Entity::Entity(std::string entityName)
{
	// Tap into the tile manager
	TileManager *tm = &TileManager::getInstance();

	// Empty entity, make it air and move on.
	if (entityName == "" || tm->tileDict->get(entityName) == nullptr)
	{
		entityName = "air";
		WARN("Could not find texture '"<< entityName <<"'. Default to 'air'.");
	}
	
	// Populate data
	_displayName = tm->getString(entityName, "display");
	_entityName = entityName;
	_textureName = _entityName;
	_textureSuffix = ""; // Will be determined later
	_solid = (bool)tm->getInt(entityName, "solid");
	_connected = NONE;
	
	// Connected is an optional parameter.
	std::string givenConnected = tm->getString(entityName, "connected");
	
	// converts to enum
	if (givenConnected == "self")
	{
		_connected = SELF;
	} else if (givenConnected == "solid") {
		_connected = SOLID;
	} else {
		_connected = NONE;
	}
}

// Empty entity, treat as "air"
Entity::Entity() : Entity("air") {}

Entity::~Entity() { }

// Entity use
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
	// To be used in conjunction with _textureName
	return _textureSuffix;
}

Entity::contType Entity::getContType()
{
	return _connected;
}