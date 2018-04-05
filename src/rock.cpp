#include "rock.h"
#include "main.h"

Rock::Rock(float x, float y, float z, float size, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -0.5f * size,-0.5f,-0.5f * size, // triangle 1 : begin
        -0.5f * size,-0.5f, 0.5f * size,
        -0.35f * size, 0.5f * size, 0.35f * size, // triangle 1 : end

        0.5f * size,-0.5f, 0.5f * size,
        -0.5f * size,-0.5f,-0.5f * size,
        0.5f * size,-0.5f,-0.5f * size,

        -0.5f * size,-0.5f,-0.5f * size,
        -0.35f * size, 0.5f * size, 0.35f * size,
        -0.35f * size, 0.5f * size,-0.35f * size,

        0.5f * size,-0.5f, 0.5f * size,
        -0.5f * size,-0.5f, 0.5f * size,
        -0.5f * size,-0.5f,-0.5f * size,

        0.35f * size, 0.5f * size, 0.35f * size,
        0.5f * size,-0.5f,-0.5f * size,
        0.35f * size, 0.5f * size,-0.35f * size,

        0.5f * size,-0.5f,-0.5f * size,
        0.35f * size, 0.5f * size, 0.35f * size,
        0.5f * size,-0.5f, 0.5f * size,

        0.35f * size, 0.5f * size, 0.35f * size,
        -0.35f * size, 0.5f * size, 0.35f * size,
        -0.35f * size, 0.5f * size,-0.35f * size,

        -0.35f * size, 0.5f * size,-0.35f * size,
        0.35f * size, 0.5f * size,-0.35f * size,
        0.35f * size, 0.5f * size, 0.35f * size,

        0.35f * size, 0.5f * size, 0.35f * size,
        -0.35f * size, 0.5f * size, 0.35f * size,
        0.5f * size,-0.5f, 0.5f * size,

        -0.35f * size, 0.5f * size, 0.35f * size,
        -0.5f * size,-0.5f, 0.5f * size,
        0.5f * size,-0.5f, 0.5f * size,

        0.35f * size, 0.5f * size,-0.35f * size,
        -0.35f * size, 0.5f * size,-0.35f * size,
        0.5f * size,-0.5f,-0.5f * size,

        -0.35f * size, 0.5f * size,-0.35f * size,
        -0.5f * size,-0.5f,-0.5f * size,
        0.5f * size,-0.5f,-0.5f * size,
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Rock::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Rock::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

bounding_box_t Rock::bounding_box() {
    float x = this->position.x, y = this->position.z;
    bounding_box_t bbox = { x, y, 1.0f, 1.0f };
    return bbox;
}

