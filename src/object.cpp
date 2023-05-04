#define GLEW_STATIC

#include <glad/glad.h>
#include <gl/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include <program.h>
#include <object.h>
#include <objectdata.h>
#include <objects.h>

using namespace glm;

Object::Object(int index, Program *p)
{
    program = p;
    this->objIndex = index;
    setObjectData();
    next = NULL;

    if (data == NULL)
    {
        if (objIndex != -1)
            std::cout << "Object data is NULL" << std::endl;
        return;
    }

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, data->VBDSize * sizeof(GLfloat), data->VBD, GL_STATIC_DRAW);
}

void Object::setObjectData()
{
    if (objIndex == -1)
    {
        data = NULL;
        return;
    }
    data = &program->objs->allObjs[objIndex];
}

void Object::draw()
{
    MVP = program->VP * Model;
    glUniformMatrix4fv(program->matrixID, 1, GL_FALSE, &MVP[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, data->VBDSize / 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}
