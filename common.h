#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>
#include <SDL2/SDL.h>

#include "debug.h"

/**
 * @brief Initializes the SDL2 graphics library for this game.
 *
 * @return  success = SDL_Window pointer
 *          failure = NULL
 */
extern SDL_Window* sdl_init(void);
extern SDL_Surface* load_bmp(char* path);

#endif // __COMMON_H__
