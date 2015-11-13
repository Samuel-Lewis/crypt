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
	
	virtual void addBorder(std::string, std::string);
	
//	virtual void addDoor();
//	virtual void addDoor(DIRECTION);
//	
//	virtual void addFloor(std::string);
	
	
	TILEGRID tiles;

protected:
	void swap(int, int, std::string, std::string);
	
private:
	int _height;
	int _width;
					 
	
};


#endif // FEATURE_H
