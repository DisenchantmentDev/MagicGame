#include <raylib.h>
#include <stdio.h>
#define NUM_GLUMBUS 2

int main(int argc, char **argv) {
    /* ---- WINDOW INITIALIZATION ---- */
    InitWindow(600, 600, "Game");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(30);

    /* ---- Loading Directory and textures ---- */
    const char *dir = GetWorkingDirectory();
    char glumbus_buffer[100];

    sprintf(glumbus_buffer, "%s/resources/temp/glumbus.png", dir);
    Image glumbus_right = LoadImage(glumbus_buffer);
    Image glumbus_left = LoadImage(glumbus_buffer);
    ImageFlipHorizontal(&glumbus_left);

    Texture2D glumbuses[NUM_GLUMBUS] = {0};

    glumbuses[0] = LoadTextureFromImage(glumbus_right);
    glumbuses[1] = LoadTextureFromImage(glumbus_left);

    int currentGlumbus = 0;

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
        if (IsKeyDown(KEY_D)){
            if(currentGlumbus != 0) {
                currentGlumbus = (currentGlumbus + 1) % NUM_GLUMBUS;
            }
            position.x += 2;
        }
        else if (IsKeyDown(KEY_A)){
            if(currentGlumbus != 1) {
                currentGlumbus = (currentGlumbus + 1) % NUM_GLUMBUS;
            }
            position.x -= 2;
        }
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
        DrawTextureEx(glumbuses[currentGlumbus], position, 0.0f, 3.0f, WHITE);
        DrawTextureEx(trum, (Vector2){100.0f, 100.0f}, 0.0f, 1.0f, WHITE);
        EndMode2D();

        EndDrawing();
    }

    /* ---- Unloading textures and contexts; General cleanup space ---- */
    for(int i = 0; i < NUM_GLUMBUS; i++) {
        UnloadTexture(glumbuses[i]);
    }
    CloseWindow();
    return 0;
}
