
#include <SFML/Graphics.hpp>
#include "Cartographer.h"

#include "ResourcePath.hpp"
#include "TextureManager.hpp"

#include "lbLog.h"

#include <iostream>

int main(int, char const**)
{
    //lbLog::startLog("cant save to app folder.. need to put it in desktop or smething", "crypt-log", true);
    Tile::loadTileLibrary(resourcePath() + "tileLib.csv");

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1280, 1280), "Crypt");

    Cartographer test;
    std::cout << test.getCurrentPrint() << std::endl;

    Region *r = test.getRegion(0, 0);

    std::vector<sf::Sprite> tiles;
    for (int y = 0; y < r->height(); ++y)
    {
        for (int x = 0; x < r->width(); ++x)
        {
            if (r->getTileAt(x, y)->getName() == "Tree")
            {
                sf::Sprite sprite(*TextureManager::getInstance().getTexture("tree"));
                sprite.setPosition(x*32, y*32);
                tiles.push_back(sprite);
            }
            else if (r->getTileAt(x, y)->getName() == "Wall")
            {
                sf::Sprite sprite(*TextureManager::getInstance().getTexture("stone"));
                sprite.setPosition(x*32, y*32);
                tiles.push_back(sprite);
            }
        }
    }

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear();

        for (auto &&sprite : tiles)
        {
            window.draw(sprite);
        }

        // Update the window
        window.display();
    }

    // lbLog::endLog();
    TextureManager::getInstance().free();

    return EXIT_SUCCESS;
}
