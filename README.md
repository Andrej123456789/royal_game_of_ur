# Royal Game of Ur

[Royal Game of Ur](https://en.wikipedia.org/wiki/Royal_Game_of_Ur) is a two-player board game that originated in ancient Mesopotamia.

Players race pieces along a path using dice rolls to reach the end first.

This implementation is multiplayer and runs in terminal. It is written in C programming language.

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

| Number: | Step:                                                             | Command:                                                        |
| ------- | ----------------------------------------------------------------- | --------------------------------------------------------------- |
| 1       | Clone a repository                                                | `git clone https://github.com/Andrej123456789/royal_game_of_ur` |
| 2       | Enter the `src` directory                                         | `cd royal_game_of_ur/src`                                       |
| 3       | Create `build` directory                                          | `mkdir build`                                                   |
| 4       | Run CMake                                                         | `cmake .. -DVCPKG_ROOT="path_to_vcpkg`                          |
| 5       | Enter `Developer Command Prompt` and enter the `client` directory | `cd path_to_client_directory`                                   |
| 6       | Compile and run the client                                        | `cl client_windows.c && ./client_windows <ip> <port>`           |

**Notice! In order not to use Visual Studio (you still need to have it installed), you can use nmake. Run Cmake with following command: `cmake -G "NMake Makefiles" -DCMAKE_C_COMPILER=compiler-cl -DCMAKE_CXX_COMPILER=compiler-cl -DVCPKG_ROOT="path_to_vcpkg" ..`. To compile the project use command `nmake`.**

### Linux

| Number: | Step:                        | Command:                                                           |
| ------- | ---------------------------- | ------------------------------------------------------------------ |
| 1       | Clone a repository           | `git clone https://github.com/Andrej123456789/royal_game_of_ur`    |
| 2       | Enter the `src` directory    | `cd royal_game_of_ur/src`                                          |
| 3       | Compile                      | `make`                                                             |
| 4       | Run the program              | `make run`                                                         |
| 5       | Enter the `client` directory | `cd ../client`                                                     |
| 6       | Compile and run the client   | `gcc client_posix.c -o client_posix && ./client_posix <ip> <port>` |
