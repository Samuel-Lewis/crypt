//
//  Animator.hpp
//  Crypt
//
//  Created by Jacob Gonzalez on 11/10/2015.
//  Copyright © 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef Animator_hpp
#define Animator_hpp

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

struct Animation
{
    Animation() : finished(false)
    {}
    virtual ~Animation()
    {}
    virtual void execute() = 0;
    bool finished;
};

struct Transition : public Animation
{
    sf::Sprite *sprite;
    float duration;
    sf::Vector2f to;
    sf::Vector2f from;
    sf::Vector2f distance;
    sf::Vector2f vel;

    Transition(float d, sf::Vector2f t, sf::Vector2f f) : Animation(), duration(d), to(t), from(f)
    {
        distance = to - from;
        vel = distance/duration;
    }
    ~Transition()
    {}

    virtual void execute() = 0;
};

struct Translation : Transition
{
    float distance;
    Translation(float d, sf::Vector2f t, sf::Sprite *s) : Transition(d, t, s->getPosition())
    {
        sprite = s;
    }
    ~Translation()
    {}

    virtual void execute()
    {
        if (!(std::abs((sprite->getPosition() - to).x) < 2))
        {
            sprite->setPosition(sprite->getPosition().x+vel.x, sprite->getPosition().y);
        }

        if (!(std::abs((sprite->getPosition() - to).y) < 2))
        {
            sprite->setPosition(sprite->getPosition().x, sprite->getPosition().y+vel.y);
        }

        if (std::abs((sprite->getPosition() - to).x) < 2 && std::abs((sprite->getPosition() - to).y) < 2)
        {
            finished = true;
        }
    }
};

class Animator
{
public:

    Animator()
    {}
    ~Animator()
    {
        for (size_t i = 0; i < _anims.size(); ++i)
        {
            delete _anims[i];
        }
        _anims.clear();
    }

    void add(Animation *a);
    void tick();
private:
    std::vector<Animation *> _anims;
};

#endif /* Animator_hpp */
