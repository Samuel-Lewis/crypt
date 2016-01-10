
#ifndef TILE_H
#define TILE_H

#include <string>
#include <vector>
#include <map>

#include "Config.h"

class Region;

#include "Entity.h"
#include "Mob.h"

class Tile;
typedef std::vector< std::vector<Tile*> > TILEGRID;

class Tile
{
public:
	Tile();
	Tile(std::string);
	Tile(std::string, std::string);
	virtual ~Tile();
	
	bool tick();
	
	bool use();
	bool canUse();
	
	// Mob
	bool hasMob();
	void setMob(Mob*);
	void leaveMob();
	
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
	Mob* getMob();
	
	bool isSolid();
	std::string getRegionName();
	
	std::map<DIRECTION, Tile*> neighbours;
	
	// Pos
	void setPos(int,int);
	int x();
	int y();
	TILEGRID* getParentMap();
	void setParentMap(TILEGRID*);
	
private:
	
	std::vector<Entity*> _entities;
	Mob* _mob;

	std::string _regionName;
	
	int _x;
	int _y;
	
	TILEGRID* _parentMap;
	
};



#endif // TILE_H
