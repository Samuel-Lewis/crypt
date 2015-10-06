//
//  TextureManager.cpp
//  Crypt
//
//  Created by Jacob Gonzalez on 6/10/2015.
//  Copyright © 2015 Jacob Gonzalez. All rights reserved.
//

#include "TextureManager.hpp"
#include "ResourcePath.hpp"
#include "GConfig.h"

sf::Texture *TextureManager::getTexture(std::string key)
{
    return textures[key];
}

void TextureManager::loadTexturesFromFile(std::string filename)
{
    // with Generics fill up the map

    GConfig texturesDef = GConfig::read(resourcePath() + "textures.json");
    if (texturesDef.good)
    {
        GArray *tiles = GArrayFromDict(texturesDef.getDict(), "tiles");

        for (size_t i = 0; i < tiles->count(); ++i)
        {
            sf::Texture *t = new sf::Texture();
            t->loadFromFile(resourcePath() + GStringFromArray(tiles, i)->value + ".png");
            textures[GStringFromArray(tiles, i)->value] = t;
        }
    }
}

void TextureManager::free()
{
    for (auto it = textures.begin(); it != textures.end(); ++it)
    {
        delete it->second;
    }
    textures.clear();
}
