#include "scene.h"
#include "gameobject.h"
#include "camera.h"
#include "renderwindow.h"


Scene::Scene()
{
    camera = new Camera();
}

void Scene::init()
{
    for (auto it = gameObjects.begin(); it!= gameObjects.end();it++)
    {
        it->second->awake();
    }
    camera->init(RenderWindow::instance->GetPMatrixUniform(),RenderWindow::instance->GetVMatrixUniform());
    camera->perspective(80,RenderWindow::instance->width()/RenderWindow::instance->height(), 0.1f,1000);
}

void Scene::update()
{
    camera->update();
    for (auto it = gameObjects.begin(); it!= gameObjects.end();it++)
        (*it).second->update();
}

GameObject *Scene::addObject(GameObject *object, std::string name)
{
    gameObjects.insert(std::pair<std::string,GameObject*>{name, object});
    object->setWorld(this);
    return gameObjects[name];
}

void Scene::Instantiate(GameObject *gameObject, QVector3D position, std::string name)
{
    if (gameObjects[name] == nullptr)
    {
        addObject(gameObject,name);
        gameObject->setPosition(position);
        return;
    }
    else
    {
        int i = 1;
        bool check = false;
        while(!check)
        {
            if(gameObjects[name + std::to_string(i)] != nullptr)
            {
                i++;
            }
            else
            {
                check = true;
            }
        }
        addObject(gameObject,name+ std::to_string(i));
        gameObject->setPosition(position);
        gameObject->awake();
    }

}

std::unordered_map<std::string, GameObject *> Scene::getColliderObjects()
{
    std::unordered_map<std::string, GameObject *> objects;
    for (auto it = gameObjects.begin(); it!= gameObjects.end();it++)
    {
        if (it->second->CollissionActive())
        {
            objects.insert((*it));
        }

    }
    return objects;
}

std::unordered_map<std::string, GameObject *> Scene::getPhysicsObjects()
{
    std::unordered_map<std::string, GameObject *> objects;
    for (auto it = gameObjects.begin(); it!= gameObjects.end();it++)
    {
        if (it->second->simulatingPhysics())
        {
            objects.insert((*it));
        }

    }
    return objects;
}

void Scene::refreshCamera()
{
    camera->perspective(80,RenderWindow::instance->width()/RenderWindow::instance->height(), 0.1f,1000);
}
