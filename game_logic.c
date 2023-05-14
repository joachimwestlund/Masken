#include "game_logic.h"

void play(void)
{
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
            printf("dx: %d, dy:%d\n", player_pos.dx, player_pos.dy);
        #endif // DEBUG
    }
}
