/************************************\
|*   Copyright 2015 Jacob Gonzalez  *|
|*             a1687803             *|
|* -------------------------------- *|
|*          (╯°□°）╯︵ ┻━┻           *|
\************************************/

#ifndef GENERICS_H
#define GENERICS_H


#include "Generic.h"
#include "GNumber.h"
#include "GString.h"
#include "GArray.h"
#include "GDict.h"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>

// helpers to make things more user friendly

// helpers for GNumber
static inline GNumber *GNumberMake()
{
    return Generic::make<GNumber>();
}

static inline GNumber *GNumberMake(float v)
{
    return Generic::make<GNumber>(v);
}

static inline GNumber *GNumberMake(int v)
{
    return Generic::make<GNumber>(v);
}

// helpers for GString
static inline GString *GStringMake(std::string v)
{
    return Generic::make<GString>(v);
}

static inline GString *GStringMake(const char *v)
{
    return Generic::make<GString>(std::string(v));
}

// helpers for array
static inline GArray *GArrayMake()
{
    return Generic::make<GArray>();
}

static inline GArray *GArrayMake(std::vector<Generic *> v)
{
    return Generic::make<GArray>(v);
}

// helpers for dicts
static inline GDict *GDictMake()
{
    return Generic::make<GDict>();
}

static inline GDict *GDictMake(std::map<std::string, Generic *> v)
{
    return Generic::make<GDict>(v);
}

// helpers for getting from dicts and arrays
// this is so you don't have to mess with to typecasting
static inline GDict *GDictFromDict(Generic *dict, std::string key)
{
    if (dict != 0)
    {
        return dict->as<GDict>()->getAs<GDict>(key);
    }
    return 0;
}

static inline GArray *GArrayFromDict(Generic *dict, std::string key)
{
    if (dict != 0)
    {
        return dict->as<GDict>()->getAs<GArray>(key);
    }
    return 0;
}

static inline GNumber *GNumberFromDict(Generic *dict, std::string key)
{
    if (dict != 0)
    {
        return dict->as<GDict>()->getAs<GNumber>(key);
    }
    return 0;
}

static inline GString *GStringFromDict(Generic *dict, std::string key)
{
    if (dict != 0)
    {
        return dict->as<GDict>()->getAs<GString>(key);
    }
    return 0;
}

static inline GDict *GDictFromArray(Generic *array, size_t index)
{
    if (array != 0)
    {
        return array->as<GArray>()->at<GDict>(index);
    }
    return 0;
}

static inline GArray *GArrayFromArray(Generic *array, size_t index)
{
    if (array != 0)
    {
        return array->as<GArray>()->at<GArray>(index);
    }
    return 0;
}

static inline GNumber *GNumberFromArray(Generic *array, size_t index)
{
    if (array != 0)
    {
        return array->as<GArray>()->at<GNumber>(index);
    }
    return 0;
}

static inline GString *GStringFromArray(Generic *array, size_t index)
{
    if (array != 0)
    {
        return array->as<GArray>()->at<GString>(index);
    }
    return 0;
}

#endif // GENERICS_H

