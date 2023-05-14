#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "common.h"

struct render_objects
{
    SDL_Texture* texture;
    SDL_Rect dest;
    int angle;
};

struct render_objects r_objects[100];
int r_objects_count;

/** The renerer for this game */
SDL_Renderer* renderer;

/** this will act as some sort of buffer. It will be written to and later rendered to the game_texture */
SDL_Texture* buffer;

/**
 * @brief Initialize the renerer for the game
 * @param window the SDL_Window to render to.
 * @return TRUE on success or FALSE on failure.
 */
char init_renderer(SDL_Window* window);

/**
 * @brief this is the renderer that the game loop should call */
void render(void);

/**
 * @brief this function will take in a texture and render it to the offscreen buffer. For now only 100 items can be added.
 * @param texture the texture to be rendered.
 * @param rect the rectangle for position with and heigt of the texture and for collision detection.
 * @param angle of rotation of the texture.
 */
void add_to_render_queue(SDL_Texture* texture, SDL_Rect rect, int angle);

/**
 * @brief This function renders the the render queue to the double buffered screen. This is in a way the real renderer. the render function is more of a scene renderer.
 */
void render_queue(void);


#endif // __RENDERER_H__
