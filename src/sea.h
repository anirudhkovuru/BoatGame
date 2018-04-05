#include "main.h"

#ifndef SEA_H
#define SEA_H


class Sea
{
public:
    Sea() {}
    Sea(color_t color);
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

#endif // SEA_H
