#ifndef NPCO2_H
#define NPCO2_H

#include "gameobject.h"

class VisualObjectComponent;
class Parabel;

class NPCO2 : public GameObject
{
public:
    NPCO2();
    ~NPCO2() override;

    VisualObjectComponent* Mesh;

    void awake() override;
    void update(float deltaTime) override;

private:
    float NPCX;
    bool NPCdirection;
    Parabel* parabel;

};

#endif // NPCO2_H
