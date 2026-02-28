#include "world.h"

Tile gen_tile(Vector2 source_coord, Vector2 source_size, Vector2 map_coord,
              Vector2 map_size) {
    Rectangle source = {source_coord.x, source_coord.y, source_size.x,
                        source_size.y};
    Rectangle destination = {map_coord.x, map_coord.y, map_size.x, map_size.y};
    return (Tile){source, destination};
}

void init_world(World *world, Texture2D sheet) {
    Map map = {0};
    Tile trum1 = gen_tile(TRUM_SOURCE_COORDS, TRUM_SOURCE_SIZE,
                          (Vector2){100.0f, 100.0f}, (Vector2){100, 100});
    da_append(&map, trum1);

    world->world_sheet = sheet;
    world->map = map;
}

void draw_world(World *world) {
    for (size_t i = 0; i < world->map.count; ++i) {
        DrawTexturePro(world->world_sheet, world->map.items[i].source,
                       world->map.items[i].destination, (Vector2){0, 0}, 0.0f,
                       WHITE);
    }
}
