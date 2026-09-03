#pragma once

class Cell
{
    friend class SquareBoard;
    private:
        bool isMine;
        bool isRevealed;
        bool isFlagged;
        int adjacentMinesCount;
    public:
        Cell();
        void Reveal();
        void ToggleFlag();
        bool CheckMine();
        void PlaceMine();
        int GetAdjacentMinesCount();
        void IncreaseAdjacentMinesCount();
};