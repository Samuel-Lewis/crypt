//
//  GameController.cpp
//  Crypt
//
//  Created by Jacob Gonzalez on 11/10/2015.
//  Copyright © 2015 Jacob Gonzalez. All rights reserved.
//

#include "Config.h"

#include "lbLog.h"

#include "GameController.hpp"
#include "TextManager.hpp"

void GameController::keyPressed(sf::Keyboard::Key key)
{
    // change all this with proper stuff

    // region
    if (key == sf::Keyboard::A)
    {
        player.worldPos.x--;
        tiles = loadAround(player.worldPos.x, player.worldPos.y);
        printScreen("Warp Left");
    }
    else if (key == sf::Keyboard::D)
    {
        player.worldPos.x++;
        tiles = loadAround(player.worldPos.x, player.worldPos.y);
        printScreen("Warp Right");
    }
    else if (key == sf::Keyboard::W)
    {
        player.worldPos.y--;
        tiles = loadAround(player.worldPos.x, player.worldPos.y);
        printScreen("Warp Up");
    }
    else if (key == sf::Keyboard::S)
    {
        player.worldPos.y++;
        tiles = loadAround(player.worldPos.x, player.worldPos.y);
        printScreen("Warp Down");
    }

    if (key == sf::Keyboard::Num1)
    {
        minimap.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
    }
    else if (key == sf::Keyboard::Num2)
    {
        minimap.setViewport(sf::FloatRect(0, 0, 1, 1));
    }

    if (key == sf::Keyboard::L)
    {
        light = !light;
    }

    // player

    player.keyPressed(key);

    if (location != player.worldPos)
    {
        location = player.worldPos;
        tiles = loadAround(location.x, location.y);
    }
}

void GameController::update()
{
    player.update();
    *lightSeed = (TILESIZE/2)*sin(++tick/(5*TILESIZE));

    TextManager::getInstance().ticks++;
    if (TextManager::getInstance().ticks % 720 == 0)
    {
        TextManager::getInstance().pop();
    }
}

void GameController::draw()
{
    // draw tiles

    window->setView(view);

    for (auto &&tile : tiles[std::make_pair(0, 0)])
    {
        for (auto effect : effects)
        {
            if (effect->name() != "light" || light)
            {
                effect->begin(tile, player.screenPos.x, player.screenPos.y);
            }
        }
        window->draw(tile);
        for (auto effect : effects)
        {
            effect->end(tile);
        }
    }

    player.draw(window);

    // draw minimap

    window->setView(minimap);
    if (!light)
    {
        for (auto &&region : tiles)
        {
            for (auto &&tile : region.second)
            {
                if (player.screenPos.x > view.getSize().x * 0.75 - 2*TILESIZE
                    && player.screenPos.y < view.getSize().y * 0.25 + TILESIZE)
                {
                    tile.setColor(sf::Color(255,255,255,100));
                }
                window->draw(tile);
                tile.setColor(sf::Color::White);
            }
        }
    }

    player.draw(window);

    window->setView(window->getDefaultView());

    int i = 0;
    for (auto &&text : TextManager::getInstance().printQueue)
    {
        i++;
        text.setPosition(TILESIZE, REGIONSIZE*REGIONSIZE*3 - TILESIZE*2 - TILESIZE*i);
        window->draw(text);
    }
}

std::map<std::pair<int, int>, std::vector<sf::Sprite> > GameController::loadAround(int x, int y)
{
    std::map<std::pair<int, int>, std::vector<sf::Sprite> > tiles;
    for (int ry = -1; ry < 2; ++ry)
    {
        for (int rx = -1; rx < 2; ++rx)
        {
            std::vector<sf::Sprite> t = loadRegion(rx + x, ry + y);
            for (auto &&tile : t)
            {
                tile.setPosition(tile.getPosition().x + REGIONSIZE*REGIONSIZE*rx, tile.getPosition().y + REGIONSIZE*REGIONSIZE*ry);
            }
            tiles[std::make_pair(rx, ry)] = t;
        }
    }
    return tiles;
}

std::vector<sf::Sprite> GameController::loadRegion(int x, int y)
{
    Region *r = cartographer.getRegion(x, y);

    std::vector<sf::Sprite> tiles;
    for (int y = 0; y < REGIONSIZE; ++y)
    {
		for (int x = 0; x < REGIONSIZE; ++x)
        {
            sf::Texture *ground = TextureManager::getInstance().getTexture(r->getTileAt(x, y)->getGround()->getTextureName());
			
			sf::Texture *prop = TextureManager::getInstance().getTexture(r->getTileAt(x, y)->getProp()->getTextureName());

            if (ground != nullptr)
            {
                sf::Sprite spriteGround(*ground);
                spriteGround.setPosition(x*TILESIZE, y*TILESIZE);
                tiles.push_back(spriteGround);
            }
			
			if (prop != nullptr)
			{
				sf::Sprite spriteProp(*prop);
				spriteProp.setPosition(x*TILESIZE, y*TILESIZE);
				tiles.push_back(spriteProp);
			}
        }
    }
    return tiles;
    
}
