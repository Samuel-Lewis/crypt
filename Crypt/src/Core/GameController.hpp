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

#include <map>

class GameController : public AnimationDelegate
{
public:
    GameController(sf::RenderWindow *win) : location(0, 0), lockPlayer(false)
    {
        window = win;

        view = sf::View(sf::FloatRect(0,0,32*32, 32*32));
        view.setViewport(sf::FloatRect(0, 0, 1, 1));
        window->setView(view);

        minimap = sf::View(sf::FloatRect(-32*32,-32*32,3*32*32, 3*32*32));
        minimap.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));

        tiles = loadAround(location.x, location.y);

        dummyPlayer = sf::Sprite(*TextureManager().getInstance().getTexture("Player"));
        dummyPlayer.setPosition(view.getCenter());
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

    sf::Sprite dummyPlayer;
    bool lockPlayer;

    sf::Vector2i location;

    // helper to round a to nearest multiple of 'to'
    // should go into a utils header
    static int closest(int a, int to)
    {
        int remainder = a % to;
        return remainder == 0 ? a : a + to - remainder;
    }

    Cartographer cartographer;

    Animator animator;
    void animationDidFinish(Animation *sender);
};

#endif /* GameController_hpp */
