//
//  Manager.h
//  Crypt
//
//  Created by Jacob Gonzalez on 26/12/2015.
//  Copyright © 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef Manager_h
#define Manager_h

#include "TextManager.hpp"
#include "TileManager.hpp"
#include "TextureManager.hpp"
#include "BiomeManager.hpp"

class Manager {
public:
    static inline TextManager &text()
    {
        return TextManager::getInstance();
    }
    static inline TextureManager &texture()
    {
        return TextureManager::getInstance();
    }
    static inline TileManager &tile()
    {
        return TileManager::getInstance();
    }
    static inline BiomeManager &biome()
    {
        return BiomeManager::getInstance();
    }

private:
    Manager(){}
};

#endif /* Manager_h */
