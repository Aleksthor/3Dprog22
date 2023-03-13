#include "basicmesh.h"
#include "visualobject.h"
#include "visualobjectcomponent.h"

BasicMesh::BasicMesh(VisualObject *Object, std::string name) : GameObject()
{
    Mesh = new VisualObjectComponent(Object, this,"PlainShader");
    setRootComponent(Mesh);
    setName(name);
}
BasicMesh::BasicMesh(VisualObject *Object, std::string name, std::string shader) : GameObject()
{
    Mesh = new VisualObjectComponent(Object, this,shader);
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

void BasicMesh::update(float deltaTime)
{
    GameObject::update(deltaTime);
}
