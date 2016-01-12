//
//  ServerController.cpp
//  Crypt
//
//  Created by Jacob Gonzalez on 12/01/2016.
//  Copyright © 2016 Jacob Gonzalez. All rights reserved.
//

#include "ServerController.hpp"

int ServerController::loop()
{
    while (!exit)
    {
        sf::Packet packet;

        sf::IpAddress sender;
        unsigned short port;
        if (sock.receive(packet, sender, port) != sf::UdpSocket::NotReady)
        {
            sf::Int8 cmd;
            packet >> cmd;

            switch (cmd) {
                case SERVER_SEED:
                    sendSeed(port);
                    break;
                case SERVER_PLAYER:
                    break;
                case SERVER_ENTITY:
                    break;
                default:
                    break;
            }
        }
    }
    return exit;
}

void ServerController::sendSeed(int port)
{
    printf("sending seed: %s\n", lbRNG::getSeed().c_str());
    sf::Packet pack;
    pack << lbRNG::getSeed();
    sock.send(pack, sf::IpAddress::Broadcast, port);
}