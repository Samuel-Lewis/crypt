

#include <string>

#include "Config.h"

#include "ResourcePath.hpp"
#include "TileManager.hpp"

#include "lbLog.h"

#include "Entity.h"
#include "Switch.h"

Switch::Switch(std::string entityName) : Entity(entityName)
{
	_open = false;
	_locked = false;
}

void Switch::use()
{
		
}

void Switch::setOpen(bool newState)
{
	_open = newState;
}

void Switch::setLocked(bool newState)
{
	_locked = newState;
}

bool Switch::getOpen()
{
	return _open;
}

bool Switch::getLocked()
{
	return _locked;
}