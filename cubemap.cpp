#include "cubemap.h"
#include "visualobjectcomponent.h"
#include "stb_image.h"
#include "gameobject.h"
#include "scene.h"
#include "camera.h"


CubeMap::CubeMap(std::vector<std::string> _textures_faces, VisualObjectComponent *owner)
    : textures_faces(_textures_faces)
{
    mOwner = owner;
    owner->setUsingTexture(true);
}

CubeMap::~CubeMap()
{

}

void CubeMap::init()
{
    initializeOpenGLFunctions();

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < textures_faces.size(); i++)
    {
        unsigned char *data = stbi_load(textures_faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            switch(nrChannels)
            {
            case 3:
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                );
                break;
            case 4:
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                             0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data
                );
                break;
            default:
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                );
                break;

            }


            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << textures_faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


}

void CubeMap::update(GLint textureUniform)
{
    Camera* camera = mOwner->GetOwner()->getWorld()->getCamera();
    mOwner->GetOwner()->setPosition(camera->GetPosition3D());
    glDepthMask(GL_FALSE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
}
