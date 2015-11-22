/************************************\
|*   Copyright 2015 Jacob Gonzalez  *|
|*             a1687803             *|
|* -------------------------------- *|
|*          (╯°□°）╯︵ ┻━┻           *|
\************************************/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Config.h"

#include "TextureManager.hpp"
#include "TileManager.hpp"
#include "BiomeManager.hpp"
#include "GameController.hpp"

#include <iostream>


int main(int, char const**)
{
    lbLog::startLog(resourcePath(), "crypt-log", true);

    // Create the main window of size of a region
    sf::RenderWindow window(sf::VideoMode(TILESIZE*TILESIZE*3, TILESIZE*TILESIZE*3), "Crypt");

    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png"))
    {
        return EXIT_FAILURE;
    }
    window.setIcon(128, 128, icon.getPixelsPtr());

    GameController game(&window);

    sf::Music music;
    if (music.openFromFile(resourcePath() + "song.ogg"))
    {
        music.play();
    }

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                game.keyPressed(event.key.code);
            }

            if (event.type == sf::Event::KeyReleased)
            {
                game.keyReleased(event.key.code);
            }
        }

        game.update();

        // Clear screen
        window.clear();
        game.draw();
        // Update the window
        window.display();
    }


    TextureManager::getInstance().free();
    TileManager::getInstance().free();
    BiomeManager::getInstance().free();

	lbLog::endLog();


    return EXIT_SUCCESS;
}
