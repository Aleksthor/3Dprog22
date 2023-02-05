#ifndef STRUCTURES_H
#define STRUCTURES_H
class Vector3
{
public:
    Vector3()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    Vector3(float _x, float _y, float _z)
        :   x(_x), y(_y), z(_z)
    {

    }
    float x;
    float y;
    float z;

    static const Vector3 X;
    static const Vector3 Y;
    static const Vector3 Z;
    static const Vector3 Zero;
    static const Vector3 One;
    static const Vector3 Two;
};

class Vector4
{
public:
    Vector4()
    {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }
    Vector4(float _x, float _y, float _z, float _w)
        :   x(_x), y(_y), z(_z), w(_w)
    {

    }
    float x;
    float y;
    float z;
    float w;

};


struct Matrix4x4
{
    Matrix4x4();
    Matrix4x4(float m00, float m01, float m02, float m03,
              float m10, float m11, float m12, float m13,
              float m20, float m21, float m22, float m23,
              float m30, float m31, float m32, float m33);

    inline const float *constData() const { return *M; }


    void scale(const Vector3& vector);
    void translate(const Vector3& vector);
    void rotate(float angle, const Vector3& vector);

    void scale(float x, float y);
    void scale(float x, float y, float z);
    void scale(float factor);
    void translate(float x, float y);
    void translate(float x, float y, float z);
    void rotate(float angle, float x, float y, float z = 0.0f);
    void setToIdentity();

    void SetPosition(Vector3 pos) { M[3][0] = pos.x; M[3][1] = pos.y; M[3][2] = pos.z; }
    Vector3 GetPosition() { return Vector3(M[3][0], M[3][1], M[3][2]); }



    float M[4][4];


    inline Matrix4x4& operator*=(const Matrix4x4& rhs)
    {
        Matrix4x4 newMatrix;
        float temp_0= this->M[0][0] * rhs.M[0][0] + this->M[0][1] * rhs.M[1][0] + this->M[0][2] * rhs.M[2][0] + this->M[0][3] * rhs.M[3][0];
        float temp_1= this->M[0][0] * rhs.M[0][1] + this->M[0][1] * rhs.M[1][1] + this->M[0][2] * rhs.M[2][1] + this->M[0][3] * rhs.M[3][1];
        float temp_2= this->M[0][0] * rhs.M[0][2] + this->M[0][1] * rhs.M[1][2] + this->M[0][2] * rhs.M[2][2] + this->M[0][3] * rhs.M[3][2];
        float temp_3= this->M[0][0] * rhs.M[0][3] + this->M[0][1] * rhs.M[1][3] + this->M[0][2] * rhs.M[2][3] + this->M[0][3] * rhs.M[3][3];

        float temp_4= this->M[1][0] * rhs.M[0][0] + this->M[1][1] * rhs.M[1][0] + this->M[1][2] * rhs.M[2][0] + this->M[1][3] * rhs.M[3][0];
        float temp_5= this->M[1][0] * rhs.M[0][1] + this->M[1][1] * rhs.M[1][1] + this->M[1][2] * rhs.M[2][1] + this->M[1][3] * rhs.M[3][1];
        float temp_6= this->M[1][0] * rhs.M[0][2] + this->M[1][1] * rhs.M[1][2] + this->M[1][2] * rhs.M[2][2] + this->M[1][3] * rhs.M[3][2];
        float temp_7= this->M[1][0] * rhs.M[0][3] + this->M[1][1] * rhs.M[1][3] + this->M[1][2] * rhs.M[2][3] + this->M[1][3] * rhs.M[3][3];

        float temp_8  = this->M[2][0]  * rhs.M[0][0] + this->M[2][1] * rhs.M[1][0] + this->M[2][2] * rhs.M[2][0] + this->M[2][3] * rhs.M[3][0];
        float temp_9  = this->M[2][0]  * rhs.M[0][1] + this->M[2][1] * rhs.M[1][1] + this->M[2][2] * rhs.M[2][1] + this->M[2][3] * rhs.M[3][1];
        float temp_10 = this->M[2][0]  * rhs.M[0][2] + this->M[2][1] * rhs.M[1][2] + this->M[2][2] * rhs.M[2][2] + this->M[2][3] * rhs.M[3][2];
        float temp_11 = this->M[2][0]  * rhs.M[0][3] + this->M[2][1] * rhs.M[1][3] + this->M[2][2] * rhs.M[2][3] + this->M[2][3] * rhs.M[3][3];

        float temp_12 = this->M[3][0]  * rhs.M[0][0] + this->M[3][1] * rhs.M[1][0] + this->M[3][2] * rhs.M[2][0] + this->M[3][3] * rhs.M[3][0];
        float temp_13 = this->M[3][0]  * rhs.M[0][1] + this->M[3][1] * rhs.M[1][1] + this->M[3][2] * rhs.M[2][1] + this->M[3][3] * rhs.M[3][1];
        float temp_14 = this->M[3][0]  * rhs.M[0][2] + this->M[3][1] * rhs.M[1][2] + this->M[3][2] * rhs.M[2][2] + this->M[3][3] * rhs.M[3][2];
        float temp_15 = this->M[3][0]  * rhs.M[0][3] + this->M[3][1] * rhs.M[1][3] + this->M[3][2] * rhs.M[2][3] + this->M[3][3] * rhs.M[3][3];


        this->M[0][0] = temp_0;
        this->M[0][1] = temp_1;
        this->M[0][2] = temp_2;
        this->M[0][3] = temp_3;
        this->M[1][0] = temp_4;
        this->M[1][1] = temp_5;
        this->M[1][2] = temp_6;
        this->M[1][3] = temp_7;
        this->M[2][0] = temp_8;
        this->M[2][1] = temp_9;
        this->M[2][2] = temp_10;
        this->M[2][3] = temp_11;
        this->M[3][0] = temp_12;
        this->M[3][1] = temp_13;
        this->M[3][2] = temp_14;
        this->M[3][3] = temp_15;

        return  *this;
    }

