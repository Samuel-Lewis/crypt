/************************************\
|*   Copyright 2015 Jacob Gonzalez  *|
|*             a1687803             *|
|* -------------------------------- *|
|*          (╯°□°）╯︵ ┻━┻           *|
\************************************/

#ifndef G_STRING_H
#define G_STRING_H

#include "Generic.h"
#include <string>

// String Type
class GString : public Generic
{
public:
    GString() : Generic(kString), value("")
    {}
    GString(std::string str) : Generic(kString), value(str)
    {}
    ~GString()
    {}

    // print that string
    std::ostream& print(std::ostream& os);

    std::istream& read(std::istream& is);

    size_t size() const;

    // this is where the string is actually stored
    std::string value;
};

#endif // G_STRING_H
