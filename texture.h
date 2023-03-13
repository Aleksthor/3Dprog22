#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <QOpenGLFunctions_4_1_Core>

class VisualObjectComponent;

class Texture : QOpenGLFunctions_4_1_Core
{
public:
    Texture(std::string fileLoc, VisualObjectComponent* owner);

    void init();
    void update(GLint textureUniform);


private:
    VisualObjectComponent* mOwner;
    std::string fileLocation;
    unsigned int texture;
};

#endif // TEXTURE_H
