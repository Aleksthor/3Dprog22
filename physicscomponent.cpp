#include "physicscomponent.h"
#include "gameobject.h"
#include "physicsspherecollider.h"
#include "renderwindow.h"
#include <cmath>
#include "scene.h"

PhysicsComponent::PhysicsComponent(GameObject *owner)
{
    SetOwner(owner);
    owner->AddComponent(this);
    owner->setSimulatePhysics(true);
    owner->setPhysicsComponent(this);

    transform = owner->transform;
    physicsCollider = new PhysicsSphereCollider(owner, this,1.f);
    physicsCollider->setupAttachment(this);
}

PhysicsComponent::~PhysicsComponent()
{

}

void PhysicsComponent::awake()
{
    physicsCollider->awake();

    mass = 4 * M_PI;
    acceleration = QVector3D();
    velocity = QVector3D();
    gravity = false;
    gravityToOtherObjects = false;
    gravityVector = QVector3D(0,0,-1.f);

    mu = 0.1f;
    dragC = 0.1f;
    UGC = 1.f;
}

void PhysicsComponent::update()
{
    QVector3D pos = transform->getPosition3D();


    //Gravity Calculations
    addGravity();
    gravitationalAttraction();

    // Velocity
    velocity += acceleration;

    // Change Pos
    pos += velocity;
    transform->setPosition(pos);
    acceleration = QVector3D(0,0,0);
    physicsCollider->update();
}

void PhysicsComponent::collission(GameObject* other, PhysicsComponent* otherComp)
{

}

void PhysicsComponent::addForce(QVector3D force)
{
    force *= 0.005f;
    acceleration += force / mass;
}

void PhysicsComponent::addFriction()
{
    QVector3D force = velocity;
    force.normalize();
    force *= -1;

    float normal = mass;

    force *= mu * normal;
    addForce(force);
}

void PhysicsComponent::addDrag()
{
    QVector3D force = velocity;
    force.normalize();
    force *= -0.5f;

    float speed = velocity.length();

    force *= speed * dragC * speed;
    addForce(force);
}

void PhysicsComponent::addDrag(float _dragC)
{
    QVector3D force = velocity;
    force.normalize();
    force *= -0.5f;

    float speed = velocity.length();

    force *= speed * _dragC * speed;
    addForce(force);
}

void PhysicsComponent::attract(PhysicsComponent *other)
{
    QVector3D direction = GetOwner()->getPosition3D() - other->GetOwner()->getPosition3D();
    float distanceSq = direction.length() * direction.length();
    distanceSq = std::clamp(distanceSq, 100.f,100000.f);
    direction.normalize();

    float strength = mass * other->getMass();
    strength *= UGC;
    strength /= distanceSq;

    direction *= strength;
    other->addForce(direction);

}


void PhysicsComponent::setMass(float _mass)
{
    mass = _mass;
    PhysicsSphereCollider* col = (PhysicsSphereCollider*)physicsCollider;
    if (col != nullptr)
    {
        col->setRadius(mass / (M_PI * 4));
    }
}

QVector3D PhysicsComponent::randomVector()
{
    QVector3D vec = QVector3D();
    int angle = std::rand() % 361;

    float radian = (float)angle * (M_PI/180);

    vec.setX((cos(radian) * 1));
    vec.setY((sin(radian) * 1));

    return vec;

}

QVector3D PhysicsComponent::createVector3D(float zAngle, float xAngle)
{
    QVector3D vec = QVector3D();

    vec.setX(sin(zAngle)*cos(xAngle));
    vec.setY(sin(zAngle)*sin(xAngle));
    vec.setZ(cos(zAngle));

    vec.normalize();
    return vec;
}

void PhysicsComponent::addGravity()
{
    if (gravity)
    {
        QVector3D force = gravityVector * mass;
        addForce(force);
    }
}

void PhysicsComponent::gravitationalAttraction()
{
    if (gravityToOtherObjects)
    {
        std::unordered_map<std::string, GameObject *> objects = GetOwner()->getWorld()->getPhysicsObjects();
        for (auto it = objects.begin(); it != objects.end(); it++)
        {
            if ((*it).second != GetOwner())
            {
                (*it).second->getPhysicsComponent()->attract(this);
            }
        }
    }
}
