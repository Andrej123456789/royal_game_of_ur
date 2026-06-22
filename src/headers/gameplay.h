/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: Royal Game of Ur
 * LICENSE: MIT license
 * DESCRIPTION: Gameplay mechanics
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define BUFFER_LIMIT 255

/**
 * Struct containing network informations
 * @param enabled is multiplayer enabled
 * @param port server's port number
 * @param number_of_players number of network players
 */
typedef struct Network
{
    bool enabled;
    uint16_t port;
    int number_of_players;
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
 * @param type type of player: 0 - local player, 1 - computer player, 2 - network player
 */
typedef struct Player
{
    Piece pieces[7];
    int points;
    int type;

    /**
     * Struct related to the network profile of a player.
     * @param sockfd socket number, <= 0 is free slot
     * @param inbuf player's input
     * @param ready did player send an input
     */
    struct
    {
        int sockfd;
        char inbuf[BUFFER_LIMIT];
        bool ready;
    } network;
} Player;

/**
 * Struct containing gameplay informations
 * @param current_player id of current player (0 or 1)
 * @param dice current dice number
 * @param dice_rolled has dice been rolled
 * @param irvin_finkel_ruleset is game played by Irvin Finkel's rules or
 * by James Masters's rules
 * @param players array containing all of the players
 */
typedef struct Gameplay
{
    bool current_player;
    int dice;
    bool dice_rolled;
    bool irvin_finkel_ruleset;
    Player players[2];
} Gameplay;

/**
 * Move a piece of player 0
 * @param pos current position
 * @param finkel true if Finkel's rules are used, false if Masters's rules are used
 * @return int
 */
int next_value_zero(int pos, bool finkel);

/**
 * Move a piece of player 1
 * @param pos current position
 * @param finkel true if Finkel's rules are used, false if Masters's rules are used
 * @return int
 */
int next_value_one(int pos, bool finkel);

/**
 * 4-binary-dice emulation
 * @return int
 */
int roll_dice();

/**
 * Check if moving a selected piece is possible
 * @param _gameplay `Gameplay` struct
 * @param id id of current piece
 * @param p `Piece` struct
 * @return int
 */
int make_move(Gameplay* _gameplay, int id, Piece* p);

/**
 * Computer's play
 * @param _gameplay `Gameplay` struct
 * @param user_input array where computer will save its selection
 * @return void
 */
void computer_player(Gameplay* _gameplay, char* user_input);

/**
 * Gameplay mechanics
 * @param _gameplay `Gameplay` struct
 * @param _network `Network` struct
 * @return void
 */
void gameplay(Gameplay* _gameplay, Network* _network);
