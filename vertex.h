#ifndef VERTEX_H
#define VERTEX_H

#include "Structures.h"
#include <iostream>
#include <fstream>

class Vertex
{
    //! Overloaded ostream operator which writes all vertex data on an open textfile stream
    friend std::ostream& operator<< (std::ostream&, const Vertex&);

    //! Overloaded ostream operator which reads all vertex data from an open textfile stream
    friend std::istream& operator>> (std::istream&, Vertex&);

public:
    Vertex();
    Vertex(float x, float y, float z, float r, float g, float b, float u, float v);
    Vertex(Position position, Color color, UV uv);

    Vertex(float x, float y, float z, float r, float g, float b);
    Vertex(Position position, Color color);

    Position GetPosition() { return mPosition; }
    Color GetColor() { return mColor; }
    UV GetUV() { return mUV; }

    float GetX() { return mPosition.x; }
    float GetY() { return mPosition.y; }
    float GetZ() { return mPosition.z; }

    float GetR() { return mColor.r; }
    float GetG() { return mColor.g; }
    float GetB() { return mColor.b; }

    float GetU() { return mUV.u; }
    float GetV() { return mUV.v; }

    void SetPosition(float x, float y, float z) { mPosition = Position(x,y,z); }
    void SetPosition(Position position) { mPosition = position; }

    void SetColor(float r, float g, float b) { mColor = Color(r,g,b); }
    void SetColor(Color color) { mColor = color; }

    void SetUV(float u, float v) { mUV = UV(u,v); }
    void SetUV(UV uv) { mUV = uv; }


    void SetX(float x) { mPosition.x = x; }
    void SetY(float y) { mPosition.y = y; }
    void SetZ(float z) { mPosition.z = z; }

    void SetR(float r) { mColor.r = r; }
    void SetG(float g) { mColor.g = g; }
    void SetB(float b) { mColor.b = b; }

    void SetU(float u) { mUV.u = u; }
    void SetV(float v) { mUV.v = v; }


private:
    Position mPosition;
    Color mColor;
    UV mUV;
};
#endif // VERTEX_H
