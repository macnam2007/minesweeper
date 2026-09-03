//nix-shell
//g++ -I./headers main.cpp src/GameManeger.cpp src/Text.cpp src/Button.cpp src/Cell.cpp src/SquareBoard.cpp -o minesweeper -lsfml-graphics -lsfml-window -lsfml-system

#include "GameManeger.hpp"
#include <ctime>
#include <cstdlib>

int main()
{
    srand(time(NULL));

    GameManeger GAME;
    GAME.Run();
    return 0;
}