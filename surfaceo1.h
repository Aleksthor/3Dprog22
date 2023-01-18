#ifndef SURFACEO1_H
#define SURFACEO1_H
#include "visualobject.h"

class SurfaceO1 : public VisualObject
{
public:
   SurfaceO1();
   SurfaceO1(std::string filnavn);
   ~SurfaceO1() override;
   void readFile(std::string filnavn);
   void init(GLint shader) override;
   void draw() override;
};

#endif // SURFACEO1_H
