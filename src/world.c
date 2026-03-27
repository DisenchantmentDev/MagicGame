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
        // DrawRectangleRec(world->map.items[i].destination, RED);
        DrawTexturePro(world->world_sheet, world->map.items[i].source,
                       world->map.items[i].destination, (Vector2){0, 0}, 0.0f,
                       WHITE);
    }
}

Vector2 world_resolve_collision(World *world, Vector2 transform_vec,
                                Vector2 pos) {
    Map m = world->map;
    Vector2 out = {transform_vec.x, transform_vec.y};
    Rectangle player_rect = {(pos.x + transform_vec.x),
                             (pos.y + transform_vec.y), 64, 64};
    Rectangle tile;

    /* Iterate over each tile in the world map and check collision */
    for (size_t i = 0; i < m.count; ++i) {
        tile = m.items[i].destination;
        if (CheckCollisionRecs(player_rect, tile)) {
            /* Get the rectangle that represents the overlap of the two rects */
            Rectangle col_rect = GetCollisionRec(player_rect, tile);

            /* Resolve movement based on the shape of the collision rectangle */
            if (col_rect.height > col_rect.width) {
                out.x = 0.0;
            } else if (col_rect.height < col_rect.width) {
                out.y = 0.0;
            } else {
                out.x = 0.0;
                out.y = 0.0;
            }
        }
    }
    return out;
}
