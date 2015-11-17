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

#include "RenderEffect.hpp"

#include "Cartographer.h"
#include "Player.hpp"

class GameController : public UpdateRequestDelegate
{
public:
    GameController(sf::RenderWindow *win) : location(0, 0), player(0, 0), light(false), tick(0), showmap(false)
    {
        window = win;

        view = sf::View(sf::FloatRect(0,0,REGIONSIZE*REGIONSIZE, REGIONSIZE*REGIONSIZE));
        view.setViewport(sf::FloatRect(0, 0, 1, 1));
        window->setView(view);

        minimap = sf::View(sf::FloatRect(-REGIONSIZE*REGIONSIZE,-REGIONSIZE*REGIONSIZE,3*REGIONSIZE*REGIONSIZE, 3*REGIONSIZE*REGIONSIZE));
         minimap.setViewport(sf::FloatRect(0, 0, 1, 1));

        tiles = loadAround(location.x, location.y);

        player.cartographer = &cartographer;
        player.delegate = this;

        LightEffect *le = new LightEffect();
        lightSeed = &le->flickerSeed;

        effects.push_back(le);

    }
    ~GameController()
    {
        for (size_t i = 0; i < effects.size(); ++i)
        {
            delete effects[i];
        }
        effects.clear();
    }

    std::vector<sf::Sprite> loadRegion(int x, int y);

    std::map<std::pair<int, int>, std::vector<sf::Sprite> > loadAround(int x, int y);

    bool light;

    void keyPressed(sf::Keyboard::Key key);
    void keyReleased(sf::Keyboard::Key key);
    void update();
    void draw();

    void updateRequested(UpdateRequestDelegate *sender);

    sf::View view;
    sf::View minimap;
    bool showmap;
    sf::RenderWindow *window;

    std::map<std::pair<int, int>, std::vector<sf::Sprite> > tiles;

    Player player;

    sf::Vector2i location;

    Cartographer cartographer;

    std::vector<RenderEffect *> effects;
    int *lightSeed;
    unsigned int tick;
};

#endif /* GameController_hpp */
