
#include "input.h"

struct inputs* get_inputs(SDL_Event* event)
{
    input.DOWN = FALSE;
    input.ESCAPE = FALSE;
    input.LEFT = FALSE;
    input.RIGHT = FALSE;
    input.UP = FALSE;

    while(SDL_PollEvent(event))
    {
        if (event->type == SDL_QUIT)
        {
            input.ESCAPE = TRUE;
        }
        else if(event->type == SDL_KEYDOWN)
        {
            switch(event->key.keysym.sym)
            {
            case SDLK_UP:
                input.UP = TRUE;
                #ifdef DEBUG
                    printf("UP\n");
                #endif // DEBUG
                break;
            case SDLK_DOWN:
                input.DOWN = TRUE;
                #ifdef DEBUG
                    printf("DOWN\n");
                #endif // DEBUG
                break;
            case SDLK_LEFT:
                input.LEFT = TRUE;
                #ifdef DEBUG
                    printf("LEFT\n");
                #endif // DEBUG
                break;
            case SDLK_RIGHT:
                input.RIGHT = TRUE;
                #ifdef DEBUG
                    printf("RIGHT\n");
                #endif // DEBUG
                break;
            case SDLK_ESCAPE:
                input.ESCAPE = TRUE;
                #ifdef DEBUG
                    printf("ESCAPE\n");
                #endif // DEBUG
                break;
            case SDLK_1:
                change_music(1);
                #ifdef DEBUG
                    printf("1\n");
                #endif // DEBUG
                break;
            case SDLK_2:
                change_music(2);
                #ifdef DEBUG
                    printf("2\n");
                #endif // DEBUG
                break;
            case SDLK_3:
                change_music(3);
                #ifdef DEBUG
                    printf("3\n");
                #endif // DEBUG
                break;
            case SDLK_4:
                change_music(4);
                #ifdef DEBUG
                    printf("4\n");
                #endif // DEBUG
                break;
            case SDLK_5:
                change_music(5);
                #ifdef DEBUG
                    printf("5\n");
                #endif // DEBUG
                break;
            case SDLK_0:
                change_music(0);
                #ifdef DEBUG
                    printf("0\n");
                #endif // DEBUG
                break;
            case SDLK_SPACE:
                if (!is_playing && !game_over)
                    play();
                #ifdef DEBUG
                    printf("SPACE\n");
                #endif // DEBUG
                break;
            default:
                break;
            }
        }
    }
    return &input;
}
