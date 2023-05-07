#ifndef BSPLINE_H
#define BSPLINE_H

#include "visualobject.h"


class BSpline : public VisualObject
{
public:
    BSpline(std::vector<QVector2D> _points, std::vector<float> _knots);

    virtual ~BSpline() override;
    virtual void init(GLint matrixUniform) override;
    virtual void draw() override;
    virtual void draw(QMatrix4x4 transformMatrix) override;

    float B(int i, int d, float x);

    std::vector<QVector2D> points;
    std::vector<float> knots;
};

#endif // BSPLINE_H
