#ifndef WRITEFILE_H
#define WRITEFILE_H

#include <vector>
#include "vertex.h"

class WriteFile
{
public:
    WriteFile();

    void makeFile();
private:
    std::vector<Vertex> mVertices;
};

#endif // WRITEFILE_H
