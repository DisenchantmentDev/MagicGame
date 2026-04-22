#include "world.h"

Tile gen_tile(Vector2 source_coord, Vector2 source_size, Vector2 map_coord,
              Vector2 map_size, Texture2D imTexture,
              Vector2 (*move_behavior)(
                  Vector2 transform_vec,
                  Vector2 pos, // I deeply apologize for this nightmare
                  Rectangle tile)) {  // Add texture parameter
    Rectangle source = {source_coord.x, source_coord.y, source_size.x,
                        source_size.y};
    Rectangle destination = {map_coord.x, map_coord.y, map_size.x, map_size.y};
    Texture2D texture = imTexture; // Store the texture in the tile struct
    return (Tile){source, destination, move_behavior, texture};
}

void init_world(World *world, Texture2D trum_texture, Texture2D grass_texture) {
    Map map = {0};
    // Grass tiles  

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            Tile grass_tile = gen_tile(MAGIC_GRASS_SOURCE_COORDS, MAGIC_GRASS_SOURCE_SIZE,
                                      (Vector2){j * 100.0f, i * 100.0f}, (Vector2){100, 100}, grass_texture, move_slow);
            da_append(&map, grass_tile);
        }
    }
    
    //TRUM tiles

    Tile trum1 = gen_tile(TRUM_SOURCE_COORDS, TRUM_SOURCE_SIZE,
                          (Vector2){100.0f, 100.0f}, (Vector2){100, 100}, trum_texture, move_wall);
    da_append(&map, trum1);
    Tile trum2 = gen_tile(TRUM_SOURCE_COORDS, TRUM_SOURCE_SIZE,
                          (Vector2){000.0f, 000.0f}, (Vector2){100, 100}, trum_texture, move_wall);
    da_append(&map, trum2);
    Tile trum3 = gen_tile(TRUM_SOURCE_COORDS, TRUM_SOURCE_SIZE,
                          (Vector2){100.0f, 000.0f}, (Vector2){100, 100}, trum_texture, move_wall);
    da_append(&map, trum3);

    // Store one texture for compatibility (you might not need this anymore)
    world->world_sheet = grass_texture;
    world->map = map;
}

void draw_world(World *world) {
    for (size_t i = 0; i < world->map.count; ++i) {
        // DrawRectangleRec(world->map.items[i].destination, RED);
        DrawTexturePro(world->map.items[i].texture, world->map.items[i].source,
                       world->map.items[i].destination, (Vector2){0, 0}, 0.0f,
                       WHITE);
    }
}


Vector2 move_slow(Vector2 transform_vec, Vector2 pos, Rectangle tile) {
    Vector2 out = {transform_vec.x * 0.5, transform_vec.y * 0.5};
    return out;
}

Vector2 move_wall(Vector2 transform_vec, Vector2 pos, Rectangle tile) {
    Vector2 out = {transform_vec.x, transform_vec.y};
    Rectangle player_rect = {(pos.x + transform_vec.x),
                             (pos.y + transform_vec.y), 64, 64};
    Rectangle col_rect = GetCollisionRec(player_rect, tile);
    if (col_rect.height > col_rect.width) {
        out.x = 0.0;
    } else if (col_rect.height < col_rect.width) {
        out.y = 0.0;
    } else if (col_rect.height == col_rect.width &&
               col_rect.height > 2) { // if the collision rectangle has
        // no indication of direction
        out.x = -1 * (transform_vec.x);
        out.y = -1 * (transform_vec.y);
    }
    return out;
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
            out = m.items[i].move_behavior(transform_vec, pos, tile);
        }
    }
    return out;
}
