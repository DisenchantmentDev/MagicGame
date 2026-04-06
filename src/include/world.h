#pragma once

#include <raylib.h>
#include <stdlib.h>

/* Define the location and size of sprites on the world sprite sheet */
#define TRUM_SOURCE_COORDS (Vector2){0, 0}
#define TRUM_SOURCE_SIZE (Vector2){100, 100}
#define MAGIC_GRASS_SOURCE_COORDS (Vector2){0, 0}
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
              Vector2 map_size);
void init_world(World *world, Texture2D sheet);
void draw_world(World *world);
Vector2 world_resolve_collision(World *world, Vector2 transform_vec,
                                Vector2 pos);
