#include "basicmesh.h"
#include "visualobject.h"
#include "visualobjectcomponent.h"

BasicMesh::BasicMesh(VisualObject *Object, std::string name)
{
    Mesh = new VisualObjectComponent(Object, this);
    setRootComponent(Mesh);
    setName(name);
}

BasicMesh::~BasicMesh()
{

}

void BasicMesh::awake()
{
    GameObject::awake();
}

void BasicMesh::update()
{
    GameObject::update();
}
