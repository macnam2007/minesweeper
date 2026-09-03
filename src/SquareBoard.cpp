#include "SquareBoard.hpp"

SquareBoard::SquareBoard(sf::Font& font) : number(font)
{}

void SquareBoard::Create(int width, int height, int number, float wScreen, float hScreen)
{
    this->wBoard = width;
    this->hBoard = height;
    this->numberBomb = number;
    this->isGameOver = false;
    this->isFirstClick = true;
    this->numberRevealed = 0;

    this->Board.assign(width*height, Cell());
    this->widthCell = (hScreen-120)/height;
    this->xStartPaint = (wScreen-width*this->widthCell)/2;
    this->yStartPaint = 60;

    this->cellUp.setSize(sf::Vector2f(this->widthCell,this->widthCell));
    this->cellUp.setFillColor(sf::Color::Blue);
    this->cellUp.setOutlineColor(sf::Color::Black);
    this->cellUp.setOutlineThickness(3.0f);

    this->cellDown.setSize(sf::Vector2f(this->widthCell,this->widthCell));
    this->cellDown.setFillColor(sf::Color(200,200,200));
    this->cellDown.setOutlineColor(sf::Color(220,220,220));
    this->cellDown.setOutlineThickness(3.0f);

    this->flag.setRadius(this->widthCell/2);
    this->flag.setFillColor(sf::Color::Red);

    this->number.setCharacterSize(40);
    
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

void SquareBoard::PrintBoard() // in ra màn hình terminal
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
            else if (currentCell.GetAdjacentMinesCount() == 0)
                std::cout<<" [ ] ";
            else std::cout<<" ["<<currentCell.GetAdjacentMinesCount()<<"] ";
        }
        std::cout<<std::endl;
    }
}

void SquareBoard::ShowBoard(sf::RenderWindow& window)
{
    for (int y=0; y< this->hBoard; y++)
    {
        for (int x=0 ; x< this->wBoard; x++)
        {
            this->cellDown.setPosition({this->xStartPaint + x*this->widthCell, this->yStartPaint + y*this->widthCell});
            window.draw(this->cellDown);

            Cell& currentCell = GetCell(x,y);
            if (!currentCell.isRevealed)
            {
                this->cellUp.setPosition({this->xStartPaint + x*this->widthCell, this->yStartPaint + y*this->widthCell});
                window.draw(this->cellUp);
                if (currentCell.isFlagged)
                {
                    this->flag.setPosition({this->xStartPaint + x*this->widthCell, this->yStartPaint + y*this->widthCell});
                    window.draw(this->flag);
                }
            }
            else if (currentCell.GetAdjacentMinesCount() > 0)
            {
                this->number.setString(std::to_string(currentCell.GetAdjacentMinesCount()));
                sf::FloatRect bounds = this->number.getLocalBounds();
                this->number.setOrigin(
                    {
                        bounds.position.x + bounds.size.x/2.0f,
                        bounds.position.y + bounds.size.y/2.0f
                    }
                );
                this->number.setPosition({float(this->xStartPaint + (x+0.5f)*this->widthCell) , float(this->yStartPaint + (y+0.5f)*this->widthCell)});
                window.draw(this->number);
            }
        }
    }
}

void SquareBoard::InteractCell(sf::RenderWindow& window, GameState& state)
{
    if (CheckWin())
        state = GameState::Win;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);
        int xMouse = (mouseWorldPos.x-this->xStartPaint)/this->widthCell;
        int yMouse = (mouseWorldPos.y-this->yStartPaint)/this->widthCell;
        
        if (xMouse<0 || xMouse>=this->wBoard || yMouse<0 || yMouse>=this->hBoard) return;
        Cell& currentCell =GetCell(xMouse,yMouse);
        if (!currentCell.isRevealed && !currentCell.isFlagged)
        {
            bool checkLose = !RevealCell(xMouse,yMouse);
            if (checkLose) state = GameState::GameOver;
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    {
        sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);
        int xMouse = (mouseWorldPos.x-this->xStartPaint)/this->widthCell;
        int yMouse = (mouseWorldPos.y-this->yStartPaint)/this->widthCell;

        if (xMouse<0 || xMouse>=this->wBoard || yMouse<0 || yMouse>=this->hBoard) return;
        Cell& currentCell =GetCell(xMouse,yMouse);
        if (!currentCell.isRevealed)
        {
            currentCell.ToggleFlag();
        }
    }
}
