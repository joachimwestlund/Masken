/**
 * @mainpage
 * @brief Masken is a snake clone written in C for educational purposes.
 * @details It uses the SDL2 library version 2.26.5 for the graphics
 *          https://www.libsdl.org.
 *
 * @date 2023-05-10
 * @author Joachim Westlund
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
#include "hiscore.h"

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
    is_adding_body_parts = FALSE;
    double time_counter = 0;
    unsigned int delay = 5;

    printf("Masken. A snake clone made by Joachim Westlund.\n\n");

    srand(time(NULL));  // use current time as seed for random numbers

    #ifdef DEBUG
        printf("DEBUGING INFORMATION ON\n\n");
    #endif // DEBUG

    // Initialization and creation of the main window.
    if ((window = sdl_init()) == NULL)
        return -1;

    if (init_renderer(window) == FALSE)
        return -1;

    screen_surface = SDL_GetWindowSurface(window);

    if (init_hiscore() == FALSE)
    {
        #ifdef DEBUG
            printf("Failed to initialize the hiscore.\n");
        #endif // DEBUG
        return -1;
    }

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

    if (init_game_over_screen(renderer) == NULL)
    {
        #ifdef DEBUG
            printf("Failed to initialize the game over screen\n");
        #endif // DEBUG
        return -1;
    }

    max_number_of_objects = 300;
    max_number_of_body_objects = max_number_of_objects - 2; // minus 1 head and 1 food.

    init_player();
    init_body();
    init_food();

    #ifdef PLAY_MUSIC
        change_music(1);
    #endif // PLAY_MUSIC

    // Main event and game loop.
    while(!quit)
    {
        input = get_inputs(&event);
        if (input->ESCAPE == TRUE)
        {
            if (game_over == TRUE)
            {
                game_over = FALSE;
                is_playing = FALSE;
                delay = 5;
                #ifdef PLAY_MUSIC
                    change_music(1);
                #endif // PLAY_MUSIC
            }
            else if (is_playing == TRUE)
            {
                is_playing = FALSE;
                reset_game();
                delay = 5;
                #ifdef PLAY_MUSIC
                    change_music(1);
                #endif // PLAY_MUSIC
            }
            else
                quit = TRUE;
        }

        handle_input();

        if (is_playing)
        {
            move_player();
            add_to_render_queue(player.head, player.rect, player.angle);
            add_to_render_queue(food.texture, food.rect, food.angle);
            for (int i = 0; i < player.no_body_sections; i++)
            {
                add_to_render_queue(body_sections[i].body, body_sections[i].rect, body_sections[i].angle);
            }
        }

        render();

        check_and_handle_collisions();

        SDL_Delay(delay);

        is_adding_body_parts = FALSE;

        if (game_over) {
            is_playing = FALSE;
        }

        time_counter = get_number_of_seconds();
        if (time_counter > 30)                  // speed boost every 30 seconds
        {
            start_clock();
            delay -= 1;
            if (delay <= 1)
                delay = 1;
            #ifdef DEBUG
                printf("Speed boost (less delay per frame): %d\n", delay);
            #endif // DEBUG
        }

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


