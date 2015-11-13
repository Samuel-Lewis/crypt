#ifndef FEATURE_H
#define FEATURE_H

#include <string>
#include <vector>

#include "Config.h"

#include "lbLog.h"

#include "Tile.h"

class Feature
{

public:
	Feature(int, int);
	virtual ~Feature();
	

	void setRegionName(std::string);
	
	// Super generic one, mostly for particular versions in children
	virtual void generate();

	virtual void addBorder(std::string, std::string);
	
//	virtual void addDoor();
//	virtual void addDoor(DIRECTION);
//	
	virtual void addFloor(std::string);
	
	
	TILEGRID tiles;

protected:
	void swapGround(int, int, std::string);
	void swapTop(int, int, std::string);
	
private:
	int _height;
	int _width;
					 
	
};


#endif // FEATURE_H
