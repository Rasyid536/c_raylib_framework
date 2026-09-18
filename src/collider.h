#ifndef COLLIDER_H
#define COLLIDER_H

#include <stdbool.h>
typedef struct{
    float x, y, width, height;
    void *owner;
} Collider;


Collider Collider_Create(float x, float y, float width, float height, void *owner);

#endif
