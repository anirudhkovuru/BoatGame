#include "sea.h"
#include "main.h"

Sea::Sea(color_t color)
{
    static const GLfloat vertex_buffer_data[] = {
        1000.0f,-0.55f, 1000.0f,
        -1000.0f, -0.55f, 1000.0f,
        -1000.0f, -0.55f,-1000.0f,

        1000.0f,-0.55f, 1000.0f,
        1000.0f, -0.55f,-1000.0f,
        -1000.0f, -0.55f,-1000.0f,

        1000.0f,-500.55f, 1000.0f,
        -1000.0f, -500.55f, 1000.0f,
        -1000.0f, -500.55f,-1000.0f,

        1000.0f,-500.55f, 1000.0f,
        1000.0f, -500.55f,-1000.0f,
        -1000.0f, -500.55f,-1000.0f,

        1000.0f,-0.55f, 1000.0f,
        -1000.0f, -0.55f, 1000.0f,
        -1000.0f, -500.55f, 1000.0f,

        1000.0f,-500.55f, 1000.0f,
        -1000.0f, -500.55f, 1000.0f,
        1000.0f, -0.55f, 1000.0f,

        -1000.0f,-0.55f, -1000.0f,
        1000.0f, -0.55f, -1000.0f,
        1000.0f, -500.55f, -1000.0f,

        -1000.0f,-500.55f, -1000.0f,
        1000.0f, -500.55f, -1000.0f,
        -1000.0f, -0.55f, -1000.0f,

        -1000.0f,-0.55f, -1000.0f,
        -1000.0f, -0.55f, 1000.0f,
        -1000.0f, -500.55f, 1000.0f,

        -1000.0f,-500.55f, -1000.0f,
        -1000.0f, -500.55f, 1000.0f,
        -1000.0f, -0.55f, -1000.0f,

        1000.0f,-0.55f, 1000.0f,
        1000.0f, -0.55f, -1000.0f,
        1000.0f, -500.55f, -1000.0f,

        1000.0f,-500.55f, 1000.0f,
        1000.0f, -500.55f, -1000.0f,
        1000.0f, -0.55f, 1000.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Sea::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

