#version 410 core

out vec4 fragmentColor;     //color sent to fragment on screen
in vec3 textureDir;              //color received from the pipeline (and vertex shader)
uniform samplerCube textureSampler;

void main() {
   fragmentColor = texture(textureSampler, textureDir);
}
