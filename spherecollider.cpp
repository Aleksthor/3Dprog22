#include "spherecollider.h"
#include "gameobject.h"
#include "scene.h"
#include "renderwindow.h"
#include "octahedron.h"
#include "shader.h"
#include "uniforms.h"
#include "logger.h"

SphereCollider::SphereCollider(GameObject* _owner, float _radius)
{
    owner = _owner;
    offset = QVector3D(0,0,0);
    radius = _radius;
    owner->SetCollissionActive(true);
    owner->setCollider(this);
    owner->AddComponent(this);

    renderOutline = false;
    outline = new Octahedron(radius, 2);
    Octahedron* octa = (Octahedron*)outline;
    octa->setRenderFrame(true);
}

SphereCollider::SphereCollider(GameObject* _owner, float _radius, QVector3D relativePos)
{           
    owner = _owner;
    offset = relativePos;
    radius = _radius;
    owner->SetCollissionActive(true);
    owner->setCollider(this);
    owner->AddComponent(this);

    renderOutline = false;
    outline = new Octahedron(radius, 2);
    Octahedron* octa = (Octahedron*)outline;
    octa->setRenderFrame(true);

}

SphereCollider::~SphereCollider()
{

}

void SphereCollider::awake()
{
    Shader* shader = owner->getWorld()->getShader("PlainShader");
    shader->uploadMaterial(Material::whitePlastic);
    GLint modelUnifrom = shader->getUniform()->mMmatrixUniform;
    outline->init(modelUnifrom);
    //outline->scale(QVector3D(radius, radius, radius));

}

void SphereCollider::update()
{

    if (renderOutline)
    {
        Shader* shader = owner->getWorld()->getShader("PlainShader");
        shader->uploadMaterial(Material::whitePlastic);
        outline->draw(owner->transform->getMatrix());
    }

    std::unordered_map<std::string, GameObject *> objects = owner->getWorld()->getColliderObjects();

    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        if ((*it).second != owner)
        {

            float distance = (owner->getPosition3D() + offset).distanceToPoint((*it).second->getPosition3D());

            Collider* col = (*it).second->getCollider();
            SphereCollider* sphere = (SphereCollider*)col;
            float otherRadius = sphere->radius;

            if (distance < radius + otherRadius)
            {
                owner->collission((*it).second);
                (*it).second->collission(owner);
            }
        }
    }
}


