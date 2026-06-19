/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: Royal Game of Ur
 * LICENSE: MIT license
 * DESCRIPTION: Gameplay mechanics
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "headers/board.h"
#include "headers/gameplay.h"

void gameplay(Gameplay* _gameplay)
{
    draw_board(_gameplay);

    while (true)
    {
        printf("Player %d [roll, moveX, help, exit]: ", _gameplay->current_player);

        char user_input[6];
        scanf("%5s", user_input);

        if (strcmp(user_input, "roll") == 0)
        {
            if (_gameplay->dice_rolled == true)
            {
                printf("Dice already rolled! Dice is: %d.\n", _gameplay->dice);
                continue;
            }

            srand(time(NULL));
            _gameplay->dice = rand() % 5;
            _gameplay->dice_rolled = true;

            printf("Dice is set at: %d\n", _gameplay->dice);
        }

        else if (strncmp(user_input, "move", 4) == 0)
        {
            printf("\x1b[H\x1b[J"); // move cursor to the beginning and clear from cursor down
            draw_board(_gameplay);
        }

        else if (strcmp(user_input, "help") == 0)
        {
            printf("--- HELP ---\n");
            printf("roll - roll the dice, only possible to roll once per turn\n");
            printf("moveX - move a piece with index 'X', use letter n to bring a new piece to the board\n");
            printf("help - help with the commands\n");
            printf("exit - stop the game\n");
            printf("GitHub: https://github.com/Andrej123456789/royal_game_of_ur\n");
        }

        else if (strcmp(user_input, "exit") == 0)
        {
            printf("Exiting...");
            break;
        }

        else
        {
            printf("Incorrect command!\n");
        }
    }
}
