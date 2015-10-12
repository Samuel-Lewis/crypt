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

struct Animation;

class AnimationDelegate
{
public:
    virtual void animationDidFinish(Animation *sender) = 0;
};

struct Animation
{
    Animation() : finished(false)
    {}
    
    virtual ~Animation()
    {}
    
    virtual void execute() = 0;
    bool finished;
    
    std::string name;
    AnimationDelegate *delegate;
    
};

struct Transition : public Animation
{
    Transition(sf::Transformable *_sprite, float _dist, int _ticks) : Animation(), sprite(_sprite), dist(_dist), ticks(_ticks)
    {
        by = dist/ticks;
    }
    
    virtual ~Transition()
    {}
    
    bool tick()
    {
        if (ticks > 0)
        {
            ticks--;
            return true;
        }
        else
        {
            finished = true;
            if (delegate)
            {
                delegate->animationDidFinish(this);
            }
            return true;
        }
    }
    
    sf::Transformable *sprite;
    
    int ticks;
    float dist;
    float by;
    
    virtual void execute() = 0;
};

struct MoveX : public Transition
{
    MoveX(sf::Transformable *_sprite, float _dist, int _ticks) : Transition(_sprite, _dist, _ticks)
    {}
    
    virtual ~MoveX()
    {}
    
    void execute()
    {
        if (tick())
        {
            sprite->move(by, 0);
        }
    }
};

struct MoveY : public Transition
{
    MoveY(sf::Transformable *_sprite, float _dist, int _ticks) : Transition(_sprite, _dist, _ticks)
    {}
    
    virtual ~MoveY()
    {}
    
    void execute()
    {
        if (tick())
        {
            sprite->move(0, by);
        }
    }
};


struct Rotate : public Transition
{
    Rotate(sf::Transformable *_sprite, float _dist, int _ticks) : Transition(_sprite, _dist, _ticks)
    {}
    
    virtual ~Rotate()
    {}
    
    void execute()
    {
        if (tick())
        {
            sprite->rotate(by);
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

static inline void *AnimMoveX(sf::Sprite *s, float dist, int ticks, Animator &a, AnimationDelegate *delegate, std::string name)
{
    MoveX *m = new MoveX(s, dist, ticks);
    m->delegate = delegate;
    m->name = name;
    a.add(m);
}

static inline void *AnimMoveY(sf::Sprite *s, float dist, int ticks, Animator &a, AnimationDelegate *delegate, std::string name)
{
    MoveY *m = new MoveY(s, dist, ticks);
    m->delegate = delegate;
    m->name = name;
    a.add(m);
}


#endif /* Animator_hpp */
