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
    Vector2 position = {300.0f, 300.0f};

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        /* ---- DRAWING ---- */
        BeginDrawing();
        ClearBackground(BLACK);

        DrawTextureEx(glumbus, position, 0.0f, 3.0f, WHITE);

        EndDrawing();
    }

    /* ---- Unloading textures and contexts; General cleanup space ---- */
    UnloadTexture(glumbus);
    CloseWindow();
    return 0;
}
