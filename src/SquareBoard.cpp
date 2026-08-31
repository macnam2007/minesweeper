#include "SquareBoard.hpp"

SquareBoard::SquareBoard(int width, int height, int number) : wBoard(width),hBoard(height), numberBomb(number), isGameOver(false), isFirstClick(true), numberRevealed(0)
{
    this->Board.assign(width*height, Cell());
}

Cell& SquareBoard::GetCell(int x, int y)
{
    return this->Board[this->wBoard*y + x];
}

void SquareBoard::GenerateMines(int firstX, int firstY)
{
    int count = 0;
    int xBomb,yBomb;
    while (count < this->numberBomb)
    {
        xBomb = rand() % this->wBoard;
        yBomb = rand() % this->hBoard;
        if (xBomb == firstX && yBomb == firstY)
            continue;
        if (GetCell(xBomb,yBomb).CheckMine())
            continue;
        GetCell(xBomb,yBomb).PlaceMine();
        count++;
    }
}

void SquareBoard::GiveAdjacentMinesCount()
{
    for (int xBomb=0; xBomb < this->wBoard; xBomb++)
    {
        for (int yBomb=0; yBomb < this->hBoard; yBomb++)
        {
            if (GetCell(xBomb,yBomb).CheckMine())
            {
                if (yBomb-1 >= 0)
                {
                    if (xBomb-1 >= 0)
                        GetCell(xBomb-1,yBomb-1).IncreaseAdjacentMinesCount();
                    if (xBomb+1 < this->wBoard) 
                        GetCell(xBomb+1,yBomb-1).IncreaseAdjacentMinesCount();
                    GetCell(xBomb,yBomb-1).IncreaseAdjacentMinesCount();
                }

                if (yBomb+1 < this->hBoard)
                {
                    if (xBomb-1 >= 0)
                        GetCell(xBomb-1,yBomb+1).IncreaseAdjacentMinesCount();
                    if (xBomb+1 < this->wBoard) 
                        GetCell(xBomb+1,yBomb+1).IncreaseAdjacentMinesCount();
                    GetCell(xBomb,yBomb+1).IncreaseAdjacentMinesCount();
                }

                if (xBomb-1 >= 0)
                    GetCell(xBomb-1,yBomb).IncreaseAdjacentMinesCount();
                if (xBomb+1 < this->wBoard) 
                    GetCell(xBomb+1,yBomb).IncreaseAdjacentMinesCount();
                GetCell(xBomb,yBomb).IncreaseAdjacentMinesCount();
            }
        }
    }
}

bool SquareBoard::RevealCell(int x, int y)
{
    Cell& currentCell = GetCell(x,y);
    if (currentCell.isFlagged || currentCell.isRevealed)
        return true;
    if (this->isFirstClick)
    {
        this->isFirstClick = false;
        GenerateMines(x,y);
        GiveAdjacentMinesCount();
    }

    if (currentCell.CheckMine())
        return false;
    currentCell.Reveal();
    this->numberRevealed++;
    RevealAdjacentCells(x,y);
    return true;
}

void SquareBoard::RevealAdjacentCells(int x, int y)
{
    std::queue<std::pair<int,int>> Save;
    if (GetCell(x,y).GetAdjacentMinesCount() > 0)
        return;
    Save.push({x,y});
    while(!Save.empty())
    {
        int currentX = Save.front().first;
        int currentY = Save.front().second;
        Save.pop();

        for (int xCell = currentX-1 ; xCell <= currentX+1; xCell++)
        {
            for (int yCell = currentY-1; yCell <= currentY+1; yCell++)
            {
                if (xCell == currentX && yCell == currentY)
                    continue;
                if (xCell<0 || yCell<0 || xCell>=this->wBoard || yCell>=this->hBoard)
                    continue;

                Cell& currentCell = GetCell(xCell,yCell);
                if (currentCell.isRevealed || currentCell.isFlagged)
                    continue;

                currentCell.Reveal();
                this->numberRevealed++;
                if (currentCell.GetAdjacentMinesCount() == 0)
                    Save.push({xCell, yCell});
            }
        }
    }
}

void SquareBoard::FlagCell(int x, int y)
{
    GetCell(x,y).ToggleFlag();
}

bool SquareBoard::CheckWin()
{
    if (this->numberRevealed + this->numberBomb == this->wBoard * this->hBoard)
        return true;
    return false;
}

void SquareBoard::PrintBoard()
{
    for (int y = 0; y < this->hBoard; y++)
    {
        for (int x = 0; x < this->wBoard; x++)
        {
            Cell& currentCell = GetCell(x,y);
            if (!currentCell.isRevealed)
            {
                std::cout<<" [~] ";
                continue;
            }
            if (currentCell.GetAdjacentMinesCount() == 0)
                std::cout<<" [ ] ";
            else std::cout<<" ["<<currentCell.GetAdjacentMinesCount()<<"] ";
        }
        std::cout<<std::endl;
    }
}