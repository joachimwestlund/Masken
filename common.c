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

    if (TTF_Init() == -1)
    {
        #ifdef DEBUG
            printf("Unable to initialize SDL2_ttf: %s\n", TTF_GetError());
        #endif // DEBUG
        return NULL;
    }

    SDL_UpdateWindowSurface(window);

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

SDL_Surface* load_png(char *path)
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

TTF_Font* load_font(char* path, int size)
{
    TTF_Font* fnt = NULL;

    fnt = TTF_OpenFont(path, size);
    if (fnt == NULL)
    {
        #ifdef DEBUG
            printf("Unable to load font: %s. %s\n", path, TTF_GetError());
        #endif // DEBUG
        return NULL;
    }
    return fnt;
}

char print_text(TTF_Font* fnt, char* text, SDL_Color* color, SDL_Surface* destination, int x, int y)
{
    SDL_Surface* text_surface = NULL;

    text_surface = TTF_RenderText_Solid(fnt, text, *color);
    if (text_surface == NULL)
    {
        #ifdef DEBUG
            printf("Unable to render font: %s\n", TTF_GetError());
        #endif // DEBUG
        return FALSE;
    }
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = text_surface->w;
    rect.h = text_surface->h;
    SDL_BlitSurface(text_surface, NULL, destination, &rect);

    return TRUE;
}
