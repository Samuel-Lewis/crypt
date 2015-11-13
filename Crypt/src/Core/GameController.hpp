//
//  GameController.hpp
//  Crypt
//
//  Created by Jacob Gonzalez on 11/10/2015.
//  Copyright © 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef GameController_hpp
#define GameController_hpp

#include <map>

#include <SFML/Graphics.hpp>

#include "Config.h"

#include "lbLog.h"
#include "lbRNG.h"

#include "ResourcePath.hpp"
#include "TextureManager.hpp"

#include "Cartographer.h"
#include "Player.hpp"

class GameController
{
public:
    GameController(sf::RenderWindow *win) : location(0, 0), player(0, 0)
    {
        window = win;

        view = sf::View(sf::FloatRect(0,0,REGIONSIZE*REGIONSIZE, REGIONSIZE*REGIONSIZE));
        view.setViewport(sf::FloatRect(0, 0, 1, 1));
        window->setView(view);

        minimap = sf::View(sf::FloatRect(-REGIONSIZE*REGIONSIZE,-REGIONSIZE*REGIONSIZE,3*REGIONSIZE*REGIONSIZE, 3*REGIONSIZE*REGIONSIZE));
        minimap.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));

        tiles = loadAround(location.x, location.y);

        player.cartographer = &cartographer;

    }
    ~GameController()
    {}

    std::vector<sf::Sprite> loadRegion(int x, int y);

    std::map<std::pair<int, int>, std::vector<sf::Sprite> > loadAround(int x, int y);


    void keyPressed(sf::Keyboard::Key key);
    void update();
    void draw();

    sf::View view;
    sf::View minimap;
    sf::RenderWindow *window;

    std::map<std::pair<int, int>, std::vector<sf::Sprite> > tiles;

    Player player;

    sf::Vector2i location;

    Cartographer cartographer;
};

#endif /* GameController_hpp */
