#include "main.h"

#ifndef CANNONBALL_H
#define CANNONBALL_H


class Cannonball {
public:
    Cannonball() {}
    Cannonball(float x, float y, float z, color_t color, double sx, double sz, double sy);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speedy;
    double gravity;
    double speedx;
    double speedz;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // CANNONBALL_H
