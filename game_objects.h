#ifndef __GAME_OBJECTS_H__
#define __GAME_OBJECTS_H__

/** structure to hold player data. */
struct player_object
{
    /** Graphics of the player head */
    SDL_Texture* head;
    /** Graphics of the body sections */
    SDL_Texture* body;
    /** x position */
    int x;
    /** y position */
    int y;
    /** number of body sections currently */
    int no_body_sections;
};

/** structure to hold food data for the worm. */
struct food_object
{
    /** Graphics of the food */
    SDL_Texture* texture;
    /** x position */
    int x;
    /** y position */
    int y;
    /** the score that this food will give when eaten */
    int score;
};

/** instantiated player object for the game */
struct player_object player;

/** Title screen texture */
SDL_Texture* title_screen;

/** Game screen texture */
SDL_Texture* game_screen;

#endif // __GAME_OBJECTS_H__
