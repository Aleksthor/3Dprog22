#include "bspline.h"

BSpline::BSpline(std::vector<QVector2D> _points, std::vector<float> _knots)
    : points(_points), knots(_knots)
{
    if (points.size() < 4)
    {
        std::cout << "couldnt make bspline, not enough points" << std::endl;
        return;
    }
    if (knots.size() != points.size() + 4)
    {
        std::cout << "couldnt make bspline, knot vector size wrong" << std::endl;
        return;
    }

    for (int i = 0; i < (int)points.size() - 3; i++)
    {
        for (float j = 0.1f; j <= 1.f; j+=0.1f)
        {
            float pos1x = B(i,3,(float)i+j)   * points[i].x();
            float pos2x = B(i+1,3,(float)i+j) * points[i+1].x();
            float pos3x = B(i+2,3,(float)i+j) * points[i+2].x();
            float pos4x = B(i+3,3,(float)i+j) * points[i+3].x();

            float pos1y = B(i,3,(float)i+j)   * points[i].y();
            float pos2y = B(i+1,3,(float)i+j) * points[i+1].y();
            float pos3y = B(i+2,3,(float)i+j) * points[i+2].y();
            float pos4y = B(i+3,3,(float)i+j) * points[i+3].y();

            QVector2D vertex = QVector2D(pos1x+pos2x+pos3x+pos4x,pos1y+pos2y+pos3y+pos4y);
            mVertices.push_back(Vertex(QVector3D(vertex.x(),5,vertex.y()),QVector3D(1,1,1)));
            std::cout << "ADDING VERTEX :" << vertex.x() << ", " << vertex.y() <<std::endl;
        }
    }


}

BSpline::~BSpline()
{

}

void BSpline::init(GLint matrixUniform)
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

void BSpline::draw()
{
    if (isActive)
    {
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawArrays(GL_LINE_STRIP, 0, mVertices.size());
    }
}

void BSpline::draw(QMatrix4x4 transformMatrix)
{
    if (isActive)
    {
        transformMatrix *= mMatrix;
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, transformMatrix.constData());
        glDrawArrays(GL_LINE_STRIP, 0, mVertices.size());
    }
}

float BSpline::B(int i, int d, float x)
{  
    // If we're ont he bottom level
    if (d <= 0)
    {
        // If we're at the end : 0
        if ((int)knots.size() <= i+1) return 0;

        // If we're inside our allowed area : 1
        if (x > knots[i] && x < knots[i+1]) return 1;

        return 0;
    }

    // If we cant access knots[i+d] we cant get anythin : 0
    if ((int)knots.size() <= i + d)
    {
        return 0;
    }
    else
    {
        // if we cant access knots[i+d+1] just return the first half
        if ((int)knots.size() <= i + d + 1)
        {
            // check if divisor is 0
            if (knots[i + d] - knots[i] == 0)
            {
                return 0;
            }
            else
            {
                // Wi,d * Bi,d-1
                return ((x - knots[i]) / (knots[i + d] - knots[i])) * B(i,d-1,x);
            }
        }
        // If we can access the latter part, knots[i+d+1]
        else
        {
            // if divisor is 0 in Wi,d
            if (knots[i + d] - knots[i] == 0)
            {
                // if divisor is + in wi+1,d
                if (knots[i + d + 1] - knots[i + 1] == 0)
                {
                    return 0;
                }
                else
                {
                    // (1 - Wi+1,d) * Bi+1,d-1
                    return (1 - ((x - knots[i + 1]) / (knots[i + d + 1] - knots[i + 1]))) * B(i + 1, d - 1, x);
                }

            }
            // First half is okay
            else
            {
                // if divisor is 0 in Wi+1,d
                if (knots[i + d + 1] - knots[i + 1] == 0)
                {
                    // Wi,d * Bi,d-1
                    return ((x - knots[i]) / (knots[i + d] - knots[i])) * B(i,d-1,x);
                }
                // Everything is okay
                else
                {
                   // Wi,d * Bi,d-1 + (1 - Wi+1,d) * Bi+1,d-1
                   return ((x - knots[i]) / (knots[i + d] - knots[i])) * B(i,d-1,x) + ((1 - ((x - knots[i + 1]) / (knots[i + d + 1] - knots[i + 1]))) * B(i + 1, d - 1, x));
                }

            }


        }
    }

}

