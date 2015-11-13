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
	// Hacky work around for empty entities
	if (key == "")
	{
		return nullptr;
	}
	
	if (textures.find(key) != textures.end())
    {
        return textures[key];
    }
    
    ERROR("Could not find texture '" << key << "'");
	
    return nullptr;
}

void TextureManager::loadTileTexturesFromFile(std::string filename)
{
	GConfig texturesDef = GConfig::read(resourcePath() + filename);
	
	if (texturesDef.good)
	{
		INFO("Loading tiles...")
		for (auto &&pair : texturesDef.getDict()->value)
		{
			std::string name = pair.first;
			
			
            GDict *tile = pair.second->as<GDict>();
            std::string connected = GStringFromDict(tile, "connected")->value;
			
			if (connected == "self" || connected == "solid")
			{
				INFO("Loading '" << name << "' as connected texture...");
				textures[name + "--nw"] = loadConTexture(name, 0,0);
				textures[name + "--nn"] = loadConTexture(name, 1,0);
				textures[name + "--ne"] = loadConTexture(name, 2,0);
				textures[name + "--n"] = loadConTexture(name, 3,0);
				textures[name + ""] = loadConTexture(name, 5,0);
				textures[name + "--ww"] = loadConTexture(name, 0,1);
				textures[name + "--center"] = loadConTexture(name, 1,1);
				textures[name + "--ee"] = loadConTexture(name, 2,1);
				textures[name + "--ns"] = loadConTexture(name, 3,1);
				textures[name + "--w"] = loadConTexture(name, 4,1);
				textures[name + "--we"] = loadConTexture(name, 5,1);
				textures[name + "--e"] = loadConTexture(name, 6,1);
				textures[name + "--sw"] = loadConTexture(name, 0,2);
				textures[name + "--ss"] = loadConTexture(name, 1,2);
				textures[name + "--se"] = loadConTexture(name, 2,2);
				textures[name + "--s"] = loadConTexture(name, 3,2);
			} else {
				textures[name] = loadConTexture(name, 0,0);
			}
			
			INFO("Loaded tile: "<< name);
		}
	}
	else
	{
		ERROR("Texture manager failed to load '" << filename <<"'");
	}

}

sf::Texture* TextureManager::loadConTexture(std::string filename, int x, int y)
{
	sf::Texture *t = new sf::Texture();
	sf::IntRect rect(x*16,y*16,16,16);
	
	if (!t->loadFromFile(resourcePath() + filename + ".png", rect))
	{
		FATAL("Missing texture " << filename << ".png [" << x*16 << "," << y*16 <<"]");
	}
	
	return t;
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

            sf::IntRect rect(0,0,32,32);

            if (array->count() > 0)
            {
                rect = sf::IntRect(GNumberFromArray(array, 0)->asInt(),
                                   GNumberFromArray(array, 1)->asInt(),
                                   GNumberFromArray(array, 2)->asInt(),
                                   GNumberFromArray(array, 3)->asInt());
            }

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
        ERROR("Texture manager failed to load '" << filename << "'");
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
