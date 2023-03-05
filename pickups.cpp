#include "pickups.h"
#include "octahedron.h"
#include "visualobjectcomponent.h"
#include "spherecollider.h"
#include "logger.h"

Pickups::Pickups()
{
    Mesh = new VisualObjectComponent(new Octahedron(5), this);
    setRootComponent(Mesh);
    Collider = new SphereCollider(this, 1);
    Collider->setupAttachment(Mesh);
    setName("Pickups1");
}

Pickups::~Pickups()
{

}

void Pickups::awake()
{
    GameObject::awake();
}

void Pickups::update()
{
    GameObject::update();
}

void Pickups::collission(GameObject *other)
{
    if (other->getName() == "Player")
        this->setActive(false);
}
