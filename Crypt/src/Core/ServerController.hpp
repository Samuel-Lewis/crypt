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
#define SERVER_SEED          0x04
// add player to array
#define SERVER_PLAYER_REG    0x05
// udate player pos
#define SERVER_PLAYER_UPDATE 0x06
// requ all players
#define SERVER_PLAYER_GET    0x07
// use an entity
#define SERVER_ENTITY_USE    0x08

#include <SFML/Network.hpp>
#include "lbRNG.h"
#include "Cartographer.h"
#include "Player.hpp"

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

    void sendSeed(sf::IpAddress addr, int port);
    void regPlayer(sf::IpAddress addr, int port, sf::Packet &pack);

    std::vector<PlayerDTO> players;

    sf::UdpSocket sock;
    Cartographer cart;

};

#endif /* ServerController_hpp */
