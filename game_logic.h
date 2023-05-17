#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "debug.h"
#include "common.h"
#include "input.h"
#include "game_objects.h"

char head_direction_changed;
char head_direction_changed_completed;
int move_point_index;

struct move_point
{
    int dx;
    int dy;
    int x;
    int y;
    SDL_Rect rect;
};

struct move_point move_points[1000];

/** structure to hande player movement and position */
struct player_movement
{
    /** delta x position to update player x position before next frame */
    int dx;
    /** delta y position to update player x position before next frame */
    int dy;
    /** previous delta x posision */
    int prev_dx;
    /** previous delta y posision */
    int prev_dy;
};

/** the instantiated player position and movement structure */
struct player_movement player_pos;

/**
 * @brief This function will start the game from the title screen.
 */
void play(void);

/**
 * @brief This function will check the input struct every frame and uppdate direction.
 */
void handle_input(void);

/**
 * @brief This function will move the player based on player_movement struct.
 */
void move_player(void);

/**
 * @brief This function handles the collisions in the game.
 */
void check_and_handle_collisions(void);

void add_body_parts(void);

#endif // __GAME_LOGIC_H__
