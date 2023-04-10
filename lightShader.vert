#version 410 core

layout(location = 0) in vec3 positionIn;   // 1st attribute buffer = vertex positions
layout(location = 1) in vec3 normalIn;   // 2nd attribute buffer = colors
layout(location = 2) in vec2 UVIn;      // 3rd attribute buffer = colors


out vec4 color;                           //color sent to rest of pipeline
out vec2 uv;

struct Material {
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform mat4 pmatrix;                   // nye matriser 28/1
uniform mat4 vmatrix;                   // nye matriser 28/1
uniform mat4 matrix;                    //the matrix for the model

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform Material material;

void main() {

    gl_Position = pmatrix * vmatrix * matrix * vec4(positionIn,1.0);

    // ambient lighting
    vec3 ambient = material.ambient * lightColor;

    // calculations
    vec3 fragPos = vec3(matrix * vec4(positionIn, 1.0));
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 norm = normalize(normalIn);

    // Specular
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec * lightColor;

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * material.diffuse;


    vec3 result = (ambient + diffuse + specular) * material.color;
    color = vec4(result, 1.0);
    uv = UVIn;




}
