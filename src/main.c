#include "game.h"
#include "player.h"
#include "world.h"

int main(int argc, char **argv) {
    /* ---- WINDOW INITIALIZATION ---- */
    InitWindow(600, 600, "Game");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(30);

    /* Initialize all of the stuff for the game */
    GameCtx ctx = {0};
    game_init(&ctx);

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        /* ---- CONTROLS ---- */
        player_move(&ctx.player);

        /* ---- Camera Follow Player ---- */
        game_update_camera(&ctx);

        /* ---- DRAWING ---- */
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(ctx.camera);
        draw_current_glumbus(&ctx.player);
        draw_world(&ctx.world);
        // DrawTextureEx(trum, (Vector2){100.0f, 100.0f}, 0.0f, 1.0f, WHITE);
        EndMode2D();

        EndDrawing();
    }

    /* ---- Unloading textures and contexts; General cleanup space ---- */
    game_unload(&ctx);

    CloseWindow();
    return 0;
}
