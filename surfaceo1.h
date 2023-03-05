#ifndef SURFACEO1_H
#define SURFACEO1_H
#include "visualobject.h"

class SurfaceO1 : public VisualObject
{
public:
   SurfaceO1();
   SurfaceO1(std::string filnavn);
   ~SurfaceO1() override;

   float f(float x, float y);
   void readFile(std::string filnavn);
   void init(GLint shader) override;
   void draw() override;
   void draw(QMatrix4x4& transformMatrix) override;

private:
   float A;
};

#endif // SURFACEO1_H
