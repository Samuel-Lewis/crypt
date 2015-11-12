

#pragma once

#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "TextureManager.hpp"
#include "Animator.hpp"
#include "Cartographer.h"


#include "lbLog.h"
#include "lbRNG.h"

#include <vector>
#include <map>


class Player : public AnimationDelegate
{
public:
    Player(int x, int y);
    Player(sf::Vector2i pos);
    ~Player(){}

    // setters for tile/screen pos will update sprite
    void setTilePos(int x, int y);
    void setScreenPos(float x, float y);
    void setTilePos(sf::Vector2i pos);
    void setScreenPos(sf::Vector2f pos);

    sf::Vector2i tilePos;
    sf::Vector2f screenPos;
    sf::Vector2i worldPos;

    sf::Sprite sprite;

    // get relative tile pos's
    sf::Vector2i tileLeft();
    sf::Vector2i tileRight();
    sf::Vector2i tileUp();
    sf::Vector2i tileDown();

    bool checkCollision(int rx, int ry, int tx, int ty);
    void keyPressed(sf::Keyboard::Key key);
    void update();
    void draw(sf::RenderWindow *window);

    void snap();

    bool locked;

    Cartographer *cartographer;

private:
    // animator stuff
    Animator animator;
    void animationDidFinish(Animation *sender);

};