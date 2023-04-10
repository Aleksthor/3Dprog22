#include "scene.h"
#include "gameobject.h"
#include "camera.h"
#include "renderwindow.h"
#include "shader.h"
#include "uniforms.h"
#include "basicmesh.h"
#include "visualobjectcomponent.h"
#include "cubemap.h"
#include "octahedron.h"
Scene::Scene()
{
    camera = new Camera();
    lightPos = QVector3D(0, 0, 5.0f);
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
    Shader* shader3 = new Shader("../3Dprog22/cubemap.vert", "../3Dprog22/cubemap.frag");
    Shader* shader4 = new Shader("../3Dprog22/lightShader.vert", "../3Dprog22/lightShader.frag");

    Shaders.insert(std::pair<std::string, Shader*>{"PlainShader", shader1});
    Shaders.insert(std::pair<std::string, Shader*>{"TextureShader", shader2});
    Shaders.insert(std::pair<std::string, Shader*>{"CubeMapShader", shader3});
    Shaders.insert(std::pair<std::string, Shader*>{"LightShader", shader4});

    Uniforms* plainUniform = new Uniforms(glGetUniformLocation(Shaders["PlainShader"]->getProgram(), "matrix"),
                                          glGetUniformLocation(Shaders["PlainShader"]->getProgram(), "vmatrix"),
                                          glGetUniformLocation(Shaders["PlainShader"]->getProgram(), "pmatrix"));

    plainUniform->mObjectColor = glGetUniformLocation(Shaders["PlainShader"]->getProgram(), "material.color");
    plainUniform->mLightColor = glGetUniformLocation(Shaders["PlainShader"]->getProgram(), "lightColor");
    plainUniform->mLightPos = glGetUniformLocation(Shaders["PlainShader"]->getProgram(), "lightPos");
    plainUniform->mViewPos = glGetUniformLocation(Shaders["PlainShader"]->getProgram(), "viewPos");
    plainUniform->mAmbientUniform = glGetUniformLocation(Shaders["PlainShader"]->getProgram(), "material.ambient");
    plainUniform->mDiffuseUniform = glGetUniformLocation(Shaders["PlainShader"]->getProgram(), "material.diffuse");
    plainUniform->mSpecularUniform = glGetUniformLocation(Shaders["PlainShader"]->getProgram(), "material.specular");
    plainUniform->mShininessUniform = glGetUniformLocation(Shaders["PlainShader"]->getProgram(), "material.shininess");


    Uniforms* textureUniform = new Uniforms(glGetUniformLocation(Shaders["TextureShader"]->getProgram(), "matrix"),
                                            glGetUniformLocation(Shaders["TextureShader"]->getProgram(), "vmatrix"),
                                            glGetUniformLocation(Shaders["TextureShader"]->getProgram(), "pmatrix"),
                                            glGetUniformLocation(Shaders["TextureShader"]->getProgram(), "textureSampler"));

    Uniforms* cubeMapUniform = new Uniforms(glGetUniformLocation(Shaders["CubeMapShader"]->getProgram(), "matrix"),
                                            glGetUniformLocation(Shaders["CubeMapShader"]->getProgram(), "vmatrix"),
                                            glGetUniformLocation(Shaders["CubeMapShader"]->getProgram(), "pmatrix"),
                                            glGetUniformLocation(Shaders["CubeMapShader"]->getProgram(), "textureSampler"));


    Uniforms* ligthShaderUniform = new Uniforms(glGetUniformLocation(Shaders["LightShader"]->getProgram(), "matrix"),
                                          glGetUniformLocation(Shaders["LightShader"]->getProgram(), "vmatrix"),
                                          glGetUniformLocation(Shaders["LightShader"]->getProgram(), "pmatrix"));

    ligthShaderUniform->mObjectColor = glGetUniformLocation(Shaders["LightShader"]->getProgram(), "material.color");
    ligthShaderUniform->mLightColor = glGetUniformLocation(Shaders["LightShader"]->getProgram(), "lightColor");
    ligthShaderUniform->mLightPos = glGetUniformLocation(Shaders["LightShader"]->getProgram(), "lightPos");
    ligthShaderUniform->mViewPos = glGetUniformLocation(Shaders["LightShader"]->getProgram(), "viewPos");
    ligthShaderUniform->mAmbientUniform = glGetUniformLocation(Shaders["LightShader"]->getProgram(), "material.ambient");
    ligthShaderUniform->mDiffuseUniform = glGetUniformLocation(Shaders["LightShader"]->getProgram(), "material.diffuse");
    ligthShaderUniform->mSpecularUniform = glGetUniformLocation(Shaders["LightShader"]->getProgram(), "material.specular");
    ligthShaderUniform->mShininessUniform = glGetUniformLocation(Shaders["LightShader"]->getProgram(), "material.shininess");


    Shaders["PlainShader"]->setUniform(plainUniform);
    Shaders["TextureShader"]->setUniform(textureUniform);
    Shaders["CubeMapShader"]->setUniform(cubeMapUniform);
    Shaders["LightShader"]->setUniform(ligthShaderUniform);





    cubeMap = new BasicMesh(new Cube(), "CubeMap", "CubeMapShader");
    cubeMap->setWorld(this);
    cubeMap->scale(100);
    cubeMap->rotate(90,QVector3D(1,0,0));
    VisualObjectComponent* VO = (VisualObjectComponent*)cubeMap->getRootComponent();
    std::vector<std::string> textures{"../3Dprog22/cloudy/right.jpg","../3Dprog22/cloudy/left.jpg","../3Dprog22/cloudy/top.jpg",
                                      "../3Dprog22/cloudy/bottom.jpg","../3Dprog22/cloudy/front.jpg","../3Dprog22/cloudy/back.jpg"};
    VO->setTexture(new CubeMap(textures, VO));

    cubeMap->awake();
    for (auto it = gameObjects.begin(); it!= gameObjects.end();it++)
    {
        it->second->awake();
    }
    camera->init(Shaders["PlainShader"]->getUniform()->mPmatrixUniform,Shaders["PlainShader"]->getUniform()->mVmatrixUniform);
    camera->perspective(90,RenderWindow::instance->width()/RenderWindow::instance->height(), 0.1f,1000);


    lightSource = new BasicMesh(new Octahedron(3), "LightSource", "LightShader");
    lightSource->setWorld(this);
    lightSource->scale(0.5f);
    VisualObjectComponent* lightVO = (VisualObjectComponent*)lightSource->getRootComponent();
    lightVO->setMaterial(Material::light);
    lightSource->awake();

    DeltaTime.start();
}

