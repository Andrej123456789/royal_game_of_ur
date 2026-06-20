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

int next_value_zero(int x)
{
    // special transitions
    if (x == 0) return 1;
    if (x == 22) return 21;

    // increasing phase: 1, 4, 7, ...
    if (x >= 1 && (x - 1) % 3 == 0)
    {
        return x + 3;
    }

    // decreasing phase: multiples of 3 (12, 9, 6, 3, 21, 18)
    if (x % 3 == 0)
    {
        return x - 3;
    }

    // fallback (should not happen for valid inputs)
    return x;
}

int next_value_one(int x)
{
    // special transitions
    if (x == 2) return 1;
    if (x == 22) return 23;

    // increasing phase: 1, 4, 7, ...
    if (x >= 1 && (x - 1) % 3 == 0)
    {
        return x + 3;
    }

    // decreasing phase: 14, 11, 8, 5, 2, 23, 20
    if (x % 3 == 2)
    {
        return x - 3;
    }

    // fallback
    return x;
}

void gameplay(Gameplay* _gameplay)
{
    draw_board(_gameplay);

    srand(time(NULL));
    _gameplay->current_player = rand() % 2;

    printf("Player %d starts first. [0 - left, 1 - right]\n", _gameplay->current_player);

    while (true)
    {
        printf("Player %d [roll, moveX, help, skip, exit]: ", _gameplay->current_player);

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

            if (_gameplay->dice == 0)
            {
                printf("No moves.\n");

                _gameplay->current_player = !_gameplay->current_player;
                _gameplay->dice_rolled = false;
            }
        }

        else if (strncmp(user_input, "move", 4) == 0)
        {
            int id = (int)(user_input[4] - '0');
            if (id < 0 || id > 6)
            {
                printf("Invalid piece ID '%c'!\n", user_input[4]);
                continue;
            }

            if (_gameplay->dice_rolled == false)
            {
                printf("First roll a dice!\n");
                continue;
            }

            Piece* p = &_gameplay->players[_gameplay->current_player].pieces[id];
            if (p->position == 15 || p->position == 17)
            {
                printf("Invalid move!\n");
                continue;
            }

            int old_pos = p->position;
            int new_pos = -1;

            for (int i = 0; i < _gameplay->dice; i++)
            {
                if (_gameplay->current_player == false)
                {
                    new_pos = next_value_zero(p->position);
                }

                else
                {
                    new_pos = next_value_one(p->position);
                }

                p->position = new_pos;
            }

            // Perform checks to ensure move is valid
            bool invalid = false;

            for (int i = 0; i < 7; i++)
            {
                if (i != id && _gameplay->players[_gameplay->current_player].pieces[i].position == new_pos)
                {
                    invalid = true;
                    break;
                }
            }

            for (int i = 0; i < 7; i++)
            {
                if (_gameplay->players[!_gameplay->current_player].pieces[i].position == new_pos)
                {
                    // You cannot capture on rosette squares
                    if (new_pos == 10)
                    {
                        invalid = true;
                        break;
                    }

                    _gameplay->players[!_gameplay->current_player].pieces[i].position = (!_gameplay->current_player == 0) ? 12 : 14;
                    break;
                }
            }

            if ((_gameplay->current_player == 0 && new_pos < 15 && old_pos > 15) || (_gameplay->current_player == 1 && new_pos < 17 && old_pos > 17))
            {
                invalid = true; // you need exact number of steps in order to finish
            }

            if (invalid == true)
            {
                printf("Invalid move!\n");
                p->position = old_pos;

                continue;
            }

            p->position = new_pos;

            printf("\x1b[2J\x1b[H");
            draw_board(_gameplay);

            if ((_gameplay->current_player == 0 && new_pos == 15) || (_gameplay->current_player == 1 && new_pos == 17))
            {
                _gameplay->players[_gameplay->current_player].points++;

                if (_gameplay->players[_gameplay->current_player].points == 7)
                {
                    printf("Player %d won!\n", _gameplay->current_player);
                    break;
                }
            }

            _gameplay->current_player = !_gameplay->current_player;
            _gameplay->dice_rolled = false;
        }

        else if (strcmp(user_input, "help") == 0)
        {
            printf("--- HELP ---\n");
            printf("roll - roll the dice, only possible to roll once per turn\n");
            printf("moveX - move a piece with index 'X'\n");
            printf("help - help with the commands\n");
            printf("skip - skip current turn\n");
            printf("exit - stop the game\n");
            printf("GitHub: https://github.com/Andrej123456789/royal_game_of_ur\n");
        }

        else if (strcmp(user_input, "skip") == 0)
        {
            _gameplay->current_player = !_gameplay->current_player;
            _gameplay->dice_rolled = false;
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
