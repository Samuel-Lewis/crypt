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
        tiles = loadRegion(location.x, location.y);
    }
    else if (key == sf::Keyboard::D)
    {
        location.x++;
        tiles = loadRegion(location.x, location.y);
    }
    else if (key == sf::Keyboard::W)
    {
        location.y--;
        tiles = loadRegion(location.x, location.y);
    }
    else if (key == sf::Keyboard::S)
    {
        location.y++;
        tiles = loadRegion(location.x, location.y);
    }
    // player
    else if (key == sf::Keyboard::Left)
    {
        if (dummyPlayer.getPosition().x < 32)
        {
            location.x--;
            tiles = loadRegion(location.x, location.y);
            dummyPlayer.setPosition(view.getSize().x-32, dummyPlayer.getPosition().y);
            return;
        }

        // collison
        if (!cartographer.getRegion(location.x, location.y)->getTileAt((int)(dummyPlayer.getPosition().x-32) / 32, (int)dummyPlayer.getPosition().y / 32)->isSolid())
        {
            AnimMoveX(&dummyPlayer, -32, 100, animator);
            //dummyPlayer.move(-32, 0);
        }
    }
    else if (key == sf::Keyboard::Right)
    {
        if (dummyPlayer.getPosition().x > view.getSize().x-64)
        {
            location.x++;
            tiles = loadRegion(location.x, location.y);
            dummyPlayer.setPosition(0, dummyPlayer.getPosition().y);
            return;
        }

        if (!cartographer.getRegion(location.x, location.y)->getTileAt((int)(dummyPlayer.getPosition().x+32) / 32, (int)dummyPlayer.getPosition().y / 32)->isSolid())
        {
            AnimMoveX(&dummyPlayer, 32, 100, animator);
        }
    }
    else if (key == sf::Keyboard::Up)
    {
        if (dummyPlayer.getPosition().y < 32)
        {
            location.y--;
            tiles = loadRegion(location.x, location.y);
            dummyPlayer.setPosition(dummyPlayer.getPosition().x, view.getSize().y-32);
            return;
        }

        if (!cartographer.getRegion(location.x, location.y)->getTileAt((int)dummyPlayer.getPosition().x / 32, (int)(dummyPlayer.getPosition().y-32)/ 32)->isSolid())
        {
            AnimMoveY(&dummyPlayer, -32, 100, animator);
        }
    }
    else if (key == sf::Keyboard::Down)
    {
        if (dummyPlayer.getPosition().y > view.getSize().y-64)
        {
            location.y++;
            tiles = loadRegion(location.x, location.y);
            dummyPlayer.setPosition(dummyPlayer.getPosition().x, 0);
            return;
        }

        if (!cartographer.getRegion(location.x, location.y)->getTileAt((int)dummyPlayer.getPosition().x / 32, (int)(dummyPlayer.getPosition().y+32)/ 32)->isSolid())
        {
            AnimMoveY(&dummyPlayer, 32, 100, animator);
        }
    }
}

void GameController::update()
{
    animator.tick();
}

void GameController::draw()
{
    // draw tiles

    window->setView(view);

    for (auto &&tile : tiles)
    {
        window->draw(tile);
    }

    window->draw(dummyPlayer);

    // draw minimap

    if (!(dummyPlayer.getPosition().x > view.getSize().x * 0.75 - 64
        && dummyPlayer.getPosition().y < view.getSize().y * 0.25 + 32))
    {
        window->setView(minimap);

        for (auto &&tile : tiles)
        {
            window->draw(tile);
        }
        
        window->draw(dummyPlayer);
    }

    window->setView(window->getDefaultView());
}

std::vector<sf::Sprite> GameController::loadRegion(int x, int y)
{
    Region *r = cartographer.getRegion(x, y);

    std::vector<sf::Sprite> tiles;
    for (int y = 0; y < r->height(); ++y)
    {
        for (int x = 0; x < r->width(); ++x)
        {
            sf::Texture *text = TextureManager::getInstance().getTexture(r->getTileAt(x, y)->getName());
            if (text != nullptr)
            {
                sf::Sprite sprite(*text);
                sprite.setPosition(x*32, y*32);
                tiles.push_back(sprite);
            }
        }
    }
    return tiles;
    
}