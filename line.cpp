#include "line.h"

Line::Line(Vertex v1, Vertex v2)
{
    mVertices.push_back(v1);
    mVertices.push_back(v2);
}

Line::Line(std::vector<QVector3D> p)
{
    for (size_t i{}; i < p.size(); i++)
    {
        mVertices.push_back(Vertex(p[i], Color::Red));
    }
}

Line::~Line()
{

}

void Line::init(GLint matrixUniform)
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

void Line::draw()
{
    if (isActive)
    {
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawArrays(GL_LINE_STRIP, 0, mVertices.size());
    }
}

void Line::draw(QMatrix4x4 transformMatrix)
{
    if (isActive)
    {
        transformMatrix *= mMatrix;
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, transformMatrix.constData());
        glDrawArrays(GL_LINE_STRIP, 0, mVertices.size());
    }
}

void Line::addVertex(Vertex v)
{
    mVertices.push_back(v);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size()*sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);
}

void Line::updateLine(QVector3D v1, QVector3D v2)
{
    mVertices[0] = Vertex(v1,mVertices[0].GetColor());
    mVertices[1] = Vertex(v2,mVertices[1].GetColor());

    init(mMatrixUniform);
}
void Line::updateLine(std::vector<QVector3D> p)
{

    for (size_t i{}; i < mVertices.size(); i++)
    {
        mVertices[i] = Vertex(p[i], Color::Red);
    }

    init(mMatrixUniform);
}
