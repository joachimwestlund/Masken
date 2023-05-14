#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "debug.h"
#include "common.h"
#include "input.h"
#include "game_objects.h"

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

#endif // __GAME_LOGIC_H__
