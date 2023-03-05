#ifndef BASICMESH_H
#define BASICMESH_H

#include "gameobject.h"

class VisualObjectComponent;
class VisualObject;

class BasicMesh : public GameObject
{
public:
    BasicMesh(VisualObject* Object, std::string name);
    ~BasicMesh() override;

    VisualObjectComponent* Mesh;

    void awake() override;
    void update() override;
};

#endif // BASICMESH_H