void Scene::update()
{
    camera->update();
    if (lightSource != nullptr)
    {
        lightSource->setPosition(lightPos);
    }

    // for shaders in allShaders
    for(auto it = Shaders.begin(); it != Shaders.end(); it++)
    {
        glUseProgram(it->second->getProgram());
        it->second->setLightPos(lightPos);
        Uniforms* uni = it->second->getUniform();
        camera->bind(uni->mPmatrixUniform, uni->mVmatrixUniform);
        camera->uploadPos(uni->mViewPos);
    }

    cubeMap->update((float)DeltaTime.nsecsElapsed() / 1000000000.f);
    glDepthMask(GL_TRUE);

    lightSource->update((float)DeltaTime.nsecsElapsed() / 1000000000.f);
    for (auto it = gameObjects.begin(); it!= gameObjects.end();it++)
    {        
        (*it).second->update((float)DeltaTime.nsecsElapsed() / 1000000000.f);
    }


    for (auto it = gameObjects.begin(); it!= gameObjects.end();it++)
    {
        if (it->second->getName() == "Player")
            lightPos = gameObjects["Player"]->getPosition3D() + QVector3D(0,0,5);
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
        if (it->second != nullptr)
        {
            if (it->second->simulatingPhysics())
            {
                objects.insert((*it));
            }
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
    glUseProgram(this->Shaders[shader]->getProgram());
}
