#include "parabel.h"
#include "logger.h"

Parabel::Parabel()
{
    double p1x = -5;
    double p2x = -4;
    double p3x = -3;
    double p4x = -1;
    double p5x = 1;
    double p6x = 3;
    double p7x = 4;
    double p8x = 5;

    double p1y = 7;
    double p2y = 5;
    double p3y = 4;
    double p4y = 3.5;
    double p5y = 3.5;
    double p6y = 4;
    double p7y = 5;
    double p8y = 7;


    y =
    {p1y,
     p2y,
     p3y,
     p4y,
     p5y,
     p6y,
     p7y,
     p8y};


    A =
    {
        {p1x * p1x,p1x,1},
        {p2x * p2x,p2x,1},
        {p3x * p3x,p3x,1},
        {p4x * p4x,p4x,1},
        {p5x * p5x,p5x,1},
        {p6x * p6x,p6x,1},
        {p7x * p7x,p7x,1},
        {p8x * p8x,p8x,1},
    };

    AT =
    {
        {p1x * p1x,p2x * p2x,p3x * p3x,p4x * p4x,p5x * p5x,p6x * p6x,p7x * p7x,p8x * p8x},
        {p1x,p2x,p3x,p4x,p5x,p6x,p7x,p8x},
        {     1,     1,     1,     1,     1,     1,     1,     1}
    };

    ATA =
    {
        {
            (AT[0][0] * A[0][0]) + (AT[0][1] * A[1][0]) + (AT[0][2] * A[2][0]) + (AT[0][3] * A[3][0]) + (AT[0][4] * A[4][0]) + (AT[0][5] * A[5][0]) + (AT[0][6] * A[6][0]) + (AT[0][7] * A[7][0]),
            (AT[0][0] * A[0][1]) + (AT[0][1] * A[1][1]) + (AT[0][2] * A[2][1]) + (AT[0][3] * A[3][1]) + (AT[0][4] * A[4][1]) + (AT[0][5] * A[5][1]) + (AT[0][6] * A[6][1]) + (AT[0][7] * A[7][1]),
            (AT[0][0] * A[0][2]) + (AT[0][1] * A[1][2]) + (AT[0][2] * A[2][2]) + (AT[0][3] * A[3][2]) + (AT[0][4] * A[4][2]) + (AT[0][5] * A[5][2]) + (AT[0][6] * A[6][2]) + (AT[0][7] * A[7][2])
        },
        {
            (AT[1][0] * A[0][0]) + (AT[1][1] * A[1][0]) + (AT[1][2] * A[2][0]) + (AT[1][3] * A[3][0]) + (AT[1][4] * A[4][0]) + (AT[1][5] * A[5][0]) + (AT[1][6] * A[6][0]) + (AT[1][7] * A[7][0]),
            (AT[1][0] * A[0][1]) + (AT[1][1] * A[1][1]) + (AT[1][2] * A[2][1]) + (AT[1][3] * A[3][1]) + (AT[1][4] * A[4][1]) + (AT[1][5] * A[5][1]) + (AT[1][6] * A[6][1]) + (AT[1][7] * A[7][1]),
            (AT[1][0] * A[0][2]) + (AT[1][1] * A[1][2]) + (AT[1][2] * A[2][2]) + (AT[1][3] * A[3][2]) + (AT[1][4] * A[4][2]) + (AT[1][5] * A[5][2]) + (AT[1][6] * A[6][2]) + (AT[1][7] * A[7][2])
        },
        {
            (AT[2][0] * A[0][0]) + (AT[2][1] * A[1][0]) + (AT[2][2] * A[2][0]) + (AT[2][3] * A[3][0]) + (AT[2][4] * A[4][0]) + (AT[2][5] * A[5][0]) + (AT[2][6] * A[6][0]) + (AT[2][7] * A[7][0]),
            (AT[2][0] * A[0][1]) + (AT[2][1] * A[1][1]) + (AT[2][2] * A[2][1]) + (AT[2][3] * A[3][1]) + (AT[2][4] * A[4][1]) + (AT[2][5] * A[5][1]) + (AT[2][6] * A[6][1]) + (AT[2][7] * A[7][1]),
            (AT[2][0] * A[0][2]) + (AT[2][1] * A[1][2]) + (AT[2][2] * A[2][2]) + (AT[2][3] * A[3][2]) + (AT[2][4] * A[4][2]) + (AT[2][5] * A[5][2]) + (AT[2][6] * A[6][2]) + (AT[2][7] * A[7][2])
        }

    };

    double a = ATA[0][0];
    double b = ATA[0][1];
    double c = ATA[0][2];

    double detA = (ATA[1][1] * ATA[2][2]) - (ATA[2][1] * ATA[1][2]);
    double detB = (ATA[1][0] * ATA[2][2]) - (ATA[2][0] * ATA[1][2]);
    double detC = (ATA[1][0] * ATA[2][1]) - (ATA[2][0] * ATA[1][1]);
    double detD = (ATA[0][1] * ATA[2][2]) - (ATA[2][1] * ATA[0][2]);
    double detE = (ATA[0][0] * ATA[2][2]) - (ATA[2][0] * ATA[0][2]);
    double detF = (ATA[0][0] * ATA[2][1]) - (ATA[2][0] * ATA[0][1]);
    double detG = (ATA[0][1] * ATA[1][2]) - (ATA[1][1] * ATA[0][2]);
    double detH = (ATA[0][0] * ATA[1][2]) - (ATA[1][0] * ATA[0][2]);
    double detI = (ATA[0][0] * ATA[1][1]) - (ATA[1][0] * ATA[0][1]);




    det = (a * detA) - (b * detB) + (c * detC);

    IB =
    {
        { detA, - detB,   detC},
        {-detD,   detE, - detF},
        { detG, - detH,   detI}
    };

    for (int i{}; i < 3 ; i++)
    {
        for (int j{}; j < 3 ; j++)
        {

            IB[j][i] *= (1.f /det);

        }


    }

    // c
    ATy =
    {
        (AT[0][0] * y[0]) + (AT[0][1] * y[1]) + (AT[0][2] * y[2]) + (AT[0][3] * y[3]) + (AT[0][4] * y[4]) + (AT[0][5] * y[5]) + (AT[0][6] * y[6]) + (AT[0][7] * y[7]),
        (AT[1][0] * y[0]) + (AT[1][1] * y[1]) + (AT[1][2] * y[2]) + (AT[1][3] * y[3]) + (AT[1][4] * y[4]) + (AT[1][5] * y[5]) + (AT[1][6] * y[6]) + (AT[1][7] * y[7]),
        (AT[2][0] * y[0]) + (AT[2][1] * y[1]) + (AT[2][2] * y[2]) + (AT[2][3] * y[3]) + (AT[2][4] * y[4]) + (AT[2][5] * y[5]) + (AT[2][6] * y[6]) + (AT[2][7] * y[7])
    };


    // x
    a1 = (IB[0][0] * ATy[0]);
    b1 = (IB[0][1] * ATy[1]);
    c1 = (IB[0][2] * ATy[2]);
    double x1 = a1 + b1 + c1;
    double x2 = (IB[1][0] * ATy[0]) + (IB[1][1] * ATy[1]) + (IB[1][2] * ATy[2]);
    a1 = (IB[2][0] * ATy[0]);
    b1 = (IB[2][1] * ATy[1]);
    c1 = (IB[2][2] * ATy[2]);
    double x3 = a1+b1+c1;
    IBATy =
    {
        x1,
        x2,
        x3
    };




    float n = 100;
    float start = p1x;
    float end = p8x;

    float h = (end-start)/n;

    Color blue = Color::Blue;
    for (auto x = start; x < end; x += h)
    {
        float y = (IBATy[0] * x * x) + (IBATy[1] * x) + IBATy[2];
        mVertices.push_back(Vertex(Position(x,y,1), blue));
    }

}

Parabel::~Parabel()
{

}

void Parabel::init(GLint matrixUniform)
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

void Parabel::draw()
{
    if (isActive)
    {
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawArrays(GL_LINE_STRIP, 0, mVertices.size());
    }
}
void Parabel::draw(QMatrix4x4 transformMatrix)
{
    if (isActive)
    {
        transformMatrix *= mMatrix;
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, transformMatrix.constData());
        glDrawArrays(GL_LINE_STRIP, 0, mVertices.size());
    }
}

