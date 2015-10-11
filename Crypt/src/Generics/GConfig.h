#ifndef G_CONFIG_H
#define G_CONFIG_H

#include "Generics.h"

// Wrapper over GDict for writing/reading config files
class GConfig
{
public:
    GConfig() : good(false)
    {
        _dict = GDictMake();
    }
    virtual ~GConfig()
    {
        _dict->free();
    }

    static GConfig read(std::string filename);
    void write(std::string filename);

    // get value as type
    template<typename T>
    T *getAs(std::string key)
    {
        return _dict->getAs<T>(key);
    }

    // get value as generic
    Generic *get(std::string key);

    // set an item
    void set(std::string key, Generic *item);

    // get/set underlying dict
    GDict *getDict() const;
    void setDict(GDict *dict);

    bool good;

protected:
    GDict *_dict;
};

#endif // G_CONFIG_H
