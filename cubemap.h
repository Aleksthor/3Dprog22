#ifndef CUBEMAP_H
#define CUBEMAP_H

#include "texture.h"

//class VisualObjectComponent;

class CubeMap : public Texture
{
public:
    CubeMap(std::vector<std::string> _textures_faces, VisualObjectComponent *owner);
    virtual ~CubeMap() override;

    virtual void init() override;
    virtual void update(GLint textureUniform) override;

    std::vector<std::string> textures_faces;
};

#endif // CUBEMAP_H
