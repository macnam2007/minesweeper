#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cell.hpp"

class SquareBoard
{
    private:
        int wBoard;
        int hBoard;
        float widthCell;
        float xStartPaint;
        float yStartPaint;
        sf::Text number;
        sf::RectangleShape cellUp;
        sf::RectangleShape cellDown;
        sf::CircleShape flag;
        int numberBomb;
        int numberRevealed;
        bool isGameOver;
        bool isFirstClick;
        std::vector<Cell> Board;
    public:
        SquareBoard(sf::Font&);
        void Create(int, int, int, float, float);
        Cell& GetCell(int x, int y);
        void GenerateMines(int firstX, int firstY);
        void GiveAdjacentMinesCount();
        bool RevealCell(int x, int y);
        void RevealAdjacentCells(int x, int y);
        void FlagCell(int x, int y);
        bool CheckWin();
        void PrintBoard();
        void ShowBoard(sf::RenderWindow& window);
};