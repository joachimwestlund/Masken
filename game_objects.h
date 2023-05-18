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
    /** pixels to move before direction change */
    int delta_pixels;
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
    /** delta position in x direction */
    int dx;
    /** delta position in y direction */
    int dy;
    /** position to start changeing direction */
    SDL_Rect change_pos;

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

/** maximum number of objects that are renderable */
int max_number_of_objects;

/** maximum number of body objects that are allowed. Should be max_number_of_objects - other_render_objects */
int max_number_of_body_objects;

/** instantiated player object for the game */
struct player_object player;

/** A instantiated body object that is used to copy into the body_sections array */
struct body_object body;

/** array of body objects for the game. The number of objects are stored in the player struct. */
struct body_object body_sections[500];

/** instantiated food object for the game */
struct food_object food;

/** Title screen texture */
SDL_Texture* title_screen;

/** Game screen texture */
SDL_Texture* game_screen;

#endif // __GAME_OBJECTS_H__
