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

    score_fnt = load_font("Life is goofy.ttf", 80);
    if (score_fnt == NULL)
    {
        #ifdef DEBUG
            printf("Unable to create the score font: %s\n", SDL_GetError());
        #endif // DEBUG
        return FALSE;
    }

    score_color.r = 0x00;
    score_color.g = 0x00;
    score_color.b = 0x00;
    score_color.a = 0x00;

    r_objects_count = 0;

    return TRUE;
}

void render(void)
{
    SDL_RenderClear(renderer);
    if (is_playing == FALSE && game_over == FALSE)
    {
        SDL_RenderCopy(renderer, title_screen, NULL, NULL);
    }
    else if (game_over == TRUE)
    {
        SDL_RenderCopy(renderer, game_over_screen, NULL, NULL);
    }
    else
    {
        SDL_RenderCopy(renderer, game_screen, NULL, NULL);
        score_surface = TTF_RenderText_Solid(score_fnt, convert_score_to_str(), score_color);
        score_texture = SDL_CreateTextureFromSurface(renderer, score_surface);
        score_rect.w = score_surface->w;
        score_rect.h = score_surface->h;
        score_rect.x = 400;
        score_rect.y = 35;
        SDL_RenderCopy(renderer, score_texture, NULL, &score_rect);
        SDL_FreeSurface(score_surface);
        SDL_DestroyTexture(score_texture);
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

void add_to_render_queue(SDL_Texture* texture, SDL_Rect rect, int angle)
{
    r_objects[r_objects_count].dest = rect;
    r_objects[r_objects_count].texture = texture;
    r_objects[r_objects_count].angle = angle;
    if (r_objects_count < max_number_of_objects)
        r_objects_count++;
}

char* convert_score_to_str()
{
    itoa(score, score_str, 10);
    printf("%s\n",score_str);
    return score_str;
}
