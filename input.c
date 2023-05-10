
#include "input.h"

struct inputs input;

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
            default:
                break;
            }
        }
    }
    return &input;
}
