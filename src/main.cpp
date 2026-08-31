//nix-shell
//g++ -I./headers src/main.cpp src/Cell.cpp src/SquareBoard.cpp -o minesweeper -lsfml-graphics -lsfml-window -lsfml-system
#include "SquareBoard.hpp"

int main()
{
    SquareBoard Table(10,10,9);
    int x, y;
    for (int i = 0; i< 4; i++)
    {
        Table.PrintBoard();
        std::cin>>x;
        std::cin>>y;
        Table.RevealCell(x,y);
    }
    Table.PrintBoard();
    return 0;
}