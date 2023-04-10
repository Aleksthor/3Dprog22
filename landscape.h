#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include "visualobject.h"
#include "ppm.h"
#include "PerlinNoise.h"

class Landscape : public VisualObject
{
public:
    Landscape(QVector2D bottomLeft, QVector2D topRigh);
    Landscape(std::string fileLocation);
    ~Landscape() override;


    void init(GLint matrixUniform) override;
    void draw() override;
    void draw(QMatrix4x4 transformMatrix) override;

    float f(float x, float y);

    QVector2D GetVertexPos(QVector3D playerPos);

    int mOctaves;
    float mPersitence;
    float mLacunarity;
    float mScale;
    int height;
    int width;
    float Step;
};

#endif // LANDSCAPE_H
