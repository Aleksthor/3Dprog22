#ifndef BASICMESH_H
#define BASICMESH_H

#include "gameobject.h"

class VisualObjectComponent;
class VisualObject;

class BasicMesh : public GameObject
{
public:
    BasicMesh(VisualObject* Object, std::string name);
    BasicMesh(VisualObject* Object, std::string name, std::string shader);
    ~BasicMesh() override;

    VisualObjectComponent* Mesh;

    void awake() override;
    void update(float deltaTime) override;
};

#endif // BASICMESH_H
