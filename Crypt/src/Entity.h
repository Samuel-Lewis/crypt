
#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity {
	
public:
	Entity();
	Entity(std::string);
	virtual ~Entity();
	
	// Getters
	bool isSolid();
	std::string getDisplayName();
	std::string getTileName();
	
	
private:
	
	bool _solid;
	std::string _displayName;
	std::string _tileName;
	
};

#endif // ENTITY_H