#include "draw.h"
#include "asset_manager.h"
#include "entity.h"
#include "raylib.h"

void Draw_Entity(Entity *ent, Sprite sprite) {
    if (ent->state == STATE_WALK) {
        ent->anim_timer += GetFrameTime();
        if (ent->anim_timer >= 0.15f) {
            ent->anim_timer = 0.0f;
            ent->anim_frame = (ent->anim_frame + 1) % sprite.cols;
        }
    } else {
        ent->anim_frame = sprite.cols / 2;
        ent->anim_timer = 0.0f;
    }

    int row;
    switch (ent->dir) {
        case DIR_UP:    row = 0; break;
        case DIR_DOWN:  row = 2; break;
        default:        row = 1; break;
    }

    int ps = sprite.pixel_size;
    Rectangle source = {
        .x = ent->anim_frame * ps,
        .y = row * ps,
        .width  = (ent->dir == DIR_LEFT) ? -ps : ps,
        .height = ps,
    };

    Rectangle dest = {
        .x = ent->transform.x,
        .y = ent->transform.y,
        .width = ent->transform.width,
        .height = ent->transform.height,
    };

    DrawTexturePro(sprite.texture, source, dest, (Vector2){0, 0}, 0.0f, WHITE);
}
