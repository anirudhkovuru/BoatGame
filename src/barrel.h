#include "main.h"

#ifndef BARREL_H
#define BARREL_H


class Barrel
{
public:
public:
    Barrel() {}
    Barrel(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    double speedy;
    double accelaratey;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BARREL_H
