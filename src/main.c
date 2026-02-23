#include <raylib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    /* ---- WINDOW INITIALIZATION ---- */
    InitWindow(600, 600, "Game");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(30);

    /* ---- Loading Directory and textures ---- */
    const char *dir = GetWorkingDirectory();
    char glumbus_buffer[100];
    sprintf(glumbus_buffer, "%s/resources/temp/glumbus.png", dir);
    Texture2D glumbus = LoadTexture(glumbus_buffer);

    /* Just reuse the same buffer for seperate textures */
    sprintf(glumbus_buffer, "%s/resources/temp/Trum.png", dir);
    Texture2D trum = LoadTexture(glumbus_buffer);

    Vector2 position = {150.0f, 150.0f};

    Camera2D camera = {0};
    camera.target = (Vector2){position.x + 30.0f, position.y + 30.0f};
    camera.offset =
        (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        /* ---- CONTROLS ---- */
        if (IsKeyDown(KEY_D))
            position.x += 2;
        else if (IsKeyDown(KEY_A))
            position.x -= 2;

        if (IsKeyDown(KEY_S))
            position.y += 2;
        else if (IsKeyDown(KEY_W))
            position.y -= 2;

        /* ---- Camera Follow Player ---- */
        camera.target = (Vector2){position.x + 30.0f, position.y + 30.0f};

        /* ---- DRAWING ---- */
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
        DrawTextureEx(glumbus, position, 0.0f, 3.0f, WHITE);
        DrawTextureEx(trum, (Vector2){100.0f, 100.0f}, 0.0f, 1.0f, WHITE);
        EndMode2D();

        EndDrawing();
    }

    /* ---- Unloading textures and contexts; General cleanup space ---- */
    UnloadTexture(glumbus);
    CloseWindow();
    return 0;
}
