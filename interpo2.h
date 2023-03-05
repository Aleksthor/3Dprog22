#ifndef INTERPO2_H
#define INTERPO2_H

#include "visualobject.h"

class InterpO2 : public VisualObject
{
public:
    InterpO2();
    ~InterpO2() override;


    void init(GLint matrixUniform) override;
    void draw() override;
    void draw(QMatrix4x4& transformMatrix) override;

private:
    QMatrix4x4 A;
    QMatrix4x4 IA;
    QVector4D B;
    QVector4D X;
};

#endif // INTERPO2_H
