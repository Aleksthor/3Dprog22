#include "Structures.h"
#include "qgenericmatrix.h"

# define M_PI           3.14159265358979323846  /* pi */
#include <cmath>




Matrix4x4::Matrix4x4()
{
    // set to identity matrix
    for (int m{}; m < 4; m++)
    {
        for (int n{}; n < 4; n++)
        {
            if (n == m)
            {
                M[n][m] = 1;
            }
            else
                M[n][m] = 0;
        }
    }

}

Matrix4x4::Matrix4x4(float m00, float m01, float m02, float m03,
          float m10, float m11, float m12, float m13,
          float m20, float m21, float m22, float m23,
          float m30, float m31, float m32, float m33)
{
    M[0][0] = m00; M[0][1] = m01; M[0][2] = m02; M[0][3] = m03;
    M[1][0] = m10; M[1][1] = m11; M[1][2] = m12; M[1][3] = m13;
    M[2][0] = m20; M[2][1] = m21; M[2][2] = m22; M[2][3] = m23;
    M[3][0] = m30; M[3][1] = m31; M[3][2] = m32; M[3][3] = m33;
}

void Matrix4x4::scale(const Vector3 &vector)
{
    M[0][0] *= vector.x;
    M[1][1] *= vector.y;
    M[2][2] *= vector.z;
}
void Matrix4x4::translate(const Vector3& vector)
{
    M[3][0] += vector.x;
    M[3][1] += vector.y;
    M[3][2] += vector.z;
}
void Matrix4x4::rotate(float angle, const Vector3& vector)
{
    //mMatrix.rotate(angle, vector.x, vector.y, vector.z);
    float radian = (angle * M_PI) / 180.f;
    if (vector.x != 0)
    {
        *this = *this * Matrix4x4::createRotationX(radian) ;
    }
    if (vector.y != 0)
    {
       *this = *this * Matrix4x4::createRotationY(radian);
    }
    if (vector.z != 0)
    {
        *this = *this * Matrix4x4::createRotationZ(radian) ;
    }

}

void Matrix4x4::scale(float x, float y)
{
    M[0][0] *= x;
    M[1][1] *= y;
}
void Matrix4x4::scale(float x, float y, float z)
{
    M[0][0] *= x;
    M[1][1] *= y;
    M[2][2] *= z;
}
void Matrix4x4::scale(float factor)
{
    M[0][0] *= factor;
    M[1][1] *= factor;
    M[2][2] *= factor;
}
void Matrix4x4::translate(float x, float y)
{
    M[3][0] += x;
    M[3][1] += y;
}
void Matrix4x4::translate(float x, float y, float z)
{
    M[3][0] += x;
    M[3][1] += y;
    M[3][2] += z;
}
void Matrix4x4::rotate(float angle, float _x, float _y, float _z)
{
    //mMatrix.rotate(angle, vector.x, vector.y, vector.z);
    float radian = (angle * M_PI) / 180.f;
    if (_x != 0)
    {
        *this = Matrix4x4::createRotationX(radian) * *this;
    }
    if (_y != 0)
    {
       *this = Matrix4x4::createRotationY(radian) * *this;
    }
    if (_z != 0)
    {
        *this = Matrix4x4::createRotationZ(radian) * *this;
    }
}

void Matrix4x4::setToIdentity()
{
    {
        // set to identity matrix
        for (int m{}; m < 4; m++)
        {
            for (int n{}; n < 4; n++)
            {
                if (n == m)
                {
                    M[n][m] = 1;
                }
                else
                    M[n][m] = 0;
            }
        }
    }
}

Matrix4x4 Matrix4x4::createRotationX(float angle)
{
    Matrix4x4 newMatrix = Matrix4x4();
    newMatrix.M[1][1] = std::cos(angle);
    newMatrix.M[1][2] = -std::sin(angle);
    newMatrix.M[2][1] = std::sin(angle);
    newMatrix.M[2][2] = std::cos(angle);
    return newMatrix;
}

Matrix4x4 Matrix4x4::createRotationY(float angle)
{
    Matrix4x4 newMatrix = Matrix4x4();
    newMatrix.M[0][0] = std::cos(angle);
    newMatrix.M[0][2] = std::sin(angle);
    newMatrix.M[2][0] = -std::sin(angle);
    newMatrix.M[2][2] = std::cos(angle);
    return newMatrix;
}

Matrix4x4 Matrix4x4::createRotationZ(float angle)
{
    Matrix4x4 newMatrix = Matrix4x4();
    newMatrix.M[0][0] = std::cos(angle);
    newMatrix.M[0][1] = -std::sin(angle);
    newMatrix.M[1][0] = std::sin(angle);
    newMatrix.M[1][1] = std::cos(angle);
    return newMatrix;
}

const Position Position::Origo(0,0,0);

const Vector3 Vector3::X(1,0,0);
const Vector3 Vector3::Y(0,1,0);
const Vector3 Vector3::Z(0,0,1);

const Vector3 Vector3::Zero(0,0,0);
const Vector3 Vector3::One(1,1,1);
const Vector3 Vector3::Two(2,2,2);


const Color Color::Red(1,0,0);
const Color Color::Green(0,1,0);
const Color Color::Blue(0,0,1);
const Color Color::Purple(1,0,1);
const Color Color::Orange(1,0.6f,0);
const Color Color::White(1,1,1);



Interp::Interp(std::vector<QVector3D> _points)

    :   points(_points)
{
    int n = points.size() / sizeof(QVector3D);


}


