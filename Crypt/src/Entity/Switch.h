
#ifndef ENTITY_SWITCH_H
#define ENTITY_SWITCH_H

#include <string>

#include "Config.h"

#include "Entity.h"

class Switch: public Entity {
public:
	Switch(std::string, std::string);
	
	virtual bool use();
	
	void setLocked(bool);
	bool getLocked();
	
private:
	bool _active;
	bool _locked;
	
	//  Current data will be loaded from here
	Entity* _currentEnt;
	
	// Binary states
	Entity* _activeEnt;
	Entity* _nonActiveEnt;
	
};

#endif // ENTITY_SWITCH_H