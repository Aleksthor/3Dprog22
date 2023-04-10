#include "vertex.h"

Vertex::Vertex()
    : mPosition (Position()), mNormal(QVector3D()), mUV(UV())
{

}
Vertex::Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v)
    : mPosition (Position(x,y,z)), mNormal(QVector3D(nx,ny,nz)), mUV(UV(u,v))
{

}
Vertex::Vertex(Position position, QVector3D normal, UV uv)
    : mPosition(position), mNormal(normal), mUV(uv)
{

}
Vertex::Vertex(float x, float y, float z, float nx, float ny, float nz)
    : mPosition (Position(x,y,z)), mNormal(QVector3D(nx,ny,nz)), mUV(UV())
{

}
Vertex::Vertex(Position position, QVector3D normal)
    : mPosition(position), mNormal(normal), mUV(UV())
{

}

Vertex::Vertex(Position position, Color normal)
    : mPosition(position), mNormal(QVector3D(normal.r,normal.g,normal.b)), mUV(UV())
{

}

Vertex::Vertex(QVector3D position, QVector3D normal)
    : mPosition(Position(position.x(), position.y(), position.z())), mNormal(normal), mUV(UV())
{

}

Vertex::Vertex(QVector3D position, Color color)
    : mPosition(Position(position.x(), position.y(), position.z())), mNormal(QVector3D(color.r,color.g,color.b)), mUV(UV())
{

}

Vertex::Vertex(QVector3D position, QVector3D normal, UV uv)
    : mPosition(Position(position.x(), position.y(), position.z())), mNormal(normal), mUV(uv)
{

}


std::ostream& operator<< (std::ostream& os, const Vertex& v) {
  os << std::fixed;
  os << "(" << v.mPosition.x << ", " << v.mPosition.y << ", " << v.mPosition.z << ") ";
  os << "(" << v.mNormal.x() << ", " << v.mNormal.y() << ", " << v.mNormal.z() << ") ";
  os << "(" << v.mUV.u << ", " << v.mUV.v << ") ";
  return os;
}
std::istream& operator>> (std::istream& is, Vertex& v) {
// Trenger fire temporære variabler som kun skal lese inn parenteser og komma
  char dum, dum2, dum3, dum4;
  float nx = v.mNormal.x();
  float ny = v.mNormal.y();
  float nz = v.mNormal.z();
  is >> dum >> v.mPosition.x >> dum2 >> v.mPosition.y >> dum3 >> v.mPosition.z  >> dum4;
  is >> dum >> nx >> dum2 >> ny  >> dum3 >> nz >> dum4;
  is >> dum >> v.mUV.u >> dum2 >> v.mUV.v >> dum3;
  return is;
}
