#ifndef TETRAEDER_H
#define TETRAEDER_H

#include "VisualObject.h"

class Tetraeder : public VisualObject
{
public:
    Tetraeder();
    Tetraeder(Position pos, Vector3 scale);
    virtual ~Tetraeder();
    virtual void init(GLint matrixUniform);
    virtual void draw();

private:
    QVector2D rotatePoint(QVector2D point, float angle);
};

#endif // TETRAEDER_H
