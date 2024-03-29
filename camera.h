#ifndef CAMERA_H
#define CAMERA_H
#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <QVector3D>
#include "Structures.h"

class GameObject;

class Camera : public QOpenGLFunctions_4_1_Core
{

public:
   Camera();
   ~Camera() { }
   void init(GLint pMatrixUniform, GLint vMatrixUniform);
   void bind(GLint pMatrixUniform, GLint vMatrixUniform);
   void perspective(int degrees, double aspect, double nearplane, double farplane);
   void lookAt(const QVector3D& eye, const QVector3D& at, const QVector3D& up);
   void update();
   void translate(float dx, float dy, float dz);
   void rotate(float pitch, float yaw, float roll);
   void setPosition(QVector3D position);
   void setForward(QVector3D at);

   void uploadPos(GLint uniform);


   QVector3D GetForwardVector3D() { return mForward; }
   Vector3 GetForwardVector() { return Vector3(mForward.x(), mForward.y(), mForward.z());}

   QVector3D GetPosition3D() { return mPosition; }
   Vector3 GetPosition() { return Vector3(mPosition.x(), mPosition.y(), mPosition.z()); }

   void setFollowGameObject(GameObject* _follow) { follow = _follow; }

private:
   GLint  mPmatrixUniform;        //OpenGL reference to the Uniform in the shader program
   GLint  mVmatrixUniform;        //OpenGL reference to the Uniform in the shader program
   QVector3D mPosition;
   QVector3D mForward;
   QVector3D mRight;
   QVector3D mUp;
   QMatrix4x4 mPmatrix{};
   QMatrix4x4 mVmatrix{};
   float mYaw;

   GameObject* follow;
};

#endif // CAMERA_H
