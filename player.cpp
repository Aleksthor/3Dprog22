#include "player.h"
#include "cube.h"
#include "visualobjectcomponent.h"
#include "spherecollider.h"
#include "landscape.h"
#include "logger.h"
#include "scene.h"


Player::Player()
{
    Mesh = new VisualObjectComponent(new Cube(), this);
    setRootComponent(Mesh);


    Collider = new SphereCollider(this, 0.3f);
    Collider->setupAttachment(Mesh);


    setName("Player");
}

Player::~Player()
{

}

void Player::awake()
{
    GameObject::awake();
}

void Player::update()
{
    GameObject::update();

    QVector3D posNow = getPosition3D();

    if (getWorld()->getObject("Landscape") != nullptr)
    {
        // Casting to get the object
        VisualObjectComponent* VO =  (VisualObjectComponent*)getWorld()->getObject("Landscape")->getRootComponent();
        Landscape* landscape = (Landscape*)VO->getObject();

        // Set position
        float z = landscape->f(posNow.x(), posNow.y());
        posNow.setZ(z);
        setPosition(posNow);
    }


}

void Player::collission(GameObject *other)
{
    Logger::getInstance()->logText("Player Colliding");
}
