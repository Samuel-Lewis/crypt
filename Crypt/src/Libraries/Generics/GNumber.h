#ifndef G_NUMBER_H
#define G_NUMBER_H

#include "Generic.h"

// Float/Integer Type
class GNumber : public Generic
{
public:
    GNumber() : Generic(kNumber), value(0)
    {}
    GNumber(float i) : Generic(kNumber), value(i)
    {}
    GNumber(int i) : Generic(kNumber), value(i)
    {}
    ~GNumber()
    {}

    // print dat float/int
    std::ostream& print(std::ostream& os);

    std::istream& read(std::istream& is);

    float asFloat() const;
    int asInt() const;

    // this is where the float is actually stored
    float value;
};

#endif // G_NUMBER_H
