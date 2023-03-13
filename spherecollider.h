#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "collider.h"
#include <QVector3D>

class VisualObject;

class SphereCollider : public Collider
{
public:
    SphereCollider(GameObject* owner, float radius);
    SphereCollider(GameObject* owner, float radius, QVector3D offset);
    virtual ~SphereCollider() override;

    void awake() override;
    void update() override;

    float radius;
    QVector3D offset;

    void setRenderOutline(bool input) { renderOutline = input; }

private:
    bool renderOutline;
    VisualObject* outline;
};

#endif // SPHERECOLLIDER_H
