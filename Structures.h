#ifndef STRUCTURES_H
#define STRUCTURES_H

struct Position
{
    Position()
    {
        x = 0.f;
        y = 0.f;
        z = 0.f;
    }

    Position (float _x, float _y, float _z)
        : x(_x), y(_y), z(_z)
    {

    }

    Position (float _x, float _y)
        : x(_x), y(_y)
    {

    }


    float x;
    float y;
    float z;

};

struct Normal
{
    Normal()
    {
        x = 0.f;
        y = 0.f;
        z = 0.f;
    }
    Normal (float _x, float _y, float _z)
        : x(_x), y(_y), z(_z)
    {

    }
    Normal (float _x, float _y)
        : x(_x), y(_y)
    {

    }

    float x;
    float y;
    float z;
};


struct Color
{
    Color()
    {
        r = 0.f;
        g = 0.f;
        b = 0.f;
    }

    Color (float _r, float _g, float _b)
        : r(_r), g(_g), b(_b)
    {

    }

    float r;
    float g;
    float b;
};

struct UV
{
    UV()
    {
        u = 0.f;
        v = 0.f;
    }

    UV(float _u, float _v)
        : u(_u), v(_v)
    {

    }

    float u;
    float v;
};




#endif // STRUCTURES_H
