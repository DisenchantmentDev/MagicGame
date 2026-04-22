#pragma once

#include <raylib.h>
#include <stdlib.h>

/* Define the location and size of sprites on the world sprite sheet */
#define TRUM_SOURCE_COORDS (Vector2){0, 0}
#define TRUM_SOURCE_SIZE (Vector2){100, 100}
#define MAGIC_GRASS_SOURCE_COORDS (Vector2){0, 0}  // Use same coords as TRUM for now
#define MAGIC_GRASS_SOURCE_SIZE (Vector2){100, 100}

#define da_append(xs, x)                                                       \
    do {                                                                       \
        if ((xs)->count >= (xs)->capacity) {                                   \
            if ((xs)->capacity == 0)                                           \
                (xs)->capacity = 256;                                          \
            else                                                               \
                (xs)->capacity *= 2;                                           \
            (xs)->items =                                                      \
                realloc((xs)->items, (xs)->capacity * sizeof(*(xs)->items));   \
        }                                                                      \
        (xs)->items[(xs)->count++] = (x);                                      \
    } while (0)

typedef struct {
    Rectangle source;
    Rectangle destination;
    Vector2 (*move_behavior)(
        Vector2 transform_vec, Vector2 pos,
        Rectangle tile); // somehow figure out passing in player
    Texture2D texture;  // Add texture pointer to each tile
} Tile;

typedef struct {
    Tile *items;
    size_t capacity;
    size_t count;
} Map;

typedef struct {
    Texture2D world_sheet;
    Map map;
} World;

Tile gen_tile(Vector2 source_coord, Vector2 source_size, Vector2 map_coord,
              Vector2 map_size, Texture2D texture,
              Vector2 (*move_behavior)(Vector2 transform_vec, Vector2 pos,
                                       Rectangle tile));
void init_world(World *world, Texture2D trum_texture, Texture2D grass_texture);
void draw_world(World *world);
Vector2 move_default(Vector2 transform_vec, Vector2 pos);
Vector2 move_wall(Vector2 transform_vec, Vector2 pos, Rectangle tile);
Vector2 move_slow(Vector2 transform_vec, Vector2 pos, Rectangle tile);
Vector2 world_resolve_collision(World *world, Vector2 transform_vec,
                                Vector2 pos);
