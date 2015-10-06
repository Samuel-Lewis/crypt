//
//  TextureManager.cpp
//  Crypt
//
//  Created by Jacob Gonzalez on 6/10/2015.
//  Copyright © 2015 Jacob Gonzalez. All rights reserved.
//

#include "TextureManager.hpp"
#include "ResourcePath.hpp"

sf::Texture *TextureManager::getTexture(std::string key)
{
    return textures[key];
}

void TextureManager::loadTexturesFromFile(std::string filename)
{
    // with Generics fill up the map
    // but for now

    sf::Texture *t1 = new sf::Texture();
    t1->loadFromFile(resourcePath() + "tree.png");
    textures["tree"] = t1;

    sf::Texture *t2 = new sf::Texture();
    t2->loadFromFile(resourcePath() + "stone.png");
    textures["wall"] = t2;
}

void TextureManager::free()
{
    for (auto it = textures.begin(); it != textures.end(); ++it)
    {
        delete it->second;
    }
    textures.clear();
}
