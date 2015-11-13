//
//  TileManager.cpp
//  Crypt
//
//  Created by Jacob Gonzalez on 10/10/2015.
//  Copyright © 2015 Jacob Gonzalez. All rights reserved.
//

#include "Config.h"

#include "TileManager.hpp"
#include "ResourcePath.hpp"
#include "lbLog.h"

#include <fstream>

void TileManager::loadTilesFromFile(std::string filename)
{
    // as we get these anytime, we need to keep the dict alive so load it in manually
    tileDict = GDictMake();
    std::ifstream tileFile(resourcePath() + filename);
    if (tileFile.good())
    {
        tileFile >> tileDict;
    }
    tileFile.close();

    if (!tileDict->good)
    {
        ERROR("TileManager failed to load");
    }
}

std::string TileManager::getString(std::string tile, std::string attr)
{
    return getAttributeAs<GString>(tile, attr)->value;
}

int TileManager::getInt(std::string tile, std::string attr)
{
    return getAttributeAs<GNumber>(tile, attr)->asInt();
}

void TileManager::free()
{
    tileDict->free();
}