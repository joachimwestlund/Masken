/**
 *      @mainpage
 *      @brief Masken is a worm clone written in C for educational purposes.
 *
 *      @details It uses the SDL2 library version 2.26.5 for the graphics
 *               https://www.libsdl.org.
 *
 *      @date 2023-05-10
 *      @author Joachim Westlund
 */


#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>


#include "debug.h"
#include "common.h"
#include "input.h"

/**
 * @brief This is the main entry of the program.
 * @return 0 on success and -1 on failure.
 */
int main(void)
{
    SDL_Window* window;
    SDL_Surface* screen_surface;
    SDL_Surface* picture;
    SDL_Surface* worm_logo;
    SDL_Event event;
    TTF_Font* fnt;
    SDL_Color color;


    struct inputs* input;
    char quit = FALSE;
    char ret;

    printf("Masken. A worm clone made by Joachim Westlund.\n\n");

    #ifdef DEBUG
        printf("DEBUGING INFORMATION ON\n\n");
    #endif // DEBUG

    if ((window = sdl_init()) == NULL)
        return -1;

    screen_surface = SDL_GetWindowSurface(window);

    picture = load_bmp("hello.bmp");
    if (picture == NULL)
        return -1;

    SDL_BlitSurface(picture, NULL, screen_surface, NULL);
    SDL_UpdateWindowSurface(window);


    worm_logo = load_png("worm.png");

    SDL_Rect rect;
    rect.x = (screen_surface->w / 2) - (worm_logo->w / 2);
    rect.y = (screen_surface->h / 2) - (worm_logo->h / 2);
    rect.h = worm_logo->h;
    rect.w = worm_logo->w;
    SDL_BlitSurface(worm_logo, NULL, screen_surface, &rect);
    SDL_UpdateWindowSurface(window);

    fnt = load_font("Butterflies Free.ttf", 200);
    if (fnt == NULL)
        return -1;

    color.r = 0xaa;
    color.g = 0x44;
    color.b = 0x44;
    color.a = 0x00;
    ret = print_text(fnt, "Masken", &color, screen_surface, 10, 400);
    if (ret == FALSE)
        return -1;


    change_music(1);

    SDL_UpdateWindowSurface(window);


    // Main event and game loop.
    // Input
    // GameLogic
    // Render
    while(!quit)
    {
        input = get_inputs(&event);
        if (input->ESCAPE == TRUE)
            quit = TRUE;

        //game_logic();

        //Render();
    }

    // free stuff and quit
    TTF_CloseFont(fnt);
    SDL_FreeSurface(worm_logo);
    worm_logo = NULL;
    SDL_FreeSurface(picture);
    picture = NULL;
    SDL_FreeSurface(screen_surface);
    screen_surface = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}


