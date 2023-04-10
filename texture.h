#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <QOpenGLFunctions_4_1_Core>


class VisualObjectComponent;

class Texture : public QOpenGLFunctions_4_1_Core
{
public:
    Texture();
    virtual ~Texture() {};

    virtual void init() = 0;
    virtual void update(GLint textureUniform) = 0;

public:
    VisualObjectComponent* mOwner;
    std::string fileLocation;
    unsigned int texture;
};

#endif // TEXTURE_H
