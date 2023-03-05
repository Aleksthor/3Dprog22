#ifndef CURVEO1_H
#define CURVEO1_H

#include "visualobject.h"

class CurveO1 : public VisualObject
{
public:
    CurveO1();
    CurveO1(std::string string);
    ~CurveO1() override;

    void init(GLint matrixUniform) override;
    void draw() override;
    void draw(QMatrix4x4& transformMatrix) override;

    float f(float x);
};

#endif // CURVEO1_H
