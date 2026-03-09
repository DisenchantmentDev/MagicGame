#pragma once

#include "player.h"
#include "world.h"
#include <raylib.h>

typedef struct {
    Camera2D camera;
    Player player;
    World world;
} GameCtx;

void game_init(GameCtx *ctx);
void game_update_camera(GameCtx *ctx);
void game_unload(GameCtx *ctx);
