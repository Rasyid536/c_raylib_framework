#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>

typedef struct {
    float x, y;
    float width, height;
} Trans2D;

typedef enum {DIR_DOWN, DIR_UP, DIR_RIGHT, DIR_LEFT} Direction;
typedef enum {STATE_WALK, STATE_IDLE} State;


typedef struct {
    Trans2D transform;
    float speed;
    Direction dir;
    State state;

    float anim_timer;
    int anim_frame;
} Entity;


Entity Entity_Create(float x, float y, float w, float h, float speed);

#endif
