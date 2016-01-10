#include <string>

#include "Config.h"

#include "ResourcePath.hpp"
#include "Manager.h"

#include "lbLog.h"

#include "Mob.h"
#include "Livestock.h"

Sheep::Sheep() : Mob("mob_sheep")
{}

Sheep::~Sheep()
{}

bool Sheep::think()
{
	
	return false;
}