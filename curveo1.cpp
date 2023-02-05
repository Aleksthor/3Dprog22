#include "curveo1.h"
#include <fstream>

CurveO1::CurveO1() : VisualObject()
{
    float n = 100;
    float a = 0;
    float b = 10;

    float h = (b-a)/n;

    for (auto x = a; x < b; x += h)
    {
        float y = f(x);
        mVertices.push_back(Vertex(Position(x,y,0), Color(abs(x),abs(y),0)));
    }

    // Write mesh to file
    std::fstream data;
    data.open("CurveO1.txt",  std::fstream::in | std::fstream::out | std::fstream::trunc);

    data << mVertices.size() << std::endl << std::endl;

    for(size_t i = 0; i < mVertices.size(); i++)
    {
        data << mVertices[i] << std::endl;
        std::cout << std::endl;
    }

    data.close();

}

CurveO1::CurveO1(std::string string)
{
   readFile(string);
}
CurveO1::~CurveO1()
{

}

void CurveO1::readFile(std::string filnavn) {
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

float CurveO1::f(float x)
{
    return (-0.5f * x * x * x) + (3 * x * x) - (3 * x);
}

void CurveO1::init(GLint matrixUniform)
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
}

void CurveO1::draw()
{
   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
   glDrawArrays(GL_LINE_STRIP, 0, mVertices.size());



}
