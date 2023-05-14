#include "game_logic.h"

void play(void)
{
    is_playing = TRUE;
    //change_music(5);
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
            printf("dx: %d, dy:%d\n", player_pos.dx, player_pos.dy);
        #endif // DEBUG
    }
}

void move_player(void)
{
    if (player_pos.dx == -1)
    {
        player.x--;
        if (player.x <= 16)
            player.x = 16;
    }
    else if (player_pos.dx == 1)
    {
        player.x++;
        if (player.x >= 768)
            player.x = 768;
    }
    else if (player_pos.dy == -1)
    {
        player.y--;
        if (player.y <= 101)
            player.y = 101;
    }
    else if (player_pos.dy == 1)
    {
        player.y++;
        if (player.y >= 568)
            player.y = 568;
    }
}
