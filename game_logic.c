#include "game_logic.h"

SDL_Surface* init_title_screen(void)
{
    SDL_Surface* image;
    TTF_Font* fnt;
    SDL_Color color;
    char ret;

    title_screen = NULL;

    title_screen = load_bmp("hello.bmp");
    if (title_screen == NULL)
        return NULL;

    image = load_png("worm.png");
    SDL_Rect rect;
    rect.x = (title_screen->w / 2) - (image->w / 2) - 80;
    rect.y = (title_screen->h / 2) - (image->h / 2) - 50;
    rect.h = image->h;
    rect.w = image->w;
    SDL_BlitSurface(image, NULL, title_screen, &rect);
    SDL_FreeSurface(image);

    image = load_png("joachim_westlund.png");
    rect.x = 10;
    rect.y = 10;
    rect.h = image->h;
    rect.w = image->w;
    SDL_BlitSurface(image, NULL, title_screen, &rect);
    SDL_FreeSurface(image);

    fnt = load_font("Butterflies Free.ttf", 200);
    if (fnt == NULL)
        return NULL;

    color.r = 0xdd;
    color.g = 0x44;
    color.b = 0x44;
    color.a = 0x00;
    ret = print_text(fnt, "Masken", &color, title_screen, 180, 410);
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
    ret = print_text(fnt, "Music keys 1-5 and 0", &color, title_screen, 380, 10);
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
    ret = print_text(fnt, "SPACE to play!", &color, title_screen, 380, 210);
    if (ret == FALSE)
        return NULL;

    TTF_CloseFont(fnt);

    return title_screen;
}
