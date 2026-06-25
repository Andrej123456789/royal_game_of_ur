# Royal Game of Ur

[Royal Game of Ur](https://en.wikipedia.org/wiki/Royal_Game_of_Ur) is a two-player board game that originated in ancient Mesopotamia.
Players race pieces along a path using dice rolls to reach the end first.

This is a terminal-based implementation written in C programming language. ANSI-compatible terminal required.
Supports local, computer and network play.

## Rules

### Irving Finkel ruleset

- 2 players, 7 pieces each
- 24-square shared board with branching path
- 4 tetrahedral dice (0–4 per roll)
- pieces enter from start and follow fixed route to exit
- landing on opponent piece on normal square sends it back to start
- rosette squares are safe (cannot be captured) and grant an extra roll
- pieces must fully traverse the board and exit via an exact roll
- first to bear off all 7 pieces wins

### James Masters ruleset

- 2 players, 7 pieces each
- 24-square shared board with branching path
- 3 tetrahedral dice (0–4 per roll), rolling a total of 0 allows a special move of exactly 4 squares
- pieces enter from start and follow fixed route to exit
- landing on an opponent's piece anywhere (including rosettes) sends it back to the start
- rosette squares are evenly spaced (every 4th square) and not safe (can be captured), but still grant an extra roll
- pieces must fully traverse the board and exit via an exact roll
- first to bear off all 7 pieces wins

## Compile

## Installing dependencies

### Windows

- Git
- Visual Studio with C/C++ development extension
- CMake
- json-c (x64 static version from vcpkg)

### Linux

| Package: | Command:                                                                                                                           |
| -------- | ---------------------------------------------------------------------------------------------------------------------------------- |
| git      | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install git`</td><td>`pacman -S git`</td></tr></table>              |
| make     | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install make`</td><td>`pacman -S make`</td></tr></table>            |
| gcc      | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install gcc`</td><td>`pacman -S gcc`</td></tr></table>              |
| json-c   | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install libjson-c-dev`</td><td>`pacman -S json-c`</td></tr></table> |

## Compiling & running

### Windows

| Number: | Step:                                                             | Command:                                                           |
| ------- | ----------------------------------------------------------------- | ------------------------------------------------------------------ |
| 1       | Clone a repository                                                | `git clone https://github.com/Andrej123456789/royal_game_of_ur`    |
| 2       | Enter the `src` directory                                         | `cd royal_game_of_ur\src`                                          |
| 3       | Create the `build` directory and enter it                         | `mkdir build && cd build`                                          |
| 4       | Run CMake                                                         | `cmake .. -DVCPKG_ROOT="path_to_vcpkg"`                            |
| 5       | Open Visual Studio and build the solution                         |                                                                    |
| 6       | Run the program located inside the `Debug` or `Release` folder    | `.\Debug\royal_game_of_ur.exe` or `.\Release\royal_game_of_ur.exe` |
| 7       | Enter `Developer Command Prompt` and enter the `client` directory | `cd path_to_client_directory`                                      |
| 8       | Compile and run the client                                        | `cl client_windows.c && .\client_windows <ip> <port>`              |

**Notice! In order not to use Visual Studio (you still need to have it installed), you can use nmake. Run CMake with following command: `cmake -G "NMake Makefiles" -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl -DVCPKG_ROOT="path_to_vcpkg" ..`. To compile the project use command `nmake`. You need to be inside _Developer Command Prompt_ or _Developer Powershell_.**

### Linux

| Number: | Step:                        | Command:                                                           |
| ------- | ---------------------------- | ------------------------------------------------------------------ |
| 1       | Clone a repository           | `git clone https://github.com/Andrej123456789/royal_game_of_ur`    |
| 2       | Enter the `src` directory    | `cd royal_game_of_ur/src`                                          |
| 3       | Compile                      | `make`                                                             |
| 4       | Run the program              | `make run`                                                         |
| 5       | Enter the `client` directory | `cd ../client`                                                     |
| 6       | Compile and run the client   | `gcc client_posix.c -o client_posix && ./client_posix <ip> <port>` |

## settings.json

```json
{
  "irvin_finkel_ruleset": true, // if true game uses Irvin Finkel's ruleset,
  // if false game uses James Masters's ruleset

  "players": [
    {
      // 0 - local player, 1 - computer player, 2 - network player
      "player0": 0,
      "player1": 0
    }
  ],

  "network": [
    {
      "enabled": false, // multiplayer enabled or not
      "port": 5555 // server's port
    }
  ]
}
```
