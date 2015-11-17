#include "Generic.h"


bool Generic::is(Type t)
{
    return type == t;
}

void Generic::free()
{
    delete this;
}
