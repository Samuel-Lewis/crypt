
#ifndef ENTITY_CROP_H
#define ENTITY_CROP_H

#include <string>

#include "Config.h"

#include "Entity.h"

class Crop: public Entity {
public:
	Crop(std::string);
	~Crop();
	
	virtual bool use();
	
	void grow();
	
private:
	int _stage;
};

#endif // ENTITY_CROP_H