#ifndef OCTAHEDRON_H
#define OCTAHEDRON_H

#include "visualobject.h"

class Vertex;
class SphereCollider;

class Octahedron : public VisualObject
{
public:
   Octahedron(int n=0);
   ~Octahedron();

   SphereCollider* collider;

   void init(GLint matrixUniform) override;
   void draw() override;
   void draw(QMatrix4x4& transformMatrix) override;

private:
   int m_rekursjoner;
   int m_indeks;               // brukes i rekursjon, til å bygge m_vertices
   void lagTriangel(const QVector3D& v1, const QVector3D& v2, const QVector3D& v3);
   void subDivide(const QVector3D& a, const QVector3D& b, const QVector3D& c, int n);
   void oktaederUnitBall();
};

#endif // OCTAHEDRON_H
