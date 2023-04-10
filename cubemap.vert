#version 410 core

layout(location = 0) in vec3 positionIn;   // 1st attribute buffer = vertex positions
layout(location = 1) in vec3 colorIn;      // 2nd attribute buffer = colors
layout(location = 2) in vec2 textureUV;    // 3rd attribute buffer = uvs


out vec3 textureDir;                           //color sent to rest of pipeline
uniform mat4 pmatrix;                   // nye matriser 28/1
uniform mat4 vmatrix;                   // nye matriser 28/1
uniform mat4 matrix;                    //the matrix for the model


void main() {
  textureDir = positionIn;
  gl_Position = pmatrix * vmatrix * matrix * vec4(positionIn,1.0);
}
