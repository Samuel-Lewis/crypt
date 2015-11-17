#pragma once

struct Dimension
{
    int x;
    int y;
    int width;
    int height;
    float radius;
};

struct MapObject
{
    MapObject(Dimension d) : dim(d)
    {}
    virtual ~MapObject()
    {}
    Dimension dim;
};

struct BlockingObject : public MapObject
{
    BlockingObject(bool s, Dimension d) : solid(s), MapObject(d)
    {}
    ~BlockingObject()
    {}

    bool solid;
};

struct LightSource : public MapObject
{
    LightSource(float i, Dimension d) : intensity(i), MapObject(d)
    {}
    ~LightSource()
    {}

    float intensity;
};