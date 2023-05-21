#include "game_logic.h"

void play(void)
{
    if (is_playing != TRUE)
    {
        #ifdef PLAY_MUSIC
            change_music(4);
        #endif // PLAY_MUSIC
    }
    is_playing = TRUE;
    player_pos.dy = -1;
    player_pos.dx = 0;
    move_point_index = 0;
    score = 0;
    start_clock();
}

void add_to_score(int s)
{
    score += s;
    #ifdef DEBUG
        printf("Score: %d\n", score);
    #endif // DEBUG
}

void reset_game(void)
{
    player.rect.x = 400;
    player.rect.y = 300;
    player.angle = 0;
    player.no_body_sections = 0;
    move_point_index = 0;
    score = 0;
}

void game_over_func(void)
{
    game_over = TRUE;
    is_playing = FALSE;
    if (score > get_hiscore())
        save_hiscore(score);
    init_game_over_screen(renderer);
    reset_game();
    #ifdef PLAY_MUSIC
        change_music(5);
    #endif // PLAY_MUSIC
}

void add_move_point(SDL_Rect rect, int dx, int dy)
{
    for(int i = move_point_index; i > 0; i--)
    {
        move_points[i] = move_points[i - 1];
    }
    move_points[0].rect = rect;
    move_points[0].dx = dx;
    move_points[0].dy = dy;
    move_point_index++;
}

void handle_input(void)
{
    if (is_playing)
    {
        if (input.DOWN == TRUE)
        {
            if (player_pos.dy == -1 && player.no_body_sections > 0)
                game_over_func();
            player_pos.dy = 1;
            player_pos.dx = 0;
            if (player.no_body_sections > 0)
            {
                add_move_point(player.rect, player_pos.dx, player_pos.dy);
            }
        }
        if (input.UP == TRUE)
        {
            if (player_pos.dy == 1 && player.no_body_sections > 0)
                game_over_func();
            player_pos.dy = -1;
            player_pos.dx = 0;
            if (player.no_body_sections > 0)
            {
                add_move_point(player.rect, player_pos.dx, player_pos.dy);
            }
        }
        if (input.LEFT == TRUE)
        {
            if (player_pos.dx == 1 && player.no_body_sections > 0)
                game_over_func();
            player_pos.dx = -1;
            player_pos.dy = 0;
            if (player.no_body_sections > 0)
            {
                add_move_point(player.rect, player_pos.dx, player_pos.dy);
            }
        }
        if (input.RIGHT == TRUE)
        {
            if (player_pos.dx == -1 && player.no_body_sections > 0)
                game_over_func();
            player_pos.dx = 1;
            player_pos.dy = 0;
            if (player.no_body_sections > 0)
            {
                add_move_point(player.rect, player_pos.dx, player_pos.dy);
            }
        }
        #ifdef VERBOSE_DEBUG
            printf("dx: %d, dy:%d\n", player_pos.dx, player_pos.dy);
        #endif // DEBUG
    }
}

void move_player(void)
{
    // screen posisions
    // x = 16px to 768px
    // y = 101px to 568px

    if (player_pos.dx == -1)
    {
        player.rect.x--;
        if (player.rect.x < 16)
            game_over_func();
        player.angle = 270;
    }
    else if (player_pos.dx == 1)
    {
        player.rect.x++;
        if (player.rect.x > 768)
            game_over_func();
        player.angle = 90;
    }
    else if (player_pos.dy == -1)
    {
        player.rect.y--;
        if (player.rect.y < 101)
            game_over_func();
        player.angle = 0;
    }
    else if (player_pos.dy == 1)
    {
        player.rect.y++;
        if (player.rect.y > 568)
            game_over_func();
        player.angle = 180;
    }

    // handle body
    if (player.no_body_sections > 0)
    {
        // now we move stuff for the body
        for (int i = 0; i < player.no_body_sections; i++)
        {
            for (int j = 0; j < move_point_index; j++)
            {
                if (SDL_RectEquals(&body_sections[i].rect, &move_points[j].rect) == SDL_TRUE)
                {
                    body_sections[i].dx = move_points[j].dx;
                    body_sections[i].dy = move_points[j].dy;
                    if ((i == (player.no_body_sections - 1)) && (j == (move_point_index - 1)))
                    {
                        move_point_index--;
                    }
                }
            }

            if (body_sections[i].dx == -1)
            {
                body_sections[i].rect.x--;
            }
            if (body_sections[i].dx == 1)
            {
                body_sections[i].rect.x++;
            }
            if (body_sections[i].dy == -1)
            {
                body_sections[i].rect.y--;
            }
            if (body_sections[i].dy == 1)
            {
                body_sections[i].rect.y++;
            }
        }
    }

    #ifdef VERBOSE_DEBUG
        printf("move point index: %d  body segments: %d\n", move_point_index, player.no_body_sections);
    #endif // DEBUG
}

