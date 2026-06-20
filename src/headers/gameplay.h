/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: Royal Game of Ur
 * LICENSE: MIT license
 * DESCRIPTION: Gameplay mechanics
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

/**
 * Struct containing network informations
 * @param enabled is multiplayer enabled
 * @param port server's port number
 */
typedef struct Network
{
    bool enabled;
    uint16_t port;
} Network;

/**
 * Struct containing piece informations
 * @param position position of the piece, squares are numbered sequentially
 * left-to-right, top-to-bottom (row by row), starting at 0.
 */
typedef struct Piece
{
    int position;
} Piece;

/**
 * Struct containing player's informations
 * @param pieces array containing all of the player's pieces
 * @param points how many pieces have completed their turn
 */
typedef struct Player
{
    Piece pieces[7];
    int points;
} Player;

/**
 * Struct containing gameplay informations
 * @param current_player id of current player (0 or 1)
 * @param dice current dice number
 * @param dice_rolled has dice been rolled
 * @param players array containing all of the players
 * @param irvin_finkel_ruleset is game played by Irvin Finkel's rules or
 * by James Masters's rules
 */
typedef struct Gameplay
{
    bool current_player;
    int dice;
    bool dice_rolled;
    Player players[2];
    bool irvin_finkel_ruleset;
} Gameplay;

/**
 * Move piece of player 0
 * @param pos current position
 * @param finkel if true Finkel's rules are used, if false Masters's rules are used
 * @return int
 */
int next_value_zero(int pos, bool finkel);

/**
 * Move piece of player 1
 * @param pos current position
 * @param finkel if true Finkel's rules are used, if false Masters's rules are used
 * @return int
 */
int next_value_one(int pos, bool finkel);

/**
 * Gameplay mechanics
 * @param _gameplay `Gameplay` struct
 */
void gameplay(Gameplay* _gameplay);
