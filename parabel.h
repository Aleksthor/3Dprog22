#ifndef PARABEL_H
#define PARABEL_H

#include "visualobject.h"

class Parabel : public VisualObject
{
public:
    Parabel();
    ~Parabel() override;


    void init(GLint matrixUniform) override;
    void draw() override;
    void draw(QMatrix4x4 transformMatrix) override;
    float f(float x) { return ((float)IBATy[0] * x * x) + ((float)IBATy[1] * x) +(float)IBATy[2]; }

private:
    std::vector<double> y;
    std::vector<std::vector<double>> A;
    std::vector<std::vector<double>> AT;
    std::vector<std::vector<double>> ATA;
    std::vector<std::vector<double>> IB;
    std::vector<double> ATy;
    std::vector<double> IBATy;


    double a1, b1, c1;
    double det;
};

#endif // PARABEL_H
