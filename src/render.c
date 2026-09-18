#include "render.h"
#include "asset_manager.h"
#include "draw.h"
#include <stddef.h>
#include <stdlib.h>

static RenderItem items[RENDER_MAX_ENTITIES];
static size_t count;

static int CompareByFeet(const void *a, const void *b) {
    const RenderItem *ia = a;
    const RenderItem *ib = b;
    float feet_a = ia->ent->transform.y + ia->ent->transform.height;
    float feet_b = ib->ent->transform.y + ib->ent->transform.height;

    if (feet_a < feet_b) return  -1;
    if (feet_a > feet_b) return 1;

    return  (ia->ent < ib->ent) ? -1 : (ia->ent > ib->ent) ? 1 : 0;
}

void Render_Begin(void) {
    count = 0;
}

void Render_Add(Entity *ent, Sprite sprite) {
    if (count >= RENDER_MAX_ENTITIES) return;

    items[count].ent = ent;
    items[count].sprite = sprite;
    count++;
}

void Render_End(void) {
    qsort(items, count, sizeof(RenderItem), CompareByFeet);
    for (size_t i = 0; i < count; i++) {
        Draw_Entity(items[i].ent, items[i].sprite);
    }
}
