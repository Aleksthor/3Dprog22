#ifndef LINE_H
#define LINE_H

#include "visualobject.h"

class Line : public VisualObject
{
public:
    Line(Vertex v1, Vertex v2);
    ~Line() override;

    void init(GLint matrixUniform) override;
    void draw() override;
    void draw(QMatrix4x4& transformMatrix) override;

    void addVertex(Vertex v);
};

#endif // LINE_H
