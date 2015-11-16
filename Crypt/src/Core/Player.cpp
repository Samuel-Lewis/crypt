
#include "Config.h"
#include "lbLog.h"

#include "Player.hpp"

Player::Player(int x, int y) : worldPos(0,0), locked(false), dir(kLeft)
{
    sprite = sf::Sprite(*TextureManager().getInstance().getTexture("player"));
    setTilePos(x, y);
    setScreenPos(x*TILESIZE, y*TILESIZE);
}

Player::Player(sf::Vector2i pos) : worldPos(0,0), locked(false), dir(kLeft)
{
    sprite = sf::Sprite(*TextureManager().getInstance().getTexture("player"));
    setTilePos(pos);
    setScreenPos(pos.x*TILESIZE, pos.y*TILESIZE);
}

bool Player::checkCollision(int rx, int ry, int tx, int ty)
{
    if (cartographer == nullptr)
    {
        WARN("no cartog ref in player.. no collision detection");
        return false;
    }
    return (cartographer->getRegion(rx, ry)->getTileAt(tx, ty)->isSolid());
}

void Player::setTilePos(int x, int y)
{
    tilePos.x = x;
    tilePos.y = y;
}

void Player::setScreenPos(float x, float y)
{
    screenPos.x = x;
    screenPos.y = y;

    sprite.setPosition(x, y);
}

void Player::setTilePos(sf::Vector2i pos)
{
    tilePos = pos;
}

void Player::setScreenPos(sf::Vector2f pos)
{
    screenPos = pos;

    sprite.setPosition(pos);
}

void Player::keyPressed(sf::Keyboard::Key key)
{
    if (locked)
    {
        return;
    }

    switch (key)
    {
        case sf::Keyboard::Left:

            sprite.setTextureRect(sf::IntRect(0, 0, TILESIZE, TILESIZE));

            if (dir == kLeft && tilePos.x == 0)
            {
                worldPos.x--;
                tilePos.x = REGIONSIZE-1;
                setScreenPos(tilePos.x*TILESIZE, tilePos.y*TILESIZE);
                break;
            }

            if (dir == kLeft && !checkCollision(worldPos.x, worldPos.y, tileLeft().x, tileLeft().y))
            {
                tilePos = tileLeft();
                AnimMoveX(&sprite, -TILESIZE, 15, animator, this, "moveLeft");
                locked = true;
            }

            dir = kLeft;

            break;
        case sf::Keyboard::Right:

            sprite.setTextureRect(sf::IntRect(TILESIZE, 0, -TILESIZE, TILESIZE));

            if (dir == kRight && tilePos.x == REGIONSIZE-1)
            {
                worldPos.x++;
                tilePos.x = 0;
                setScreenPos(tilePos.x*TILESIZE, tilePos.y*TILESIZE);
                break;
            }

            if (dir == kRight && !checkCollision(worldPos.x, worldPos.y, tileRight().x, tileRight().y))
            {
                tilePos = tileRight();
                AnimMoveX(&sprite, TILESIZE, 15, animator, this, "moveRight");
                locked = true;
            }

            dir = kRight;

            break;
        case sf::Keyboard::Up:

            if (dir == kUp && tilePos.y == 0)
            {
                worldPos.y--;
                tilePos.y = REGIONSIZE-1;
                setScreenPos(tilePos.x*TILESIZE, tilePos.y*TILESIZE);
                break;
            }

            if (dir == kUp && !checkCollision(worldPos.x, worldPos.y, tileUp().x, tileUp().y))
            {
                tilePos = tileUp();
                AnimMoveY(&sprite, -TILESIZE, 15, animator, this, "moveUp");
                locked = true;
            }

            dir = kUp;

            break;
        case sf::Keyboard::Down:

            if (dir == kDown && tilePos.y == REGIONSIZE-1)
            {
                worldPos.y++;
                tilePos.y = 0;
                setScreenPos(tilePos.x*TILESIZE, tilePos.y*TILESIZE);
                break;
            }

            if (dir == kDown && !checkCollision(worldPos.x, worldPos.y, tileDown().x, tileDown().y))
            {
                tilePos = tileDown();
                AnimMoveY(&sprite, TILESIZE, 15, animator, this, "moveDown");
                locked = true;
            }

            dir = kDown;

            break;
        default:
            break;
    }
}

void Player::update()
{
    animator.tick();
}

void Player::snap()
{
    int sx = (int)screenPos.x & 0xFFF0 << 1;
    int sy = (int)screenPos.y & 0xFFF0 << 1;
    setScreenPos(sx, sy);
}

void Player::animationDidFinish(Animation *sender)
{
    setScreenPos(tilePos.x*TILESIZE, tilePos.y*TILESIZE);
    locked = false;
}

void Player::draw(sf::RenderWindow *window)
{
    window->draw(sprite);
}

sf::Vector2i Player::tileLeft()
{
    return sf::Vector2i {tilePos.x-1, tilePos.y};
}

sf::Vector2i Player::tileRight()
{
    return sf::Vector2i  {tilePos.x+1, tilePos.y};
}

sf::Vector2i Player::tileUp()
{
    return sf::Vector2i  {tilePos.x, tilePos.y-1};
}

sf::Vector2i Player::tileDown()
{
    return sf::Vector2i  {tilePos.x, tilePos.y+1};
}