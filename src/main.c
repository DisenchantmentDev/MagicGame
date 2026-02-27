#include <stdio.h>

#include "player.h"
#include "world.h"

int main(int argc, char **argv) {
    /* ---- WINDOW INITIALIZATION ---- */
    InitWindow(600, 600, "Game");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(30);

    /* ---- Loading Directory and textures ---- */
    const char *dir = GetWorkingDirectory();
    char glumbus_buffer[100];

    sprintf(glumbus_buffer, "%s/resources/temp/glumbus.png", dir);
    Image glumbus = LoadImage(glumbus_buffer);

    Player player = {0};
    init_player(&player, glumbus);

    /* Just reuse the same buffer for seperate textures */
    sprintf(glumbus_buffer, "%s/resources/temp/Trum.png", dir);
    Texture2D trum = LoadTexture(glumbus_buffer);

    Camera2D camera = {0};
    camera.target = (Vector2){player.pos.x + 30.0f, player.pos.y + 30.0f};
    camera.offset =
        (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.5f;

    /* Unused for now but testing header file stuff */
    GameCtx gamectx = {camera};

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        /* ---- CONTROLS ---- */
        player_move(&player);

        /* ---- Camera Follow Player ---- */
        camera.target = (Vector2){player.pos.x + 30.0f, player.pos.y + 30.0f};

        /* ---- DRAWING ---- */
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
        draw_current_glumbus(&player);
        DrawTextureEx(trum, (Vector2){100.0f, 100.0f}, 0.0f, 1.0f, WHITE);
        EndMode2D();

        EndDrawing();
    }

    /* ---- Unloading textures and contexts; General cleanup space ---- */
    UnloadTexture(player.sprite_sheet);
    UnloadTexture(player.sprite_sheet);

    CloseWindow();
    return 0;
}
