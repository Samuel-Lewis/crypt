#include <string>

#include "Config.h"

#include "ResourcePath.hpp"
#include "TileManager.hpp"

#include "lbLog.h"

#include "Entity.h"
#include "Switch.h"

Switch::Switch(std::string nonActName, std::string actName) : Entity(nonActName)
{
	_active = false;
	_locked = false;

	// Entities the switch will toggle between. Only binary states.
	_nonActiveEnt = new Entity(nonActName);
	_activeEnt = new Entity(actName);
	
	_currentEnt = _nonActiveEnt;
}

bool Switch::use()
{
	if (!_locked)
	{
		// Switch entity to other one
		if (_active)
		{
			_currentEnt = _nonActiveEnt;
			_active = false;
		} else {
			_currentEnt = _activeEnt;
			_active = true;
		}
	
		// Populate *this* entity with data from the new state
		_displayName = _currentEnt->getDisplayName();
		_entityName = _currentEnt->getEntityName();
		_textureName = _currentEnt->getTextureName();
		_solid = _currentEnt->isSolid();
		_connected = _currentEnt->getContType();
		
		INFO("Switch '" << _entityName << "' was switched");
		
		return true;
		
	} else {
		// Is locked, nothing happend (yet)
		return false;
	}
}


bool Switch::canUse()
{
	return true;
}

void Switch::setLocked(bool newState)
{
	_locked = newState;
}

bool Switch::getLocked()
{
	return _locked;
}