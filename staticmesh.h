#ifndef STATICMESH_H
#define STATICMESH_H

#include "visualobject.h"
class Texture;

class StaticMesh : public VisualObject
{
public:
    StaticMesh(char* path);

    virtual ~StaticMesh() override;
    virtual void init(GLint matrixUniform) override;
    virtual void draw() override;
    virtual void draw(QMatrix4x4 transformMatrix) override;

    void loadModel(char* path);

};

#endif // STATICMESH_H
