//nix-shell
//g++ -I./headers main.cpp src/GameManeger.cpp src/Text.cpp src/Button.cpp src/Cell.cpp src/SquareBoard.cpp -o minesweeper -lsfml-graphics -lsfml-window -lsfml-system

#include "GameManeger.hpp"

int main()
{
    // SquareBoard Table(10,10,9);
    // int x, y;
    // for (int i = 0; i< 4; i++)
    // {
    //     Table.PrintBoard();
    //     std::cin>>x;
    //     std::cin>>y;
    //     Table.RevealCell(x,y);
    // }
    // Table.PrintBoard();

    GameManeger GAME;
    GAME.Run();
    return 0;
}