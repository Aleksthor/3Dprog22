#include "vertex.h"

Vertex::Vertex()
    : mPosition (Position()), mColor(Color()), mUV(UV())
{

}
Vertex::Vertex(float x, float y, float z, float r, float g, float b, float u, float v)
    : mPosition (Position(x,y,z)), mColor(Color(r,g,b)), mUV(UV(u,v))
{

}
Vertex::Vertex(Position position, Color color, UV uv)
    : mPosition(position), mColor(color), mUV(uv)
{

}
Vertex::Vertex(float x, float y, float z, float r, float g, float b)
    : mPosition (Position(x,y,z)), mColor(Color(r,g,b)), mUV(UV())
{

}
Vertex::Vertex(Position position, Color color)
    : mPosition(position), mColor(color), mUV(UV())
{

}

std::ostream& operator<< (std::ostream& os, const Vertex& v) {
  os << std::fixed;
  os << "(" << v.mPosition.x << ", " << v.mPosition.y << ", " << v.mPosition.z << ") ";
  os << "(" << v.mColor.r << ", " << v.mColor.g << ", " << v.mColor.b << ") ";
  os << "(" << v.mUV.u << ", " << v.mUV.v << ") ";
  return os;
}
std::istream& operator>> (std::istream& is, Vertex& v) {
// Trenger fire temporære variabler som kun skal lese inn parenteser og komma
  char dum, dum2, dum3, dum4;
  is >> dum >> v.mPosition.x >> dum2 >> v.mPosition.y >> dum3 >> v.mPosition.z  >> dum4;
  is >> dum >> v.mColor.r >> dum2 >> v.mColor.g  >> dum3 >> v.mColor.b >> dum4;
  is >> dum >> v.mUV.u >> dum2 >> v.mUV.v >> dum3;
  return is;
}
