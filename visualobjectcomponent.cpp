#include "visualobjectcomponent.h"
#include "visualobject.h"
#include "gameobject.h"
#include "transform.h"
#include "scene.h"
#include "shader.h"
#include "uniforms.h"
#include "texture.h"
#include "material.h"
#include "logger.h"

VisualObjectComponent::VisualObjectComponent(VisualObject *object, GameObject* owner, std::string shader)
    : mObject(object), shaderName(shader)
{
    SetOwner(owner);
    owner->AddComponent(this);
    useObjectSpace = true;
    usingTexture = false;
    texture = nullptr;
    material = Material();
}





VisualObjectComponent::~VisualObjectComponent()
{

}






void VisualObjectComponent::awake()
{
    GetOwner()->getWorld()->runProgram(shaderName);
    Shader* shader = GetOwner()->getWorld()->getShader(shaderName);
    GLint modelUnifrom = shader->getUniform()->mMmatrixUniform;
    init(modelUnifrom);
}





void VisualObjectComponent::update()
{
    GetOwner()->getWorld()->runProgram(shaderName);
    if (shaderName == "PlainShader" || shaderName == "LightShader")
    {
        GetOwner()->getWorld()->getShader(shaderName)->setLightColor(QVector3D(1.f,1.f,1.f));
        GetOwner()->getWorld()->getShader(shaderName)->uploadMaterial(material);
    }

    if (IsActive())
        render(GetOwner()->transform->getMatrix());

}





void VisualObjectComponent::setIsActive(bool active)
{
    if (mObject != nullptr)
    {
        mObject->setActive(active);
    }
}

void VisualObjectComponent::setTexture(Texture *tex)
{
    texture = tex;
    usingTexture = true;
}

void VisualObjectComponent::setMaterial(Material _material)
{
    material = _material;
}

void VisualObjectComponent::setColor(QVector3D color)
{
    material.color = color;
}

void VisualObjectComponent::setColor(Color color)
{
    material.color = QVector3D(color.r,color.g,color.b);
}

void VisualObjectComponent::init(GLint matrixUniform)
{
    if(mObject != nullptr)
    {
        if(texture != nullptr)
        {
            texture->init();
        }
        mObject->init(matrixUniform);
    }
}

void VisualObjectComponent::render(QMatrix4x4& transformMatrix)
{

    if(mObject != nullptr)
    {
        if (texture != nullptr)
        {
            texture->update(GetOwner()->getWorld()->getShader(shaderName)->getUniform()->mTextureSampler);
        }
        mObject->draw(transformMatrix);
    }


}
