#include "Cell.hpp"

Cell::Cell() : isMine(false), isFlagged(false), isRevealed(false), adjacentMinesCount(0)
{
}

void Cell::Reveal()
{
    this->isRevealed = true;
}

void Cell::ToggleFlag()
{
    if (this->isRevealed == false)
        this->isFlagged = !(this->isFlagged);
}

bool Cell::CheckMine()
{
    return isMine;
}

void Cell::PlaceMine()
{
    this->isMine = true;
}

int Cell::GetAdjacentMinesCount()
{
    return this->adjacentMinesCount;
}

void Cell::IncreaseAdjacentMinesCount()
{
    this->adjacentMinesCount += 1;
}