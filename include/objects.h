#pragma once

#include <objectdata.h>

class Objects
{
public:
    // other members go here
    static ObjectData *allObjs;
    // static std::vector<ObjectData *> allObjs;

    ObjectData *cube;
    ObjectData *triangle;
    //  move cubeVBD to the end of the class definition
    //  GLfloat *cubeVBD;
    //  GLfloat *triangleVBD;

    Objects();
    ~Objects();
    // GLuint create(int objIndex); // returns vertexbuffer
    // void draw(GLuint vertexbuffer);
};