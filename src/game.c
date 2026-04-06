#include <stdio.h>

#include "game.h"
#include "player.h"
#include "world.h"

void game_init(GameCtx *ctx) {
    /* ---- Loading Directory and textures ---- */
    const char *dir = GetApplicationDirectory();
    char glumbus_buffer[100];

    sprintf(glumbus_buffer, "%s../resources/temp/glumbus.png", dir);
    Image glumbus = LoadImage(glumbus_buffer);

    Player player = {0};
    init_player(&player, glumbus);

    /* Just reuse the same buffer for seperate textures */
    sprintf(glumbus_buffer, "%s../resources/temp/Trum.png", dir);
    Texture2D trum = LoadTexture(glumbus_buffer);

    sprintf(glumbus_buffer, "%s../resources/temp/Magicgrass_Placeholder.png", dir);
    Texture2D magic_grass = LoadTexture(glumbus_buffer);


    /* Camera initialization */
    Camera2D camera = {0};
    camera.target = (Vector2){player.pos.x + 30.0f, player.pos.y + 30.0f};
    camera.offset =
        (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.5f;

    /* World Initialization */
    World world = {0};
    init_world(&world, trum);

    ctx->player = player;
    ctx->world = world;
    ctx->camera = camera;
}

void game_update_camera(GameCtx *ctx) {
    ctx->camera.target =
        (Vector2){ctx->player.pos.x + 30.0f, ctx->player.pos.y + 30.0f};
}

void game_unload(GameCtx *ctx) {
    UnloadTexture(ctx->player.sprite_sheet);
    UnloadTexture(ctx->world.world_sheet);
}