    friend Matrix4x4 operator*(const Matrix4x4& left, const Matrix4x4& right);

    static Matrix4x4 createRotationX(float angle);
    static Matrix4x4 createRotationY(float angle);
    static Matrix4x4 createRotationZ(float angle);
};

inline Matrix4x4 operator*(const Matrix4x4& left, const Matrix4x4& right)
{
    Matrix4x4 newMatrix = left;
    newMatrix *= right;
    return newMatrix;
}

class Position
{
public:
    Position()
    {
        x = 0.f;
        y = 0.f;
        z = 0.f;
    }

    Position (float _x, float _y, float _z)
        : x(_x), y(_y), z(_z)
    {

    }

    Position (float _x, float _y)
        : x(_x), y(_y)
    {

    }

    Position operator+=(const Position& pos)
    {
        this->x += pos.x;
        this->y += pos.y;
        this->z += pos.z;

        return *this;
    }

    Position operator+(const Position& pos)
    {
        this->x += pos.x;
        this->y += pos.y;
        this->z += pos.z;

        return *this;
    }

    Position operator*=(const Vector3& pos)
    {
        this->x *= pos.x;
        this->y *= pos.y;
        this->z *= pos.z;

        return *this;
    }


    float x;
    float y;
    float z;

    static const Position Origo;

};



class Normal
{
public:
    Normal()
    {
        x = 0.f;
        y = 0.f;
        z = 0.f;
    }
    Normal (float _x, float _y, float _z)
        : x(_x), y(_y), z(_z)
    {

    }
    Normal (float _x, float _y)
        : x(_x), y(_y)
    {

    }

    float x;
    float y;
    float z;
};


class Color
{
public:
    Color()
    {
        r = 0.f;
        g = 0.f;
        b = 0.f;
    }

    Color (float _r, float _g, float _b)
        : r(_r), g(_g), b(_b)
    {

    }

    float r;
    float g;
    float b;

    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Purple;

};



class UV
{
public:
    UV()
    {
        u = 0.f;
        v = 0.f;
    }

    UV(float _u, float _v)
        : u(_u), v(_v)
    {

    }

    float u;
    float v;
};










#endif // STRUCTURES_H
