/************************************\
|*   Copyright 2015 Jacob Gonzalez  *|
|*             a1687803             *|
|* -------------------------------- *|
|*          (╯°□°）╯︵ ┻━┻           *|
\************************************/

#include "GConfig.h"
#include <fstream>

GConfig GConfig::read(std::string filename)
{
    GConfig config;
    std::ifstream file(filename.c_str());
    if (file.good())
    {
        file >> config._dict;
        config.good = true;
    }
    file.close();
    return config;
}

void GConfig::write(std::string filename)
{
    std::ofstream file(filename.c_str());
    if (file.good() && good)
    {
        file << _dict;
    }
    file.close();
}

Generic *GConfig::get(std::string key)
{
    return _dict->get(key);
}

void GConfig::set(std::string key, Generic *item)
{
    _dict->set(key, item);
}

GDict *GConfig::getDict() const
{
    return _dict;
}

void GConfig::setDict(GDict *dict)
{
    _dict = dict;
}
