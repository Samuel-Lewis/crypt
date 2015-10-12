//
//  Animator.cpp
//  Crypt
//
//  Created by Jacob Gonzalez on 11/10/2015.
//  Copyright © 2015 Jacob Gonzalez. All rights reserved.
//

#include "Animator.hpp"


void Animator::add(Animation *a)
{
    _anims.push_back(a);
}

void Animator::tick()
{
    for (size_t i = 0; i < _anims.size(); ++i)
    {
        _anims[i]->execute();
        if (_anims[i]->finished)
        {
            delete _anims[i];
            _anims.erase(_anims.begin()+i);
            i--;
        }
    }
}

