/************************************\
|*   Copyright 2015 Jacob Gonzalez  *|
|*             a1687803             *|
|* -------------------------------- *|
|*          (╯°□°）╯︵ ┻━┻           *|
\************************************/

#ifndef G_DICT_H
#define G_DICT_H

#include "Generic.h"
#include "GNumber.h"
#include "GString.h"
#include "GArray.h"
#include "Utils.h"
#include <map>
#include <vector>
#include <sstream>

class GDict : public Generic
{
public:
    GDict() : Generic(kDict), value()
    {}
    GDict(std::map<std::string, Generic *> dict) : Generic(kDict), value(dict)
    {}
    ~GDict()
    {
        for (std::map<std::string, Generic *>::iterator it = value.begin(); it != value.end(); ++it)
        {
            delete it->second;
            it->second = 0;
        }
    }

    //pretty print
    std::ostream& print(std::ostream& os);

    std::istream& read(std::istream& is);

    template <typename T>
    T *getAs(std::string key)
    {
        if (value.find(key) != value.end())
        {
            return value[key]->as<T>();
        }
        return 0;
    }

    Generic *get(std::string key)
    {
        if (value.find(key) != value.end())
        {
            return value[key];
        }
        return 0;
    }

    void set(std::string key, Generic *item);

    std::map<std::string, Generic *> value;
};

#endif // G_DICT_H
