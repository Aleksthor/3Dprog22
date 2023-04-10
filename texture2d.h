#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "texture.h"

class Texture2D : public Texture
{
public:
    Texture2D(std::string fileLoc, VisualObjectComponent* owner);

    virtual ~Texture2D() override;

    virtual void init() override;
    virtual void update(GLint textureUniform) override;
};

#endif // TEXTURE2D_H
