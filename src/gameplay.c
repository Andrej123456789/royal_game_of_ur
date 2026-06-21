/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: Royal Game of Ur
 * LICENSE: MIT license
 * DESCRIPTION: Gameplay mechanics
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined _WIN32 || defined _WIN64
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

#include "headers/board.h"
#include "headers/gameplay.h"
#include "headers/server.h"

int next_value_zero(int x, bool finkel)
{
    if (finkel == true)
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

    else
    {
        static const int seq[] = {
            12, 9, 6, 3, 0, 1, 4, 7, 10,
            13, 16, 19, 20, 23, 22, 21,
            18, 15
        };

        const int n = sizeof(seq) / sizeof(seq[0]);

        for (int i = 0; i < n; i++)
        {
            if (seq[i] == x)
            {
                return seq[(i + 1) % n]; // wrap around
            }
        }

        // fallback
        return x;
    }
}

int next_value_one(int x, bool finkel)
{
    if (finkel == true)
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

    else
    {
        static const int seq[] = {
            14, 11, 8, 5, 2, 1, 4, 7, 10,
            13, 16, 19, 18, 21, 22, 23,
            20, 17
        };

        int n = sizeof(seq) / sizeof(seq[0]);

        for (int i = 0; i < n; i++)
        {
            if (seq[i] == x)
            {
                return seq[(i + 1) % n]; // wrap around
            }
        }

        // fallback
        return x;
    }
}

int roll_dice()
{
    int sum = 0;
    for (int i = 0; i < 4; i++)
    {
        sum += rand() & 1;
    }

    return sum;
}

int make_move(Gameplay* _gameplay, int id, Piece* p)
{
    if (p->position == 15 || p->position == 17)
    {
        return -1;
    }

    int old_pos = p->position;
    int new_pos = -1;

    for (int i = 0; i < _gameplay->dice; i++)
    {
        if (_gameplay->current_player == false)
        {
            new_pos = next_value_zero(p->position, _gameplay->irvin_finkel_ruleset);
        }

        else
        {
            new_pos = next_value_one(p->position, _gameplay->irvin_finkel_ruleset);
        }

        p->position = new_pos;
    }

    // Perform checks to ensure move is valid

    for (int i = 0; i < 7; i++)
    {
        if (i != id && new_pos != 15 && new_pos != 17 && _gameplay->players[_gameplay->current_player].pieces[i].position == new_pos)
        {
            new_pos = -1;
            break;
        }
    }

    for (int i = 0; i < 7; i++)
    {
        if (_gameplay->players[!_gameplay->current_player].pieces[i].position == new_pos)
        {
            // You cannot capture on rosette squares
            if (new_pos == 10 && _gameplay->irvin_finkel_ruleset == true)
            {
                new_pos = -1;
                break;
            }

            _gameplay->players[!_gameplay->current_player].pieces[i].position = (!_gameplay->current_player == 0) ? 12 : 14;
            break;
        }
    }

    if ((_gameplay->current_player == 0 && new_pos < 15 && old_pos > 15) || (_gameplay->current_player == 1 && new_pos < 17 && old_pos > 17))
    {
        new_pos = -1; // you need exact number of steps in order to finish
    }

    p->position = old_pos;
    return new_pos;
}

void computer_player(Gameplay* _gameplay, char* user_input)
{
    if (_gameplay->dice_rolled == false)
    {
        strcpy(user_input, "roll");
        return;
    }

    for (int i = 0; i < 7; i++)
    {
        int new_pos = make_move(_gameplay, i, &_gameplay->players[_gameplay->current_player].pieces[i]);
        if (new_pos != -1)
        {
            snprintf(user_input, 6, "move%d", i);
            return;
        }
    }

    strcpy(user_input, "skip");
    return;
}

