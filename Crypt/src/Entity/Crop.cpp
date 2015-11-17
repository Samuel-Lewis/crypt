#include <string>

#include "Config.h"

#include "ResourcePath.hpp"
#include "TextManager.hpp"

#include "lbLog.h"

#include "Entity.h"
#include "Crop.h"

Crop::Crop(std::string entityName) : Entity(entityName)
{
	_canUse = true;
	
	_stage = 0;
	
}

Crop::~Crop() {}

bool Crop::use()
{
	std::string msg = "";

	// Get level of growth and just a debug message for now
	switch(_stage)
	{
		case 0: msg = "It's a recently planted " + _displayName; break;
		case 1: msg = "It's a ready to be harvested " + _displayName; break;
		
		default:
			msg = "It's a " + _displayName + "!"; break;
	}
	
	printScreen(msg);
	
	return false;
}

void Crop::grow()
{
	_stage++;
}