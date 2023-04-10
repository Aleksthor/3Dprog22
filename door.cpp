#include "door.h"
#include "visualobjectcomponent.h"
#include "cube.h"
#include "spherecollider.h"
#include "visualobject.h"
#include "renderwindow.h"


Door::Door() : GameObject()
{
    Mesh = new VisualObjectComponent(new Cube(), this, "PlainShader");
    Mesh->setMaterial(Material::gold);
    setRootComponent(Mesh);
    transform->scale(QVector3D(1.f,0.1f,2.f));



    Collider = new SphereCollider(this, 1, QVector3D(0,1,-1));
    Collider->setupAttachment(Mesh);
    setName("Door");

    openDoor = false;
    Pos = QVector3D(0,-7,2);
    transform->setPosition(Pos);
    doorOpenPos = Pos - QVector3D(0,0,3);
}

Door::~Door()
{

}

void Door::awake()
{
    GameObject::awake();
}

void Door::update(float deltaTime)
{
    GameObject::update(deltaTime);

    if (openDoor)
    {
        Pos += QVector3D(0,0,-0.1f);
        setPosition(Pos);

        if (Pos.z() < doorOpenPos.z())
        {
            RenderWindow::instance->changeScene(2);
            openDoor = false;
        }
    }

}

void Door::collission(GameObject *other)
{
    if (other->getName() == "Player")
    {
        if (RenderWindow::Keymap[Qt::Key_E])
        {
            openDoor = true;
        }
    }
}
