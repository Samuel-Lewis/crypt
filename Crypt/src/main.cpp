
#include <SFML/Graphics.hpp>
#include "Cartographer.h"

#include "ResourcePath.hpp"
#include "TextureManager.hpp"

#include "lbLog.h"
#include "lbRNG.h"

#include "Animator.hpp"

#include <iostream>

std::vector<sf::Sprite> loadRegion(Cartographer &cart, int x, int y)
{
    Region *r = cart.getRegion(x, y);

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

int main(int, char const**)
{
    lbLog::startLog(resourcePath(), "crypt-log", true);
    Tile::loadTileLibrary(resourcePath() + "tileLib.csv");

    //Animator animator;

    Cartographer test;
    std::cout << test.getCurrentPrint() << std::endl;

    std::vector<sf::Sprite> tiles = loadRegion(test, 0, 0);

    // Create the main window of size of region
    sf::RenderWindow window(sf::VideoMode(32*30, 32*30), "Crypt");

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

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                tiles = loadRegion(test, lbRNG::linear(-10, 10), lbRNG::linear(-10, 10));
                /*for (int y = 0; y < 32; ++y)
                {
                    for (int x = 0; x < 32; ++x)
                    {
                        Translation *t = new Translation(300,  sf::Vector2f(x*32,y*32), &tiles[x*y]);
                        animator.add(t);
                    }
                }*/
            }
        }

        // Clear screen
        window.clear();

        //animator.tick();

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
