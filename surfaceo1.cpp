#include "surfaceo1.h"

SurfaceO1::SurfaceO1() : VisualObject()
{
    float xmin=0.0f, xmax=1.0f, ymin=0.0f, ymax=1.0f, h=0.125f;
    for (float x = xmin; x < xmax; x += h)
    {
        for (float y = ymin; y < ymax; y += h)
        {
            // f (x,y) = sin (x * root(x^2 + y^2))
            float z = sin(M_PI * sqrt(x * x + y * y));
            mVertices.push_back(Vertex(Position(x,y,z), Color(x,y,z)));

            z = sin(M_PI * sqrt((x + h) * (x + h) + y * y));
            mVertices.push_back(Vertex(Position(x + h,y,z), Color(x,y,z)));

            z = sin(M_PI * sqrt(x * x + (y + h) * (y + h)));
            mVertices.push_back(Vertex(Position(x,y + h,z), Color(x,y,z)));



            z = sin(M_PI * sqrt((x + h) * (x + h) + y * y));
            mVertices.push_back(Vertex(Position(x + h,y,z), Color(x + h,y + h,z + h)));

            z = sin(M_PI * sqrt((x + h) * (x + h) + (y + h) * (y + h)));
            mVertices.push_back(Vertex(Position(x + h,y + h,z), Color(x + h,y + h,z + h)));

            z = sin(M_PI * sqrt(x * x + (y + h) * (y + h)));
            mVertices.push_back(Vertex(Position(x,y + h,z), Color(x + h,y + h,z + h)));
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
}

void SurfaceO1::draw()
{
   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
   glDrawArrays(GL_TRIANGLES, 0, mVertices.size());

}


