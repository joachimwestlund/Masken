#include "game_logic.h"

void play(void)
{
    if (is_playing != TRUE)
        //change_music(5);
    is_playing = TRUE;
    player_pos.dy = -1;
    player_pos.dx = 0;
    move_point_index = 0;
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
                game_over = TRUE;
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
                game_over = TRUE;
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
                game_over = TRUE;
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
                game_over = TRUE;
            player_pos.dx = 1;
            player_pos.dy = 0;
            if (player.no_body_sections > 0)
            {
                add_move_point(player.rect, player_pos.dx, player_pos.dy);
            }
        }
        #ifdef DEBUG
            //printf("dx: %d, dy:%d\n", player_pos.dx, player_pos.dy);
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
        if (player.rect.x <= 16)
            player.rect.x = 16;
        player.angle = 270;
    }
    else if (player_pos.dx == 1)
    {
        player.rect.x++;
        if (player.rect.x >= 768)
            player.rect.x = 768;
        player.angle = 90;
    }
    else if (player_pos.dy == -1)
    {
        player.rect.y--;
        if (player.rect.y <= 101)
            player.rect.y = 101;
        player.angle = 0;
    }
    else if (player_pos.dy == 1)
    {
        player.rect.y++;
        if (player.rect.y >= 568)
            player.rect.y = 568;
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
    printf("move point index: %d  body segments: %d\n", move_point_index, player.no_body_sections);
}

void check_and_handle_collisions(void)
{
    SDL_bool collision;

    collision = SDL_HasIntersection(&player.rect, &food.rect);
    if (collision == SDL_TRUE)
    {
        printf("collision with food.\n");
        if (is_adding_body_parts == FALSE)
            add_body_parts();
        is_adding_body_parts = TRUE;
    }

    // check for collision but not for the first body segment behind the head.
    for (int i = 1; i < player.no_body_sections; i++)
    {
        collision = SDL_HasIntersection(&player.rect, &body_sections[i].rect);
        if (collision == SDL_TRUE)
        {
            printf("collision body part: %d. move point index: %d\n", i, move_point_index);
            game_over = TRUE;
        }
    }
}

void add_body_parts(void)
{
    int body_size = 16;
    int count = 0;

    if (player.no_body_sections >= max_number_of_body_objects)
    {
        player.no_body_sections = max_number_of_body_objects;
        return;
    }

    if ((player.no_body_sections + food.score) <= max_number_of_body_objects)
    {
        count = food.score;
    }
    else
    {
        count = max_number_of_body_objects - (player.no_body_sections + food.score);
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
