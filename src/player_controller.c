#include  "player_controller.h"
#include "entity.h"
#include "raylib.h"


void PlayerController_Update(Entity *ent) {

    float move_speed = ent->speed * GetFrameTime();
    ent->state = STATE_IDLE;

    if (IsKeyDown(KEY_RIGHT)){
        ent->transform.x += move_speed;
        ent->dir = DIR_RIGHT;
        ent->state = STATE_WALK;
    }
    else if (IsKeyDown(KEY_LEFT)) {
        ent->transform.x -= move_speed;
        ent->dir = DIR_LEFT;
        ent->state = STATE_WALK;
    }
    else if (IsKeyDown(KEY_DOWN)) {
        ent->transform.y += move_speed;
        ent->dir = DIR_DOWN;
        ent->state = STATE_WALK;
    }
    else if (IsKeyDown(KEY_UP)) {
        ent->transform.y -= move_speed;
        ent->dir = DIR_UP;
        ent->state = STATE_WALK;
    }

    if (ent->transform.x < 0) ent->transform.x = 0;
    if (ent->transform.y < 0) ent->transform.y = 0;

    if (ent->transform.x + ent->transform.width > (float)GetScreenWidth()) {
        ent->transform.x = (float)GetScreenWidth() - ent->transform.width;
    }
    if (ent->transform.y + ent->transform.height > (float)GetScreenHeight()) {
        ent->transform.y = (float)GetScreenHeight() - ent->transform.height;
    }
}

