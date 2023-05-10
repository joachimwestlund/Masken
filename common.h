#ifndef __COMMON_H__
#define __COMMON_H__

#include <SDL2/SDL.h>

#include "debug.h"

#define TRUE 1
#define FALSE 0


/**
 * @brief Initializes the SDL2 graphics library for this game.
 *
 * @return  success = SDL_Window pointer
 *          failure = NULL
 */
extern SDL_Window* sdl_init(void);
extern SDL_Surface* load_bmp(char* path);

#endif // __COMMON_H__
