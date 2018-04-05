#include "cannonball.h"
#include "main.h"

Cannonball::Cannonball(float x, float y, float z, color_t color, double sx, double sz, double sy) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speedy = sy;
    gravity = 0.01;
    speedx = sx;
    speedz = sz;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -0.25f, 0.25f, 0.25f,
        0.25f, 0.25f, 0.25f,
        0.25f,-0.25f, 0.25f,

        -0.25f, 0.25f, 0.25f,
        -0.25f,-0.25f, 0.25f,
        0.25f,-0.25f, 0.25f,

        -0.25f, 0.25f,-0.25f,
        0.25f, 0.25f,-0.25f,
        0.25f,-0.25f,-0.25f,

        -0.25f, 0.25f,-0.25f,
        -0.25f,-0.25f,-0.25f,
        0.25f,-0.25f,-0.25f,

        0.25f, 0.25f, 0.25f,
        0.25f, 0.25f,-0.25f,
        0.25f,-0.25f, 0.25f,

        0.25f,-0.25f,-0.25f,
        0.25f, 0.25f,-0.25f,
        0.25f,-0.25f, 0.25f,

        -0.25f, 0.25f, 0.25f,
        -0.25f, 0.25f,-0.25f,
        -0.25f,-0.25f, 0.25f,

        -0.25f,-0.25f,-0.25f,
        -0.25f, 0.25f,-0.25f,
        -0.25f,-0.25f, 0.25f,

        -0.25f, 0.25f, 0.25f,
        -0.25f, 0.25f,-0.25f,
        0.25f, 0.25f, 0.25f,

        0.25f, 0.25f, 0.25f,
        0.25f, 0.25f,-0.25f,
        -0.25f, 0.25f,-0.25f,

        -0.25f,-0.25f, 0.25f,
        -0.25f,-0.25f,-0.25f,
        0.25f,-0.25f, 0.25f,

        0.25f,-0.25f, 0.25f,
        0.25f,-0.25f,-0.25f,
        -0.25f,-0.25f,-0.25f,
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Cannonball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cannonball::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cannonball::tick() {
    this->position.z -= speedz;
    this->position.x -= speedx;
    this->position.y += speedy;
    speedy -= gravity;
}

bounding_box_t Cannonball::bounding_box() {
    float x = this->position.x, y = this->position.z;
    bounding_box_t bbox = { x, y, 0.5f, 0.5f };
    return bbox;
}

