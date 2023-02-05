#ifndef CAMERA_H
#define CAMERA_H
#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <QVector3D>

class Camera : public QOpenGLFunctions_4_1_Core
{

public:
   Camera();
   ~Camera() { }
   void init(GLint pMatrixUniform, GLint vMatrixUniform);
   void perspective(int degrees, double aspect, double nearplane, double farplane);
   void lookAt(const QVector3D& eye, const QVector3D& at, const QVector3D& up);
   void update();
   void translate(float dx, float dy, float dz);

private:
   GLint  mPmatrixUniform;        //OpenGL reference to the Uniform in the shader program
   GLint  mVmatrixUniform;        //OpenGL reference to the Uniform in the shader program
   QVector3D mPosition;
   QMatrix4x4 mPmatrix{};
   QMatrix4x4 mVmatrix{};
};

#endif // CAMERA_H
