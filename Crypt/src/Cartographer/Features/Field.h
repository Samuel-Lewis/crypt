#ifndef FEATURE_FIELD_H
#define FEATURE_FIELD_H

#include <string>
#include <vector>

#include "Config.h"

#include "lbLog.h"

#include "Feature.h"
#include "Tile.h"

class Field: public Feature
{

public:
	Field(int, int);
	virtual ~Field();

	void generate();
	
};


#endif // FEATURE_FIELD_H
