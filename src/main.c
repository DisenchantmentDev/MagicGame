#include <stdio.h>
#include <raylib.h>

int main(int argc, char **argv) {
    InitWindow(600, 600, "Game");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(30);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }
    printf("Hello World!\n");
    return 0;
}
