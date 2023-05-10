#ifndef __INPUT_H__
#define __INPUT_H__

#include <SDL2/SDL.h>
#include "debug.h"
#include "common.h"

extern struct inputs
{
    char LEFT;
    char RIGHT;
    char UP;
    char DOWN;
    char ESCAPE;
};

extern struct inputs* get_inputs(SDL_Event*);


#endif // __INPUT_H__
