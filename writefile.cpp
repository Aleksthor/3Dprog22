#include "writefile.h"
#include <fstream>
#include <cmath>
#include "logger.h"


WriteFile::WriteFile()
{
    float xmin=-1.0f, xmax=1.0f, ymin=-1.0f, ymax=1.0f, h=0.125f;
    for (float x = xmin; x < xmax; x += h)
    {
        for (float y = ymin; y < ymax; y += h)
        {
            // f (x,y) = sin (x * root(x^2 + y^2))
            float z = sin(M_PI * sqrt(x * x + y * y));
            mVertices.push_back(Vertex(Position(x,y,z), Color(0,0,z)));

            z = sin(M_PI * sqrt((x + h) * (x + h) + y * y));
            mVertices.push_back(Vertex(Position(x + h,y,z), Color(0,0,z)));

            z = sin(M_PI * sqrt(x * x + (y + h) * (y + h)));
            mVertices.push_back(Vertex(Position(x,y + h,z), Color(0,0,z)));



            z = sin(M_PI * sqrt((x + h) * (x + h) + y * y));
            mVertices.push_back(Vertex(Position(x + h,y,z), Color(0 + h,0 + h,z + h)));

            z = sin(M_PI * sqrt((x + h) * (x + h) + (y + h) * (y + h)));
            mVertices.push_back(Vertex(Position(x + h,y + h,z), Color(0 + h,0 + h,z + h)));

            z = sin(M_PI * sqrt(x * x + (y + h) * (y + h)));
            mVertices.push_back(Vertex(Position(x,y + h,z), Color(0 + h,0 + h,z + h)));
        }
    }
}

void WriteFile::makeFile()
{
    // Write mesh to file
    std::fstream data;
    data.open("SurfaceO1.txt",  std::fstream::in | std::fstream::out | std::fstream::trunc);

    data << mVertices.size() << std::endl << std::endl;

    for(size_t i = 0; i < mVertices.size(); i++)
    {
        data << mVertices[i] << std::endl;
        std::cout << std::endl;
    }

    data.close();
}
