#ifndef PICKUPS_H
#define PICKUPS_H

#include "gameobject.h"

class VisualObjectComponent;
class SphereCollider;

class Pickups : public GameObject
{
public:
    Pickups();
    virtual ~Pickups() override;

    VisualObjectComponent* Mesh;

    SphereCollider* Collider;

    void awake() override;
    void update() override;
    void collission(GameObject* other) override;
};

#endif // PICKUPS_H
