#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->front = glm::vec3(0, 0, 1);
    speed = 0;
    speedy = 0;
    gravity = 0.01;
    speedx = 0;
    speedz = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        //the boat
        -0.5f,-0.5f,-1.0f, // triangle 1 : begin
        -0.5f,-0.5f, 1.0f,
        -0.5f, 0.5f, 1.0f, // triangle 1 : end

        0.5f,-0.5f, 1.0f,
        -0.5f,-0.5f,-1.0f,
        0.5f,-0.5f,-1.0f,

        -0.5f,-0.5f,-1.0f,
        -0.5f, 0.5f, 1.0f,
        -0.5f, 0.5f,-1.0f,

        0.5f,-0.5f, 1.0f,
        -0.5f,-0.5f, 1.0f,
        -0.5f,-0.5f,-1.0f,

        0.5f, 0.5f, 1.0f,
        0.5f,-0.5f,-1.0f,
        0.5f, 0.5f,-1.0f,

        0.5f,-0.5f,-1.0f,
        0.5f, 0.5f, 1.0f,
        0.5f,-0.5f, 1.0f,

        0.5f, 0.5f, 1.0f,
        0.5f,-0.5f, 1.0f,
        0.0f, 0.5f, 2.0f,

        -0.5f, 0.5f, 1.0f,
        -0.5f,-0.5f, 1.0f,
        0.0f, 0.5f, 2.0f,

        0.0f, 0.5f, 2.0f,
        0.5f,-0.5f, 1.0f,
        -0.5f,-0.5f, 1.0f,

        0.5f, 0.5f,-1.0f,
        0.5f,-0.5f,-1.0f,
        0.5f, 0.5f,-1.5f,

        -0.5f, 0.5f,-1.0f,
        -0.5f,-0.5f,-1.0f,
        -0.5f, 0.5f,-1.5f,

        0.5f, 0.5f,-1.5f,
        0.5f,-0.5f,-1.0f,
        -0.5f,-0.5f,-1.0f,

        -0.5f,-0.5f,-1.0f,
        -0.5f, 0.5f,-1.5f,
        0.5f, 0.5f,-1.5f,

        //The mast
        0.05f,-0.5f, 0.05f,
        0.05f,-0.5f,-0.05f,
        -0.05f,-0.5f, 0.05f,

        -0.05f,-0.5f,-0.05f,
        -0.05f,-0.5f, 0.05f,
        0.05f,-0.5f,-0.05f,

        0.05f,-0.5f, 0.05f,
        0.05f,-0.5f,-0.05f,
        0.05f, 2.5f,-0.05f,

        0.05f, 2.5f,-0.05f,
        0.05f, 2.5f, 0.05f,
        0.05f,-0.5f, 0.05f,

        0.05f,-0.5f, 0.05f,
        -0.05f,-0.5f, 0.05f,
        -0.05f, 2.5f, 0.05f,

        -0.05f, 2.5f, 0.05f,
        0.05f, 2.5f, 0.05f,
        0.05f,-0.5f, 0.05f,

        -0.05f,-0.5f,-0.05f,
        -0.05f,-0.5f, 0.05f,
        -0.05f, 2.5f, 0.05f,

        -0.05f, 2.5f, 0.05f,
        -0.05f, 2.5f,-0.05f,
        -0.05f,-0.5f,-0.05f,

        -0.05f,-0.5f,-0.05f,
        0.05f,-0.5f,-0.05f,
        0.05f, 2.5f,-0.05f,

        0.05f, 2.5f,-0.05f,
        -0.05f, 2.5f,-0.05f,
        -0.05f,-0.5f,-0.05f,

        0.05f,2.5f, 0.05f,
        0.05f,2.5f,-0.05f,
        -0.05f,2.5f, 0.05f,

        -0.05f,2.5f,-0.05f,
        -0.05f,2.5f, 0.05f,
        0.05f,2.5f,-0.05f,

        //the sail
        0.0f, 2.45f, 0.0f,
        0.0f, 0.6f, 0.0f,
        0.0f, 0.6f,0.7f,

        0.0f, 2.25f, 0.0f,
        0.0f, 0.6f, 0.0f,
        0.0f, 0.6f,-1.4f,

        //the cannon
        0.25f,  0.6f, 2.0f,
        0.25f,  0.6f, 1.0f,
        -0.25f,  0.6f, 2.0f,

        -0.25f,  0.6f, 1.0f,
        -0.25f,  0.6f, 2.0f,
        0.25f,  0.6f, 1.0f,

        0.25f,  0.6f, 2.0f,
        0.25f,  0.6f, 1.0f,
        0.25f,    1.1f, 1.0f,

        0.25f,    1.1f, 1.0f,
        0.25f,    1.1f, 2.0f,
        0.25f,  0.6f, 2.0f,

        0.25f,  0.6f, 2.0f,
        -0.25f,  0.6f, 2.0f,
        -0.25f,    1.1f, 2.0f,

        -0.25f,    1.1f, 2.0f,
        0.25f,    1.1f, 2.0f,
        0.25f,  0.6f, 2.0f,

        -0.25f,  0.6f, 1.0f,
        -0.25f,  0.6f, 2.0f,
        -0.25f,    1.1f, 2.0f,

        -0.25f,    1.1f, 2.0f,
        -0.25f,    1.1f, 1.0f,
        -0.25f,  0.6f, 1.0f,

        -0.25f,  0.6f, 1.0f,
        0.25f,  0.6f, 1.0f,
        0.25f,    1.1f, 1.0f,

        0.25f,    1.1f, 1.0f,
        -0.25f,    1.1f, 1.0f,
        -0.25f,  0.6f, 1.0f,

        0.25f,   1.1f, 2.0f,
        0.25f,   1.1f, 1.0f,
        -0.25f,   1.1f, 2.0f,

        -0.25f,   1.1f, 1.0f,
        -0.25f,   1.1f, 2.0f,
        0.25f,   1.1f, 1.0f,

        0.25f, 0.85f, 1.0f,
        0.25f, 0.5f, 1.25f,
        0.25f, 0.5f, 0.75f,

        -0.25f, 0.85f, 1.0f,
        -0.25f, 0.5f, 1.25f,
        -0.25f, 0.5f, 0.75f,
    };

    this->object1 = create3DObject(GL_TRIANGLES, 13*3, vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 12*3, &vertex_buffer_data[13*3*3], COLOR_GREEN, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, &vertex_buffer_data[25*3*3], COLOR_BEIGE, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 14*3, &vertex_buffer_data[27*3*3], COLOR_GREY, GL_FILL);
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
}

void Boat::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {
    this->front.x = sin(this->rotation * M_PI / 180.0f);
    this->front.z = cos(this->rotation * M_PI / 180.0f);

    this->position.z -= speed*cos(this->rotation * M_PI / 180.0f) +  speedz;
    this->position.x -= speed*sin(this->rotation * M_PI / 180.0f) +  speedx;
    speed -= 0.1*speed;

    this->position.y += speedy;
    speedy -= gravity;
}

bounding_box_t Boat::bounding_box() {
    float x = this->position.x, y = this->position.z;
    bounding_box_t bbox = { x, y, 1.0f, 3.5f };
    return bbox;
}

