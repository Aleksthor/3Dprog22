#ifndef CURVEO1_H
#define CURVEO1_H

#include "visualobject.h"

class CurveO1 : public VisualObject
{
public:
    CurveO1();
    CurveO1(std::string string);
    ~CurveO1() override;

    void readFile(std::string filnavn);
    void init(GLint matrixUniform) override;
    void draw() override;

    float f(float x);
};

#endif // CURVEO1_H
