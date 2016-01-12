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

            printf("cmd: %d\n", cmd);

            switch (cmd) {
                case SERVER_SEED:
                    printf("cmd: seed\n");
                    sendSeed(sender, port);
                    break;
                case SERVER_PLAYER_REG:
                    printf("cmd: reg\n");
                    regPlayer(sender, port, packet);
                    break;
                case SERVER_PLAYER_UPDATE:
                    break;
                default:
                    break;
            }
        }
    }
    return exit;
}

void ServerController::regPlayer(sf::IpAddress addr, int port, sf::Packet &pack)
{
    sf::Int32 id;
    pack >> id;
    printf("reg player with id %d", id);
    PlayerDTO p;
    p.net_id = id;
    players.push_back(p);
}

void ServerController::sendSeed(sf::IpAddress addr, int port)
{
    printf("sending seed: %s\n", lbRNG::getSeed().c_str());
    sf::Packet pack;
    pack << lbRNG::getSeed();
    sock.send(pack, addr, port);
}