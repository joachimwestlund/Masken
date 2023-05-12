#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "debug.h"
#include "common.h"

/**< the surface containing the graphics of the title screen. */
SDL_Surface* title_screen;

/**
 * @brief This will return the SDL_Surface containing the title screen.
 * @param game_surface is used to format the new surface.
 * @return a SDL_Surface containing the title screen. Or NULL on failure.
 */
SDL_Surface* init_title_screen(void);

#endif // __GAME_LOGIC_H__
