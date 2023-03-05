#include "tetraeder.h"
#include <cmath>

Tetraeder::Tetraeder() : VisualObject()
{
    Position A = Position(0,1,0);
    Position B = Position(0,0,1/sqrt(3));

    QVector2D p1 = rotatePoint(QVector2D(0,B.z), 4*M_PI/3);
    QVector2D p2 = rotatePoint(QVector2D(0,B.z), 2*M_PI/3);

    Position C = Position(p1.x(),0,p1.y());
    Position D = Position(p2.x(),0,p2.y());

    // Lag Trekant 1
    mVertices.push_back(Vertex(B, Color::Red));
    mVertices.push_back(Vertex(C, Color::Red));
    mVertices.push_back(Vertex(D, Color::Red));

    // Lag Trekant 2
    mVertices.push_back(Vertex(B, Color::Blue));
    mVertices.push_back(Vertex(C, Color::Blue));
    mVertices.push_back(Vertex(A, Color::Blue));

    // Lag Trekant 3
    mVertices.push_back(Vertex(D, Color::Green));
    mVertices.push_back(Vertex(B, Color::Green));
    mVertices.push_back(Vertex(A, Color::Green));

    // Lag Trekant 4
    mVertices.push_back(Vertex(C, Color::Purple));
    mVertices.push_back(Vertex(D, Color::Purple));
    mVertices.push_back(Vertex(A, Color::Purple));
}



Tetraeder::~Tetraeder()
{

}

void Tetraeder::init(GLint matrixUniform)
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

void Tetraeder::draw()
{
    if (isActive)
    {
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    }
}
void Tetraeder::draw(QMatrix4x4& transformMatrix)
{
    if (isActive)
    {
        transformMatrix *= mMatrix;
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, transformMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    }
}


QVector2D Tetraeder::rotatePoint(QVector2D point, float angle)
{
    QVector2D returnVector = QVector2D();

    returnVector.setX((point.x()* std::cos(angle)) - (point.y() * std::sin(angle)));
    returnVector.setY((point.x() * std::sin(angle)) + (point.y() * std::cos(angle)));

    return returnVector;
}
