#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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

/**
 * @brief Loads an image of BMP format to an RGB format SDL_surface
 * @param Path to the image
 * @return Returns a pointer to a SDL_Surface containing the image.
 */
SDL_Surface* load_bmp(char* path);

/**
 * @brief Loads an image of PNG format to an RGBA format SDL_surface
 * @param Path to the image
 * @return Returns a pointer to a SDL_Surface containing the image or NULL on failiure.
 */
SDL_Surface* load_png(char *path);

/**
 * @brief Loads a true type font
 * @param Path to the font
 * @return Returns a pointer to a TTF_Font containing the font or NULL on failiure.
 */
TTF_Font* load_font(char*, int);

/**
 * @brief Blits a font to a surface
 * @param fnt that should be rendered.
 * @param text the text to be rendered.
 * @param color SDL_Color to color the thing.
 * @param destination surface that the font should be blitted to.
 * @param x coordinate on the destination.
 * @param y coordinate on the destination.
 * @return Returns TRUE if success and FALSE on failiure.
 */
char print_text(TTF_Font* fnt, char* text, SDL_Color* color, SDL_Surface* destination, int x, int y);

#endif // __COMMON_H__
