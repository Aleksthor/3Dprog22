#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include "visualobject.h"
#include "ppm.h"
#include "PerlinNoise.h"

class Landscape : public VisualObject
{
public:
    Landscape(QVector2D bottomLeft, QVector2D topRigh);
    ~Landscape() override;

    void update(int _octaves,float _persistance,float _lacunarity,float _scale);

    void init(GLint matrixUniform) override;
    void draw() override;
    void draw(QMatrix4x4 transformMatrix) override;

    float f(float x, float y);
    Color recalc(float z);

    int mOctaves;
    float mPersitence;
    float mLacunarity;
    float mScale;
};

#endif // LANDSCAPE_H
