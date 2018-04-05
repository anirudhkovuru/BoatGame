#include "main.h"

#ifndef GIFT_H
#define GIFT_H


class Gift
{
public:
public:
    Gift() {}
    Gift(float x, float y, float z, color_t color);
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

#endif // GIFT_H
