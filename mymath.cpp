#include "mymath.h"

MyMath::MyMath()
{

}

QVector2D MyMath::Bernstein(QVector2D p1, QVector2D p2, QVector2D p3, float t)
{
    return QVector2D();
}

QVector3D MyMath::Bary(const QVector2D playerPos, const QVector2D P, const QVector2D Q, const QVector2D R)
{
    QVector2D PQ = Q - P;
    QVector2D PR = R - P;

    QVector3D PQR = crossProduct2D(PQ,PR);
    float normalPQR = PQR.length();

    QVector3D Bary = QVector3D();


    QVector2D XP = P - playerPos;
    QVector2D XQ = Q - playerPos;
    // normalen til XPQ
    Bary.setX(crossProduct2D(XP,XQ).z() / normalPQR);


    QVector2D XR = R - playerPos;
    // normalen til XQR
    Bary.setY(crossProduct2D(XQ,XR).z() / normalPQR);

    // normalen til XRP
    Bary.setZ(crossProduct2D(XR,XP).z() / normalPQR);

    return Bary;
}

QVector3D MyMath::crossProduct2D(QVector2D A, QVector2D B)
{
    QVector3D cross = QVector3D();

    cross.setZ((A.x() * B.y()) - (A.y() * B.x()));

    return cross;
}
