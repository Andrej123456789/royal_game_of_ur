/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: Royal Game of Ur
 * LICENSE: MIT license
 * DESCRIPTION: Gameplay mechanics
 */

#pragma once

#include <stdbool.h>

typedef struct piece_T
{
    int position;
} Piece;

typedef struct player_T
{
    Piece pieces[7];
} Player;

typedef struct gameplay_T
{
    bool current_player;
    int dice;
    bool dice_rolled;
    Player players[2];
} Gameplay;

void gameplay(Gameplay* _gameplay);
