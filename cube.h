#ifndef CUBE_H
#define CUBE_H

#include "visualobject.h"

class Cube : public VisualObject
{
public:
   Cube();
   Cube(Position position, Color color, Vector3 scale);
   ~Cube() override;

   void readFile(std::string filnavn);
   void init(GLint matrixUniform) override;
   void draw() override;

};

#endif // CUBE_H
