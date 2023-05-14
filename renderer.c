#include "renderer.h"

char init_renderer(SDL_Window* window)
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED/* | SDL_RENDERER_PRESENTVSYNC*/);
    if (renderer == NULL)
    {
        #ifdef DEBUG
            printf("Unable to create the renderer: %s\n", SDL_GetError());
        #endif // DEBUG
        return FALSE;
    }

    r_objects_count = 0;

    return TRUE;
}

void render(void)
{
    SDL_RenderClear(renderer);
    if (is_playing == FALSE)
    {
        SDL_RenderCopy(renderer, title_screen, NULL, NULL);
    }
    else
    {
        SDL_RenderCopy(renderer, game_screen, NULL, NULL);
        render_queue();
    }

    SDL_RenderPresent(renderer);

}

void render_queue(void)
{
    for(int i = 0; i < r_objects_count; i++)
    {
       SDL_RenderCopyEx(renderer, r_objects[i].texture, NULL, &r_objects[i].dest, r_objects[i].angle, NULL, SDL_FLIP_NONE);
    }
    r_objects_count = 0;
}

void add_to_render_queue(SDL_Texture* texture, int x, int y, int angle)
{
    SDL_Rect dest;
    int w;
    int h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    dest.x = x;
    dest.y = y;
    dest.h = h;
    dest.w = w;

    r_objects[r_objects_count].dest = dest;
    r_objects[r_objects_count].texture = texture;
    r_objects[r_objects_count].angle = angle;
    r_objects_count++;
}
