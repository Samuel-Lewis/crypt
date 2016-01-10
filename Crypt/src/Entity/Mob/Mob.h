
#ifndef ENTITY_MOB_H
#define ENTITY_MOB_H

#include <string>

#include "Config.h"

class Tile;
#include "Entity.h"

class Mob: public Entity {
public:

	Mob(std::string);
	virtual ~Mob();
	
	virtual bool think() = 0;
	
	void setParentTile(Tile*);
	
private:
	
	Tile* _parentTile;
	
	//TODO: mob name
	// std::string _name;
	
	//TODO: Level of aggression
	
	//TODO: Path to move
	
	//TODO: Target entity
	// Entity* _target;

	
};

#endif // ENTITY_MOB_H