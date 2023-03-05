#ifndef PHYSICSSPHERECOLLIDER_H
#define PHYSICSSPHERECOLLIDER_H

#include "collider.h"

class PhysicsComponent;

class PhysicsSphereCollider : public Collider
{
public:
    PhysicsSphereCollider(GameObject* _owner, PhysicsComponent *_ownerComponent, float _radius);
    virtual ~PhysicsSphereCollider() override;


    void awake() override;
    void update() override;

    void setRadius(float r) { radius = r; }

    float radius;
    PhysicsComponent* ownerComponent;

};
#endif // PHYSICSSPHERECOLLIDER_H
