#ifndef TETRAEDER_H
#define TETRAEDER_H

#include "VisualObject.h"

class Tetraeder : public VisualObject
{
public:
    Tetraeder();
    ~Tetraeder() override;
    void init(GLint matrixUniform) override;
    void draw() override;
    void draw(QMatrix4x4& transformMatrix) override;

private:
    QVector2D rotatePoint(QVector2D point, float angle);
};

#endif // TETRAEDER_H
