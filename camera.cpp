#include "camera.h"

Camera::Camera()
    : mPosition(0,0,0)
{
    mVmatrix.setToIdentity();
    mPmatrix.setToIdentity();
}

void Camera::init(GLint pMatrixUniform, GLint vMatrixUniform)
{
    mVmatrix.setToIdentity();
    mPmatrix.setToIdentity();
    mPmatrixUniform = pMatrixUniform;
    mVmatrixUniform = vMatrixUniform;
}

void Camera::perspective(int degrees, double aspect, double nearplane, double farplane)
{
    mPmatrix.perspective(degrees, aspect, nearplane, farplane);
}

void Camera::lookAt(const QVector3D &eye, const QVector3D &at, const QVector3D &up)
{
    mVmatrix.lookAt(eye, at, up);
}

void Camera::update()
{
    initializeOpenGLFunctions();
    glUniformMatrix4fv(mPmatrixUniform, 1, GL_FALSE, mPmatrix.constData());
    glUniformMatrix4fv(mVmatrixUniform, 1, GL_FALSE, mVmatrix.constData());
}

void Camera::translate(float dx, float dy, float dz)
{
    mVmatrix.translate(dx,dy,dz);
}
