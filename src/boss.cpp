#include "boss.h"
#include "main.h"

Boss::Boss(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->front = glm::vec3(0, 0, 1);
    speedx = 0;
    speedy = 0;
    speedz = 0;
    gravity = 0.01;
    this->range = glm::vec3(16, 0, 16);

    static const GLfloat vertex_buffer_data[] = {
        //body
        -4.0f, 5.0f, 4.0f,
        4.0f, 5.0f, 4.0f,
        4.0f,-5.0f, 4.0f,

        -4.0f, 5.0f, 4.0f,
        -4.0f,-5.0f, 4.0f,
        4.0f,-5.0f, 4.0f,

        -4.0f, 5.0f,-4.0f,
        4.0f, 5.0f,-4.0f,
        4.0f,-5.0f,-4.0f,

        -4.0f, 5.0f,-4.0f,
        -4.0f,-5.0f,-4.0f,
        4.0f,-5.0f,-4.0f,

        4.0f, 5.0f, 4.0f,
        4.0f, 5.0f,-4.0f,
        4.0f,-5.0f, 4.0f,

        4.0f,-5.0f,-4.0f,
        4.0f, 5.0f,-4.0f,
        4.0f,-5.0f, 4.0f,

        -4.0f, 5.0f, 4.0f,
        -4.0f, 5.0f,-4.0f,
        -4.0f,-5.0f, 4.0f,

        -4.0f,-5.0f,-4.0f,
        -4.0f, 5.0f,-4.0f,
        -4.0f,-5.0f, 4.0f,

        -4.0f, 5.0f, 4.0f,
        -4.0f, 5.0f,-4.0f,
        4.0f, 5.0f, 4.0f,

        4.0f, 5.0f, 4.0f,
        4.0f, 5.0f,-4.0f,
        -4.0f, 5.0f,-4.0f,

        -4.0f,-5.0f, 4.0f,
        -4.0f,-5.0f,-4.0f,
        4.0f,-5.0f, 4.0f,

        4.0f,-5.0f, 4.0f,
        4.0f,-5.0f,-4.0f,
        -4.0f,-5.0f,-4.0f,

        //eye
        -3.0f, 4.0f, 4.01f,
        3.0f, 4.0f, 4.01f,
        3.0f, 0.0f, 4.01f,

        -3.0f, 4.0f, 4.01f,
        3.0f, 0.0f, 4.01f,
        -3.0f, 0.0f, 4.01f,

        -1.0f, 2.5f, 4.02f,
        1.0f, 2.5f, 4.02f,
        1.0f, 1.5f, 4.02f,

        -1.0f, 2.5f, 4.02f,
        -1.0f, 1.5f, 4.02f,
        1.0f, 1.5f, 4.02f,

        //arms
        4.0f, 1.0f, 5.0f,
        6.0f, 1.0f, 5.0f,
        6.0f,-3.0f, 5.0f,

        4.0f, 1.0f, 5.0f,
        4.0f,-3.0f, 5.0f,
        6.0f,-3.0f, 5.0f,

        4.0f, 1.0f,0.0f,
        6.0f, 1.0f,0.0f,
        6.0f,-3.0f,0.0f,

        4.0f, 1.0f,0.0f,
        4.0f,-3.0f,0.0f,
        6.0f,-3.0f,0.0f,

        6.0f, 1.0f, 5.0f,
        6.0f, 1.0f,0.0f,
        6.0f,-3.0f, 5.0f,

        6.0f,-3.0f,0.0f,
        6.0f, 1.0f,0.0f,
        6.0f,-3.0f, 5.0f,

        4.0f, 1.0f, 5.0f,
        4.0f, 1.0f,0.0f,
        4.0f,-3.0f, 5.0f,

        4.0f,-3.0f,0.0f,
        4.0f, 1.0f,0.0f,
        4.0f,-3.0f, 5.0f,

        4.0f, 1.0f, 5.0f,
        4.0f, 1.0f,0.0f,
        6.0f, 1.0f, 5.0f,

        6.0f, 1.0f, 5.0f,
        6.0f, 1.0f,0.0f,
        4.0f, 1.0f,0.0f,

        4.0f,-3.0f, 5.0f,
        4.0f,-3.0f,0.0f,
        6.0f,-3.0f, 5.0f,

        6.0f,-3.0f, 5.0f,
        6.0f,-3.0f,0.0f,
        4.0f,-3.0f,0.0f,

        //arm 2
        -4.0f, 1.0f, 5.0f,
        -6.0f, 1.0f, 5.0f,
        -6.0f,-3.0f, 5.0f,

        -4.0f, 1.0f, 5.0f,
        -4.0f,-3.0f, 5.0f,
        -6.0f,-3.0f, 5.0f,

        -4.0f, 1.0f,0.0f,
        -6.0f, 1.0f,0.0f,
        -6.0f,-3.0f,0.0f,

        -4.0f, 1.0f,0.0f,
        -4.0f,-3.0f,0.0f,
        -6.0f,-3.0f,0.0f,

        -6.0f, 1.0f, 5.0f,
        -6.0f, 1.0f,0.0f,
        -6.0f,-3.0f, 5.0f,

        -6.0f,-3.0f,0.0f,
        -6.0f, 1.0f,0.0f,
        -6.0f,-3.0f, 5.0f,

        -4.0f, 1.0f, 5.0f,
        -4.0f, 1.0f,0.0f,
        -4.0f,-3.0f, 5.0f,

        -4.0f,-3.0f,0.0f,
        -4.0f, 1.0f,0.0f,
        -4.0f,-3.0f, 5.0f,

        -4.0f, 1.0f, 5.0f,
        -4.0f, 1.0f,0.0f,
        -6.0f, 1.0f, 5.0f,

        -6.0f, 1.0f, 5.0f,
        -6.0f, 1.0f,0.0f,
        -4.0f, 1.0f,0.0f,

        -4.0f,-3.0f, 5.0f,
        -4.0f,-3.0f,0.0f,
        -6.0f,-3.0f, 5.0f,

        -6.0f,-3.0f, 5.0f,
        -6.0f,-3.0f,0.0f,
        -4.0f,-3.0f,0.0f,
    };

    this->object1 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, &vertex_buffer_data[12*3*3], COLOR_WHITE, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, &vertex_buffer_data[14*3*3], COLOR_BLACK, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 24*3, &vertex_buffer_data[16*3*3], COLOR_YELLOW, GL_FILL);
}

void Boss::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
}

void Boss::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boss::tick() {
    this->front.x = sin(this->rotation * M_PI / 180.0f);
    this->front.z = cos(this->rotation * M_PI / 180.0f);

    this->position.z -= speedz;
    this->position.x -= speedx;

    this->position.y += speedy;
    speedy -= gravity;
    if (this->position.y < 1.5) {
        speedy = 0.1;
        gravity = 0.01;
    }
    else if (this->position.y > 6.5) {
        speedy = -0.1;
        gravity = -0.01;
    }
}

bounding_box_t Boss::bounding_box() {
    float x = this->position.x, y = this->position.z;
    bounding_box_t bbox = { x, y, 8.0f, 8.0f };
    return bbox;
}

