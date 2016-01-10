
#ifndef TILE_H
#define TILE_H

#include <string>
#include <vector>

#include "Config.h"

#include "Entity.h"
#include "Mob.h"

class Tile
{
public:
	Tile();
	Tile(std::string);
	Tile(std::string, std::string);
	virtual ~Tile();
	
	bool use();
	bool canUse();
	
	// Mob
	bool hasMob();
	void setMob(Mob*);
	
	// Setters
	void setRegionName(std::string);
	
	// _entities manipulation
	void addEntTop(Entity*);
	void addEntBottom(Entity*);
	void removeEntTop();
	void removeEntBottom();
	void removeEntSolid();
	
	void clearEntities();
	
	// Getters
	std::vector<Entity*> getEntities();
	
	bool isSolid();
	std::string getRegionName();
	
private:
	
	std::vector<Entity*> _entities;
	Mob* _mob; // TODO: Change to Mob*

	std::string _regionName;
	
};

typedef std::vector< std::vector<Tile*> > TILEGRID;

#endif // TILE_H
