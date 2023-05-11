#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "debug.h"

#define TRUE 1
#define FALSE 0


/**
 * @brief Initializes the SDL2 graphics library for this game.
 *
 * @return  success = SDL_Window pointer
 *          failure = NULL
 */
SDL_Window* sdl_init(void);
SDL_Surface* load_bmp(char* path);
SDL_Surface* loadPNG(char *path);

#endif // __COMMON_H__
