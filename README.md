# Royal Game of Ur

[Royal Game of Ur](https://en.wikipedia.org/wiki/Royal_Game_of_Ur) is a two-player board game that originated in ancient Mesopotamia.

Players race pieces along a path using dice rolls to reach the end first.

This implementation is multiplayer and runs in terminal. It is written in C programming language.

## Compile

### Installing dependencies

| Package: | Command:                                                                                                                           |
| -------- | ---------------------------------------------------------------------------------------------------------------------------------- |
| git      | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install git`</td><td>`pacman -S git`</td></tr></table>              |
| make     | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install make`</td><td>`pacman -S make`</td></tr></table>            |
| gcc      | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install gcc`</td><td>`pacman -S gcc`</td></tr></table>              |
| json-c   | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install libjson-c-dev`</td><td>`pacman -S json-c`</td></tr></table> |

**Notice for Windows users! You only need to install CMake and Visual Studio with C/C++ development extension!**

### Compiling & running

| Number: | Step:                        | Command:                                                           |
| ------- | ---------------------------- | ------------------------------------------------------------------ |
| 1       | Clone a repository           | `git clone https://github.com/Andrej123456789/royal_game_of_ur`    |
| 2       | Enter the `src` directory    | `cd royal_game_of_ur/src`                                          |
| 3       | Compile                      | `make`                                                             |
| 4       | Run the program              | `make run`                                                         |
| 5       | Enter the `client` directory | `cd ../client`                                                     |
| 6       | Compile and run the client   | `gcc client_posix.c -o client_posix && ./client_posix <ip> <port>` |

**Notice for Windows users! Install x64 static version of `json-c` from vcpkg and run CMake with the following argument: `-DVCPKG_ROOT="path_to_vcpkg"`.**

**Notice for Windows users! Enter `Developer Command Prompt` and run the following command to compile and run the client: `cl client_windows.c && ./client_windows <ip> <port>`.**
