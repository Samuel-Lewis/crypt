
#include "Config.h"
#include "lbLog.h"

#include "Player.hpp"
#include "TextManager.hpp"

Player::Player(int x, int y) : worldPos(0,0), locked(false), dir(kLeft), speed(PLAYERSPEED), textStep(0)
{
    sprite = sf::Sprite(*TextureManager().getInstance().getTexture("player_l_0"));
    setTilePos(x, y);
    setScreenPos(x*TILESIZE, y*TILESIZE);
}

Player::Player(sf::Vector2i pos) : worldPos(0,0), locked(false), dir(kLeft), speed(PLAYERSPEED), textStep(0)
{
    sprite = sf::Sprite(*TextureManager().getInstance().getTexture("player"));
    setTilePos(pos);
    setScreenPos(pos.x*TILESIZE, pos.y*TILESIZE);
}

Tile *Player::tileAt(int rx, int ry, int tx, int ty)
{
    return cartographer->getRegion(rx, ry)->getTileAt(tx, ty);
}

bool Player::checkCollision(int rx, int ry, int tx, int ty)
{
    if (cartographer == nullptr)
    {
        WARN("no cartog ref in player.. no collision detection");
        return false;
    }
    return tileAt(rx, ry, tx, ty)->isSolid();
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
                AnimMoveX(&sprite, -TILESIZE, speed, animator, this, "moveLeft");
                locked = true;
            }

            if (tileAt(worldPos.x, worldPos.y, tileLeft().x, tileLeft().y) != nullptr && tileAt(worldPos.x, worldPos.y, tileLeft().x, tileLeft().y)->canUse())
            {
                printScreen("Press 'E' to Use");
            }

            dir = kLeft;
            dir_char = "_l_";
            setTexture();

            break;
        case sf::Keyboard::Right:

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
                AnimMoveX(&sprite, TILESIZE, speed, animator, this, "moveRight");
                locked = true;
            }

            if (tileAt(worldPos.x, worldPos.y, tileRight().x, tileRight().y) != nullptr && tileAt(worldPos.x, worldPos.y, tileRight().x, tileRight().y)->canUse())
            {
                printScreen("Press 'E' to Use");
            }

            dir = kRight;
            dir_char = "_r_";
            setTexture();

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
                AnimMoveY(&sprite, -TILESIZE, speed, animator, this, "moveUp");
                locked = true;
            }

            if (tileAt(worldPos.x, worldPos.y, tileUp().x, tileUp().y) != nullptr && tileAt(worldPos.x, worldPos.y, tileUp().x, tileUp().y)->canUse())
            {
                printScreen("Press 'E' to Use");
            }

            dir = kUp;
            dir_char = "_u_";
            setTexture();

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
                AnimMoveY(&sprite, TILESIZE, speed, animator, this, "moveDown");
                locked = true;
            }

            if (tileAt(worldPos.x, worldPos.y, tileDown().x, tileDown().y) != nullptr && tileAt(worldPos.x, worldPos.y, tileDown().x, tileDown().y)->canUse())
            {
                printScreen("Press 'E' to Use");
            }

            dir = kDown;
            dir_char = "_d_";
            setTexture();

            break;
        case sf::Keyboard::E:
            use();
            break;
        default:
            break;
    }
}

void Player::setTexture()
{
    sprite.setTexture(*TextureManager::getInstance().getTexture("player" + dir_char + std::to_string(textStep)));
}

void Player::use()
{
	Tile* curr = nullptr;
    switch (dir) {
        case kLeft:
            curr = tileAt(worldPos.x, worldPos.y, tileLeft().x, tileLeft().y);
            break;
        case kRight:
            curr = tileAt(worldPos.x, worldPos.y, tileRight().x, tileRight().y);
            break;
        case kDown:
            curr = tileAt(worldPos.x, worldPos.y, tileDown().x, tileDown().y);
            break;
        case kUp:
            curr = tileAt(worldPos.x, worldPos.y, tileUp().x, tileUp().y);
            break;
        default:
            break;
    }
	if (curr != nullptr)
    {
        if (curr->canUse())
        {
            if (curr->use())
            {
                requestUpdate(delegate);
            }
        }
    }
}

void Player::update()
{
    animator.tick();

    if (animator.ticks % PLAYERANIM == 0 && locked)
    {
        textStep = ++textStep % 4;
        setTexture();
    }
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
    textStep = 0;
    setTexture();
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