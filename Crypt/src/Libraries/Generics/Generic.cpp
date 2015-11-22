/************************************\
|*   Copyright 2015 Jacob Gonzalez  *|
|*             a1687803             *|
|* -------------------------------- *|
|*          (╯°□°）╯︵ ┻━┻           *|
\************************************/

#include "Generic.h"


bool Generic::is(Type t)
{
    return type == t;
}

void Generic::free()
{
    delete this;
}
