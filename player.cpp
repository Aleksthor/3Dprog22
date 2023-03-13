#include "player.h"
#include "cube.h"
#include "visualobjectcomponent.h"
#include "spherecollider.h"
#include "landscape.h"
#include "logger.h"
#include "scene.h"
#include "texture.h"

Player::Player() : GameObject()
{
    Mesh = new VisualObjectComponent(new Cube(), this,"TextureShader");
    Mesh->setTexture(new Texture("../3Dprog22/image.png",Mesh));
    setRootComponent(Mesh);
    Mesh->getObject()->scale(0.5);
    //Mesh->setIsActive(false);

    Collider = new SphereCollider(this,0.5);
    Collider->setupAttachment(Mesh);
    Collider->setRenderOutline(true);


    setName("Player");
}

Player::~Player()
{

}

void Player::awake()
{
    GameObject::awake();
}

void Player::update(float deltaTime)
{
    GameObject::update(deltaTime);

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
    Logger::getInstance()->logText("Player Colliding with " + other->getName() );
}
