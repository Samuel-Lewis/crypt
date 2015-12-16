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
	
	virtual void generate();

	void addAll(std::string);
	void addAll(std::string, int, int, int, int);
	void addBorder(std::string);
	void addBorder(std::string, int, int, int, int);
	void addEntity(int, int, Entity*);
	
	void clearAll(int, int, int, int);
	void clearAll();
	void clearBorder(int,int,int,int);
	void clearBorder();
	
	virtual void addDoor(std::string, std::string);
	virtual void addDoor(std::string, std::string, DIRECTION);

	TILEGRID tiles;

protected:
	void mutAll(int, int, int, int, std::function<void(Tile*)>);
	void mutBorder(int, int, int, int, std::function<void(Tile*)>);
	
	int _height;
	int _width;

};


#endif // FEATURE_H
