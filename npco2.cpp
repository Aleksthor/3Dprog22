#include "npco2.h"
#include "visualobjectcomponent.h"
#include "tetraeder.h"
#include "parabel.h"

NPCO2::NPCO2()
{
    setName("NPC");

    Mesh = new VisualObjectComponent(new Tetraeder(), this);
    setRootComponent(Mesh);

    parabel = new Parabel();

    NPCX = 0;
    NPCdirection = false;

    Mesh->getObject()->setPosition(QVector3D(NPCX,parabel->f(NPCX),1));

}

NPCO2::~NPCO2()
{

}

void NPCO2::awake()
{
    GameObject::awake();
}

void NPCO2::update()
{
    GameObject::update();
    transform->setPosition(QVector3D(0,0,0));

    if (NPCdirection)
    {
        NPCX += 0.01f;
        if (NPCX > 5)
        {
            NPCdirection = false;
        }
    }
    else
    {
        NPCX -= 0.01f;
        if (NPCX < -5)
        {
            NPCdirection = true;
        }
    }

    Mesh->getObject()->setPosition(QVector3D(NPCX,parabel->f(NPCX),1));
}
