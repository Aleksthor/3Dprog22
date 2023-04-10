#include "player.h"
#include "cube.h"
#include "visualobjectcomponent.h"
#include "spherecollider.h"
#include "landscape.h"
#include "logger.h"
#include "scene.h"
#include "texture2d.h"
#include "octahedron.h"
#include "mymath.h"

Player::Player() : GameObject()
{
    Mesh = new VisualObjectComponent(new Cube(), this);
    setRootComponent(Mesh);
    Mesh->getObject()->scale(0.5);
    Mesh->setMaterial(Material::emerald);
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

    if (getWorld()->getObject("Landscape") != nullptr)
    {
        // Casting to get the object
        VisualObjectComponent* VO =  (VisualObjectComponent*)getWorld()->getObject("Landscape")->getRootComponent();
        landscape = (Landscape*)VO->getObject();

        QVector2D vertexIndex = landscape->GetVertexPos(transform->getPosition3D());


        // My own safety check, -10 means error
        if (vertexIndex.x() == -10) return;

        int index = vertexIndex.x() + (landscape->width * vertexIndex.y());

        currentIndex = index;
        QVector3D Bary1 = MyMath::Bary(transform->getPosition2D(),landscape->GetVertex2D(index), landscape->GetVertex2D(index + 1), landscape->GetVertex2D(index + landscape->width));
        QVector3D Bary2 = MyMath::Bary(transform->getPosition2D(),landscape->GetVertex2D(index + 1), landscape->GetVertex2D(index + landscape->width + 1), landscape->GetVertex2D(index + landscape->width));


        if (Bary1.x() >= 0.f && Bary1.x() <= 1.f && Bary1.y() >= 0.f && Bary1.y() <= 1.f  && Bary1.y() >= 0.f && Bary1.y() <= 1.f )
        {
            QVector3D P = landscape->GetVertex(index);
            QVector3D Q = landscape->GetVertex(index + 1);
            QVector3D R = landscape->GetVertex(index + landscape->width);

            transform->setPosition(transform->getX(), transform->getY(), Bary1.x() * P.z() + Bary1.y() * Q.z() + Bary1.z() * R.z());
        }
        if (Bary2.x() >= 0.f && Bary2.x() <= 1.f && Bary2.y() >= 0.f && Bary2.y() <= 1.f  && Bary2.y() >= 0.f && Bary2.y() <= 1.f )
        {
            QVector3D P = landscape->GetVertex(index + 1);
            QVector3D Q = landscape->GetVertex(index + landscape->width + 1);
            QVector3D R = landscape->GetVertex(index + landscape->width);

            transform->setPosition(transform->getX(), transform->getY(), Bary1.x() * P.z() + Bary1.y() * Q.z() + Bary1.z() * R.z());
        }
        std::cout << "Bary1: " + std::to_string(Bary1.x()) + "," + std::to_string(Bary1.y())+ "," + std::to_string(Bary1.z())<< std::endl;
        std::cout << "Bary2: " + std::to_string(Bary2.x()) + "," + std::to_string(Bary2.y())+ "," + std::to_string(Bary2.z())<< std::endl;
    }
}

void Player::update(float deltaTime)
{
    GameObject::update(deltaTime);

    QVector3D Bary1 = MyMath::Bary(transform->getPosition2D(),landscape->GetVertex2D(currentIndex), landscape->GetVertex2D(currentIndex + 1), landscape->GetVertex2D(currentIndex + landscape->width));
    QVector3D Bary2 = MyMath::Bary(transform->getPosition2D(),landscape->GetVertex2D(currentIndex + 1), landscape->GetVertex2D(currentIndex + landscape->width + 1), landscape->GetVertex2D(currentIndex + landscape->width));

    bool isHere = false;
    if (Bary1.x() >= 0.f && Bary1.x() <= 1.f && Bary1.y() >= 0.f && Bary1.y() <= 1.f  && Bary1.y() >= 0.f && Bary1.y() <= 1.f )
    {
        QVector3D P = landscape->GetVertex(currentIndex);
        QVector3D Q = landscape->GetVertex(currentIndex + 1);
        QVector3D R = landscape->GetVertex(currentIndex + landscape->width);
        isHere = true;
        transform->setPosition(transform->getX(), transform->getY(), Bary1.x() * P.z() + Bary1.y() * Q.z() + Bary1.z() * R.z());
    }
    if (Bary2.x() >= 0.f && Bary2.x() <= 1.f && Bary2.y() >= 0.f && Bary2.y() <= 1.f  && Bary2.y() >= 0.f && Bary2.y() <= 1.f )
    {
        QVector3D P = landscape->GetVertex(currentIndex + 1);
        QVector3D Q = landscape->GetVertex(currentIndex + landscape->width + 1);
        QVector3D R = landscape->GetVertex(currentIndex + landscape->width);
        isHere = true;
        transform->setPosition(transform->getX(), transform->getY(), Bary1.x() * P.z() + Bary1.y() * Q.z() + Bary1.z() * R.z());
    }
    if (!isHere)
    {
        CheckNewCurrentIndex();
    }




}

