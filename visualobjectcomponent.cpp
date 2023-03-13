#include "visualobjectcomponent.h"
#include "visualobject.h"
#include "gameobject.h"
#include "transform.h"
#include "scene.h"
#include "shader.h"
#include "uniforms.h"
#include "texture.h"

VisualObjectComponent::VisualObjectComponent(VisualObject *object, GameObject* owner, std::string shader)
    : mObject(object), shaderName(shader)
{
    SetOwner(owner);
    owner->AddComponent(this);
    useObjectSpace = true;
    usingTexture = false;
    texture = nullptr;
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

    if (usingTexture)
    {
        if (useObjectSpace)
        {
            if(mObject != nullptr)
            {
                if (texture != nullptr)
                {
                    texture->update( GetOwner()->getWorld()->getShader(shaderName)->getUniform()->mTextureSampler);
                }

                mObject->draw(transformMatrix);
            }
        }
        else
        {
            if(mObject != nullptr)
            {
                mObject->draw();
            }
        }
    }
    else
    {
        if (useObjectSpace)
        {
            if(mObject != nullptr)
            {
                mObject->draw(transformMatrix);
            }
        }
        else
        {
            if(mObject != nullptr)
            {
                mObject->draw();
            }
        }
    }


}
