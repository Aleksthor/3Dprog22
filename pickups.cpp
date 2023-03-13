#include "pickups.h"
#include "octahedron.h"
#include "visualobjectcomponent.h"
#include "spherecollider.h"
#include "logger.h"

Pickups::Pickups() : GameObject()
{
    Mesh = new VisualObjectComponent(new Octahedron(5), this,"PlainShader");
    setRootComponent(Mesh);


    Collider = new SphereCollider(this, 1);
    Collider->setupAttachment(Mesh);
    Collider->setRenderOutline(true);

    setName("Pickup");
}

Pickups::~Pickups()
{

}

void Pickups::awake()
{
    GameObject::awake();
    //Mesh->getObject()->scale(QVector3D(0.5f,0.5f,0.5f));
}

void Pickups::update(float deltaTime)
{
    GameObject::update(deltaTime);
}

void Pickups::collission(GameObject *other)
{
    if (other->getName() == "Player")
        this->setActive(false);
}