void gameplay(Gameplay* _gameplay, Network* _network)
{
    int listener_fd = -1;
    if (_network->enabled == true)
    {
        listener_fd = net_start_server(_network->port, 2);
    }

    /* Wait for all clients to join the game */
    if (_network->enabled == true)
    {
        uint16_t connected_clients = 0;
        while (connected_clients < _network->number_of_players)
        {
            connected_clients = 0; // reset counter so it counts all connected clients correctly
            if (listener_fd >= 0)
            {
                net_accept_clients(listener_fd, _gameplay->players, 2);
                net_poll_clients(_gameplay->players, 2);
            }

            for (uint16_t i = 0; i < 2; i++)
            {
                if (_gameplay->players[i].network.sockfd > 0)
                {
                    connected_clients++;
                }
            }
        }
    }

    printf("Royal Game of Ur");
    if (_network->enabled == true)
    {
        broadcast(_gameplay->players, 2, "Royal Game of Ur");
    }

    if (_gameplay->irvin_finkel_ruleset == true)
    {
        printf(" | Irving Finkel's ruleset\n");
        if (_network->enabled == true)
        {
            broadcast(_gameplay->players, 2, " | Irving Finkel's ruleset\n");
        }
    }

    else
    {
        printf(" | James Masters's ruleset\n");
        if (_network->enabled == true)
        {
            broadcast(_gameplay->players, 2, " | James Masters's ruleset\n");
        }
    }

    draw_board(_gameplay, _network);

    srand(time(NULL));
    if (roll_dice() >= roll_dice())
    {
        _gameplay->current_player = 0;
    }

    else
    {
        _gameplay->current_player = 1;
    }

    printf("Player %d starts first. [0 - left, 1 - right]\n", _gameplay->current_player);
    if (_network->enabled == true)
    {
        broadcast(_gameplay->players, 2, "Player %d starts first. [0 - left, 1 - right]\n", _gameplay->current_player);
    }

    while (true)
    {
        if (listener_fd >= 0) 
        {
            net_accept_clients(listener_fd, _gameplay->players, 2);
            net_poll_clients(_gameplay->players, 2);
        }

        char user_input[6];
        switch (_gameplay->players[_gameplay->current_player].type)
        {
            case 1: // computer player
                computer_player(_gameplay, user_input);
                break;

            case 2: // network player
                if (_network->enabled == true)
                {
                    send_to_player(&_gameplay->players[_gameplay->current_player], "Player %d [roll, moveX, help, skip, exit]: ", _gameplay->current_player);
    
                    const int TIME_LIMIT_SEC = 60;
                    const int POLL_SLEEP_US = 10000; // 10 ms
    
                    time_t deadline = time(NULL) + TIME_LIMIT_SEC;
    
                    /* poll until we get a full line or the timer expires */
                    while (!_gameplay->players[_gameplay->current_player].network.ready && time(NULL) < deadline)
                    {
                        net_poll_clients(_gameplay->players, 2);   /* non‑blocking socket pump  */
    
                        #if defined _WIN32 || defined _WIN64
                            Sleep(POLL_SLEEP_US / 100);    /* nap to save CPU */
                        #else
                            usleep(POLL_SLEEP_US);         /* nap to save CPU */
                        #endif
                    }
    
                    if (_gameplay->players[_gameplay->current_player].network.ready)
                    {
                        strncpy(user_input, _gameplay->players[_gameplay->current_player].network.inbuf, 5);
                        user_input[5] = '\0';
                    }
    
                    else
                    {
                        strcpy(user_input, "time");
                    }
    
                    /* reset buffer */
                    _gameplay->players[_gameplay->current_player].network.inbuf[0] = '\0';
                    _gameplay->players[_gameplay->current_player].network.ready = false;
                }

                break;
            
            default:
                printf("Player %d [roll, moveX, help, skip, exit]: ", _gameplay->current_player);
                scanf("%5s", user_input);

                break;
        }

        if (strcmp(user_input, "roll") == 0)
        {
            if (_gameplay->dice_rolled == true)
            {
                printf("Dice already rolled! Dice is: %d.\n", _gameplay->dice);

                if (_network->enabled == true)
                {
                    send_to_player(&_gameplay->players[_gameplay->current_player], "Dice already rolled! Dice is: %d.\n", _gameplay->dice);
                }

                continue;
            }

            _gameplay->dice = roll_dice();
            _gameplay->dice_rolled = true;

            printf("Dice is set at: %d\n", _gameplay->dice);
            if (_network->enabled == true)
            {
                broadcast(_gameplay->players, 2, "Dice is set at: %d\n", _gameplay->dice);
            }

            if (_gameplay->dice == 0 && _gameplay->irvin_finkel_ruleset == true)
            {
                printf("No moves.\n");
                if (_network->enabled == true)
                {
                    broadcast(_gameplay->players, 2, "No moves.\n");
                }

                _gameplay->current_player = !_gameplay->current_player;
                _gameplay->dice_rolled = false;
            }

            else if (_gameplay->dice == 0 && _gameplay->irvin_finkel_ruleset == false)
            {
                _gameplay->dice = 4;

                printf("Dice is set at: 4\n");
                if (_network->enabled == true)
                {
                    broadcast(_gameplay->players, 2, "Dice is set at: 4\n");
                }
            }
        }

        else if (strncmp(user_input, "move", 4) == 0)
        {
            int id = (int)(user_input[4] - '0');
            if (id < 0 || id > 6)
            {
                printf("Invalid piece ID '%c'!\n", user_input[4]);
                if (_network->enabled == true)
                {
                    send_to_player(&_gameplay->players[_gameplay->current_player], "Invalid piece ID '%c'!\n", user_input[4]);
                }

                continue;
            }

            if (_gameplay->dice_rolled == false)
            {
                printf("First roll a dice!\n");
                if (_network->enabled == true)
                {
                    send_to_player(&_gameplay->players[_gameplay->current_player], "First roll a dice!\n");
                }

                continue;
            }

            Piece* p = &_gameplay->players[_gameplay->current_player].pieces[id];
            int new_pos = make_move(_gameplay, id, p);

            if (new_pos == -1)
            {
                printf("Invalid move!\n");
                if (_network->enabled == true)
                {
                    send_to_player(&_gameplay->players[_gameplay->current_player], "Invalid move!\n");
                }

                continue;
            }

            p->position = new_pos;
            if ((_gameplay->current_player == 0 && new_pos == 15) || (_gameplay->current_player == 1 && new_pos == 17))
            {
                _gameplay->players[_gameplay->current_player].points++;
            }

            printf("\x1b[2J\x1b[H");
            if (_network->enabled == true)
            {
                broadcast(_gameplay->players, 2, "\x1b[2J\x1b[H");
            }

            draw_board(_gameplay, _network);

            if (_gameplay->players[_gameplay->current_player].type != 0)
            {
                printf("Player %d moved piece %d to position %d.\n", _gameplay->current_player, id, new_pos);
                if (_network->enabled == true)
                {
                    broadcast(_gameplay->players, 2, "Player %d moved piece %d to position %d.\n", _gameplay->current_player, id, new_pos);
                }
            }

            if (_gameplay->players[_gameplay->current_player].points == 7)
            {
                printf("Player %d won!\n", _gameplay->current_player);
                if (_network->enabled == true)
                {
                    broadcast(_gameplay->players, 2, "Player %d won!\n", _gameplay->current_player);
                }

                break;
            }

            // Rosette tiles gives an extra roll dice. Double negation will not give turn to the next player
            if (new_pos == 0 || new_pos == 2 || new_pos == 10 || new_pos == 18 || new_pos == 20)
            {
                _gameplay->current_player = !_gameplay->current_player;
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

            if (_network->enabled == true)
            {
                broadcast(_gameplay->players, 2, "--- HELP ---\n");
                broadcast(_gameplay->players, 2, "roll - roll the dice, only possible to roll once per turn\n");
                broadcast(_gameplay->players, 2, "moveX - move a piece with index 'X'\n");
                broadcast(_gameplay->players, 2, "help - help with the commands\n");
                broadcast(_gameplay->players, 2, "skip - skip current turn\n");
                broadcast(_gameplay->players, 2, "exit - stop the game\n");
                broadcast(_gameplay->players, 2, "GitHub: https://github.com/Andrej123456789/royal_game_of_ur\n");
            }
        }

        else if (strcmp(user_input, "skip") == 0)
        {
            printf("Skipping...\n");
            if (_network->enabled == true)
            {
                broadcast(_gameplay->players, 2, "Skipping...\n");
            }

            _gameplay->current_player = !_gameplay->current_player;
            _gameplay->dice_rolled = false;
        }

        else if (strcmp(user_input, "time") == 0)
        {
            printf("Player %d timed out! Skipping...\n", _gameplay->current_player);
            if (_network->enabled == true)
            {
                broadcast(_gameplay->players, 2, "Player %d timed out! Skipping...\n", _gameplay->current_player);
            }

            _gameplay->current_player = !_gameplay->current_player;
            _gameplay->dice_rolled = false;
        }

        else if (strcmp(user_input, "exit") == 0)
        {
            printf("Exiting...");
            if (_network->enabled == true)
            {
                broadcast(_gameplay->players, 2, "Exiting...");
            }

            break;
        }

        else
        {
            printf("Incorrect command!\n");
            if (_network->enabled == true)
            {
                send_to_player(&_gameplay->players[_gameplay->current_player], "Incorrect command!\n");
            }
        }
    }
}
