#include "game_logic.h"

void play(void)
{
    if (is_playing != TRUE)
        change_music(5);
    is_playing = TRUE;
}

void handle_input(void)
{
    if (is_playing)
    {
        if (input.DOWN == TRUE)
        {
            player_pos.dy = 1;
            player_pos.dx = 0;
        }
        if (input.UP == TRUE)
        {
            player_pos.dy = -1;
            player_pos.dx = 0;
        }
        if (input.LEFT == TRUE)
        {
            player_pos.dx = -1;
            player_pos.dy = 0;
        }
        if (input.RIGHT == TRUE)
        {
            player_pos.dx = 1;
            player_pos.dy = 0;
        }
        #ifdef DEBUG
            //printf("dx: %d, dy:%d\n", player_pos.dx, player_pos.dy);
        #endif // DEBUG
    }
}

void move_player(void)
{
    if (player_pos.dx == -1)
    {
        player.rect.x--;
        player.angle = 270;
        if (player.rect.x <= 16)
            player.rect.x = 16;
    }
    else if (player_pos.dx == 1)
    {
        player.rect.x++;
        player.angle = 90;
        if (player.rect.x >= 768)
            player.rect.x = 768;
    }
    else if (player_pos.dy == -1)
    {
        player.rect.y--;
        player.angle = 0;
        if (player.rect.y <= 101)
            player.rect.y = 101;
    }
    else if (player_pos.dy == 1)
    {
        player.rect.y++;
        player.angle = 180;
        if (player.rect.y >= 568)
            player.rect.y = 568;
    }
}
