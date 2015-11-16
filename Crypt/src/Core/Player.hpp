
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <map>

#include <SFML/Graphics.hpp>

#include "Config.h"
#include "ResourcePath.hpp"

#include "lbLog.h"
#include "lbRNG.h"

#include "TextureManager.hpp"

#include "Animator.hpp"
#include "Cartographer.h"


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

    enum Direction {
        kLeft,
        kRight,
        kUp,
        kDown
    } dir;

    sf::Sprite sprite;

    // get relative tile pos's
    sf::Vector2i tileLeft();
    sf::Vector2i tileRight();
    sf::Vector2i tileUp();
    sf::Vector2i tileDown();

    Tile *tileAt(int rx, int ry, int tx, int ty);
    bool checkCollision(int rx, int ry, int tx, int ty);
    void use();
    void keyPressed(sf::Keyboard::Key key);
    void update();
    void draw(sf::RenderWindow *window);

    void snap();
    int speed;

    bool locked;

    Cartographer *cartographer;

private:
    // animator stuff
    Animator animator;
    void animationDidFinish(Animation *sender);

};

#endif // PLAYER_ONCE