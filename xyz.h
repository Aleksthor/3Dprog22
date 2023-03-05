#ifndef XYZ_H
#define XYZ_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "visualobject.h"

class XYZ : public VisualObject
{
public:
   XYZ();
   ~XYZ() override;
   void init(GLint matrixUniform) override;
   void draw() override;
   void draw(QMatrix4x4& transformMatrix) override;
};


#endif // XYZ_H
