
#ifndef ENTITY_SWITCH_H
#define ENTITY_SWITCH_H

#include <string>

#include "Config.h"

#include "Entity.h"

class Switch: public Entity {
public:
	Switch(std::string);
	
	virtual void use();
	
	void setOpen(bool);
	void setLocked(bool);
	
	bool getOpen();
	bool getLocked();
	
private:
	bool _open;
	bool _locked;
	
};

#endif // ENTITY_SWITCH_H