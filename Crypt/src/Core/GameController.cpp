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
    // player
    if (lockPlayer)
    {
        return;
    }

    if (key == sf::Keyboard::Left)
    {
        if (dummyPlayer.getPosition().x < 32)
        {
            location.x--;
            tiles = loadAround(location.x, location.y);
            dummyPlayer.setPosition(view.getSize().x-32, dummyPlayer.getPosition().y);
            return;
        }

        // collison
        if (!cartographer.getRegion(location.x, location.y)->getTileAt((int)(dummyPlayer.getPosition().x-32) / 32, (int)dummyPlayer.getPosition().y / 32)->isSolid())
        {
            //AnimMoveX(&dummyPlayer, -32, 75, animator, this, "move");
            //lockPlayer = true;
            dummyPlayer.move(-32, 0);
        }
    }
    else if (key == sf::Keyboard::Right)
    {
        if (dummyPlayer.getPosition().x > view.getSize().x-64)
        {
            location.x++;
            tiles = loadAround(location.x, location.y);
            dummyPlayer.setPosition(0, dummyPlayer.getPosition().y);
            return;
        }

        if (!cartographer.getRegion(location.x, location.y)->getTileAt((int)(dummyPlayer.getPosition().x+32) / 32, (int)dummyPlayer.getPosition().y / 32)->isSolid())
        {
            //AnimMoveX(&dummyPlayer, 32, 75, animator, this, "move");
            //lockPlayer = true;
            dummyPlayer.move(32, 0);
        }
    }
    else if (key == sf::Keyboard::Up)
    {
        if (dummyPlayer.getPosition().y < 32)
        {
            location.y--;
            tiles = loadAround(location.x, location.y);
            dummyPlayer.setPosition(dummyPlayer.getPosition().x, view.getSize().y-32);
            return;
        }

        if (!cartographer.getRegion(location.x, location.y)->getTileAt((int)dummyPlayer.getPosition().x / 32, (int)(dummyPlayer.getPosition().y-32)/ 32)->isSolid())
        {
            //AnimMoveY(&dummyPlayer, -32, 75, animator, this, "move");
            //lockPlayer = true;
            dummyPlayer.move(0, -32);
        }

    }
    else if (key == sf::Keyboard::Down)
    {
        if (dummyPlayer.getPosition().y > view.getSize().y-64)
        {
            location.y++;
            tiles = loadAround(location.x, location.y);
            dummyPlayer.setPosition(dummyPlayer.getPosition().x, 0);
            return;
        }

        if (!cartographer.getRegion(location.x, location.y)->getTileAt((int)dummyPlayer.getPosition().x / 32, (int)(dummyPlayer.getPosition().y+32)/ 32)->isSolid())
        {
            //AnimMoveY(&dummyPlayer, 32, 75, animator, this, "move");
            //lockPlayer = true;
            dummyPlayer.move(0, 32);
        }

    }
}

void GameController::animationDidFinish(Animation *sender)
{
    if (sender->name == "move")
    {
        dummyPlayer.setPosition(closest(dummyPlayer.getPosition().x, 32), closest(dummyPlayer.getPosition().y, 32));
        lockPlayer = false;
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

    for (auto &&tile : tiles[std::make_pair(0, 0)])
    {
        window->draw(tile);
    }

    window->draw(dummyPlayer);

    // draw minimap

    if (!(dummyPlayer.getPosition().x > view.getSize().x * 0.75 - 64
          && dummyPlayer.getPosition().y < view.getSize().y * 0.25 + 32))
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

    window->draw(dummyPlayer);

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
