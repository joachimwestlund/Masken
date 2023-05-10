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
    }
    else
    {
        SDL_UpdateWindowSurface(window);
    }

    return window;
}


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
