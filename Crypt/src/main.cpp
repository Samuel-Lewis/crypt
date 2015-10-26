
#include <SFML/Graphics.hpp>

#include "TextureManager.hpp"
#include "GameController.hpp"

#include <iostream>


int main(int, char const**)
{
    lbLog::startLog(resourcePath(), "crypt-log", true);

    // Create the main window of size of a region
    sf::RenderWindow window(sf::VideoMode(32*32*1.5, 32*32*1.5), "Crypt");

    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png"))
    {
        return EXIT_FAILURE;
    }
    window.setIcon(128, 128, icon.getPixelsPtr());

    GameController game(&window);

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
        }

        game.update();

        // Clear screen
        window.clear();
        game.draw();
        // Update the window
        window.display();
    }

    lbLog::endLog();
    TextureManager::getInstance().free();

    return EXIT_SUCCESS;
}
