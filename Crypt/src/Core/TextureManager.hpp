//
//  TextureManager.hpp
//  Crypt
//
//  Created by Jacob Gonzalez on 6/10/2015.
//  Copyright © 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "Singleton.hpp"

#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <vector>

class TextureManager : public Singleton<TextureManager>
{
public:
    TextureManager() : Singleton<TextureManager>()
    {
        loadTexturesFromFile("textures.json");
		loadTileTexturesFromFile("tiles.json");
    }

    void loadTexturesFromFile(std::string filename);
	void loadTileTexturesFromFile(std::string filename);
    sf::Texture *getTexture(std::string key);

    // singletons don't have deconstructors
    void free();
    
    std::map<std::string, sf::Texture *> textures;
    
};

#endif /* TextureManager_hpp */
