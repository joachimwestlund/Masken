#include "renderer.h"

char init_renderer(SDL_Window* window)
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
    printf("%d\n", r_objects_count);
    for(int i = 0; i < r_objects_count; i++)
    {
       SDL_RenderCopy(renderer, r_objects[i].texture, NULL, r_objects[i].dest);
    }
    r_objects_count = 0;
}

void add_to_render_queue(SDL_Texture* texture, int x, int y)
{
    SDL_Rect dest;
    int w;
    int h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    dest.x = x;
    dest.y = y;
    dest.h = h;
    dest.w = w;

    r_objects[r_objects_count].dest = &dest;
    r_objects[r_objects_count].texture = texture;
    r_objects_count++;
}
