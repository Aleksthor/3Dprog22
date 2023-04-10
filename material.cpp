#include "material.h"
#include "Structures.h"

Material::Material()
{
    color =   QVector3D(1.f, 0.5f, 0.3f);
    ambient = QVector3D(1.f, 0.5f, 0.3f);
    diffuse = QVector3D(1.f, 0.5f, 0.3f);
    specular = QVector3D(0.5f, 0.5f, 0.5f);
    shininess = 32.f;
}

Material::Material(QVector3D _color, QVector3D _ambient, QVector3D _diffuse, QVector3D _specular, float _shininess)
    : color(_color), ambient(_ambient), diffuse(_diffuse), specular(_specular), shininess(_shininess)
{

}

Material::Material(Color _color, QVector3D _ambient, QVector3D _diffuse, QVector3D _specular, float _shininess)
    : color(QVector3D(_color.r,_color.g,_color.b)), ambient(_ambient), diffuse(_diffuse), specular(_specular), shininess(_shininess)
{

}

Material::~Material()
{

}


const Material Material::emerald(QVector3D(80.f/255.f,220.f/255.f,100.f/255.f),QVector3D(0.0215f,0.1745f,0.0215f), QVector3D(0.07568f,0.61424f,0.07568f), QVector3D(0.633f,0.727811f,0.633f), 0.6f * 128.f);
const Material Material::jade(QVector3D(0,0.659f,0.42f), QVector3D(0.135f, 0.2225f,0.1575f),QVector3D(0.54f,0.89f,0.63f), QVector3D(0.316228f, 0.316228f,0.316228f), 0.1f * 128.f);

const Material Material::gold(QVector3D(1,0.843f,0),QVector3D(0.2472f,0.1995f,0.0745f),QVector3D(0.7516f,0.6064f,0.2264f),QVector3D(0.628281f,0.555802f,0.366065f),0.4f*128.f);

const Material Material::cyanPlastic(QVector3D(0,1,1), QVector3D(0,0.1f,0.06f),QVector3D(0.f,0.5098f,0.5098f),QVector3D(0.5019f,0.5019f,0.5019f),0.25f*128.f);
const Material Material::redPlastic(QVector3D(1.f, 0.5f, 0.3f), QVector3D(0,0,0),QVector3D(0.55f,0.0f,0.0f),QVector3D(0.7f,0.6f,0.6f),0.25f*128.f);
const Material Material::whitePlastic(QVector3D(1,1,1), QVector3D(0,0,0),QVector3D(0.55f,0.55f,0.55f),QVector3D(0.7f,0.7f,0.7f),0.25f*128.f);

const Material Material::light(QVector3D(1,1,1),QVector3D(1,1,1),QVector3D(0,0,0),QVector3D(0,0,0),1.f);
