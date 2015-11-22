/************************************\
|*   Copyright 2015 Jacob Gonzalez  *|
|*             a1687803             *|
|* -------------------------------- *|
|*          (╯°□°）╯︵ ┻━┻           *|
\************************************/

#include "GNumber.h"

 // print dat int
std::ostream& GNumber::print(std::ostream& os)
{
    os << value;
    return os;
}

std::istream& GNumber::read(std::istream& is)
{
    is >> value;
    return is;
}

float GNumber::asFloat() const
{
    return value;
}

int GNumber::asInt() const
{
    return static_cast<int>(value);
}
