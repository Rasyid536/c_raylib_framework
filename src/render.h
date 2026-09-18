#ifndef RENDER_H
#define RENDER_H
#include "entity.h"
#include "asset_manager.h"

#define RENDER_MAX_ENTITIES 64

typedef struct {
    Entity *ent;
    Sprite sprite;
} RenderItem;


void Render_Begin(void);
void Render_Add(Entity *ent, Sprite sprite);
void Render_End(void);


#endif
