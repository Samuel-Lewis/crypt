
#ifndef ENTITY_MOB_LIVESTOCK_H
#define ENTITY_MOB_LIVESTOCK_H

#include <string>

#include "Config.h"

#include "Mob.h"

class Sheep: public Mob {
public:
	
	Sheep(Tile*);
	virtual ~Sheep();
	
	bool think();
	
private:
	
};

#endif // ENTITY_MOB_LIVESTOCK_H