
#include <program.h>
#include <object.h>
#include <objects.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

//  #include "external/glew-1.13.0/include/GL/glew.h"
//  #include "external/glfw-3.1.2/include/GLFW/glfw3.h"

// #include "external/glm-0.9.7.1/glm/glm.hpp"

using namespace std;

Program::Program(GLFWwindow *win, GLuint MatrixID)
{
    window = win;
    matrixID = MatrixID;
    projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    view = glm::lookAt(
        glm::vec3(2, 2, 2), // Camera is at (4,3,3), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    //*VP = *projection * *view;
    i = 0;
    prevFrameTime = 0;
    objs = new Objects(); // object datas
    objList = new Object(-1, this);
}
Program::Program()
{
    cout << "Program screwed" << endl;
}
Program::~Program()
{
    delete objs;
}

Object *Program::createObject(int index)
{
    Object *o = new Object(index, this);
    o->next = objList;
    objList = o;
    return o;
}
void Program::draw()
{
    Object *o = objList;
    while (o->data != NULL) // or o->next != NULL
    {
        o->draw();
        o = o->next;
    }
}

float totalCountedTime = 0;
int frameCount = 0;

glm::vec3 cameraPos = glm::vec3(2, 2, 2);
glm::vec3 cameraFront = glm::vec3(1, 0, 0);
glm::vec3 cameraUp = glm::vec3(0, 1, 0);
// Model matrix : an identity matrix (model will be at the origin)
// glm::mat4 Model = glm::mat4(1.0f);
// glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
float yaw0;
float pitch0;
float movementSpeed = 8.0f;

void Program::loop()
{

    time = glfwGetTime();
    i += 1;

    printTime();
    cameraControl();

    prevFrameTime = time;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) // chatgpt yazdı :(
{
    float sensitivity = 0.4f; // change this value to your liking
    static double lastX = 0, lastY = 0;
    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    // sensitivity is your mouse movement sensitivity, you can define it yourself
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    // yaw and pitch are global variables
    yaw0 += xoffset;
    pitch0 += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch0 > 89.0f)
        pitch0 = 89.0f;
    if (pitch0 < -89.0f)
        pitch0 = -89.0f;

    // cameraFront, cameraUp and cameraRight are global variables
    glm::vec3 front;
    front.x = cos(glm::radians(yaw0)) * cos(glm::radians(pitch0));
    front.y = sin(glm::radians(pitch0));
    front.z = sin(glm::radians(yaw0)) * cos(glm::radians(pitch0));
    cameraFront = glm::normalize(front);
}

void Program::cameraControl()
{
    // glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += cameraFront * (float)(time - prevFrameTime) * movementSpeed;
        cout << "cameraPos: " << cameraPos.x << " " << cameraPos.y << " " << cameraPos.z << endl;
        cout << "cameraFront: " << cameraFront.x << " " << cameraFront.y << " " << cameraFront.z << endl;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraFront * (float)(time - prevFrameTime) * movementSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * (float)(time - prevFrameTime) * movementSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * (float)(time - prevFrameTime) * movementSpeed;

    glfwSetCursorPosCallback(window, mouse_callback);

    view = glm::lookAt(
        cameraPos,               // Camera is at (4,3,3), in World Space
        cameraPos + cameraFront, // and looks at the origin
        cameraUp                 // Head is up (set to 0,-1,0 to look upside-down)
    );

    VP = projection * view;

    // Our ModelViewProjection : multiplication of our 3 matrices
    //*mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around
    // cout << "" << View[3][0] << " " << View[3][1] << " " << View[3][2] << " " << endl;
}

void Program::printTime()
{
    if (frameCount < 60)
    {
        totalCountedTime += time - prevFrameTime;
        frameCount += 1;
        // cout << "Frame count: " << frameCount << endl;
    }
    else
    {
        cout << "Average FPS: " << 100 / totalCountedTime << endl;
        frameCount = 0;
        totalCountedTime = 0;
    }

    // cout << "Time: " << time << endl;
    // cout << "Delta time: " << time - prevFrameTime << endl;
    // cout << "FPS: " << 1 / (time - prevFrameTime) << endl;
    // cout << time << " " << glfwGetTime() << endl;
}
