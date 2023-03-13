#include "interpo2.h"
#include "logger.h"

InterpO2::InterpO2()
{
    QVector2D p1 = QVector2D(-2,2);
    QVector2D p2 = QVector2D(0,4);
    QVector2D p3 = QVector2D(2,3);
    QVector2D p4 = QVector2D(5,6);


    A.setRow(0, QVector4D(p1.x()*p1.x()*p1.x(), p1.x() * p1.x(), p1.x(), 1));
    A.setRow(1, QVector4D(p2.x()*p2.x()*p2.x(), p2.x() * p2.x(), p2.x(), 1));
    A.setRow(2, QVector4D(p3.x()*p3.x()*p3.x(), p3.x() * p3.x(), p3.x(), 1));
    A.setRow(3, QVector4D(p4.x()*p4.x()*p4.x(), p4.x() * p4.x(), p4.x(), 1));

    IA = A.inverted();

    B.setX(p1.y());
    B.setY(p2.y());
    B.setZ(p3.y());
    B.setW(p4.y());

    X = IA * B;


    float n = 100;
    float start = p1.x();
    float end = p4.x();

    float h = (end-start)/n;
    Color orange = Color::Orange;
    for (auto x = start; x < end; x += h)
    {
        float y = (X.x() * x * x * x) + (X.y() * x * x) + (X.z() * x) + X.w();
        mVertices.push_back(Vertex(Position(0,x,y), orange));
    }

}
InterpO2::~InterpO2()
{

}

void InterpO2::init(GLint matrixUniform)
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

    Logger* logger = Logger::getInstance();

    logger->logText(std::to_string(X[0]));

    logger->logText(std::to_string(X[1]));

    logger->logText(std::to_string(X[2]));

    logger->logText(std::to_string(X[3]));
}

void InterpO2::draw()
{
    if (isActive)
    {
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawArrays(GL_LINE_STRIP, 0, mVertices.size());
    }

}

void InterpO2::draw(QMatrix4x4 transformMatrix)
{
    if (isActive)
    {
        transformMatrix *= mMatrix;
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, transformMatrix.constData());
        glDrawArrays(GL_LINE_STRIP, 0, mVertices.size());
    }
}
