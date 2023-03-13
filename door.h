#ifndef DOOR_H
#define DOOR_H

#include "gameobject.h"

class VisualObjectComponent;
class SphereCollider;

class Door : public GameObject
{
public:
    Door();
    virtual ~Door() override;

    VisualObjectComponent* Mesh;
    SphereCollider* Collider;

    void awake() override;
    void update(float deltaTime) override;
    void collission(GameObject* other) override;

private:
   bool openDoor;
   QVector3D doorClosedPos;
   QVector3D doorOpenPos;

   QVector3D Pos;

};

#endif // DOOR_H
