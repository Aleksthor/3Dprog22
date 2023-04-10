#include "landscape.h"
#include "stb_image.h"
#include "logger.h"

Landscape::Landscape(QVector2D bottomLeft, QVector2D topRight)
{

    height = 0;
    mPersitence = 0.5;
    mLacunarity = 2;
    mOctaves = 4;
    mScale = 4;
    width = 0;

    float minX = bottomLeft.x();
    float maxX = topRight.x();

    float minY = bottomLeft.y();
    float maxY = topRight.y();


    float step = 0.5f;

    for (auto y = minY; y < maxY; y += step)
    {
        height++;
        for (auto x = minX; x < maxX; x += step)
        {
            width++;
            float z = f(x,y);
            mVertices.push_back(Vertex(QVector3D(x,y,z), QVector3D(0,0,1), UV(x,y))); // UV's wrong

        }
    }


    width /= height;
    for (auto y = 0; y < height - 1; y++)
    {
        for (auto x = 0; x < width - 1; x++)
        {
            mIndices.push_back((y * width) + x);
            mIndices.push_back((y * width) + x + 1);
            mIndices.push_back((y * width) + x + width);

            mIndices.push_back((y * width) + x + 1);
            mIndices.push_back((y * width) + x + width + 1);
            mIndices.push_back((y * width) + x + width);
        }
    }
    for (auto y = 0; y < height - 1; y++)
    {
        for (auto x = 0; x < width - 1; x++)
        {
            QVector3D normal = QVector3D();
            int numOfTriangles = 0;

            QVector3D ourpos = mVertices[x + (y * width)].GetPosition3D();


            QVector3D north = mVertices[x + (y * width) + width].GetPosition3D() - ourpos;
            QVector3D east = mVertices[x + (y * width) + 1].GetPosition3D() - ourpos;



            // Our Own Triangle (NE)
            // East vector crossed with North vector
            normal += QVector3D::crossProduct(east,north).normalized();
            numOfTriangles++;
            // Triangle 2 (SE)
            if (x + (y * width) - width > 0 && x + (y * width) % width != width - 1)
            {
                QVector3D south = mVertices[x + (y * width) - width].GetPosition3D() - ourpos;
                QVector3D southEast = mVertices[x + (y * width) - width + 1].GetPosition3D() - ourpos;
                // SouthEast vector crossed with East vector
                normal += QVector3D::crossProduct(southEast,east).normalized();
                numOfTriangles++;
                // South vector crossed with SouthEast vector
                normal += QVector3D::crossProduct(south,southEast).normalized();
                numOfTriangles++;
            }
            // Triangle 3 (SW)
            if (x + (y * width) - width - 1 > 0 && x + (y * width) % width != 0)
            {
                QVector3D south = mVertices[x + (y * width) - width].GetPosition3D() - ourpos;
                QVector3D west = mVertices[x + (y * width) - 1].GetPosition3D() - ourpos;
                // West vector crossed with South vector
                normal += QVector3D::crossProduct(west,south).normalized();
                numOfTriangles++;

            }
            // Triangle 4 (NW)
            if (x + (y * width) - 1 > 0 && x + (y * width) % width != 0)
            {
                QVector3D northWest = mVertices[x + (y * width) + width - 1].GetPosition3D() - ourpos;
                QVector3D west = mVertices[x + (y * width) - 1].GetPosition3D() - ourpos;
                // West vector crossed with NorthWest vector
                normal += QVector3D::crossProduct(northWest,west).normalized();
                numOfTriangles++;
                // North vector crossed with NorthWest vector
                normal += QVector3D::crossProduct(north,northWest).normalized();
                numOfTriangles++;

            }
            normal /= numOfTriangles;

            mVertices[x + (y * width)].SetNormal(normal.normalized());
        }
    }


}

