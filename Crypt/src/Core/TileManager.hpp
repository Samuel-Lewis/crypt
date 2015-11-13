//
//  TileManager.hpp
//  Crypt
//
//  Created by Jacob Gonzalez on 10/10/2015.
//  Copyright © 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef TileManager_hpp
#define TileManager_hpp

#include "Singleton.hpp"
#include "GConfig.h"

#include "lbLog.h"

#include <string>
#include <map>

class TileManager : public Singleton<TileManager>
{
public:
    TileManager() : Singleton<TileManager>()
    {
		INFO("Loading Tile Manager...");
        loadTilesFromFile("tiles.json");
    }

    void loadTilesFromFile(std::string filename);

    template <typename T>
    T *getAttributeAs(std::string tile, std::string attr)
    {
        return GDictFromDict(tileDict, tile)->getAs<T>(attr);
    }

    std::string getString(std::string tile, std::string attr);
    int getInt(std::string tile, std::string attr);

    GDict *tileDict;

    void free();
    
};


#endif /* TileManager_hpp */
