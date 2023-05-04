#define GLEW_STATIC
#include <iostream>
#include <program.h>
#include <objects.h>
#include <object.h>
// #include "program.cpp"
// #include "objects.cpp"
//   #pragma comment(lib, "opengl32")
//   #pragma comment(lib, "glu32")

#include <glad/glad.h>
#include <gl/gl.h>
// #include <gl/glu.h>
#include <GLFW/glfw3.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

GLFWwindow *window;

// Include GLM
#include <glm/glm/gtc/matrix_transform.hpp>

// #include <shader.hpp>
#include <shader.hpp>

using namespace glm;

int main(void)
{
    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(1600, 700, "test", NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.2f, 0.0f);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders("shaders/SimpleTransform.vertexshader", "shaders/SingleColor.fragmentshader");

    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    Program prg = Program(window, MatrixID);

    GLuint vertexbuffer;

    // GLuint ucgen0 = prg.objs->create(0);
    Object *ucgen1 = prg.createObject(0);
    Object *kup = prg.createObject(1);

    do
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);

        // glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        prg.draw(); // draw all objects in the objlist
        // ucgen1.draw();
        //  kup.draw();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        prg.loop();
        // prg.draw();
        // MVP = Projection * View * Model;
        printf("a");
        // glfwSwapInterval(2);

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

    // Cleanup VBO and shader
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &VertexArrayID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
