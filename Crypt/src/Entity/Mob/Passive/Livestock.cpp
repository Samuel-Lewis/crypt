#include <string>

#include "Config.h"

#include "ResourcePath.hpp"
#include "Manager.h"

#include "lbLog.h"

#include "Mob.h"
#include "Livestock.h"

Sheep::Sheep(Tile* parTile) : Mob("mob-sheep-light", parTile)
{
	_path->setRoam();
}

Sheep::~Sheep()
{}

bool Sheep::think()
{
	move(_path->step());
	
	return true;
}