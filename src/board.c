/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: Royal Game of Ur
 * LICENSE: MIT license
 * DESCRIPTION: Board UI
 */

#include <stdio.h>
#include "headers/board.h"          
               
static char square[HEIGHT][WIDTH] =
{
    " ---  ---  ---  ",
    "|             | ",
    "|             | ",
    "|             | ",
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

void draw_board()
{
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

                    continue;
                }

                printf("%s", square[j]);
                printf("   ");
            }

            printf("\n");
        }
    }
}
