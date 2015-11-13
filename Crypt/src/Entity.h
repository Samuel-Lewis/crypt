
#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include "Config.h"

class Entity {
	
public:
	Entity();
	Entity(std::string);
	virtual ~Entity();
	
	enum contType {
		NONE,
		SELF,
		SOLID,
	};
	
	// Getters
	bool isSolid();
	std::string getDisplayName();
	std::string getTileName();
	std::string getTextureName();
	contType getContType();
	
	// Setters
	void setTextureName(std::string);
	


private:
		
	contType _connected;
	
	bool _solid;
	// Used to show tile type to user
	std::string _displayName;
	
	// Used to call tile texture, or actually differentiate between tile types
	std::string _tileName;
	
	std::string _textureName;
	
};

#endif // ENTITY_H