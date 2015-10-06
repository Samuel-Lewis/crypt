#ifndef G_ARRAY_H
#define G_ARRAY_H

#include "Generic.h"
#include "GNumber.h"
#include "GString.h"
#include "GDict.h"
#include "Utils.h"
#include <sstream>

// Generic array..
class GArray : public Generic
{
public:
    GArray() : Generic(kArray), value()
    {}
    GArray(std::vector<Generic *> array) : Generic(kArray), value(array)
    {}
    ~GArray()
    {
        // garray own the data now so delete all the children
        // this is because it could be n deep with arrays
        for (int i = 0; i < count(); ++i)
        {
            value[i]->free();
            // set to NULL.. maybe c++11 nullptr?
            value[i] = 0;
        }
    }

    //pretty print
    std::ostream& print(std::ostream& os);

    std::istream& read(std::istream& is);

    std::vector<Generic *> value;

    // implement some specific vector stuff
    size_t count() const;

    template <typename T>
    T *at(size_t index)
    {
        return value[index]->as<T>();
    }

    template <typename T>
    T *operator[](size_t index)
    {
        return at<T>(index);
    }

    void add(Generic *item);
};

#endif // G_ARRAY_H
