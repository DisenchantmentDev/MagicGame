#include "player.h"

void init_player(Player *p, Image sheet) {
    Texture2D texture = LoadTextureFromImage(sheet);
    p->sprite_sheet = texture;
    p->sprite =
        texture; // This will need to change later to a DrawTexturePro() call
    p->pos = (Vector2){PLAYER_STARTING_X, PLAYER_STARTING_Y};
    p->mov_dir = (Vector2){MOV_RIGHT, MOV_UP};
    p->health = MAX_HP;
    p->shield = MAX_SHIELD;
    p->armor = 0;
}

void draw_current_glumbus(Player *p) {
    /* Logic for actually finding and drawing rectangles goes here
     * For now though it's hard coded values*/
    Rectangle source = {0, 0, GLUMBUS_SHEET_SIZE, GLUMBUS_SHEET_SIZE};
    Rectangle destination = {p->pos.x, p->pos.y, GLUMBUS_SPRITE_SIZE,
                             GLUMBUS_SPRITE_SIZE};

    /* Actually drawing the sprite from the sheet */
    if (p->mov_dir.x == MOV_RIGHT)
        source.width = -source.width;
    DrawTexturePro(p->sprite, source, destination, (Vector2){0, 0}, 0.0f,
                   WHITE);
}

void player_move(Player *p) {
    if (IsKeyDown(KEY_D)) {
        p->pos.x += 2;
        p->mov_dir.x = MOV_RIGHT;
    } else if (IsKeyDown(KEY_A)) {
        p->pos.x -= 2;
        p->mov_dir.x = MOV_LEFT;
    }

    if (IsKeyDown(KEY_S)) {
        p->pos.y += 2;
        p->mov_dir.y = MOV_DOWN;
    } else if (IsKeyDown(KEY_W)) {
        p->pos.y -= 2;
        p->mov_dir.y = MOV_UP;
    }
}

void take_damage(Player *p, int incoming) {
    if(p->shield != 0) {
        if(p->shield < incoming) p->shield = 0; //Shield will block all damage to health when it is broken, no punch through
        else p->shield -= incoming;
    }
    else {
        int trueDamage = incoming * (1.0 - (p->armor / 100)); //This mitigates damage to health based on armor ie 60 armor = 60% damage reduction
        if(p->health < trueDamage){
            p->health = 0;
            death(p);
        }
        else p->health -= trueDamage;
    }
}

void heal(Player *p, int incoming) {
    if(incoming + p->health > MAX_HP) p->health = MAX_HP;
    else p->health += incoming;
}

void armor_increase(Player *p, int incoming) {
    if(incoming + p->armor > MAX_ARMOR) p->armor = MAX_ARMOR;
    else p->armor += incoming;
}

void death(Player *p) {
    //Empty for now, placeholder to do something on player death
}
