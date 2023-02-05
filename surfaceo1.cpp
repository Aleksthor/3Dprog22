#include "surfaceo1.h"
#include <fstream>
#include "logger.h"

SurfaceO1::SurfaceO1() : VisualObject()
{
    float h = 0.0625f;
    A = 0.f;

    for (float x = 0.f; x < 1.f; x += h)
    {
        for (float y = 0.f; y < 1.0-x; y += h)
        {
            // f (x,y) = sin (x * root(x^2 + y^2))
            float z = f(x,y);
            mVertices.push_back(Vertex(Position(x,y,z), Color(0,0,z)));

            z = f(x+h,y);
            mVertices.push_back(Vertex(Position(x + h,y,z), Color(0,0,z)));

            z = f(x,y+h);
            mVertices.push_back(Vertex(Position(x,y + h,z), Color(0,0,z)));


            z = f(x+h,y);
            mVertices.push_back(Vertex(Position(x + h,y,z), Color(0 + h,0 + h,z + h)));

            z = f(x+h,y+h);
            mVertices.push_back(Vertex(Position(x + h,y + h,z), Color(0 + h,0 + h,z + h)));

            z = f(x,y+h);
            mVertices.push_back(Vertex(Position(x,y + h,z), Color(0 + h,0 + h,z + h)));

            z = f(x,y);
            A += h * h * z;

        }


    }

}

SurfaceO1::SurfaceO1(std::string filnavn) : VisualObject()
{
   readFile(filnavn);
}

SurfaceO1::~SurfaceO1()
{

}


void SurfaceO1::readFile(std::string filnavn) {
   std::ifstream inn;
   inn.open(filnavn.c_str());

   if (inn.is_open()) {
       int n;
       Vertex vertex;
       inn >> n;
       mVertices.reserve(n);
       for (int i=0; i<n; i++) {
            inn >> vertex;
            mVertices.push_back(vertex);
       }
       inn.close();
   }
}
float SurfaceO1::f(float x, float y)
{
    return 1-x-y;
}


void SurfaceO1::init(GLint matrixUniform)
{
   mMatrixUniform = matrixUniform;

   initializeOpenGLFunctions();

   //Vertex Array Object - VAO
   glGenVertexArrays( 1, &mVAO );
   glBindVertexArray( mVAO );

   //Vertex Buffer Object to hold vertices - VBO
   glGenBuffers( 1, &mVBO );
   glBindBuffer( GL_ARRAY_BUFFER, mVBO );

   glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof( Vertex ), mVertices.data(), GL_STATIC_DRAW );

   // 1rst attribute buffer : vertices
   glBindBuffer(GL_ARRAY_BUFFER, mVBO);
   glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), (GLvoid*)0);
   glEnableVertexAttribArray(0);

   // 2nd attribute buffer : colors
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof( Vertex ),  (GLvoid*)(3 * sizeof(GLfloat)) );
   glEnableVertexAttribArray(1);

   //enable the matrixUniform
   // mMatrixUniform = glGetUniformLocation( matrixUniform, "matrix" );

   glBindVertexArray(0);

   Logger* mLogger = Logger::getInstance();
   mLogger->logText(std::to_string(A));
}

void SurfaceO1::draw()
{
   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
   glDrawArrays(GL_TRIANGLES, 0, mVertices.size());



}


