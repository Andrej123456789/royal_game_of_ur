/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: Royal Game of Ur
 * LICENSE: MIT license
 * DESCRIPTION: Board UI
 */

#include <stdio.h>

#include "headers/board.h"
#include "headers/gameplay.h"
#include "headers/server.h"

static char square[HEIGHT][WIDTH] =
{
    " ---  ---  ---  ",
    "|             | ",
    "|             | ",
    "|             | ",
    " ---  ---  ---  "
};

static char square_rosette[HEIGHT][WIDTH] =
{
    " ---  ---  ---  ",
    "|             | ",
    "|      R      | ",
    "|             | ",
    " ---  ---  ---  "
};

static char square_piece[HEIGHT][WIDTH_PIECE] =
{
    " ---  ---  ---  ",
    "| Player: %-2d  | ",
    "| Piece: %-2d   | ",
    "| Position: %-2d| ",
    " ---  ---  ---  "
};

static char empty_square[HEIGHT][WIDTH] = 
{
    "                ",
    "                ",
    "                ",
    "                ",
    "                "
};

void draw_board(Gameplay* _gameplay, Network* _network)
{
    printf("Player 0: %d - left. Completed: ", 7 - _gameplay->players[0].points);
    if (_network->enabled == true)
    {
        broadcast(_gameplay->players, 2, "Player 0: %d - left. Completed: ", 7 - _gameplay->players[0].points);
    }

    for (int i = 0; i < 7; i++)
    {
        if (_gameplay->players[0].pieces[i].position == 15)
        {
            printf("%d, ", i);
            if (_network->enabled == true)
            {
                broadcast(_gameplay->players, 2, "%d, ", i);
            }
        }
    }

    printf("\n");
    if (_network->enabled == true)
    {
        broadcast(_gameplay->players, 2, "\n");
    }

    printf("Player 1: %d - left. Completed: ", 7 - _gameplay->players[1].points);
    if (_network->enabled == true)
    {
        broadcast(_gameplay->players, 2, "Player 1: %d - left. Completed: ", 7 - _gameplay->players[1].points);
    }

    for (int i = 0; i < 7; i++)
    {
        if (_gameplay->players[1].pieces[i].position == 17)
        {
            printf("%d, ", i);
            if (_network->enabled == true)
            {
                broadcast(_gameplay->players, 2, "%d, ", i);
            }
        }
    }

    printf("\n");
    if (_network->enabled == true)
    {
        broadcast(_gameplay->players, 2, "\n");
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if ((i == 4 || i == 5) && (k == 0 || k == 2))
                {
                    printf("%s", empty_square[j]);
                    printf("   ");

                    if (_network->enabled == true)
                    {
                        broadcast(_gameplay->players, 2, "%s", empty_square[j]);
                        broadcast(_gameplay->players, 2, "   ");
                    }

                    continue;
                }

                int player_flag = -1;
                int piece_flag = -1;

                for (int player = 0; player < 2; player++)
                {
                    for (int piece = 0; piece < 7; piece++)
                    {
                        if (_gameplay->players[player].pieces[piece].position == i * 3 + k)
                        {
                            player_flag = player;
                            piece_flag = piece;

                            player = 2;   // force exit outer loop
                            break;
                        }
                    }
                }

                if (player_flag > -1)
                {
                    switch (j)
                    {
                        case 1:
                            printf(square_piece[j], player_flag);
                            if (_network->enabled == true)
                            {
                                broadcast(_gameplay->players, 2, square_piece[j], player_flag);
                            }

                            break;

                        case 2:
                            printf(square_piece[j], piece_flag);
                            if (_network->enabled == true)
                            {
                                broadcast(_gameplay->players, 2, square_piece[j], piece_flag);
                            }

                            break;

                        case 3:
                            printf(square_piece[j], i * 3 + k);
                            if (_network->enabled == true)
                            {
                                broadcast(_gameplay->players, 2, square_piece[j], i * 3 + k);
                            }

                            break;
                        
                        default:
                            printf("%s", square_piece[j]);
                            if (_network->enabled == true)
                            {
                                broadcast(_gameplay->players, 2, square_piece[j]);
                            }

                            break;
                    }
                }

                else
                {
                    if ((i == 0 && (k == 0 || k == 2)) || (i == 3 && k == 1) || (i == 6 && (k == 0 || k == 2)))
                    {
                        printf("%s", square_rosette[j]);
                        if (_network->enabled == true)
                        {
                            broadcast(_gameplay->players, 2, "%s", square_rosette[j]);
                        }
                    }

                    else
                    {
                        printf("%s", square[j]);
                        if (_network->enabled == true)
                        {
                            broadcast(_gameplay->players, 2, "%s", square[j]);
                        }
                    }
                }

                printf("   ");
                if (_network->enabled == true)
                {
                    broadcast(_gameplay->players, 2, "   ");
                }
            }

            printf("\n");
            if (_network->enabled == true)
            {
                broadcast(_gameplay->players, 2, "\n");
            }
        }
    }
}
