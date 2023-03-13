#ifndef LINE_H
#define LINE_H

#include "visualobject.h"

class Line : public VisualObject
{
public:
    Line(Vertex v1, Vertex v2);
    Line(std::vector<QVector3D> points);
    ~Line() override;

    void init(GLint matrixUniform) override;
    void draw() override;
    void draw(QMatrix4x4 transformMatrix) override;

    void addVertex(Vertex v);

    void updateLine(QVector3D v1, QVector3D v2);
    void updateLine(std::vector<QVector3D> p);
};

#endif // LINE_H
