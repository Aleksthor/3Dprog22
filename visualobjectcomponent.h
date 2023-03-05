#ifndef VISUALOBJECTCOMPONENT_H
#define VISUALOBJECTCOMPONENT_H

#include "component.h"
#include <QMatrix4x4>

class VisualObject;

typedef int GLint;


class VisualObjectComponent : public Component
{
public:
    VisualObjectComponent(VisualObject* object, GameObject* owner);
    virtual ~VisualObjectComponent() override;

    void awake() override;
    void update() override;

    void setIsActive(bool active) override;
    VisualObject* getObject() { return mObject; }

    void setUseObjectSpace(bool input) { useObjectSpace = input; }

private:
    void init(GLint mMatrixUniform);
    void render(QMatrix4x4& transformMatrix);


private:
    VisualObject* mObject;
    bool useObjectSpace;
};

#endif // VISUALOBJECTCOMPONENT_H
