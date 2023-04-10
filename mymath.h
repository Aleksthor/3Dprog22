#ifndef MYMATH_H
#define MYMATH_H
#include <QVector2D>

class MyMath
{
public:
    MyMath();

    static QVector2D Bernstein(QVector2D p1,QVector2D p2,QVector2D p3, float t);
    static QVector3D Bary(const QVector2D playerPos, const QVector2D P, const QVector2D Q, const QVector2D R);
    static QVector3D crossProduct2D(QVector2D A, QVector2D B);
};

#endif // MYMATH_H
