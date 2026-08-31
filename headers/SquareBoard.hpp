#include <vector>
#include <queue>
#include <iostream>
#include "Cell.hpp"

class SquareBoard
{
    private:
        int wBoard;
        int hBoard;
        int numberBomb;
        int numberRevealed;
        bool isGameOver;
        bool isFirstClick;
        std::vector<Cell> Board;
    public:
        SquareBoard(int, int, int);
        Cell& GetCell(int x, int y);
        void GenerateMines(int firstX, int firstY);
        void GiveAdjacentMinesCount();
        bool RevealCell(int x, int y);
        void RevealAdjacentCells(int x, int y);
        void FlagCell(int x, int y);
        bool CheckWin();
        void PrintBoard();
};