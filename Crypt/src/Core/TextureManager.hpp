//
//  TextureManager.hpp
//  Crypt
//
//  Created by Jacob Gonzalez on 6/10/2015.
//  Copyright © 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

#include <string>
#include <map>
#include <vector>

#include <SFML/Graphics.hpp>

#include "lbLog.h"

#include "Singleton.hpp"

class TextureManager : public Singleton<TextureManager>
{
public:
    TextureManager() : Singleton<TextureManager>()
    {
		INFO("Loading texture manager");
		loadTexturesFromFile("textures.json");
		loadTileTexturesFromFile("tiles.json");
    }

    void loadTexturesFromFile(std::string filename);
	void loadTileTexturesFromFile(std::string filename);
    sf::Texture *getTexture(std::string key);

    // singletons don't have deconstructors
    void free();
    
    std::map<std::string, sf::Texture *> textures;

private:
	sf::Texture* loadConTexture(std::string filename, int x, int y);

	
};

#endif /* TextureManager_hpp */
