#include "landscape.h"


Landscape::Landscape(QVector2D bottomLeft, QVector2D topRight)
{
    mPersitence = 0.5;
    mLacunarity = 2;
    mOctaves = 4;
    mScale = 4;

    float minX = bottomLeft.x();
    float maxX = topRight.x();

    float minY = bottomLeft.y();
    float maxY = topRight.y();


    float step = 0.05f;

    Color color;
    for (auto y = minY; y < maxY; y += step)
    {
        for (auto x = minX; x < maxX; x += step)
        {
            float z = f(x,y);

            color = recalc(z);
            mVertices.push_back(Vertex(Position(x,y,z), color));

            z = f(x+step,y);
            color = recalc(z);
            mVertices.push_back(Vertex(Position(x + step,y,z), color));

            z = f(x,y+step);
            color = recalc(z);
            mVertices.push_back(Vertex(Position(x,y + step,z), color));


            z = f(x+step,y);
            color = recalc(z);
            mVertices.push_back(Vertex(Position(x + step,y,z), color));

            z = f(x+step,y+step);
            color = recalc(z);
            mVertices.push_back(Vertex(Position(x + step,y + step,z), color));

            z = f(x,y+step);
            color = recalc(z);
            mVertices.push_back(Vertex(Position(x,y + step,z), color));
        }
    }
}

Landscape::~Landscape()
{

}

void Landscape::update(int _octaves, float _persistance, float _lacunarity, float _scale)
{
    mOctaves = _octaves;
    mPersitence = _persistance;
    mLacunarity = _lacunarity;
    mScale = _scale;


    for(size_t i{}; i < mVertices.size();i++)
    {
        float z = f(mVertices[i].GetX(), mVertices[i].GetY());
        Position pos = Position(mVertices[i].GetX(), mVertices[i].GetY(), z);
        mVertices[i] = Vertex(pos,recalc(z));
    }
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size()*sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);
}

void Landscape::init(GLint matrixUniform)
{
    mMatrixUniform = matrixUniform;
    initializeOpenGLFunctions();


    //Vertex Array Object - VAO
    glGenVertexArrays( 1, &mVAO );
    glBindVertexArray( mVAO );


    //Vertex Buffer Object to hold vertices - VBO
    glGenBuffers( 1, &mVBO );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO );


    glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW );


    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex),  (GLvoid*)(3 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(1);


    glBindVertexArray(0);
}

void Landscape::draw()
{
    if (isActive)
    {
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    }
}
void Landscape::draw(QMatrix4x4 transformMatrix)
{
    if (isActive)
    {
        transformMatrix *= mMatrix;
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, transformMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    }
}

float Landscape::f(float x, float y)
{

    float noiseHeight = 0;
    int octaves = mOctaves;
    float scale = mScale;
    float amplitude = 1;
    float frequency = 1;
    float persitence = mPersitence;
    float lacunarity = mLacunarity;
    PerlinNoise mPerlin = PerlinNoise();
    for (int i{}; i < octaves; i++)
    {
        double xP = (double)x /scale;
        double yP = (double)y /scale;

        xP *= frequency;
        yP *= frequency;

        float perlinValue = mPerlin.noise(xP,yP,1) * 2 - 1;
        noiseHeight += perlinValue * amplitude;

        amplitude *= persitence;
        frequency *= lacunarity;
    }

    return noiseHeight;

}

Color Landscape::recalc(float z)
{
    Color color;
    float blue = -0.5;
    float green = 0.6;


    if (z < blue)
    {
        color = Color::Blue;
        color *= abs(z) + 0.1;
    }
    else if (z < green)
    {
        color = Color::Green;
        color *= abs(z);
    }
    else
    {
        color = Color::White;
        color *= z;
    }
    return color;
}

