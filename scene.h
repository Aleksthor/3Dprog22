#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <QVector3D>
#include <QElapsedTimer>
#include <QOpenGLFunctions_4_1_Core>
#include <unordered_map>

class Shader;
class GameObject;
class Camera;


class Scene : QOpenGLFunctions_4_1_Core
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
    Shader* getShader(std::string shader) { return Shaders[shader]; }

    void refreshCamera();
    std::unordered_map<std::string, Shader*> getShaders() { return Shaders; }
    void runProgram(std::string shader);

    QVector3D getLightPos() { return lightPos; }


private:
    std::unordered_map<std::string, GameObject*> gameObjects;
    GameObject* cubeMap;
    Camera* camera;
    GameObject* lightSource;

    QElapsedTimer DeltaTime;
    std::unordered_map<std::string,Shader*> Shaders;    //holds pointer the GLSL shader program

    QVector3D lightPos;

};

#endif // SCENE_H
