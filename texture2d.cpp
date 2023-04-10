#include "texture2d.h"
#include "visualobjectcomponent.h"
#include "stb_image.h"

Texture2D::Texture2D(std::string fileLoc, VisualObjectComponent *owner) : Texture()
{
    fileLocation = fileLoc;
    mOwner = owner;
    owner->setUsingTexture(true);
}

Texture2D::~Texture2D()
{

}

void Texture2D::init()
{
    initializeOpenGLFunctions();

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(fileLocation.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        std::cout << fileLocation.c_str() << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void Texture2D::update(GLint textureUniform)
{
    glActiveTexture(GL_TEXTURE0);		// aktiverer Unit 0 - GPUen har fra 8 til 32 slike Units
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureUniform , 0); // 0 referer til glActiveTexture(GL_TEXTURE0);
}
