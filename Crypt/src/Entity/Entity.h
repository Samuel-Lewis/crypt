
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
	
	virtual bool use();
	virtual bool canUse();
	
	
	// Getters
	bool isSolid();
	std::string getDisplayName();
	std::string getEntityName();
	std::string getTextureName();
	std::string getTextureSuffix();
	contType getContType();
	
	// Setters
	void setTextureName(std::string);
	void setTextureSuffix(std::string);
	


protected:
		
	contType _connected;
	
	bool _solid;
	// Used to show tile type to user
	std::string _displayName;
	
	// Used to call tile texture, or actually differentiate between tile types
	std::string _entityName;
	
	std::string _textureName;
	std::string _textureSuffix;
	
};

#endif // ENTITY_H