/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: Royal Game of Ur
 * LICENSE: MIT license
 * DESCRIPTION: Program's entry point
 */

#include <stdio.h>
#include <stdlib.h>

#include "headers/gameplay.h"

#ifdef _WIN32
#include <windows.h>
    void enableANSI()
    {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE) return;

        DWORD mode;
        if (!GetConsoleMode(hOut, &mode)) return;

        SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
#else
    void enableANSI() {}
#endif

/**
 * Entry point
 */
int main()
{
    enableANSI();
    printf("Royal Game of Ur\n");
    
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
    free(_gameplay);

    return 0;
}
