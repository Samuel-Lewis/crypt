#include <string>

#include "Config.h"

#include "ResourcePath.hpp"
#include "Manager.h"

#include "lbLog.h"
#include "lbRNG.h"

#include "Mob.h"
#include "Livestock.h"

Sheep::Sheep(Tile* parTile) : Mob("mob-sheep-light", parTile)
{

	_speed = 1;
	_coolDown = TICKSPEED*10 / _speed;
}

Sheep::~Sheep()
{}

bool Sheep::think()
{
	
	if (_thinkCoolDown())
	{
		move((DIRECTION)lbRNG::linear(1,5));
	}

	return true;
}