//
//  GameController.cpp
//  Crypt
//
//  Created by Jacob Gonzalez on 11/10/2015.
//  Copyright © 2015 Jacob Gonzalez. All rights reserved.
//

#include "GameController.hpp"

void GameController::keyPressed(sf::Keyboard::Key key)
{
    // change all this with proper stuff

    // region
    if (key == sf::Keyboard::A)
    {
        location.x--;
        tiles = loadAround(location.x, location.y);
    }
    else if (key == sf::Keyboard::D)
    {
        location.x++;
        tiles = loadAround(location.x, location.y);
    }
    else if (key == sf::Keyboard::W)
    {
        location.y--;
        tiles = loadAround(location.x, location.y);
    }
    else if (key == sf::Keyboard::S)
    {
        location.y++;
        tiles = loadAround(location.x, location.y);
    }

    if (key == sf::Keyboard::Num1)
    {
        minimap.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
    }
    else if (key == sf::Keyboard::Num2)
    {
        minimap.setViewport(sf::FloatRect(0, 0, 1, 1));
    }

    // player

    player.keyPressed(key);
}

void GameController::update()
{
    player.update();
}

void GameController::draw()
{
    // draw tiles

    window->setView(view);

    for (auto &&tile : tiles[std::make_pair(0, 0)])
    {
        window->draw(tile);
    }

    player.draw(window);

    // draw minimap

    if (!(player.tilePos.x > view.getSize().x * 0.75 - 64
          && player.tilePos.y < view.getSize().y * 0.25 + 32))
    {
        window->setView(minimap);

        for (auto &&region : tiles)
        {
            for (auto &&tile : region.second)
            {
                window->draw(tile);
            }
        }
    }

    player.draw(window);

    window->setView(window->getDefaultView());
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
                tile.setPosition(tile.getPosition().x + 32*32*rx, tile.getPosition().y + 32*32*ry);
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
    for (int y = 0; y < r->height(); ++y)
    {
        for (int x = 0; x < r->width(); ++x)
        {
            sf::Texture *ground = TextureManager::getInstance().getTexture(r->getTileAt(x, y)->getGround()->getTileName());
			
			sf::Texture *top = TextureManager::getInstance().getTexture(r->getTileAt(x, y)->getTop()->getTileName());
			
			
            if (ground != nullptr)
            {
                sf::Sprite spriteGround(*ground);
                spriteGround.setPosition(x*32, y*32);
                tiles.push_back(spriteGround);
            }
			
			if (top != nullptr)
			{
				sf::Sprite spriteTop(*top);
				spriteTop.setPosition(x*32, y*32);
				tiles.push_back(spriteTop);
			}
        }
    }
    return tiles;
    
}
