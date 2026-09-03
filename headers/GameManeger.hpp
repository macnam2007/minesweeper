#pragma once
#include "GameState.hpp"
#include "Button.hpp"
#include "SquareBoard.hpp"
#include "Text.hpp"
#include <cassert> // in ra lỗi

class GameManeger
{
    private:
        sf::Font font;
        unsigned int wScreen , hScreen;
        GameState state;
        sf::Clock gameClock;
        int flagsPlaced;
        int minesCount;
        SquareBoard Map;

    private:
        std::vector<Button> menuButtons;    //Start, Settings, Exit
        std::vector<Button> levelButtons;   //Easy, Medium, Hard, Back
        std::vector<Button> gameOverButtons;//Play Again, Main Menu

        std::vector<Text> menuTexts;
        std::vector<Text> levelTexts;
        std::vector<Text> gameOverTexts;

    public:
        GameManeger();
        void Run();
        void UI(sf::RenderWindow& window);
        void HandleInput(sf::RenderWindow& window);
        void ChangeState();

        void SaveGame();
        void LoadGame();

        void SaveSetting();
        void LoadSetting();

        void SaveHighScore();
        void LoadHighScore();
};