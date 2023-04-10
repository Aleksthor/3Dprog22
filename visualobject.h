#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H


#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex.h"

class Collider;
class Texture;

class VisualObject : public QOpenGLFunctions_4_1_Core{
public:
    VisualObject();
    virtual ~VisualObject()=0;
    virtual void init(GLint matrixUniform)=0;
    virtual void draw()=0;
    virtual void draw(QMatrix4x4 transformMatrix) = 0;


    void readFile(std::string filename, bool Indexing = false);
    void writeFile(std::string filename, bool Indexing = false);

    void setActive(bool active) { isActive = active; }

    void move(float x, float y, float z);
    void setPosition(float x, float y, float z);
    void setPosition(QVector3D pos);
    void rotate(float angle, QVector3D vector);
    void scale(float scale);
    void scale(QVector3D scale);
    std::pair<float,float> getPosition();
    QVector3D getPosition3D();

    void setColor(Color color);
    QVector3D GetVertex(int index) { if ((int)mVertices.size() < index) {std::cout << "Error Vertices length: " <<  mVertices.size() << " index: " << index << std::endl; return QVector3D();} return mVertices[index].GetPosition3D(); }
    QVector2D GetVertex2D(int index) { if ((int)mVertices.size() < index) {std::cout << "Error Vertices length: " <<  mVertices.size() << " index: " << index << std::endl; return QVector2D();} return mVertices[index].GetPosition2D(); }


protected:
    std::vector<Vertex> mVertices;
    std::vector<GLuint> mIndices;   	// Til indeksering
    GLuint mVAO{0};
    GLuint mVBO{0};
    GLuint mIBO{0};                 		// for glDrawElements()
    GLint mMatrixUniform{0};

    QVector3D ObjectColor;

    QMatrix4x4 mMatrix;

    bool isActive;
};


#endif // VISUALOBJECT_H
