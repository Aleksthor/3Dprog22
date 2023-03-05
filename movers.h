#ifndef MOVERS_H
#define MOVERS_H

#include "gameobject.h"

class VisualObjectComponent;
class PhysicsComponent;

class Movers : public GameObject
{
public:
    Movers();
    Movers(QVector3D position);
    ~Movers() override;

    VisualObjectComponent* mesh;
    VisualObjectComponent* line;
    PhysicsComponent* physics;

    void awake() override;
    void update() override;



private:
    QVector3D position;
    float radius;
};

#endif // MOVERS_H
