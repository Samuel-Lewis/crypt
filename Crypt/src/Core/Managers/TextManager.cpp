//
//  TextureManager.cpp
//  Crypt
//
//  Created by Jacob Gonzalez on 6/10/2015.
//  Copyright © 2015 Jacob Gonzalez. All rights reserved.
//

#include "TextManager.hpp"

void TextManager::push(std::string strtext)
{
    sf::Text text;
    text.setFont(font);
    text.setString(strtext);
    text.setCharacterSize(TILESIZE);
    text.setColor(sf::Color::White);

    text.setPosition(TILESIZE, REGIONSIZE*REGIONSIZE*3 - TILESIZE*2 - TILESIZE*printQueue.size());

    printQueue.push_back(text);

    ticks = 0;
}

sf::Text TextManager::pop()
{
    if (printQueue.size() == 0)
    {
        return sf::Text();
    }
    sf::Text text = printQueue.front();
    printQueue.pop_front();
    return text;
}