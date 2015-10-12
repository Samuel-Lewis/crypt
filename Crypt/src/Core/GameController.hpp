//
//  GameController.hpp
//  Crypt
//
//  Created by Jacob Gonzalez on 11/10/2015.
//  Copyright © 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef GameController_hpp
#define GameController_hpp

#include <SFML/Graphics.hpp>
#include "Cartographer.h"

#include "ResourcePath.hpp"
#include "TextureManager.hpp"
#include "Animator.hpp"

#include "lbLog.h"
#include "lbRNG.h"

class GameController
{
public:

    GameController(sf::RenderWindow *win) : location(0, 0)
    {
        window = win;

        view = sf::View(sf::FloatRect(0,0,32*32, 32*32));
        view.setViewport(sf::FloatRect(0, 0, 1, 1));
        window->setView(view);

        minimap = sf::View(sf::FloatRect(0,0,32*32, 32*32));
        minimap.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));

        tiles = loadRegion(location.x, location.y);

        dummyPlayer = sf::Sprite(*TextureManager().getInstance().getTexture("Player"));
        dummyPlayer.setPosition(view.getCenter());
    }
    ~GameController()
    {}

    std::vector<sf::Sprite> loadRegion(int x, int y);
    
    void keyPressed(sf::Keyboard::Key key);
    void update();
    void draw();

    sf::View view;
    sf::View minimap;
    sf::RenderWindow *window;
    std::vector<sf::Sprite> tiles;

    sf::Sprite dummyPlayer;

    sf::Vector2i location;

    Cartographer cartographer;
    
    Animator animator;
};

#endif /* GameController_hpp */
