#include "cube.h"

Cube::Cube() : VisualObject()
{

   // -y veggen
   mVertices.push_back(Vertex{-1,-1,-1,1,0,0});
   mVertices.push_back(Vertex{1,-1,1,1,0,0});
   mVertices.push_back(Vertex{-1,-1,1,1,0,0});
   mVertices.push_back(Vertex{-1,-1,-1,1,0,0});
   mVertices.push_back(Vertex{1,-1,-1,1,0,0});
   mVertices.push_back(Vertex{1,-1,1,1,0,0});

   // -z veggen
   mVertices.push_back(Vertex{-1,-1,-1,1,0,0});
   mVertices.push_back(Vertex{1,-1,-1,1,0,0});
   mVertices.push_back(Vertex{-1,1,-1,1,0,0});
   mVertices.push_back(Vertex{1,-1,-1,1,0,0});
   mVertices.push_back(Vertex{1,1,-1,1,0,0});
   mVertices.push_back(Vertex{-1,1,-1,1,0,0});

   // -x veggen
   mVertices.push_back(Vertex{-1,1,-1,1,0,0});
   mVertices.push_back(Vertex{-1,-1,-1,1,0,0});
   mVertices.push_back(Vertex{-1,-1,1,1,0,0});
   mVertices.push_back(Vertex{-1,1,-1,1,0,0});
   mVertices.push_back(Vertex{-1,-1,1,1,0,0});
   mVertices.push_back(Vertex{-1,1,1,1,0,0});

   // +y veggen
   mVertices.push_back(Vertex{1,1,1,1,0,0});
   mVertices.push_back(Vertex{-1,1,1,1,0,0});
   mVertices.push_back(Vertex{-1,1,-1,1,0,0});
   mVertices.push_back(Vertex{1,1,1,1,0,0});
   mVertices.push_back(Vertex{-1,1,-1,1,0,0});
   mVertices.push_back(Vertex{1,1,-1,1,0,0});

   // + z veggen
   mVertices.push_back(Vertex{-1,-1,1,1,0,0});
   mVertices.push_back(Vertex{1,1,1,1,0,0});
   mVertices.push_back(Vertex{-1,1,1,1,0,0});
   mVertices.push_back(Vertex{-1,-1,1,1,0,0});
   mVertices.push_back(Vertex{1,-1,1,1,0,0});
   mVertices.push_back(Vertex{1,1,1,1,0,0});

   // + x veggen
   mVertices.push_back(Vertex{1,-1,-1,1,0,0});
   mVertices.push_back(Vertex{1,1,1,1,0,0});
   mVertices.push_back(Vertex{1,-1,1,1,0,0});
   mVertices.push_back(Vertex{1,-1,-1,1,0,0});
   mVertices.push_back(Vertex{1,1,-1,1,0,0});
   mVertices.push_back(Vertex{1,1,1,1,0,0});

}

Cube::Cube(Position position, Color color, Vector3 scale) : VisualObject()
{
    // -y veggen

    mVertices.push_back(Vertex{position.x-scale.x,position.y-scale.y,position.z-scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x+scale.x,position.y-scale.y,position.z+scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x-scale.x,position.y-scale.y,position.z+scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x-scale.x,position.y-scale.y,position.z-scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x+scale.x,position.y-scale.y,position.z-scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x+scale.x,position.y-scale.y,position.z+scale.z,color.r,color.g,color.b});

    // -z veggen
    mVertices.push_back(Vertex{position.x-scale.x,position.y-scale.y,position.z-scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x+scale.x,position.y-scale.y,position.z-scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x-scale.x,position.y+scale.y,position.z-scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x+scale.x,position.y-scale.y,position.z-scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x+scale.x,position.y+scale.y,position.z-scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x-scale.x,position.y+scale.y,position.z-scale.z,color.r,color.g,color.b});

    // -x veggen
    mVertices.push_back(Vertex{position.x-scale.x,position.y+scale.y,position.z-scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x-scale.x,position.y-scale.y,position.z-scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x-scale.x,position.y-scale.y,position.z+scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x-scale.x,position.y+scale.y,position.z-scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x-scale.x,position.y-scale.y,position.z+scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x-scale.x,position.y+scale.y,position.z+scale.z,color.r,color.g,color.b});

    // +y veggen
    mVertices.push_back(Vertex{position.x+scale.x,position.y+scale.y,position.z+scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x-scale.x,position.y+scale.y,position.z+scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x-scale.x,position.y+scale.y,position.z-scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x+scale.x,position.y+scale.y,position.z+scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x-scale.x,position.y+scale.y,position.z-scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x+scale.x,position.y+scale.y,position.z-scale.z,color.r,color.g,color.b});

    // + z veggen
    mVertices.push_back(Vertex{position.x-scale.x,position.y-scale.y,position.z+scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x+scale.x,position.y+scale.y,position.z+scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x-scale.x,position.y+scale.y,position.z+scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x-scale.x,position.y-scale.y,position.z+scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x+scale.x,position.y-scale.y,position.z+scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x+scale.x,position.y+scale.y,position.z+scale.z,color.r,color.g,color.b});

    // + x veggen
    mVertices.push_back(Vertex{position.x+scale.x,position.y-scale.y,position.z-scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x+scale.x,position.y+scale.y,position.z+scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x+scale.x,position.y-scale.y,position.z+scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x+scale.x,position.y-scale.y,position.z-scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x+scale.x,position.y+scale.y,position.z-scale.z,color.r,color.g,color.b});
    mVertices.push_back(Vertex{position.x+scale.x,position.y+scale.y,position.z+scale.z,color.r,color.g,color.b});
}
Cube::~Cube()
{

}

void Cube::readFile(std::string filnavn) {
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

void Cube::init(GLint matrixUniform)
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

void Cube::draw()
{
   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
   glDrawArrays(GL_TRIANGLES, 0, mVertices.size());



}
