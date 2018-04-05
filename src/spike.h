#include "main.h"

#ifndef SPIKE_H
#define SPIKE_H


class Spike {
public:
    Spike() {}
    Spike(float x, float y, float z, color_t color, float height);
    glm::vec3 position;
    float rotation;
    double h;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // SPIKE_H
