#include "scene.h"
#include "gameobject.h"
#include "camera.h"
#include "renderwindow.h"
#include "shader.h"
#include "uniforms.h"

Scene::Scene()
{
    camera = new Camera();
}

void Scene::init()
{
    initializeOpenGLFunctions();
    //Compile shaders:
    //NB: hardcoded path to files! You have to change this if you change directories for the project.
    //Qt makes a build-folder besides the project folder. That is why we go down one directory
    // (out of the build-folder) and then up into the project folder.
    Shader* shader1 = new Shader("../3Dprog22/plainshader.vert", "../3Dprog22/plainshader.frag");
    Shader* shader2 = new Shader("../3Dprog22/textureshader.vert", "../3Dprog22/textureshader.frag");
    Shaders.insert(std::pair<std::string, Shader*>{"PlainShader", shader1});
    Shaders.insert(std::pair<std::string, Shader*>{"TextureShader", shader2});


    Uniforms* plainUniform = new Uniforms(glGetUniformLocation(Shaders["PlainShader"]->getProgram(), "matrix"),
                                          glGetUniformLocation(Shaders["PlainShader"]->getProgram(), "vmatrix"),
                                          glGetUniformLocation(Shaders["PlainShader"]->getProgram(), "pmatrix"));


    Uniforms* textureUniform = new Uniforms(glGetUniformLocation(Shaders["TextureShader"]->getProgram(), "matrix"),
                                            glGetUniformLocation(Shaders["TextureShader"]->getProgram(), "vmatrix"),
                                            glGetUniformLocation(Shaders["TextureShader"]->getProgram(), "pmatrix"),
                                            glGetUniformLocation(Shaders["TextureShader"]->getProgram(), "textureSampler"));


    Shaders["PlainShader"]->setUniform(plainUniform);
    Shaders["TextureShader"]->setUniform(textureUniform);



    for (auto it = gameObjects.begin(); it!= gameObjects.end();it++)
    {
        it->second->awake();
    }
    camera->init(Shaders["PlainShader"]->getUniform()->mPmatrixUniform,Shaders["PlainShader"]->getUniform()->mVmatrixUniform);
    camera->perspective(120,RenderWindow::instance->width()/RenderWindow::instance->height(), 0.1f,1000);
    DeltaTime.start();
}

void Scene::update()
{
    camera->update();

    // for shaders in allShaders
    for(auto it = Shaders.begin(); it != Shaders.end(); it++)
    {
        glUseProgram(it->second->getProgram() );
        Uniforms* uni = it->second->getUniform();
        camera->bind(uni->mPmatrixUniform, uni->mVmatrixUniform);
    }



    for (auto it = gameObjects.begin(); it!= gameObjects.end();it++)
    {        
        (*it).second->update((float)DeltaTime.nsecsElapsed() / 1000000000.f);
    }



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

void Scene::runProgram(std::string shader)
{
    glUseProgram(Shaders[shader]->getProgram());
}
