#include "visualobject.h"

VisualObject::VisualObject()
{
    mMatrix.setToIdentity();
}

VisualObject::~VisualObject()
{
   glDeleteVertexArrays( 1, &mVAO );
   glDeleteBuffers( 1, &mVBO );
}


void VisualObject::move(float x, float y, float z)
{
    mMatrix.translate(x,y,z);
}

void VisualObject::setPosition(float x, float y, float z)
{
    mMatrix.setToIdentity();
    mMatrix.translate(x,y,z);

}

void VisualObject::rotate(float angle, QVector3D vector)
{
    mMatrix.rotate(angle, vector);

}

void VisualObject::scale(float _scale)
{
    mMatrix.scale(_scale);
}
