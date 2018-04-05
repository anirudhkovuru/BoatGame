#include "gift.h"
#include "main.h"

Gift::Gift(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speedy = 0.1;
    accelaratey = 0.01;

    static const GLfloat vertex_buffer_data[] = {
        -0.15f, 0.25f, 0.15f,
        0.15f, 0.25f, 0.15f,
        0.15f,-0.25f, 0.15f,

        -0.15f, 0.25f, 0.15f,
        -0.15f,-0.25f, 0.15f,
        0.15f,-0.25f, 0.15f,

        -0.15f, 0.25f,-0.15f,
        0.15f, 0.25f,-0.15f,
        0.15f,-0.25f,-0.15f,

        -0.15f, 0.25f,-0.15f,
        -0.15f,-0.25f,-0.15f,
        0.15f,-0.25f,-0.15f,

        0.15f, 0.25f, 0.15f,
        0.15f, 0.25f,-0.15f,
        0.15f,-0.25f, 0.15f,

        0.15f,-0.25f,-0.15f,
        0.15f, 0.25f,-0.15f,
        0.15f,-0.25f, 0.15f,

        -0.15f, 0.25f, 0.15f,
        -0.15f, 0.25f,-0.15f,
        -0.15f,-0.25f, 0.15f,

        -0.15f,-0.25f,-0.15f,
        -0.15f, 0.25f,-0.15f,
        -0.15f,-0.25f, 0.15f,

        -0.15f, 0.25f, 0.15f,
        -0.15f, 0.25f,-0.15f,
        0.15f, 0.25f, 0.15f,

        0.15f, 0.25f, 0.15f,
        0.15f, 0.25f,-0.15f,
        -0.15f, 0.25f,-0.15f,

        -0.15f,-0.25f, 0.15f,
        -0.15f,-0.25f,-0.15f,
        0.15f,-0.25f, 0.15f,

        0.15f,-0.25f, 0.15f,
        0.15f,-0.25f,-0.15f,
        -0.15f,-0.25f,-0.15f,
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Gift::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Gift::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Gift::tick() {
    this->position.y += speedy;
    speedy -= accelaratey;
    if (this->position.y < 0.125) {
        speedy = 0.02;
        accelaratey = 0.001;
    }
    else if (this->position.y > 0.375) {
        speedy = -0.02;
        accelaratey = -0.001;
    }
}

bounding_box_t Gift::bounding_box() {
    float x = this->position.x, y = this->position.z;
    bounding_box_t bbox = { x, y, 0.3f, 0.3f };
    return bbox;
}

