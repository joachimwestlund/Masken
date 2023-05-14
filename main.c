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
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "debug.h"
#include "game_objects.h"
#include "common.h"
#include "input.h"
#include "game_logic.h"
#include "renderer.h"

/**
 * @brief This is the main entry of the program.
 * @return 0 on success and -1 on failure.
 */
int main(void)
{
    SDL_Window* window;
    SDL_Surface* screen_surface;
    SDL_Event event;
    struct inputs* input;
    is_playing = FALSE;
    game_over = FALSE;
    quit = FALSE;
    SDL_bool collision = SDL_FALSE;

    printf("Masken. A worm clone made by Joachim Westlund.\n\n");

    #ifdef DEBUG
        printf("DEBUGING INFORMATION ON\n\n");
    #endif // DEBUG

    // Initialization and creation of the main window.
    if ((window = sdl_init()) == NULL)
        return -1;

    if (init_renderer(window) == FALSE)
        return -1;

    screen_surface = SDL_GetWindowSurface(window);

    if (init_title_screen(renderer) == NULL)
    {
        #ifdef DEBUG
            printf("Failed to initialize the title screen\n");
        #endif // DEBUG
        return -1;
    }

    if (init_game_screen(renderer) == NULL)
    {
        #ifdef DEBUG
            printf("Failed to initialize the game screen\n");
        #endif // DEBUG
        return -1;
    }

    init_player();
    init_body();
    init_food();

    change_music(1);

    // Main event and game loop.
    // Input
    // GameLogic
    // Render
    while(!quit)
    {
        input = get_inputs(&event);
        if (input->ESCAPE == TRUE)
            quit = TRUE;

        handle_input();
        if (is_playing) // this is so that the we don't just add stuff to the render queue to make it overflow. we need to fix this better.
        {
            move_player();
            add_to_render_queue(player.head, player.rect, player.angle);
            add_to_render_queue(food.texture, food.rect, food.angle);
        }

        render();

        collision = SDL_HasIntersection(&player.rect, &food.rect);
        if (collision == SDL_TRUE)
        {
            printf("collision\n");
        }

        SDL_Delay(3);
    }

    // free stuff and quit
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(screen_surface);
    SDL_DestroyWindow(window);
    window = NULL;
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}


