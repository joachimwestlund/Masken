#ifndef __INPUT_H__
#define __INPUT_H__

#include <SDL2/SDL.h>
#include "debug.h"
#include "common.h"
#include "game_logic.h"

/** Structure containing key presses */
struct inputs
{
    char LEFT;
    char RIGHT;
    char UP;
    char DOWN;
    char ESCAPE;
};

/** instantiated structure containing key presses */
struct inputs input;

/**
 * @brief Gets the inputs from user.
 * @details Arrow keys for controlling the worm and escape key to quit.
 * @return Structure containing the pressed buttons.
 */
struct inputs* get_inputs(SDL_Event*);


#endif // __INPUT_H__
