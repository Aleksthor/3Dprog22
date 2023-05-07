#include "pointso2.h"

PointsO2::PointsO2()
{
    mVertices.push_back(Vertex(Position(0,-2,2), QVector3D()));
    mVertices.push_back(Vertex(Position(0,0,4), QVector3D()));
    mVertices.push_back(Vertex(Position(0,2,3), QVector3D()));
    mVertices.push_back(Vertex(Position(0,5,6), QVector3D()));
}

PointsO2::PointsO2(std::vector<QVector3D> points)
{
    for (int i = 0; i < (int)points.size(); i++)
    {
        mVertices.push_back(Vertex(points[i], QVector3D()));
    }


//    mVertices.push_back(Vertex(Position(0,-5,7), Color::Blue));
//    mVertices.push_back(Vertex(Position(0,-4,5), Color::Blue));
//    mVertices.push_back(Vertex(Position(0,-3,4), Color::Blue));
//    mVertices.push_back(Vertex(Position(0,-1,3.5f), Color::Blue));
//    mVertices.push_back(Vertex(Position(0,1,3.5f), Color::Blue));
//    mVertices.push_back(Vertex(Position(0,3,4), Color::Blue));
//    mVertices.push_back(Vertex(Position(0,4,5), Color::Blue));
//    mVertices.push_back(Vertex(Position(0,5,7), Color::Blue));
}

PointsO2::~PointsO2()
{

}

void PointsO2::init(GLint matrixUniform)
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

void PointsO2::draw()
{
    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glPointSize(7.f);
    glDrawArrays(GL_POINTS, 0, mVertices.size());
}
void PointsO2::draw(QMatrix4x4 transformMatrix)
{
    if (isActive)
    {
        transformMatrix *= mMatrix;
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, transformMatrix.constData());
        glPointSize(7.f);
        glDrawArrays(GL_POINTS, 0, mVertices.size());
    }
}

