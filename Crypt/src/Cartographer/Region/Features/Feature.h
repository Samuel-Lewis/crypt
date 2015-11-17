#ifndef FEATURE_H
#define FEATURE_H

#include <string>
#include <vector>

#include "Config.h"

#include "lbLog.h"

#include "Tile.h"
#include "Entity.h"

class Feature
{

public:
	Feature(int, int);
	virtual ~Feature();
	

	void setRegionName(std::string);
	
	// Super generic one, mostly for particular versions in children
	virtual void generate();

	virtual void setBorderGround(std::string);
	virtual void setBorderProp(std::string);
	
	virtual void setAllGround(std::string);
	virtual void setAllProp(std::string);

	virtual void addDoor(std::string, std::string);
	virtual void addDoor(std::string, std::string, DIRECTION);

	TILEGRID tiles;

protected:
	void setGround(int, int, Entity*);
	void setProp(int, int, Entity*);
	
	int _height;
	int _width;

};


#endif // FEATURE_H
