#include "raylib.h"
#define CUTE_TILED_IMPLEMENTATION
#include "tilemap.h"
#include "cute_tiled.h"


bool Tilemap_Load(Tilemap *tile_map, 
        const unsigned char *json_data, unsigned int json_size,
        const unsigned char *png_data, unsigned int png_size) {

    char *json_null = malloc(json_size + 1);
    memcpy(json_null, json_data, json_size);
    json_null[json_size] = '\0';

    tile_map->map = cute_tiled_load_map_from_memory(json_null, (int)json_size, 0);
    free(json_null);

    if (!tile_map->map) {
        TraceLog(LOG_WARNING, "tilemap parse failed ->  %s (line %d)",
                cute_tiled_error_reason, cute_tiled_error_line);
        return false;
    }

    tile_map->tile_width  = tile_map->map->tilewidth;
    tile_map->tile_height = tile_map->map->tileheight;
    tile_map->cols        = tile_map->map->tilesets->columns;

    Image tilesets_image = LoadImageFromMemory(".png" , png_data, png_size ); 

    if (tilesets_image.data == NULL) {
        tilesets_image = GenImageColor(tile_map->tile_width * tile_map->cols, 
                tile_map->tile_height * 4, GRAY);
    }
    tile_map->texture = LoadTextureFromImage(tilesets_image);
    UnloadImage(tilesets_image);
    return true;
}

void Tilemap_Draw(const Tilemap *tile_map) {
    cute_tiled_layer_t *layer = tile_map->map->layers;
    for (int i = 0; i < layer->data_count; i++) {
        int global_tile_id = layer->data[i]; 

        if (!global_tile_id) continue;

        int local_tile_id = global_tile_id - 1;
        int col = local_tile_id % tile_map->cols; 
        int row = local_tile_id / tile_map->cols;

        int map_x = i % layer->width, map_y = i / layer->width;

        Rectangle s = {col *tile_map->tile_width, row *tile_map->tile_height, 
            tile_map->tile_width, tile_map->tile_height};
        Rectangle d = {map_x *tile_map->tile_width, map_y *tile_map->tile_height,
            tile_map->tile_width, tile_map->tile_height};
        
        DrawTexturePro(tile_map->texture, s, d, (Vector2){0, 0}, 0, WHITE);
    }
}

void Tilemap_Unload(Tilemap *tile_map) {
    if (!tile_map) return;

    if (tile_map->map) {
        UnloadTexture(tile_map->texture);
        cute_tiled_free_map(tile_map->map);
    }
}
