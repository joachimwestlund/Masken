#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "debug.h"
#include "game_objects.h"
#include "renderer.h"

#define TRUE 1
#define FALSE 0

/** flag to check if game is playing */
char is_playing;
/** game over flag */
char game_over;
/** user has pressed escape and wants to quit */
char quit;
/** is adding body parts */
char is_adding_body_parts;

/** song no.1 */
Mix_Music* song1;
/** song no.2 */
Mix_Music* song2;
/** song no.3 */
Mix_Music* song3;
/** song no.4 */
Mix_Music* song4;
/** song no.4 */
Mix_Music* song5;

/**
 * @brief Initializes the SDL2 graphics library for this game.
 *
 * @return  success = SDL_Window pointer
 *          failure = NULL
 */
SDL_Window* sdl_init(void);

/**
 * @brief Loads an image of BMP format to an RGB format SDL_surface
 * @param path to the image
 * @return Returns a pointer to a SDL_Surface containing the image.
 */
SDL_Surface* load_bmp(char* path);

/**
 * @brief Loads an image of PNG format to an RGBA format SDL_surface
 * @param path to the image
 * @return Returns a pointer to a SDL_Surface containing the image or NULL on failiure.
 */
SDL_Surface* load_png(char *path);

/**
 * @brief Loads a texture from disk.
 * @param path to the font.
 * @param r renderer for the texture.
 * @return Returns a pointer to a TTF_Font containing the font or NULL on failiure.
 */
SDL_Texture* load_texture(char* path, SDL_Renderer* r);

/**
 * @brief Loads a true type font.
 * @param path to the font.
 * @param size size of the font.
 * @return Returns a pointer to a TTF_Font containing the font or NULL on failiure.
 */
TTF_Font* load_font(char* path, int size);

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

/**
 * @brief Loads an vorbis ogg file.
 * @param filename to the ogg-file
 * @return Returns a pointer to MIX_Music containing the music or NULL on failiure.
 */
Mix_Music* load_music(char *filename);

/**
 * @brief Loads all 5 songs to be used in this game.
 * @return Returns TRUE on success or FAIL on failiure.
 */
char init_music(void);

/**
 * @brief Change between the 5 songs loaded or pause music.
 * @param nr number of the song to be played. 1-5. and 0 to pause music.
 * @return Returns TRUE on success or FAIL on failiure.
 */
char change_music(int nr);

/**
 * @brief Initialize and create the title screen graphics.
 * @param renderer that will render this title screen,
 * @return a SDL_Texture containing the title screen. Or NULL on failure.
 */
SDL_Texture* init_title_screen(SDL_Renderer* renderer);

/**
 * @brief Initialize and create the game screen graphics.
 * @param renderer that will render this game screen,
 * @return a SDL_Texture containing the game screen. Or NULL on failure.
 */
SDL_Texture* init_game_screen(SDL_Renderer* renderer);

/**
 * @brief Initialize and create the game over screen graphics.
 * @param renderer that will render this game over screen,
 * @return a SDL_Texture containing the game over screen. Or NULL on failure.
 */
SDL_Texture* init_game_over_screen(SDL_Renderer* renderer);

/**
 * @brief Initialize and create the player graphics and position.
 * @return TRUE on success or FALSE on failure.
 */
char init_player(void);

/**
 * @brief Initialize and create the food graphics and position and score.
 * @return TRUE on success or FALSE on failure.
 */
char init_food(void);

/**
 * @brief Initialize and create the body graphics and position.
 * @return TRUE on success or FALSE on failure.
 */
char init_body(void);

/** score */
int score;

#endif // __COMMON_H__
