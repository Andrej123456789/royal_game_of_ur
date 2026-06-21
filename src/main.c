/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: Royal Game of Ur
 * LICENSE: MIT license
 * DESCRIPTION: Program's entry point
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <json-c/json.h>

#include "headers/gameplay.h"

#ifdef _WIN32
    #include <windows.h>

    /**
     * Enable ANSI escape codes
     * Required in classic console hosts
     */
    void enableANSI()
    {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE) return;

        DWORD mode;
        if (!GetConsoleMode(hOut, &mode)) return;

        SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
#else
    /**
     * Enable ANSI escape codes
     * Not required on POSIX based systems
     */
    void enableANSI() {}
#endif

/**
 * Load settings
 * @param _gameplay `Gameplay` struct
 * @param _network `Network` struct
 * @param path path to the `.json` file
 * @return int
 */
int start(Gameplay* _gameplay, Network* _network, char* path)
{
    struct json_object_iterator it;
    struct json_object_iterator itEnd;

    json_object* root = json_object_from_file(path);
    if (root == NULL)
    {
        return 1;
    }

    it = json_object_iter_init_default();
    it = json_object_iter_begin(root);
    itEnd = json_object_iter_end(root);

    while (!json_object_iter_equal(&it, &itEnd))
    {
        const char* key = json_object_iter_peek_name(&it);
        json_object* val = json_object_iter_peek_value(&it);

        if (strcmp(key, "irvin_finkel_ruleset") == 0)
        {
            _gameplay->irvin_finkel_ruleset = json_object_get_boolean(val);
        }

        else if (strcmp(key, "players") == 0)
        {
            struct json_object* players;

            struct json_object_iterator it2;
            struct json_object_iterator itEnd2;

            for (size_t i = 0; i < json_object_array_length(val); i++)
            {
                struct json_object* element = json_object_array_get_idx(val, i);
                players = json_tokener_parse(json_object_get_string(element));
            }

            it2 = json_object_iter_init_default();
            it2 = json_object_iter_begin(players);
            itEnd2 = json_object_iter_end(players);

            while (!json_object_iter_equal(&it2, &itEnd2))
            {
                const char* key2 = json_object_iter_peek_name(&it2);
                json_object* val2 = json_object_iter_peek_value(&it2);

                if (strcmp(key2, "player0") == 0)
                {
                    _gameplay->players[0].type = json_object_get_int(val2);
                }

                else if (strcmp(key2, "player1") == 0)
                {
                    _gameplay->players[1].type = json_object_get_int(val2);
                }

                json_object_iter_next(&it2);
            }

            json_object_put(players);
        }

        else if (strcmp(key, "network") == 0)
        {
            struct json_object* network;

            struct json_object_iterator it2;
            struct json_object_iterator itEnd2;

            for (size_t i = 0; i < json_object_array_length(val); i++)
            {
                struct json_object* element = json_object_array_get_idx(val, i);
                network = json_tokener_parse(json_object_get_string(element));
            }

            it2 = json_object_iter_init_default();
            it2 = json_object_iter_begin(network);
            itEnd2 = json_object_iter_end(network);

            while (!json_object_iter_equal(&it2, &itEnd2))
            {
                const char* key2 = json_object_iter_peek_name(&it2);
                json_object* val2 = json_object_iter_peek_value(&it2);

                if (strcmp(key2, "enabled") == 0)
                {
                    _network->enabled = json_object_get_boolean(val2);
                }

                else if (strcmp(key2, "port") == 0)
                {
                    _network->port = (uint16_t)json_object_get_int(val2);
                }

                json_object_iter_next(&it2);
            }

            json_object_put(network);
        }

        json_object_iter_next(&it);
    }

    json_object_put(root);
    return 0;
}

/**
 * Entry point
 */
int main(int argc, char* argv[])
{
    enableANSI();

    Gameplay* _gameplay = (Gameplay*)malloc(sizeof(Gameplay));
    _gameplay->current_player = false;
    _gameplay->dice = -1;
    _gameplay->dice_rolled = false;
    _gameplay->irvin_finkel_ruleset = true;
    
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            _gameplay->players[i].pieces[j].position = (i == 0) ? 12 : 14;
        }

        _gameplay->players[i].points = 0;
        _gameplay->players[i].type = 0;

        _gameplay->players[i].network.sockfd = -1;
        memset(_gameplay->players[i].network.inbuf, 0, BUFFER_LIMIT);
        _gameplay->players[i].network.ready = false;
    }

    Network* _network = (Network*)malloc(sizeof(Network));
    _network->enabled = false;
    _network->port = 5555;
    _network->number_of_players = 0;

    if (argc < 2)
    {
        printf("No path to the settings file given! ");
        printf("Continuing with default settings.\n");
    }

    else
    {
        if (start(_gameplay, _network, argv[1]) != 0)
        {
            printf("Error has occurred! ");
            printf("Continuing with default settings.\n");
        }
    }

    if ((_gameplay->players[0].type == 2 || _gameplay->players[1].type == 2) && _network->enabled == false)
    {
        printf("Network is not enabled! ");
        printf("Network players are disabled.\n");
    }

    if (_network->enabled == true)
    {
        if (_gameplay->players[0].type == 2) { _network->number_of_players++; }
        if (_gameplay->players[1].type == 2) { _network->number_of_players++; }

        if (_gameplay->players[0].type != 2 && _gameplay->players[1].type != 2)
        {
            printf("No network players found! ");
            printf("Network players are disabled.\n");

            _network->enabled = false;
        }
    }

    gameplay(_gameplay, _network);

    free(_gameplay);
    free(_network);

    return 0;
}
