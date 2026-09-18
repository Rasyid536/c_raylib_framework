cmake_minimum_required(VERSION 4.0)

project(game C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)

set(GEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)

function(embed_file png_file symbol)
    set(output ${GEN_DIR}/${symbol}.h)
    add_custom_command(
        OUTPUT  ${output}
        COMMAND ${CMAKE_COMMAND}
                -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/assets/${png_file}
                -DOUTPUT=${output}
                -DSYMBOL=${symbol}
                -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/embed.cmake
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/assets/${png_file}
        VERBATIM
    )
    list(APPEND embedded_headers ${output})
    set(embedded_headers ${embedded_headers} PARENT_SCOPE)
endfunction()

# Sprite List
embed_file(player_sprite.png player_sprite)

# Audio List
embed_file(walk_sfx.wav walk_sfx)

# Tilemap List
embed_file(tilemap.tmj lvl1_map)
embed_file(level2.tmj lvl2_map)

# Tileste List
embed_file(tileset.png tileset1)
embed_file(level2.png tileset2)

add_custom_target(embed_assets DEPENDS ${embedded_headers})

add_executable(${PROJECT_NAME}
    src/main.c
    src/entity.c
    src/draw.c
    src/asset_manager.c
    src/player_controller.c
    src/collider.c
    src/audio_manager.c
    src/render.c
    src/tilemap.c
)

add_dependencies(${PROJECT_NAME} embed_assets)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_include_directories(${PROJECT_NAME} PRIVATE src ${GEN_DIR})
