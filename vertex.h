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
    Vertex(Position position, QVector3D normal, UV uv);

    Vertex(float x, float y, float z, float r, float g, float b);
    Vertex(Position position, QVector3D normal);
    Vertex(Position position, Color normal);
    Vertex(QVector3D position, QVector3D normal);
    Vertex(QVector3D position, QVector3D normal, UV uv);
    Vertex(QVector3D position, Color color);

    Position GetPosition() { return mPosition; }
    QVector3D GetPosition3D() { return QVector3D(mPosition.x,mPosition.y,mPosition.z); }
    QVector2D GetPosition2D() { return QVector2D(mPosition.x,mPosition.y); }
    QVector3D GetColor() { return mNormal; }
    QVector3D GetNormal() { return mNormal; }
    UV GetUV() { return mUV; }

    float GetX() { return mPosition.x; }
    float GetY() { return mPosition.y; }
    float GetZ() { return mPosition.z; }

    float GetNX() { return mNormal.x(); }
    float GetNY() { return mNormal.y(); }
    float GetNZ() { return mNormal.z(); }

    float GetU() { return mUV.u; }
    float GetV() { return mUV.v; }


    void SetPosition(float x, float y, float z) { mPosition = Position(x,y,z); }
    void SetPosition(Position position) { mPosition = position; }


    void SetNormal(QVector3D normal) { mNormal = normal; }

    void SetUV(float u, float v) { mUV = UV(u,v); }
    void SetUV(UV uv) { mUV = uv; }


    void SetX(float x) { mPosition.x = x; }
    void SetY(float y) { mPosition.y = y; }
    void SetZ(float z) { mPosition.z = z; }

    void SetNX(float nx) { mNormal.setX(nx); }
    void SetNY(float ny) { mNormal.setX(ny); }
    void SetNZ(float nz) { mNormal.setX(nz); }

    void SetU(float u) { mUV.u = u; }
    void SetV(float v) { mUV.v = v; }


private:
    Position mPosition;
    QVector3D mNormal;
    UV mUV;


};
#endif // VERTEX_H
