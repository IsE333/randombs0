#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <objects.h>
#include <object.h>

class Program
{
private:
    int i;
    double time;
    double prevFrameTime;
    GLFWwindow *window;

public:
    Objects *objs;
    Object *objList;
    GLuint matrixID;
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 VP;

    Program(GLFWwindow *window, GLuint MatrixID);
    Program();
    ~Program();
    Object *createObject(int index);
    void draw();
    void loop();
    void cameraControl();
    void printTime();
};