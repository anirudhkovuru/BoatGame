#include "main.h"

#ifndef MONSTER_H
#define MONSTER_H


class Monster
{
public:
    Monster() {}
    Monster(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 range;
    float rotation;
    glm::vec3 front;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speedy;
    double gravity;
    double speedx;
    double speedz;
    bounding_box_t bounding_box();
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // MONSTER_H
