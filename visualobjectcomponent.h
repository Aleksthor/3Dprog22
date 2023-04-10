#ifndef VISUALOBJECTCOMPONENT_H
#define VISUALOBJECTCOMPONENT_H

#include "component.h"
#include "Structures.h"
#include <QMatrix4x4>
#include "material.h"

class VisualObject;
class Texture;

typedef int GLint;


class VisualObjectComponent : public Component
{
public:
    VisualObjectComponent(VisualObject* object, GameObject* owner, std::string shader = "PlainShader");
    virtual ~VisualObjectComponent() override;

    void awake() override;
    void update() override;

    void setIsActive(bool active) override;
    VisualObject* getObject() { return mObject; }

    void setUseObjectSpace(bool input) { useObjectSpace = input; }
    void setUsingTexture(bool input) { usingTexture = input; }
    void setTexture(Texture* tex);
    void setMaterial(Material material);
    void setColor(QVector3D color);
    void setColor(Color color);

private:
    void init(GLint mMatrixUniform);
    void render(QMatrix4x4& transformMatrix);


private:
    std::string shaderName;
    VisualObject* mObject;
    bool useObjectSpace;
    bool usingTexture;
    Texture* texture;
    Material material;
};

#endif // VISUALOBJECTCOMPONENT_H
