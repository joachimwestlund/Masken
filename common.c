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

SDL_Texture* load_texture(char* path, SDL_Renderer* r)
{
    SDL_Texture* t = NULL;

    t = IMG_LoadTexture(r, path);
    if (t == NULL)
    {
        #ifdef DEBUG
            printf("Unable to load PNG texture: %s. %s\n", path, IMG_GetError());
        #endif // DEBUG
        return NULL;
    }

    return t;
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

SDL_Texture* init_game_over_screen(SDL_Renderer* renderer)
{
    SDL_Surface* screen;
    SDL_Texture* texture;
    TTF_Font* fnt;
    SDL_Color color;
    char ret;
    int s = 0;
    char buffer[16] = {0};

    screen = NULL;
    texture = NULL;

    screen = load_png("black.png");
    if (screen == NULL)
        return NULL;

    fnt = load_font("Butterflies Free.ttf", 200);
    if (fnt == NULL)
        return NULL;

    color.r = 0xdd;
    color.g = 0x44;
    color.b = 0x44;
    color.a = 0x00;
    ret = print_text(fnt, "Game Over", &color, screen, 100, 10);
    if (ret == FALSE)
        return NULL;

    TTF_CloseFont(fnt);

    fnt = load_font("Life is goofy.ttf", 100);
    if (fnt == NULL)
        return NULL;

    color.r = 0x20;
    color.g = 0x20;
    color.b = 0xaa;
    color.a = 0x00;
    ret = print_text(fnt, "Your score:", &color, screen, 150, 300);
    if (ret == FALSE)
        return NULL;

    color.r = 0xdd;
    color.g = 0xdd;
    color.b = 0x20;
    color.a = 0x00;
    itoa(score, buffer, 10);
    ret = print_text(fnt, buffer, &color, screen, 470, 300);
    if (ret == FALSE)
        return NULL;

    color.r = 0x20;
    color.g = 0xaa;
    color.b = 0x20;
    color.a = 0x00;
    ret = print_text(fnt, "Hiscore:", &color, screen, 150, 400);
    if (ret == FALSE)
        return NULL;

    color.r = 0xdd;
    color.g = 0xdd;
    color.b = 0x20;
    color.a = 0x00;
    s = get_hiscore();
    itoa(s, buffer, 10);
    ret = print_text(fnt, buffer, &color, screen, 400, 400);
    if (ret == FALSE)
        return NULL;

    TTF_CloseFont(fnt);

    texture = SDL_CreateTextureFromSurface(renderer, screen);
    if(texture == NULL)
    {
        #ifdef DEBUG
            printf("Unable to initialize the title screen texture: %s\n", SDL_GetError());
        #endif // DEBUG
    }

    game_over_screen = texture;

    SDL_FreeSurface(screen);

    return texture;
}

SDL_Texture* init_title_screen(SDL_Renderer* renderer)
{
    SDL_Surface* screen;
    SDL_Surface* image;
    SDL_Texture* texture;
    TTF_Font* fnt;
    SDL_Color color;
    char ret;

    screen = NULL;
    texture = NULL;

    screen = load_bmp("hello.bmp");
    if (screen == NULL)
        return NULL;

    image = load_png("worm.png");
    SDL_Rect rect;
    rect.x = (screen->w / 2) - (image->w / 2) - 80;
    rect.y = (screen->h / 2) - (image->h / 2) - 50;
    rect.h = image->h;
    rect.w = image->w;
    SDL_BlitSurface(image, NULL, screen, &rect);
    SDL_FreeSurface(image);

    image = load_png("joachim_westlund.png");
    rect.x = 10;
    rect.y = 10;
    rect.h = image->h;
    rect.w = image->w;
    SDL_BlitSurface(image, NULL, screen, &rect);
    SDL_FreeSurface(image);

    fnt = load_font("Butterflies Free.ttf", 200);
    if (fnt == NULL)
        return NULL;

    color.r = 0xdd;
    color.g = 0x44;
    color.b = 0x44;
    color.a = 0x00;
    ret = print_text(fnt, "Masken", &color, screen, 180, 410);
    if (ret == FALSE)
        return NULL;

    TTF_CloseFont(fnt);

    fnt = load_font("Life is goofy.ttf", 70);
    if (fnt == NULL)
        return NULL;

    color.r = 0x11;
    color.g = 0x11;
    color.b = 0xee;
    color.a = 0x00;
    ret = print_text(fnt, "Music keys 1-5 and 0", &color, screen, 380, 10);
    if (ret == FALSE)
        return NULL;

    TTF_CloseFont(fnt);

    fnt = load_font("Life is goofy.ttf", 100);
    if (fnt == NULL)
        return NULL;

    color.r = 0x88;
    color.g = 0x11;
    color.b = 0x99;
    color.a = 0x00;
    ret = print_text(fnt, "SPACE to play!", &color, screen, 380, 210);
    if (ret == FALSE)
        return NULL;

    TTF_CloseFont(fnt);

    texture = SDL_CreateTextureFromSurface(renderer, screen);
    if(texture == NULL)
    {
        #ifdef DEBUG
            printf("Unable to initialize the title screen texture: %s\n", SDL_GetError());
        #endif // DEBUG
    }

    title_screen = texture;

    SDL_FreeSurface(screen);

    return texture;
}

SDL_Texture* init_game_screen(SDL_Renderer* renderer)
{
    SDL_Surface* screen;
    SDL_Texture* texture;
    TTF_Font* fnt;
    SDL_Color color;
    char ret;

    screen = NULL;
    texture = NULL;

    screen = load_png("play_field.png");
    if (screen == NULL)
    {
        #ifdef DEBUG
            printf("Unable to load game field: %s\n", IMG_GetError());
        #endif // DEBUG
        return NULL;
    }

    fnt = load_font("Life is goofy.ttf", 80);
    if (fnt == NULL)
        return NULL;

    color.r = 0x00;
    color.g = 0x00;
    color.b = 0x00;
    color.a = 0x00;
    ret = print_text(fnt, "SCORE: ", &color, screen, 200, 35);
    if (ret == FALSE)
        return NULL;
    TTF_CloseFont(fnt);

    texture = SDL_CreateTextureFromSurface(renderer, screen);
    if(texture == NULL)
    {
        #ifdef DEBUG
            printf("Unable to initialize the title screen texture: %s\n", SDL_GetError());
        #endif // DEBUG
    }

    game_screen = texture;

    SDL_FreeSurface(screen);

    return texture;
}

char init_player(void)
{
    SDL_Texture* t;
    SDL_Rect rect;
    int w;
    int h;

    t = load_texture("head.png", renderer);
    if (t == NULL)
        return FALSE;

    SDL_QueryTexture(t, NULL, NULL, &w, &h);

    player.head = t;
    player.no_body_sections = 0;
    player.angle = 0;
    rect.h = h;
    rect.w = w;
    rect.x = 400;
    rect.y = 300;
    player.rect = rect;
    return TRUE;
}

char init_food(void)
{
    SDL_Texture* t;
    SDL_Rect rect;
    int w;
    int h;

    t = load_texture("apple.png", renderer);
    if (t == NULL)
    {
        return FALSE;
    }

    SDL_QueryTexture(t, NULL, NULL, &w, &h);

    food.texture = t;
    food.score = 10;
    food.angle = 0;
    rect.h = h;
    rect.w = w;
    rect.x = 0;
    rect.y = 0;
    food.rect = rect;

    new_food();

    return TRUE;
}

char new_food(void)
{
    // screen posisions
    // x = 16px to 768px
    // y = 101px to 568px

    SDL_Rect new_pos;

    // (rand() % upper - lower + 1) + lower, to calculate the range of random number
    new_pos.x = (rand() % (768 - 16 + 1)) + 16;
    new_pos.y = (rand() % (568 - 101 + 1)) + 101;
    new_pos.h = food.rect.h;
    new_pos.w = food.rect.w;
    food.score = (rand() % (10 - 1 + 1)) + 1;
    food.angle = 0;
    food.rect = new_pos;

    printf("food: %d %d %d\n", new_pos.x, new_pos.y, food.score);

    return TRUE;
}

char init_body(void)
{
    SDL_Texture* t;
    SDL_Rect rect;
    int w;
    int h;

    t = load_texture("body.png", renderer);
    if (t == NULL)
        return FALSE;

    SDL_QueryTexture(t, NULL, NULL, &w, &h);

    body.body = t;
    body.angle = 0;
    rect.h = h;
    rect.w = w;
    rect.x = 400;
    rect.y = 300;
    body.rect = rect;

    return TRUE;
}