void check_and_handle_collisions(void)
{
    SDL_bool collision;

    collision = SDL_HasIntersection(&player.rect, &food.rect);
    if (collision == SDL_TRUE)
    {
        #ifdef DEBUG
            printf("collision with food.\n");
        #endif // DEBUG

        if (is_adding_body_parts == FALSE)
        {
            add_body_parts(food.score);
            add_to_score(food.score);
            new_food();
        }
        is_adding_body_parts = TRUE;
    }

    // check for collision but not for the first body segment behind the head.
    for (int i = 1; i < player.no_body_sections; i++)
    {
        collision = SDL_HasIntersection(&player.rect, &body_sections[i].rect);
        if (collision == SDL_TRUE)
        {
            #ifdef DEBUG
                printf("collision body part: %d. move point index: %d\n", i, move_point_index);
            #endif // DEBUG
            game_over_func();
        }
    }
}

void add_body_parts(int no)
{
    int body_size = 16;
    int count = 0;

    if (player.no_body_sections >= max_number_of_body_objects)
    {
        player.no_body_sections = max_number_of_body_objects;
        return;
    }

    if ((player.no_body_sections + no) <= max_number_of_body_objects)
    {
        count = no;
    }
    else
    {
        count = max_number_of_body_objects - (player.no_body_sections + no);
    }
    if (count < 0)
        count = 0;

    player.no_body_sections += count;

    SDL_Rect pos;
    pos.h = body.rect.h;
    pos.w = body.rect.w;

    if (player_pos.dx == -1)
        player.rect.x = player.rect.x - (body_size * count);
    if (player_pos.dx == 1)
        player.rect.x = player.rect.x + (body_size * count);
    if (player_pos.dy == -1)
        player.rect.y = player.rect.y - (body_size * count);
    if (player_pos.dy == 1)
        player.rect.y = player.rect.y + (body_size * count);


    for(int i = player.no_body_sections; i >= 0; i--)
    {
        body_sections[i + count] = body_sections[i];
    }

    for(int i = 0; i < count; i++)
    {
        if (player_pos.dx == -1)
        {
            pos.x = player.rect.x + (body_size * (i+1));
            pos.y = player.rect.y;
        }
        if (player_pos.dx == 1)
        {
            pos.x = player.rect.x - (body_size * (i+1));
            pos.y = player.rect.y;
        }
        if (player_pos.dy == -1)
        {
            pos.y = player.rect.y + (body_size * (i+1));
            pos.x = player.rect.x;
        }
        if (player_pos.dy == 1)
        {
            pos.y = player.rect.y - (body_size * (i+1));
            pos.x = player.rect.x;
        }
        body_sections[i].rect = pos;
        body_sections[i].body = body.body;
        body_sections[i].angle = body.angle;
        body_sections[i].dx = player_pos.dx;
        body_sections[i].dy = player_pos.dy;
    }
}

void start_clock(void)
{
    start_t = clock();
}

double get_number_of_seconds(void)
{
    double total_t;

    end_t = clock();

    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    return total_t;
}
