/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: Royal Game of Ur
 * LICENSE: MIT license
 * DESCRIPTION: Server code
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

struct Player;

#define BUFFER_LIMIT 255

#ifdef _WIN32
    #include <winsock2.h>
    typedef SOCKET socket_t;
#else
    typedef int socket_t;
#endif

/**
 * Starts a server
 * @param port port number
 * @param max_players maximum number of players server can receive
 * @return int
 */
int net_start_server(uint16_t port, uint16_t number_of_players);

/**
 * Accepts a client's connection to the server
 * @param listener_fd file descriptor
 * @param g `Gameplay` struct
 * @return void
 */
void net_accept_clients(socket_t listener_fd, Player* players, int number_of_players);

/**
 * Polls input from clients
 * @param g `Gameplay` struct
 * @return void
 */
void net_poll_clients(Player* players, int number_of_players);

/**
 * Sends a message to one player
 * @param p player
 * @param fmt message
 * @return void
 */
void send_to_player(Player* p, const char* fmt, ...);

/**
 * Sends a message to all players
 * @param g `Gameplay` struct
 * @param fmt message
 * @param void
 */
void broadcast(Player* players, int number_of_players, const char* fmt, ...);