Landscape::Landscape(std::string fileLocation)
{

    int Width, Height, nrChannels;
    unsigned char *data = stbi_load(fileLocation.c_str(), &Width, &Height, &nrChannels, 0);

    if (data)
    {
        std::cout << fileLocation.c_str() << std::endl;
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    int a = 0, b = 0;
    for (int y = -Height / 2; y < Height/ 2; y ++)
    {
        b++;
        a = 0;
        for (int x = -Width / 2; x < Width/ 2; x++)
        {
            a++;
            float z = 0;
            for (int i{}; i < nrChannels; i++)
            {
                z +=data[a + (b * Width) * nrChannels + i ];
            }
            z /= nrChannels * 4;
            mVertices.push_back(Vertex(QVector3D(x,y,z), QVector3D(0,0,1), UV(x,y))); // UV's wrong
        }
    }


    for (int y = 0; y < Height - 1; y++)
    {
        for (int x = 0; x < Width - 1; x++)
        {
            mIndices.push_back((y * Width) + x);
            mIndices.push_back((y * Width) + x + 1);
            mIndices.push_back((y * Width) + x + Width);

            mIndices.push_back((y * Width) + x + 1);
            mIndices.push_back((y * Width) + x + Width + 1);
            mIndices.push_back((y * Width) + x + Width);
        }
    }
    for (auto y = 0; y < Height - 1; y++)
    {
        for (auto x = 0; x < Width - 1; x++)
        {
            QVector3D normal = QVector3D();
            int numOfTriangles = 0;

            // Our Own Triangle (NE)
            // East vector crossed with North vector
            normal += QVector3D::crossProduct(mVertices[x + (y * Width) + 1].GetPosition3D() - mVertices[x + (y * Width)].GetPosition3D(),
                                              mVertices[x + (y * Width) + 1].GetPosition3D() - mVertices[x + (y * Width)].GetPosition3D());
            numOfTriangles++;
            // Triangle 2 (SE)
            if (x + (y * Width) - Width > 0 && x + (y * Width) - Width % Width != Width - 1)
            {
                // SouthEast vector crossed with East vector
                normal += QVector3D::crossProduct(mVertices[x + (y * Width) - Width + 1].GetPosition3D() - mVertices[x + (y * Width)].GetPosition3D(),
                                                  mVertices[x + (y * Width) + 1].GetPosition3D()         - mVertices[x + (y * Width)].GetPosition3D());
                numOfTriangles++;
                // South vector crossed with SouthEast vector
                normal += QVector3D::crossProduct(mVertices[x + (y * Width) - Width].GetPosition3D()     - mVertices[x + (y * Width)].GetPosition3D(),
                                                  mVertices[x + (y * Width) - Width + 1].GetPosition3D() - mVertices[x + (y * Width)].GetPosition3D());
                numOfTriangles++;
            }
            // Triangle 3 (SW)
            if (x + (y * Width) - Width - 1 > 0 && x + (y * Width) - Width - 1 % Width != 0)
            {
                // West vector crossed with South vector
                normal += QVector3D::crossProduct(mVertices[x + (y * Width) - Width].GetPosition3D()     - mVertices[x + (y * Width)].GetPosition3D(),
                                                  mVertices[x + (y * Width) - Width + 1].GetPosition3D() - mVertices[x + (y * Width)].GetPosition3D());
                numOfTriangles++;

            }
            // Triangle 3 (SW)
            if (x + (y * Width) - 1 > 0 && x + (y * Width) - 1 % Width != 0)
            {
                // NorthWest vector crossed with West vector
                normal += QVector3D::crossProduct(mVertices[x + (y * Width) - 1].GetPosition3D()         - mVertices[x + (y * Width)].GetPosition3D(),
                                                  mVertices[x + (y * Width) + Width - 1].GetPosition3D() - mVertices[x + (y * Width)].GetPosition3D());
                numOfTriangles++;
                // North vector crossed with NorthWest vector
                normal += QVector3D::crossProduct(mVertices[x + (y * Width) + 1].GetPosition3D() - mVertices[x + (y * Width)].GetPosition3D(),
                                                  mVertices[x + (y * Width) - 1].GetPosition3D() - mVertices[x + (y * Width)].GetPosition3D());
                numOfTriangles++;

            }
            normal /= numOfTriangles;

            mVertices[x + (y * Width)].SetNormal(normal);
        }
    }

    width = Width;
    height = Height;

    stbi_image_free(data);
}

Landscape::~Landscape()
{

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

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndices), mIndices.data(), GL_STATIC_DRAW);

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
        glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, mIndices.data());
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

QVector2D Landscape::GetVertexPos(QVector3D playerPos)
{
    float minX = mVertices[0].GetX();
    float maxX = mVertices[mVertices.size() - 1].GetX();

    float minY = mVertices[0].GetY();
    float maxY = mVertices[mVertices.size() - 1].GetY();

    if (playerPos.x() < minX || playerPos.x() > maxX) return QVector2D(-10,-10);
    if (playerPos.y() < minY || playerPos.y() > maxY) return QVector2D(-10,-10);

    QVector2D vertexPos;
    int x = 0;
    bool setX = false;
    for(int i = -width / 2; i < width/ 2; i ++)
    {
        if (i + 1 > playerPos.x() && !setX)
        {
            vertexPos.setX(x);
            setX = true;
        }
        x++;
    }

    int y = 0;
    bool setY = false;
    for(int i = -height / 2; i < height/ 2; i ++)
    {
        if (i + 1 > playerPos.y() && !setY)
        {
            vertexPos.setY(y);
            setY = true;
        }
        y++;
    }



    return vertexPos;
}


