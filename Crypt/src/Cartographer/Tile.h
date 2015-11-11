
#ifndef TILE_H
#define TILE_H

#include <string>
#include <vector>

#include "Entity.h"

class Tile
{
public:
	Tile();
	Tile(std::string);
	Tile(std::string, std::string);
	virtual ~Tile();
	
	// Setters
	void setRegionName(std::string);
	void setSpecial(int);
	
	// Getters
	Entity* getGround();
	Entity* getTop();
	
	int getSpecial();
	bool isSolid();
	std::string getRegionName();
	
	
private:
	
	Entity* _ground;
	Entity* _top;

	int _special;
	std::string _regionName;
	
};

typedef std::vector< std::vector<Tile*> > TILEGRID;

#endif // TILE_H
