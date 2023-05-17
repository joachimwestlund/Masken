#include "game_logic.h"

void play(void)
{
    if (is_playing != TRUE)
        //change_music(5);
    is_playing = TRUE;
    player_pos.dy = -1;
    player_pos.dx = 0;
    head_direction_changed = FALSE;
    head_direction_changed_completed = TRUE;
    move_point_index = 0;
}

void handle_input(void)
{
    if (is_playing)
    {
        if (input.DOWN == TRUE)
        {
            player_pos.prev_dx = player_pos.dx;
            player_pos.prev_dy = player_pos.dy;
            player_pos.dy = 1;
            player_pos.dx = 0;
            head_direction_changed = TRUE;
            if (player.no_body_sections > 0)
            {
                move_points[move_point_index].rect = player.rect;
                move_points[move_point_index].dx = player_pos.dx;
                move_points[move_point_index].dy = player_pos.dy;
                move_point_index++;
            }
        }
        if (input.UP == TRUE)
        {
            player_pos.prev_dx = player_pos.dx;
            player_pos.prev_dy = player_pos.dy;
            player_pos.dy = -1;
            player_pos.dx = 0;
            head_direction_changed = TRUE;
            if (player.no_body_sections > 0)
            {
                move_points[move_point_index].rect = player.rect;
                move_points[move_point_index].dx = player_pos.dx;
                move_points[move_point_index].dy = player_pos.dy;
                move_point_index++;
            }
        }
        if (input.LEFT == TRUE)
        {
            player_pos.prev_dx = player_pos.dx;
            player_pos.prev_dy = player_pos.dy;
            player_pos.dx = -1;
            player_pos.dy = 0;
            head_direction_changed_completed = FALSE;
            if (player.no_body_sections > 0)
            {
                move_points[move_point_index].rect = player.rect;
                move_points[move_point_index].dx = player_pos.dx;
                move_points[move_point_index].dy = player_pos.dy;
                move_point_index++;
            }
        }
        if (input.RIGHT == TRUE)
        {
            player_pos.prev_dx = player_pos.dx;
            player_pos.prev_dy = player_pos.dy;
            player_pos.dx = 1;
            player_pos.dy = 0;
            head_direction_changed = TRUE;
            if (player.no_body_sections > 0)
            {
                move_points[move_point_index].rect = player.rect;
                move_points[move_point_index].dx = player_pos.dx;
                move_points[move_point_index].dy = player_pos.dy;
                move_point_index++;
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
    printf("%d\n", move_point_index);
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

    for (int i = 0; i < player.no_body_sections; i++)
    {
        collision = SDL_HasIntersection(&player.rect, &body_sections[i].rect);
        if (collision == SDL_TRUE)
        {
            printf("collision with body.\n");
        }
    }
}

void add_body_parts(void)
{
    int sections_before = player.no_body_sections;
    int body_size = 16;

    player.no_body_sections += food.score;
    if (player.no_body_sections >= max_number_of_body_objects)
        player.no_body_sections = max_number_of_body_objects;

    SDL_Rect pos;
    pos.h = body.rect.h;
    pos.w = body.rect.w;

    if (player_pos.dx == -1)
        player.rect.x = player.rect.x - (body_size * food.score);
    if (player_pos.dx == 1)
        player.rect.x = player.rect.x + (body_size * food.score);
    if (player_pos.dy == -1)
        player.rect.y = player.rect.y - (body_size * food.score);
    if (player_pos.dy == 1)
        player.rect.y = player.rect.y + (body_size * food.score);

    for(int i = 0; i < food.score; i++)
    {
        if ((sections_before + i) <= max_number_of_body_objects)
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
            body_sections[sections_before + i].rect = pos;
            body_sections[sections_before + i].body = body.body;
            body_sections[sections_before + i].angle = body.angle;
            body_sections[sections_before + i].dx = player_pos.dx;
            body_sections[sections_before + i].dy = player_pos.dy;
            body_sections[sections_before + i].prev_dx = player_pos.dx;
            body_sections[sections_before + i].prev_dy = player_pos.dy;
            body_sections[sections_before + i].segment_has_reached_last_pos = TRUE;
            body_sections[sections_before + i].should_change_dir = FALSE;
        }
    }
}
