/**
 *      @mainpage
 *      @brief Masken is a worm clone written in C for educational pourposes.
 *
 *      @details It uses the SDL2 library version 2.26.5 for the graphics.
 *               https://www.libsdl.org
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
int main()
{
    SDL_Window* window;
    SDL_Surface* surface;
    SDL_Surface* picture;

    SDL_Event event;

    struct inputs* input;

    char quit = FALSE;

    printf("Masken. A worm clone made by Joachim Westlund.\n\n");

    #ifdef DEBUG
        printf("DEBUGING INFORMATION ON\n\n");
    #endif // DEBUG

    if ((window = sdl_init()) == NULL)
        return -1;

    surface = SDL_GetWindowSurface(window);

    picture = load_bmp("hello.bmp");
    if (picture == NULL)
        return -1;

    SDL_BlitSurface(picture, NULL, surface, NULL);
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
    SDL_FreeSurface(picture);
    picture = NULL;
    SDL_FreeSurface(surface);
    surface = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();

    return 0;
}


