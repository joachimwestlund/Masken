#ifndef __GAME_OBJECTS_H__
#define __GAME_OBJECTS_H__

/** structure to hold player data. */
struct player_object
{
    /** Graphics of the player head */
    SDL_Texture* head;
    /** bounding box for collision detection and position*/
    SDL_Rect rect;
    /** number of body sections currently */
    int no_body_sections;
    /** head angle */
    int angle;
};

/** structure to hold body data. */
struct body_object
{
    /** Graphics of the player head */
    SDL_Texture* body;
    /** bounding box for collision detection and position*/
    SDL_Rect rect;
    /** head angle */
    int angle;
};

/** structure to hold food data for the worm. */
struct food_object
{
    /** Graphics of the food */
    SDL_Texture* texture;
    /** angle of food */
    int angle;
    /** the score that this food will give when eaten */
    int score;
    /** bounding box for collision detection and posistion*/
    SDL_Rect rect;

};

/** instantiated player object for the game */
struct player_object player;

struct body_object body;

/** instantiated food object for the game */
struct food_object food;

/** Title screen texture */
SDL_Texture* title_screen;

/** Game screen texture */
SDL_Texture* game_screen;

#endif // __GAME_OBJECTS_H__
