#include "collider.h"
#include "audio_manager.h"
#include "entity.h"
#include "raylib.h"
#include "asset_manager.h"
#include "heap_data.h"
#include "player_controller.h"
#include "render.h"
#include "tilemap.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "rcamera.h"

#include "lvl1_map.h"
#include "tileset1.h"

#include "lvl2_map.h"
#include "tileset2.h"

DECLARE_VECTOR(Collider)

DEFINE_VECTOR(Collider)

bool wall_debug;
Vector2 mouse_pos;
char mouse_text_pos[64];

static Tilemap tilemap = {0};

static const unsigned char* level_map_json[] = {lvl1_map, lvl2_map};
static const unsigned int level_map_json_size[] = {lvl1_map_size, lvl2_map_size};
static const unsigned char* tileset_png[] = {tileset1, tileset2};
static const unsigned int tileset_png_size[] = {tileset1_size, tileset2_size};
static const int level_to_map_index[]  = { 0, 1 };
static const int level_to_tileset_index[]  = { 0, 1 };
#define LEVEL_COUNT (int)(sizeof(level_to_map_index)/sizeof(level_to_map_index[0]))
static int current_level = 0;

char pos[64];

void Sync_Hitbox(Entity *ent, Collider *col) {
    col->x = ent->transform.x;
    col->y = ent->transform.y;
}

void LoadLevel(int index) {
    if (index < 0 || index >= LEVEL_COUNT) return;
    Tilemap_Unload(&tilemap);
    current_level = index;
    int map_index = level_to_map_index[index];
    int tileset_index  = level_to_tileset_index[index];
    if (!Tilemap_Load(&tilemap, level_map_json[map_index], level_map_json_size[map_index], 
                tileset_png[tileset_index], tileset_png_size[tileset_index])) {
        TraceLog(LOG_WARNING, "level failed %d ", index);
    }
}

int main(void)
{
    const float screenWidth = 800;
    const float  screenHeight = 800;

    InitWindow((int)screenWidth, (int)screenHeight, "Game");
    SetTargetFPS(0);

    InitAudioDevice();
    Audio_Init();

    AssetManager_Init();

    LoadLevel(0);
    
    Heap_Data_Collider world_collider = {0};
    addend_Collider(&world_collider, Collider_Create(322, 677, 544, 100, NULL));
    addend_Collider(&world_collider, Collider_Create(500, 300, 50, 200, NULL));


    Entity player = Entity_Create(400, 400, 32, 32, 300.0f);
    Entity npc = Entity_Create(200, 400, 64, 64, 0); 

    Camera2D camera = {0};
    camera.zoom = 2.0f;
    camera.offset = (Vector2){screenWidth / 2, screenHeight / 2};

    Collider player_coll = Collider_Create(0, 0, 32, 32, &player);

    while (!WindowShouldClose()) {

        float old_x = player.transform.x;
        float old_y = player.transform.y;

        mouse_pos = GetMousePosition();
        
        PlayerController_Update(&player);

        Sync_Hitbox(&player, &player_coll);

        Rectangle player_rect = {player_coll.x, player_coll.y, player_coll.width, player_coll.height};

        // #df1c2f
        for (size_t i = 0; i < world_collider.length; i++) {
            
            Collider target = world_collider.data[i];
            Rectangle target_rect = { target.x, target.y, target.width, target.height };

            if (CheckCollisionRecs(player_rect, target_rect)) {
                
                player.transform.x = old_x;
                player.transform.y = old_y;
                
                Sync_Hitbox(&player, &player_coll);

                break; 
            }
        }
        // #B8172B
        if (player.state == STATE_WALK) {
            AudioManager_Play(SFX_WALK);
        }

        if (IsKeyPressed(KEY_N)) LoadLevel((current_level + 1) % LEVEL_COUNT);

        camera.target = (Vector2) { player.transform.x + player.transform.width / 2,
            player.transform.y + player.transform.height / 2 };

        BeginDrawing();
            ClearBackground(BLACK);
            if (IsKeyPressed(KEY_A)) {
                if (wall_debug) {
                    wall_debug = false;
                }
                else if (!wall_debug) {
                    wall_debug = true;
                }
            }

            DrawFPS(10, 10);
            BeginMode2D(camera);
            Tilemap_Draw(&tilemap);

            if (wall_debug) {
                for (size_t i = 0; i < world_collider.length; i++) {
                    Rectangle r  = {world_collider.data[i].x, world_collider.data[i].y, 
                                    world_collider.data[i].width, world_collider.data[i].height};
                    DrawRectangleRec(r, RED);
                }
                snprintf(mouse_text_pos, sizeof(mouse_text_pos),
                        "x : %.0f, y : %.0f", mouse_pos.x, mouse_pos.y);
                DrawText(mouse_text_pos, 600, 600, 20, WHITE);
                DrawText(TextFormat("%i FPS", GetFPS()), 10, 10, 25, GREEN);
                snprintf(pos, sizeof(pos), "Posisi: %.1f, %.1f", player.transform.x, player.transform.y);
                DrawText(pos, (int)player.transform.x, (int)player.transform.y - 30, 5, GREEN);
            }
            Render_Begin();
            Render_Add(&player, AssetManager_GetSprite(SPRITE_PLAYER));
            Render_Add(&npc , AssetManager_GetSprite(SPRITE_PLAYER));
            Render_End();
            EndMode2D();
        EndDrawing();
    }
    AudioManager_Free();
    Tilemap_Unload(&tilemap);
    free(world_collider.data);
    AssetManager_Free();
    CloseWindow();

    return 0;
}
