#ifndef MATERIAL_H
#define MATERIAL_H
#include <QVector3D>
#include "Structures.h"

class Material
{
public:
    Material();
    Material(QVector3D _color,QVector3D _ambient, QVector3D _diffuse,QVector3D _specular,float _shininess);
    Material(Color _color,QVector3D _ambient, QVector3D _diffuse,QVector3D _specular,float _shininess);
    ~Material();

public:
    QVector3D color;
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
    float shininess;



    static const Material emerald;
    static const Material jade;
    static const Material obsidian;
    static const Material pearl;
    static const Material ruby;
    static const Material torquise;
    static const Material brass;
    static const Material bronze;
    static const Material chrome;
    static const Material copper;
    static const Material gold;
    static const Material silver;
    static const Material blackPlastic;
    static const Material cyanPlastic;
    static const Material greenPlastic;
    static const Material redPlastic;
    static const Material whitePlastic;
    static const Material yellowPlastic;
    static const Material blackRubber;
    static const Material cyanRubber;
    static const Material greenRubber;
    static const Material redRubber;
    static const Material whiteRubber;
    static const Material yellowRubber;
    static const Material light;

};

#endif // MATERIAL_H
