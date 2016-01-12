//
//  ServerController.hpp
//  Crypt
//
//  Created by Jacob Gonzalez on 12/01/2016.
//  Copyright © 2016 Jacob Gonzalez. All rights reserved.
//

#ifndef ServerController_hpp
#define ServerController_hpp

// return seed
#define SERVER_SEED   0x00000004
//
#define SERVER_PLAYER 0x00000005
#define SERVER_ENTITY 0x00000006

#include <SFML/Network.hpp>
#include "lbRNG.h"
#include "Cartographer.h"

class ServerController {
public:
    ServerController() : exit(false) {
        if (sock.bind(9999) != sf::UdpSocket::Done)
        {
            printf("could not bind socket\n");
            exit = true;
        }
        sock.setBlocking(false);
    }
    ~ServerController(){
        sock.unbind();
    }

    int loop();

    bool exit;

    void sendSeed(int port);

    sf::UdpSocket sock;
    Cartographer cart;

};

#endif /* ServerController_hpp */