void Player::collission(GameObject *other)
{
    Logger::getInstance()->logText("Player Colliding with " + other->getName() );
}

void Player::CheckNewCurrentIndex()
{


    // South
    int newIndex = currentIndex - landscape->width;
    if (newIndex >= 0)
    {
        if (CheckIndex(newIndex) == true)
        {
            currentIndex = newIndex;
            return;
        }
    }

    // South East
    newIndex = currentIndex - landscape->width + 1;
    if (newIndex >= 0 && newIndex % landscape->width != 0)
    {
        if (CheckIndex(newIndex) == true)
        {
            currentIndex = newIndex;
            return;
        }
    }

    // East
    newIndex = currentIndex + 1;
    if (newIndex <= landscape->width * landscape->height && newIndex % landscape->width != 0)
    {
        if (CheckIndex(newIndex) == true)
        {
            currentIndex = newIndex;
            return;
        }
    }
    // North East
    newIndex = currentIndex + 1 + landscape->width;
    if (newIndex <= landscape->width * landscape->height && newIndex % landscape->width != 0)
    {
        if (CheckIndex(newIndex) == true)
        {
            currentIndex = newIndex;
            return;
        }
    }
    // North
    newIndex = currentIndex + landscape->width;
    if (newIndex <= landscape->width * landscape->height && newIndex % landscape->width != 0)
    {
        if (CheckIndex(newIndex) == true)
        {
            currentIndex = newIndex;
            return;
        }
    }
    // North West
    newIndex = currentIndex + landscape->width - 1;
    if (newIndex <= landscape->width * landscape->height && newIndex % landscape->width != landscape->width - 1)
    {
        if (CheckIndex(newIndex) == true)
        {
            currentIndex = newIndex;
            return;
        }
    }
    // West
    newIndex = currentIndex - 1;
    if (newIndex <= landscape->width * landscape->height && newIndex % landscape->width != landscape->width - 1)
    {
        if (CheckIndex(newIndex) == true)
        {
            currentIndex = newIndex;
            return;
        }
    }
    // South West
    newIndex = currentIndex - 1 - landscape->width;
    if (newIndex <= landscape->width * landscape->height && newIndex % landscape->width != landscape->width - 1)
    {
        if (CheckIndex(newIndex) == true)
        {
            currentIndex = newIndex;
            return;
        }
    }

    QVector2D vertexIndex = landscape->GetVertexPos(transform->getPosition3D());


    // My own safety check, -10 means error
    if (vertexIndex.x() == -10) return;

    int index = vertexIndex.x() + (landscape->width * vertexIndex.y());

    currentIndex = index;


}

bool Player::CheckIndex(int index)
{
    QVector3D Bary1 = MyMath::Bary(transform->getPosition2D(),landscape->GetVertex2D(index), landscape->GetVertex2D(index + 1), landscape->GetVertex2D(index + landscape->width));
    QVector3D Bary2 = MyMath::Bary(transform->getPosition2D(),landscape->GetVertex2D(index + 1), landscape->GetVertex2D(index + landscape->width + 1), landscape->GetVertex2D(index + landscape->width));

    if (Bary1.x() >= 0.f && Bary1.x() <= 1.f && Bary1.y() >= 0.f && Bary1.y() <= 1.f  && Bary1.y() >= 0.f && Bary1.y() <= 1.f )
    {
        return true;
    }
    if (Bary2.x() >= 0.f && Bary2.x() <= 1.f && Bary2.y() >= 0.f && Bary2.y() <= 1.f  && Bary2.y() >= 0.f && Bary2.y() <= 1.f )
    {
        return true;
    }


    return false;
}
