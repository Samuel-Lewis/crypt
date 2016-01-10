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
#include "Manager.h"

void GameController::keyPressed(sf::Keyboard::Key key)
{
    // region
    switch (key)
    {
        case sf::Keyboard::A:

            player.worldPos.x--;
            tiles = loadAround(player.worldPos.x, player.worldPos.y);
            printScreen("Warp Left");
            break;
        case sf::Keyboard::D:
            player.worldPos.x++;
            tiles = loadAround(player.worldPos.x, player.worldPos.y);
            printScreen("Warp Right");
            break;
        case sf::Keyboard::W:
            player.worldPos.y--;
            tiles = loadAround(player.worldPos.x, player.worldPos.y);
            printScreen("Warp Up");
            break;
        case sf::Keyboard::S:
            player.worldPos.y++;
            tiles = loadAround(player.worldPos.x, player.worldPos.y);
            printScreen("Warp Down");
            break;
        case sf::Keyboard::M:
            player.locked = true;
            showmap = true;
            break;
        case sf::Keyboard::L:
            light = !light;
            break;
        default:
            break;
    }

    // player
    player.keyPressed(key);
    updateLighting();

    if (location != player.worldPos)
    {
        requestUpdate(this);
    }
}

void GameController::keyReleased(sf::Keyboard::Key key)
{
    switch (key)
    {
        case sf::Keyboard::M:
            player.locked = false;
            showmap = false;
            break;
        default:
            break;
    }
}

void GameController::update()
{
    player.update();
    useIcon.setTexture(*Manager::texture().getTexture("use_" + std::to_string(player.useFrame)));

	// Call ->tick(); on every tile in the region all 8 regions
    for (int ry = -1; ry < 2; ++ry)
    {
        for (int rx = -1; rx < 2; ++rx)
        {
            for (int tx = 0; tx < REGIONSIZE; ++tx)
            {
                for (int ty = 0; ty < REGIONSIZE; ++ty)
                {
                    cartographer.getRegion(rx + player.worldPos.x, ry + player.worldPos.y)->getTileAt(tx, ty)->tick();
                }
            }
        }
    }

    Manager::text().ticks++;
    if (Manager::text().ticks % 640 == 0)
    {
        Manager::text().pop();
        Manager::text().ticks = 0;
    }
}

void GameController::draw()
{
    // draw tiles
    if (!showmap)
    {
        window->setView(view);

        for (auto &&tile : tiles[std::make_pair(0, 0)])
        {
            for (auto effect : effects)
            {
                if (effect->name() != "light" || light)
                {
                    effect->begin(tile, REGIONSIZE + tile.getPosition().x/TILESIZE,  REGIONSIZE + tile.getPosition().y/TILESIZE);
                }
            }
            window->draw(tile);
            for (auto effect : effects)
            {
                effect->end(tile);
            }
        }
        
        player.draw(window);
    }

    // draw minimap
    if (showmap)
    {
        window->setView(minimap);

        for (auto &&region : tiles)
        {
            for (auto &&tile : region.second)
            {
                for (auto effect : effects)
                {
                    if (effect->name() != "light" || light)
                    {
                        effect->begin(tile, REGIONSIZE + tile.getPosition().x/TILESIZE,  REGIONSIZE + tile.getPosition().y/TILESIZE);
                    }
                }
                window->draw(tile);
                for (auto effect : effects)
                {
                    effect->end(tile);
                }

            }
        }

        player.draw(window);
        for (auto effect : effects)
        {
            effect->end(player.sprite);
        }
    }

    // draw gui
    window->setView(window->getDefaultView());

    int i = 0;
    for (auto &&text : Manager::text().printQueue)
    {
        i++;
        text.setPosition(TILESIZE, REGIONSIZE*REGIONSIZE*3 - TILESIZE*2 - TILESIZE*i);
        window->draw(text);
    }

    if (player.useIcon)
    {
        window->draw(useIcon);
    }
}

void GameController::updateRequested(UpdateRequestDelegate *sender)
{
    location = player.worldPos;
    tiles = loadAround(location.x, location.y);

    if (light)
    {
        updateLighting();
    }
}

void GameController::updateLighting()
{
    if (light)
    {
        lightMap->fillMapEmpty();
        for (auto &&region : tiles)
        {
            for (int x = 0; x < REGIONSIZE; ++x)
            {
                for (int y = 0; y < REGIONSIZE; ++y)
                {
                    if (cartographer.getRegion(region.first.first + location.x, region.first.second + location.y)->getTileAt(x, y)->isSolid())
                    {
                        lightMap->addBlockingSource((region.first.first+1)*REGIONSIZE + x, (region.first.second+1)*REGIONSIZE + y, true);
                    }
                }
            }
        }
        lightMap->addLightSource(REGIONSIZE + player.tilePos.x, REGIONSIZE + player.tilePos.y, 235, 4);

        lightMap->calculate(tick++/(M_2_PI*TILESIZE*TILESIZE));
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
			Tile* currTile = r->getTileAt(x, y);
			std::vector<Entity*> tileLayers = currTile->getEntities();
			
			for (int layer = 0; layer < (int)tileLayers.size(); layer++)
			{
                sf::Texture *texture = Manager::texture().getTexture(
												tileLayers[layer]->getTextureName() +
												tileLayers[layer]->getTextureSuffix());
				
				if (texture != nullptr)
				{
					sf::Sprite sprite(*texture);
					sprite.setPosition(x*TILESIZE, y*TILESIZE);
					tiles.push_back(sprite);
				}
			}
			
			if (currTile->hasMob())
			{
				sf::Texture *texture = Manager::texture().getTexture(currTile->getMob()->getTextureName());
				
				if (texture != nullptr)
				{
					sf::Sprite sprite(*texture);
					sprite.setPosition(x*TILESIZE, y*TILESIZE);
					tiles.push_back(sprite);
				}

			}
		}
    }
    return tiles;
    
}
