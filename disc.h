#ifndef DISC_H
#define DISC_H


#include "visualobject.h"


class Disc : public VisualObject
{
public:
   Disc();
   Disc(std::string filnavn);
   ~Disc() override;

   void init(GLint matrixUniform) override;
   void draw() override;
   void draw(QMatrix4x4& transformMatrix) override;
   void construct();

protected:
   float mRadius{0.5};			//
   QVector4D mRotation;		// her eller i VisualObjects???? Bruk en av dem
};

#endif // DISC_H
