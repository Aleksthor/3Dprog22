#ifndef POINTSO2_H
#define POINTSO2_H

#include "visualobject.h"

class PointsO2 : public VisualObject
{
public:
    PointsO2();
    ~PointsO2() override;


    void init(GLint matrixUniform) override;
    void draw() override;
    void draw(QMatrix4x4& transformMatrix) override;
};

#endif // POINTSO2_H
