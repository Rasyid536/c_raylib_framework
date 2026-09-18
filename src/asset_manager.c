#include "asset_manager.h"
#include "player_sprite.h"

#include "raylib.h"
#include <stdio.h>

static Sprite sprites[SPRITE_MAX];

static Sprite LoadSprite(const unsigned char *data, int size,  int pixel_size) {
    Sprite sprite = {0};

    Image img = LoadImageFromMemory(".png", data, size);

    if (img.width == 0) {
        img = GenImageColor(96, 96, GRAY);
        ImageDrawRectangle(&img, 0, 32, 96, 32, BLUE);
        ImageDrawRectangle(&img, 0, 64, 96, 32, GREEN);
    }

    sprite.texture = LoadTextureFromImage(img);
    sprite.pixel_size = pixel_size;
    sprite.cols = img.width / pixel_size;
    sprite.rows = img.height / pixel_size;

    UnloadImage(img);

    return sprite;
}


void AssetManager_Init(void) {
    sprites[SPRITE_PLAYER] = LoadSprite(player_sprite, (int)player_sprite_size, 32);
    printf("AssetManager: loaded %d cols x %d rows, %dpx\n",
           sprites[SPRITE_PLAYER].cols, sprites[SPRITE_PLAYER].rows,
           sprites[SPRITE_PLAYER].pixel_size);
}

Sprite AssetManager_GetSprite(SpriteID id) {
    if (id >= SPRITE_MAX) return sprites[SPRITE_PLAYER];
    return sprites[id];
}

void AssetManager_Free(void) {
    for (int i = 0; i < SPRITE_MAX; i++) {
        UnloadTexture(sprites[i].texture);
    }
    printf("AssetManager: VRAM FREED \n");
}

