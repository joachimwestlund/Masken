#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "debug.h"
#include "common.h"
#include "input.h"
#include "game_objects.h"

/** Index of how many moves the head has done */
int move_point_index;

/** structure that holds places on the map that the head has changed direction so the body can follow */
struct move_point
{
    int dx;
    int dy;
    SDL_Rect rect;
};

/** Instantiated array of move points for the body to follow */
struct move_point move_points[500];

/** structure to hande player movement and position */
struct player_movement
{
    /** delta x position to update player x position before next frame */
    int dx;
    /** delta y position to update player x position before next frame */
    int dy;
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

/** A function to add body parts to the worm and based on the food score */
void add_body_parts(void);

/** This function adds a move point to the array in a semi stack sense */
void add_move_point(SDL_Rect rect, int dx, int dy);

#endif // __GAME_LOGIC_H__
