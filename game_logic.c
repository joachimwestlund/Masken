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
}

void handle_input(void)
{
    if (is_playing)
    {
        if (input.DOWN == TRUE)
        {
            if (head_direction_changed_completed == TRUE)
            {
                player_pos.prev_dx = player_pos.dx;
                player_pos.prev_dy = player_pos.dy;
                player_pos.dy = 1;
                player_pos.dx = 0;
                head_direction_changed = TRUE;
                head_direction_changed_completed = FALSE;
                player.delta_pixels = 16;
            }
        }
        if (input.UP == TRUE)
        {
            if (head_direction_changed_completed == TRUE)
            {
                player_pos.prev_dx = player_pos.dx;
                player_pos.prev_dy = player_pos.dy;
                player_pos.dy = -1;
                player_pos.dx = 0;
                head_direction_changed = TRUE;
                head_direction_changed_completed = FALSE;
                player.delta_pixels = 16;
            }
        }
        if (input.LEFT == TRUE)
        {
            if (head_direction_changed_completed == TRUE)
            {
                player_pos.prev_dx = player_pos.dx;
                player_pos.prev_dy = player_pos.dy;
                player_pos.dx = -1;
                player_pos.dy = 0;
                head_direction_changed_completed = FALSE;
                head_direction_changed = TRUE;
                player.delta_pixels = 16;
            }
        }
        if (input.RIGHT == TRUE)
        {
            if (head_direction_changed_completed == TRUE)
            {
                player_pos.prev_dx = player_pos.dx;
                player_pos.prev_dy = player_pos.dy;
                player_pos.dx = 1;
                player_pos.dy = 0;
                head_direction_changed = TRUE;
                head_direction_changed_completed = FALSE;
                player.delta_pixels = 16;
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

    if (player.no_body_sections > 0)
    {
        // the first body section has to follow the head.
        if (head_direction_changed == TRUE)
        {
            body_sections[0].prev_dx = body_sections[0].dx;
            body_sections[0].prev_dy = body_sections[0].dy;
            body_sections[0].dx = player_pos.dx;
            body_sections[0].dy = player_pos.dy;
            body_sections[0].segment_has_reached_last_pos = FALSE;
            body_sections[0].should_change_dir = TRUE;
            body_sections[0].change_pos = player.rect;
        }

        for (int i = 1; i < player.no_body_sections; i++)
        {
            // next we set up the rest of the sections
            if (body_sections[i - 1].should_change_dir == TRUE)
            {
                if (body_sections[i - 1].segment_has_reached_last_pos == TRUE)
                {
                    body_sections[i].prev_dx = body_sections[i].dx;
                    body_sections[i].prev_dy = body_sections[i].dy;
                    body_sections[i].dx = body_sections[i - 1].dx;
                    body_sections[i].dy = body_sections[i - 1].dy;
                    body_sections[i].change_pos = body_sections[i - 1].rect;
                    body_sections[i].should_change_dir = TRUE;
                    body_sections[i].segment_has_reached_last_pos = FALSE;
                    body_sections[i - 1].should_change_dir = FALSE;      // reset former segment
                }
            }
        }

        // TODO: might need to check head movement again to check if head moved fast to set item[0] back to should change dir
    }


    // check if direction changed
    // move head 16 pixels more and then allow change to occur.
    if (head_direction_changed == TRUE)
    {
         if (player_pos.prev_dx == -1)
        {
            player.rect.x--;
            if (player.rect.x < 16)
                game_over = TRUE;
        }
        else if (player_pos.prev_dx == 1)
        {
            player.rect.x++;
            if (player.rect.x > 768)
                game_over = TRUE;
        }
        else if (player_pos.prev_dy == -1)
        {
            player.rect.y--;
            if (player.rect.y < 101)
                game_over = TRUE;
        }
        else if (player_pos.prev_dy == 1)
        {
            player.rect.y++;
            if (player.rect.y > 568)
                game_over = TRUE;
        }

        player.delta_pixels--;
        if (player.delta_pixels < 0)
        {
            head_direction_changed = FALSE;
            head_direction_changed_completed = TRUE;
        }
    }
    else
    {
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

    }

    // handle body
    if (player.no_body_sections > 0)
    {
        // now we move stuff for the body
        for (int i = 0; i < player.no_body_sections; i++)
        {
            if (body_sections[i].should_change_dir == TRUE)
            {
                if (body_sections[i].prev_dx == -1)
                {
                    body_sections[i].rect.x--;
                }
                if (body_sections[i].prev_dx == 1)
                {
                    body_sections[i].rect.x++;
                }
                if (body_sections[i].prev_dy == -1)
                {
                    body_sections[i].rect.y--;
                }
                if (body_sections[i].prev_dy == 1)
                {
                    body_sections[i].rect.y++;
                }

                if (SDL_RectEquals(&body_sections[i].rect, &body_sections[i].change_pos) == SDL_TRUE)
                {
                    //body_sections[i - 1].should_change_dir = FALSE;
                    body_sections[i].segment_has_reached_last_pos = TRUE;
                }
            }
            else
            {
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
    }
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
