#include "common.h"

SDL_Window* sdl_init(void)
{
    SDL_Window* window = NULL;

    int SCREEN_WIDTH = 800;
    int SCREEN_HEIGHT = 600;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        #ifdef DEBUG
            printf("Unable to init SDL: %s\n", SDL_GetError());
        #endif // DEBUG
        return NULL;
    }

    window = SDL_CreateWindow("Masken", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        #ifdef DEBUG
            printf("Unable to create a SDL Window: %s\n", SDL_GetError());
        #endif // DEBUG
        return NULL;
    }

    // initialize PNG image loading
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        #ifdef DEBUG
            printf("Unable to initialize SDL2_image for PNG format: %s\n", IMG_GetError());
        #endif // DEBUG
        return NULL;
    }

    SDL_UpdateWindowSurface(window);

    return window;
}

/**
 * @brief Loads an image of BMP format to an RGB format SDL_surface
 * @param Path to the image
 * @return Returns a pointer to a SDL_Surface containing the image.
 */
SDL_Surface* load_bmp(char* path)
{
    SDL_Surface* img = NULL;

    img = SDL_LoadBMP((const char*)path);
    if (img == NULL)
    {
        #ifdef DEBUG
            printf("Unable to load BMP: %s\n", SDL_GetError());
        #endif // DEBUG
    }
    return img;
}

/**
 * @brief Loads an image of PNG format to an RGBA format SDL_surface
 * @param Path to the image
 * @return Returns a pointer to a SDL_Surface containing the image or NULL on failiure.
 */
SDL_Surface* loadPNG(char *path)
{
    SDL_Surface *img = NULL;

    img = IMG_Load(path);
    if (img == NULL)
    {
        #ifdef DEBUG
            printf("Unable to load PNG: %s. %s\n", path, IMG_GetError());
        #endif // DEBUG
        return NULL;
    }
    return img;
}
