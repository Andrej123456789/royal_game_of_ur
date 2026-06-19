/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: Royal Game of Ur
 * LICENSE: MIT license
 * DESCRIPTION: Program's entry point
 */

#include <stdio.h>
#include <stdlib.h>

#include "headers/board.h"
#include "headers/gameplay.h"

/**
 * Entry point
 */
int main()
{
    printf("Royal Game of Ur\n");

    draw_board();

    Gameplay* _gameplay = (Gameplay*)malloc(sizeof(Gameplay));
    _gameplay->current_player = false;
    _gameplay->dice = -1;
    _gameplay->dice_rolled = false;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            _gameplay->players[i].pieces[j].position = -1;
        }
    }

    gameplay(_gameplay);

    return 0;
}
