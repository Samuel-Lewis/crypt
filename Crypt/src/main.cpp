/************************************\
|*   Copyright 2015 Jacob Gonzalez  *|
|*             a1687803             *|
|* -------------------------------- *|
|*          (╯°□°）╯︵ ┻━┻           *|
\************************************/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Config.h"

#include "GameController.hpp"
#include "ServerController.hpp"
#include "Manager.h"

#include <iostream>


int main(int argc, char const** argv)
{
    lbLog::startLog(resourcePath(), "crypt-log", true);

    sf::UdpSocket sock;
    bool client = false;

    if (argc > 1)
    {
        if (strcmp(argv[1], "-host") == 0)
        {
            printf("hosting server\n");
            ServerController server;
            return server.loop();
        }
        else if (strcmp(argv[1], "-connect") == 0)
        {
            if (sock.bind(sf::UdpSocket::AnyPort) == sf::UdpSocket::Done)
            {
                sf::Packet pack;
                pack << sf::Int8(SERVER_SEED);
                sock.send(pack, sf::IpAddress("127.0.0.1"), 9999);

                sf::IpAddress sender;
                unsigned short port;
                pack = sf::Packet();

                if (sock.receive(pack, sender, port) == sf::UdpSocket::Done)
                {
                    std::string seed;
                    pack >> seed;

                    lbRNG::generateSeed(seed);

                    Manager::text().push("Seed: " + seed);

                    sock.setBlocking(false);
                    client = true;
                }
                else
                {
                    Manager::text().push("Nope");
                }
            }
            else
            {
                Manager::text().push("No connect to server");
            }
        }
    }

    // Create the main window of size of a region
    sf::RenderWindow window(sf::VideoMode(TILESIZE*TILESIZE*3, TILESIZE*TILESIZE*3), "Crypt");

    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png"))
    {
        return EXIT_FAILURE;
    }
    window.setIcon(128, 128, icon.getPixelsPtr());

    sf::UdpSocket *socket = nullptr;
    if (client)
    {
        socket = &sock;
    }
    GameController game(&window, socket);

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

    if (client)
    {
        sock.unbind();
    }

    Manager::texture().free();
    Manager::tile().free();
    Manager::biome().free();

	lbLog::endLog();


    return EXIT_SUCCESS;
}
