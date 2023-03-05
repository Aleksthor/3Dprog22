#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "component.h"
#include <QVector3D>

class GameObject;
class Transform;
class Collider;

class PhysicsComponent : public Component
{
public:
    PhysicsComponent(GameObject* owner);

    ~PhysicsComponent() override;
    virtual void awake() override;
    virtual void update() override;
    void collission(GameObject* other, PhysicsComponent* otherComp);



    void addForce(QVector3D force);
    void setUsingGravity(bool input) { gravity = input; }

    void addFriction();
    void addDrag();
    void addDrag(float dragC);

    void setVelocity(QVector3D vec) { velocity = vec; }


    void attract(PhysicsComponent* other);
    void setUsingGravitationalAttraction(bool input) { gravityToOtherObjects = input; }

    void setMass(float _mass);
    float getMass() { return mass;}

    void setPhysicsCollider(Collider* collider) { physicsCollider = collider; }
    Collider* getPhysicsCollider() { return physicsCollider; }

    static QVector3D randomVector();
    static QVector3D createVector3D(float zAngle, float xAngle );


private:
    QVector3D velocity;
    QVector3D acceleration;
    float mass;

    float mu;
    float dragC;

    bool gravity;
    bool gravityToOtherObjects;
    QVector3D gravityVector;
    float UGC;

    Transform* transform;
    Collider* physicsCollider;



    void addGravity();
    void gravitationalAttraction();

};

#endif // PHYSICSCOMPONENT_H
