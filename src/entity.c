#include "entity.h"

Entity Entity_Create(float x, float y, float w, float h, float speed) {
    Entity entity;

    entity.transform.x = x;
    entity.transform.y = y;
    entity.transform.width = w;
    entity.transform.height = h;
    entity.speed = speed;


    entity.dir = DIR_DOWN;
    entity.state = STATE_IDLE;

    entity.anim_timer = 0.0f;
    entity.anim_frame = 0;

    return entity;
}
