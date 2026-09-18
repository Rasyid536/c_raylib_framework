#ifndef ASSET_MANAGER
#define ASSET_MANAGER

#include "raylib.h"

typedef struct{
Texture2D texture;
int pixel_size;
int cols, rows;
} Sprite;

typedef enum {
    SPRITE_PLAYER,
    SPRITE_MAX
} SpriteID;

void AssetManager_Init(void);
Sprite AssetManager_GetSprite(SpriteID id);
void AssetManager_Free(void);

#endif
