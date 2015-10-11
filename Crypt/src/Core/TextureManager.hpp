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

class TextureManager : public Singleton<TextureManager>
{
public:
    TextureManager() : Singleton<TextureManager>()
    {
        loadTexturesFromFile("textures.json");
    }

    void loadTexturesFromFile(std::string filename);
    sf::Texture *getTexture(std::string key);

    // singletons don't have descrustots
    void free();
    
    std::map<std::string, sf::Texture *> textures;

};

#endif /* TextureManager_hpp */
