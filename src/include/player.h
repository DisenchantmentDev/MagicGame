#pragma once

#include "world.h"
#include <raylib.h>

#define PLAYER_STARTING_X 200.0f
#define PLAYER_STARTING_Y 150.0f
#define MOV_RIGHT 1
#define MOV_LEFT -1
#define MOV_UP -1
#define MOV_DOWN 1
/* Define Glumbus sizes for draw rectangles */
#define GLUMBUS_SHEET_SIZE 32  // size of his sprite on the sprite sheet
#define GLUMBUS_SPRITE_SIZE 64 // size we want to draw him as on the screen
#define MAX_HP 100
#define MAX_SHIELD 50
#define MAX_ARMOR 90

typedef struct {
    Texture2D sprite_sheet;
    Texture2D sprite;
    Vector2 pos;
    Vector2 mov_dir;
    int health; // Added Health and Shield for Basic Stats
    int shield; // Health needs to be restored with pickups but shield will
                // restore on its own
    int armor; // Armor provides damage reduction on health damage, starts at 0
               // and can be raised up to 90%
} Player;

void init_player(Player *p, Image sheet);
void draw_current_glumbus(Player *p);
void player_move(Player *p, World *w);
void take_damage(Player *p, int incoming);
void heal(Player *p, int incoming);
void armor_increase(Player *p, int incoming);
void death(Player *p);
