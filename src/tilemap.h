#ifndef  TILEMAP_H
#define TILEMAP_H
#include "raylib.h"
#include "cute_tiled.h"

typedef  struct {
    cute_tiled_map_t *map;
    Texture2D texture;
    int tile_width, tile_height;
    int cols;
} Tilemap;

bool Tilemap_Load(Tilemap *tile_map, const unsigned char *json_data, unsigned int json_size, const unsigned char *png_data, unsigned int png_size); 
void Tilemap_Draw(const Tilemap *m);
void Tilemap_Unload(Tilemap *m);
#endif
