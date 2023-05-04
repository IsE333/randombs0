#pragma once
#include <glad/glad.h>

class ObjectData
{
public:
    ObjectData();
    ObjectData(GLfloat *VBD, int VBDSize);
    GLfloat *VBD;
    int VBDSize;

protected:
private:
};
