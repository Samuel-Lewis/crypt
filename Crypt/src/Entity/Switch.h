
#ifndef ENTITY_SWITCH_H
#define ENTITY_SWITCH_H

#include <string>

#include "Config.h"

#include "Entity.h"

class Switch: public Entity {
public:
	Switch(std::string, std::string);
	
	virtual bool use();
	virtual bool canUse();
	
	void setLocked(bool);
	bool getLocked();
	
private:
	bool _active;
	bool _locked;
	
	Entity* _currentEnt;
	
	Entity* _activeEnt;
	Entity* _nonActiveEnt;
	
};

#endif // ENTITY_SWITCH_H