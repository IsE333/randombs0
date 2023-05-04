#pragma once
#include <program.h>
#include <objectdata.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>

class Program;

class Object
{
public:
    int objIndex;
    GLuint vertexbuffer;
    ObjectData *data;
    Object *next;
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 MVP;
    Program *program;

    Object(int index, Program *p);

    void draw();

private:
    void setObjectData();
};