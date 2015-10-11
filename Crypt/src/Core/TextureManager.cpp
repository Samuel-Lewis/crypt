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
#include "lbLog.h"

sf::Texture *TextureManager::getTexture(std::string key)
{
    if (textures.find(key) != textures.end())
    {
        return textures[key];
    }
    ERROR("missing texture " << key);
    return nullptr;
}

void TextureManager::loadTexturesFromFile(std::string filename)
{
    // with Generics fill up the map with textures

    GConfig texturesDef = GConfig::read(resourcePath() + filename);

    if (texturesDef.good)
    {
        for (auto &&pair : texturesDef.getDict()->value)
        {
            std::string name = pair.first;
            GDict *tileInfo = GDictFromDict(texturesDef.getDict(), name);

            std::string tileset = GStringFromDict(tileInfo, "tileset")->value;
            GArray *array = GArrayFromDict(tileInfo, "rect");

            sf::IntRect rect(GNumberFromArray(array, 0)->asInt(),
                             GNumberFromArray(array, 1)->asInt(),
                             GNumberFromArray(array, 2)->asInt(),
                             GNumberFromArray(array, 3)->asInt());

            sf::Texture *t = new sf::Texture();
            if (!t->loadFromFile(resourcePath() + tileset, rect))
            {
                FATAL("missing texture " << tileset << " for asset" << name);
            }
            textures[name] = t;
        }
    }
    else
    {
        ERROR("texture manager failed to load");
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
