#include "physicsspherecollider.h"
#include "gameobject.h"
#include "physicscomponent.h"
#include "physicsspherecollider.h"
#include "scene.h"



PhysicsSphereCollider::PhysicsSphereCollider(GameObject* _owner, PhysicsComponent *_ownerComponent, float _radius)
{
    owner = _owner;
    ownerComponent = _ownerComponent;
    radius = _radius;
}

PhysicsSphereCollider::~PhysicsSphereCollider()
{

}

void PhysicsSphereCollider::awake()
{

}

void PhysicsSphereCollider::update()
{
    std::unordered_map<std::string, GameObject *> objects = owner->getWorld()->getPhysicsObjects();

    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        if ((*it).second != owner)
        {
            float distance = (owner->getPosition3D()).distanceToPoint((*it).second->getPosition3D());

            PhysicsComponent* comp = (*it).second->getPhysicsComponent();
            Collider* col = comp->getPhysicsCollider();
            PhysicsSphereCollider* sphere = (PhysicsSphereCollider*)col;
            float otherRadius = sphere->radius;

            if (distance < radius + otherRadius)
            {
                comp->collission((*it).second, (*it).second->getPhysicsComponent());
                (*it).second->getPhysicsComponent()->collission(owner, ownerComponent);
            }
        }
    }
}
