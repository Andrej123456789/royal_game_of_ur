/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: Royal Game of Ur
 * LICENSE: MIT license
 * DESCRIPTION: Board UI
 */

#pragma once

struct Gameplay;
struct Network;

#define WIDTH 17
#define WIDTH_PIECE 19
#define HEIGHT 5

/**
 * Draws the game board
 * @param _gameplay `Gameplay` struct
 */
void draw_board(struct Gameplay* _gameplay, struct Network* _network);
