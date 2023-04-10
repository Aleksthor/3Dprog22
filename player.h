#ifndef PLAYER_H
#define PLAYER_H

#include "gameobject.h"

class VisualObjectComponent;
class SphereCollider;
class Landscape;

class Player : public GameObject
{
public:
    Player();
    ~Player() override;

    VisualObjectComponent* Mesh;

    SphereCollider* Collider;

    void awake() override;
    void update(float deltaTime) override;
    void collission(GameObject* other) override;

    void CheckNewCurrentIndex();
    bool CheckIndex(int index);

    Landscape* landscape;
    int currentIndex;
};

#endif // PLAYER_H
