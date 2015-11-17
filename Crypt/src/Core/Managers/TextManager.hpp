//
//  TextureManager.hpp
//  Crypt
//
//  Created by Jacob Gonzalez on 6/10/2015.
//  Copyright © 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef TextManager_hpp
#define TextManager_hpp

#define DEBUG

#include <string>
#include <deque>

#include <SFML/Graphics.hpp>

#include "lbLog.h"

#include "ResourcePath.hpp"
#include "Singleton.hpp"

class TextManager : public Singleton<TextManager>
{
public:
    TextManager() : Singleton<TextManager>()
    {
        if (!font.loadFromFile(resourcePath() + "SDS_8x8.ttf"))
        {
            FATAL("cannot load font");
        }
    }

    void push(std::string strtext);
    sf::Text pop();
    int ticks;
    sf::Font font;
    std::deque<sf::Text> printQueue;

};

static inline void printScreen(std::string s)
{
    TextManager::getInstance().push(s);
}

#endif /* TextureManager_hpp */
