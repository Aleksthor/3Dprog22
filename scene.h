#ifndef SCENE_H
#define SCENE_H
#include <unordered_map>
#include <iostream>
#include <QVector3D>

class GameObject;
class Camera;

class Scene
{
public:
    Scene();
    void init();
    void update();

    GameObject* getObject(std::string name) { return gameObjects[name]; }
    GameObject *addObject(GameObject* object, std::string name);
    void Instantiate(GameObject* gameObject, QVector3D position, std::string name);

    std::unordered_map<std::string, GameObject*> getGameObjects() { return gameObjects; }
    std::unordered_map<std::string, GameObject*> getColliderObjects();
    std::unordered_map<std::string, GameObject*> getPhysicsObjects();

    Camera* getCamera() { return camera; }

    void refreshCamera();

private:
    std::unordered_map<std::string, GameObject*> gameObjects;
    Camera* camera;

};

#endif // SCENE_H
