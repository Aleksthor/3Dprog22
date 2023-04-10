#include "octahedron.h"
#include "vertex.h"
#include "spherecollider.h"

Octahedron::Octahedron(int n) : VisualObject(),
     m_rekursjoner(n), m_indeks(0)
{
    isActive = true;
    radius = 1;
    renderFrame = false;
    colorDefined=false;
    mVertices.reserve(3 * 8 * pow(4, m_rekursjoner));
    oktaederUnitBall();
}

Octahedron::Octahedron(float r, int n) : VisualObject(),
     m_rekursjoner(n), m_indeks(0)
{
    isActive = true;
    radius = r;
    colorDefined = false;
    renderFrame = false;
    mVertices.reserve(3 * 8 * pow(4, m_rekursjoner));
    oktaederUnitBall();
}

Octahedron::~Octahedron()
{
   //
}

void Octahedron::lagTriangel(const QVector3D& v1, const QVector3D& v2,
const QVector3D& v3)
{
   if (colorDefined)
   {
       Vertex v = Vertex{v1.x(), v1.y(), v1.z(), c.r, c.g, c.b};
       mVertices.push_back(v);
       v = Vertex{v2.x(), v2.y(), v2.z(), c.r, c.g, c.b};
       mVertices.push_back(v);
       v = Vertex{v3.x(), v3.y(), v3.z(), c.r, c.g, c.b};
       mVertices.push_back(v);
   }
   else
   {
       Vertex v = Vertex{v1.x(), v1.y(), v1.z(), v1.normalized().x(), v1.normalized().y(), v1.normalized().z()};
       mVertices.push_back(v);
       v = Vertex{v2.x(), v2.y(), v2.z(), v2.normalized().x(), v2.normalized().y(), v2.normalized().z()};
       mVertices.push_back(v);
       v = Vertex{v3.x(), v3.y(), v3.z(), v3.normalized().x(), v3.normalized().y(), v3.normalized().z()};
       mVertices.push_back(v);
   }

}

void Octahedron::subDivide(const QVector3D& a, const QVector3D& b, const QVector3D& c, int n)
{
    if (n>0) {
        QVector3D v1 = a+b; v1.normalize();
        QVector3D v2 = a+c; v2.normalize();
        QVector3D v3 = c+b; v3.normalize();
        v1 *= radius;
        v2 *= radius;
        v3 *= radius;
        subDivide(a, v1, v2, n-1);
        subDivide(c, v2, v3, n-1);
        subDivide(b, v3, v1, n-1);
        subDivide(v3, v2, v1, n-1);
    } else {
        lagTriangel(a, b, c);
    }
}
void Octahedron::oktaederUnitBall()
{
   QVector3D v0{0, 0, radius};
   QVector3D v1{radius, 0, 0};
   QVector3D v2{0, radius, 0};
   QVector3D v3{-radius, 0, 0};
   QVector3D v4{0, -radius, 0};
   QVector3D v5{0, 0, -radius};


   subDivide(v0, v1, v2, m_rekursjoner);
   subDivide(v0, v2, v3, m_rekursjoner);
   subDivide(v0, v3, v4, m_rekursjoner);
   subDivide(v0, v4, v1, m_rekursjoner);
   subDivide(v5, v2, v1, m_rekursjoner);
   subDivide(v5, v3, v2, m_rekursjoner);
   subDivide(v5, v4, v3, m_rekursjoner);
   subDivide(v5, v1, v4, m_rekursjoner);
}

void Octahedron::init(GLint matrixUniform)
{
   mMatrixUniform = matrixUniform;
   initializeOpenGLFunctions();


   //Vertex Array Object - VAO
   glGenVertexArrays( 1, &mVAO );
   glBindVertexArray( mVAO );


   //Vertex Buffer Object to hold vertices - VBO
   glGenBuffers( 1, &mVBO );
   glBindBuffer( GL_ARRAY_BUFFER, mVBO );


   glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW );


   glBindBuffer(GL_ARRAY_BUFFER, mVBO);
   glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,sizeof(Vertex), (GLvoid*)0);
   glEnableVertexAttribArray(0);


   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex),  (GLvoid*)(3 * sizeof(GLfloat)) );
   glEnableVertexAttribArray(1);


   glBindVertexArray(0);
}


void Octahedron::draw()
{
    if (isActive)
    {
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());//mVertices.size());
    }
}
void Octahedron::draw(QMatrix4x4 transformMatrix)
{
    if (isActive)
    {
        transformMatrix *= mMatrix;
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, transformMatrix.constData());
        if (renderFrame)
        {
            glDrawArrays(GL_LINES, 0, mVertices.size());
        }
        else
        {
            glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
        }

    }
}

