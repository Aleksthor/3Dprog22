#include "transform.h"
#include "gameobject.h"

Transform::Transform(GameObject* owner)
{
    mOwner = owner;
    mMatrix.setToIdentity();

}

Transform::~Transform()
{

}


std::pair<float, float> Transform::getPosition()
{
    auto col = mMatrix.column(3);
    return std::pair<float,float>(col.x(), col.y());
}

QVector3D Transform::getPosition3D()
{
    auto col = mMatrix.column(3);
    return QVector3D(col.x(), col.y(), col.z());
}

QVector2D Transform::getPosition2D()
{
    auto col = mMatrix.column(3);
    return QVector2D(col.x(), col.y());
}



void Transform::move(float x, float y, float z)
{
    mMatrix.translate(x,y,z);
}
void Transform::move(QVector3D direction)
{
    mMatrix.translate(direction);
}


void Transform::setPosition(float x, float y, float z)
{
    QVector4D position = mMatrix.column(3);
    position = QVector4D(x,y,z,position.w());
    mMatrix.setColumn(3, position);
}

void Transform::setPosition(QVector3D pos)
{
    QVector4D position = mMatrix.column(3);
    position = QVector4D(pos.x(),pos.y(),pos.z(),position.w());
    mMatrix.setColumn(3, position);
}

void Transform::rotate(float angle, QVector3D vector)
{
    mMatrix.rotate(angle, vector);
}

float Transform::scale(float _scale)
{
    mMatrix.scale(_scale);
    return _scale;
}

void Transform::scale(QVector3D _scale)
{
    mMatrix.scale(_scale);
}

void Transform::setX(float x)
{
    QVector4D position = mMatrix.column(3);
    position = QVector4D(x,position.y(),position.z(),position.w());
    mMatrix.setColumn(3, position);
}

void Transform::setY(float y)
{
    QVector4D position = mMatrix.column(3);
    position = QVector4D(position.x(),y,position.z(),position.w());
    mMatrix.setColumn(3, position);
}

void Transform::setZ(float z)
{
    QVector4D position = mMatrix.column(3);
    position = QVector4D(position.x(),position.y(),z,position.w());
    mMatrix.setColumn(3, position);
}

float Transform::getX()
{
    auto col = mMatrix.column(3);
    return col.x();
}

float Transform::getY()
{
    auto col = mMatrix.column(3);
    return col.y();
}

float Transform::getZ()
{
    auto col = mMatrix.column(3);
    return col.z();
}
