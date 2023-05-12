#include "common.h"

SDL_Window* sdl_init(void)
{
    SDL_Window* window = NULL;

    int SCREEN_WIDTH = 800;
    int SCREEN_HEIGHT = 600;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

    if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG)
    {
        #ifdef DEBUG
            printf("Unable to initialize sound system: %s\n", Mix_GetError());
        #endif // DEBUG
        return NULL;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512) != 0)
    {
        #ifdef DEBUG
            printf("Unable to initialize default audio device for playback: %s\n", Mix_GetError());
        #endif // DEBUG
        return NULL;
    }

    if (init_music() == FALSE)
    {
        #ifdef DEBUG
            printf("Unable to initialize songs: %s\n", Mix_GetError());
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

    SDL_FreeSurface(text_surface);

    return TRUE;
}

Mix_Music* load_music(char *filename)
{
    Mix_Music* music = NULL;

    music = Mix_LoadMUS(filename);
    if(music == NULL)
    {
        #ifdef DEBUG
            printf("Unable to load music: %s. %s\n", filename, Mix_GetError());
        #endif // DEBUG
        return NULL;
    }
    return music;
}

char init_music(void)
{
    song1 = Mix_LoadMUS("1990chip.ogg");
    if(song1 == NULL)
    {
        #ifdef DEBUG
            printf("Unable to load song1: %s\n", Mix_GetError());
        #endif // DEBUG
        return FALSE;
    }

    song2 = Mix_LoadMUS("c64theme.ogg");
    if(song2 == NULL)
    {
        #ifdef DEBUG
            printf("Unable to load song2: %s\n", Mix_GetError());
        #endif // DEBUG
        return FALSE;
    }

    song3 = Mix_LoadMUS("childrenhard.ogg");
    if(song3 == NULL)
    {
        #ifdef DEBUG
            printf("Unable to load song3: %s\n", Mix_GetError());
        #endif // DEBUG
        return FALSE;
    }

    song4 = Mix_LoadMUS("medc64-mania.ogg");
    if(song4 == NULL)
    {
        #ifdef DEBUG
            printf("Unable to load song4: %s\n", Mix_GetError());
        #endif // DEBUG
        return FALSE;
    }

    song5 = Mix_LoadMUS("c64_tune_odkin.ogg");
    if(song5 == NULL)
    {
        #ifdef DEBUG
            printf("Unable to load song5: %s\n", Mix_GetError());
        #endif // DEBUG
        return FALSE;
    }
    return TRUE;
}

char change_music(int nr)
{
    if (nr == 1)
    {
        if (Mix_PlayMusic(song1, 100) == -1)
        {
            #ifdef DEBUG
                printf("Unable to play song1");
            #endif // DEBUG
            return FALSE;
        }
    }
    else if(nr == 2)
    {
        if (Mix_PlayMusic(song2, 100) == -1)
        {
            #ifdef DEBUG
                printf("Unable to play song2");
            #endif // DEBUG
            return FALSE;
        }
    }
    else if(nr == 3)
    {
        if (Mix_PlayMusic(song3, 100) == -1)
        {
            #ifdef DEBUG
                printf("Unable to play song3");
            #endif // DEBUG
            return FALSE;
        }
    }
    else if(nr == 4)
    {
        if (Mix_PlayMusic(song4, 100) == -1)
        {
            #ifdef DEBUG
                printf("Unable to play song4");
            #endif // DEBUG
            return FALSE;
        }
    }
    else if(nr == 5)
    {
        if (Mix_PlayMusic(song5, 100) == -1)
        {
            #ifdef DEBUG
                printf("Unable to play song5");
            #endif // DEBUG
            return FALSE;
        }
    }
    else if (nr == 0)
    {
        Mix_PauseMusic();
    }

    return TRUE;
}
