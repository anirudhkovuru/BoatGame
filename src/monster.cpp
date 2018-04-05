#include "monster.h"
#include "main.h"

Monster::Monster(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->front = glm::vec3(0, 0, 1);
    speedx = 0;
    speedy = 0;
    speedz = 0;
    gravity = 0.01;
    this->range = glm::vec3(9, 0, 9);

    static const GLfloat vertex_buffer_data[] = {
        //body
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f,-0.5f, 0.5f,

        -0.5f, 0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f,
        0.5f,-0.5f, 0.5f,

        -0.5f, 0.5f,-0.5f,
        0.5f, 0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,

        -0.5f, 0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,

        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f,-0.5f,
        0.5f,-0.5f, 0.5f,

        0.5f,-0.5f,-0.5f,
        0.5f, 0.5f,-0.5f,
        0.5f,-0.5f, 0.5f,

        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f,-0.5f,
        -0.5f,-0.5f, 0.5f,

        -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,
        -0.5f,-0.5f, 0.5f,

        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f,-0.5f,
        0.5f, 0.5f, 0.5f,

        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,

        -0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f,-0.5f,
        0.5f,-0.5f, 0.5f,

        0.5f,-0.5f, 0.5f,
        0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,

        //eye
        0.25f, 0.25f, 0.51f,
        -0.25f, 0.25f, 0.51f,
        -0.25f,-0.25f, 0.51f,

        -0.25f,-0.25f, 0.51f,
        0.25f,-0.25f, 0.51f,
        0.25f, 0.25f, 0.51f,

        0.125f, 0.125f, 0.52f,
        -0.125f, 0.125f, 0.52f,
        -0.125f,-0.125f, 0.52f,

        -0.125f,-0.125f, 0.52f,
        0.125f,-0.125f, 0.52f,
        0.125f, 0.125f, 0.52f,

        //tail
        -0.25f, 0.25f, 0.25f,
        0.25f, 0.25f, 0.25f,
        0.25f,-0.25f, 0.25f,

        -0.25f, 0.25f, 0.25f,
        -0.25f,-0.25f, 0.25f,
        0.25f,-0.25f, 0.25f,

        -0.25f, 0.25f,-0.75f,
        0.25f, 0.25f,-0.75f,
        0.25f,-0.25f,-0.75f,

        -0.25f, 0.25f,-0.75f,
        -0.25f,-0.25f,-0.75f,
        0.25f,-0.25f,-0.75f,

        0.25f, 0.25f, 0.25f,
        0.25f, 0.25f,-0.75f,
        0.25f,-0.25f, 0.25f,

        0.25f,-0.25f,-0.75f,
        0.25f, 0.25f,-0.75f,
        0.25f,-0.25f, 0.25f,

        -0.25f, 0.25f, 0.25f,
        -0.25f, 0.25f,-0.75f,
        -0.25f,-0.25f, 0.25f,

        -0.25f,-0.25f,-0.75f,
        -0.25f, 0.25f,-0.75f,
        -0.25f,-0.25f, 0.25f,

        -0.25f, 0.25f, 0.25f,
        -0.25f, 0.25f,-0.75f,
        0.25f, 0.25f, 0.25f,

        0.25f, 0.25f, 0.25f,
        0.25f, 0.25f,-0.75f,
        -0.25f, 0.25f,-0.75f,

        -0.25f,-0.25f, 0.25f,
        -0.25f,-0.25f,-0.75f,
        0.25f,-0.25f, 0.25f,

        0.25f,-0.25f, 0.25f,
        0.25f,-0.25f,-0.75f,
        -0.25f,-0.25f,-0.75f,

    };

    this->object1 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, &vertex_buffer_data[12*3*3], COLOR_WHITE, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, &vertex_buffer_data[14*3*3], COLOR_BLACK, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 12*3, &vertex_buffer_data[16*3*3], COLOR_YELLOW, GL_FILL);
}

void Monster::draw(glm::mat4 VP) {
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

void Monster::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Monster::tick() {
    this->front.x = sin(this->rotation * M_PI / 180.0f);
    this->front.z = cos(this->rotation * M_PI / 180.0f);

    this->position.z -= speedz;
    this->position.x -= speedx;

    this->position.y += speedy;
    speedy -= gravity;
    if (this->position.y < -0.25) {
        speedy = 0.1;
        gravity = 0.01;
    }
    else if (this->position.y > 0.25) {
        speedy = -0.1;
        gravity = -0.01;
    }
}

bounding_box_t Monster::bounding_box() {
    float x = this->position.x, y = this->position.z;
    bounding_box_t bbox = { x, y, 1.0f, 1.0f };
    return bbox;
}

