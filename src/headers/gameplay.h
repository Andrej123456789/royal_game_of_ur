/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: Royal Game of Ur
 * LICENSE: MIT license
 * DESCRIPTION: Gameplay mechanics
 */

#pragma once

#include <stdbool.h>

typedef struct Piece
{
    int position;
} Piece;

typedef struct Player
{
    Piece pieces[7];
    int points;
} Player;

typedef struct Gameplay
{
    bool current_player;
    int dice;
    bool dice_rolled;
    Player players[2];
} Gameplay;

void gameplay(Gameplay* _gameplay);
