#include "GameManeger.hpp"

GameManeger::GameManeger() : wScreen(1280), hScreen(720), state(GameState::MainMenu)
{
    assert(this->font.openFromFile("assets/Roboto-Regular.ttf") && "Error: không tải được font chữ !!!\n");


    //          MENU
    //Text
    this->menuTexts.push_back(
        Text("MINESWEEPER",this->font, 40, this->wScreen/2, this->hScreen/5.0f)
    );
    //Button
    this->menuButtons.push_back(
        Button(
            this->wScreen/2.0f-200,this->hScreen/5.0f+100, 400, 50,
            "START GAME", this->font, 30,
            sf::Color(200,200,200),
            sf::Color(180,180,180),
            sf::Color(170,170,170)
        )
    );
    this->menuButtons.push_back(
        Button(
            this->wScreen/2.0f-200,this->hScreen/5.0f+200, 400, 50,
            "SETTINGS", this->font, 30,
            sf::Color(200,200,200),
            sf::Color(180,180,180),
            sf::Color(170,170,170)
        )
    );
    this->menuButtons.push_back(
        Button(
            this->wScreen/2.0f-200,this->hScreen/5.0f+300, 400, 50,
            "EXIT", this->font, 30,
            sf::Color(200,200,200),
            sf::Color(180,180,180),
            sf::Color(170,170,170)
        )
    );



    //          SELECT LEVEL
    //Text
    this->levelTexts.push_back(
        Text("Select Level",this->font, 40, this->wScreen/2, this->hScreen/5.0f)
    );
    //Button
    this->levelButtons.push_back(
        Button(
            this->wScreen/2.0f-200,this->hScreen/5.0f+100, 400, 50,
            "Easy", this->font, 30,
            sf::Color(200,200,200),
            sf::Color(180,180,180),
            sf::Color(170,170,170)
        )
    );
    this->levelButtons.push_back(
        Button(
            this->wScreen/2.0f-200,this->hScreen/5.0f+200, 400, 50,
            "Normal", this->font, 30,
            sf::Color(200,200,200),
            sf::Color(180,180,180),
            sf::Color(170,170,170)
        )
    );
    this->levelButtons.push_back(
        Button(
            this->wScreen/2.0f-200,this->hScreen/5.0f+300, 400, 50,
            "Hard", this->font, 30,
            sf::Color(200,200,200),
            sf::Color(180,180,180),
            sf::Color(170,170,170)
        )
    );

}

void GameManeger::Run()
{
    sf::RenderWindow window(sf::VideoMode({this->wScreen, this->hScreen}), "Minesweeper");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        HandleInput(window);
        UI(window);
    }
}

void GameManeger::HandleInput(sf::RenderWindow& window)
{
    while (const std::optional<sf::Event> event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();

        switch(this->state)
        {
            case GameState::MainMenu:
                // tương tác tại trang MainMenu
                for (auto& button : menuButtons)
                {
                    bool check = button.Update(window);
                    if (check)
                        if (button.text == "START GAME")
                            this->state = GameState::LevelSelect;
                }
                break;

            case GameState::LevelSelect:
                for (auto& button : levelButtons)
                {
                    bool check = button.Update(window);
                    if (check)
                    {
                        this->state = GameState::Playing;
                        // tạo bảng game tại đây
                    }
                }
                break;
            

        }
    }
}

void GameManeger::UI(sf::RenderWindow& window)
{
    window.clear(sf::Color::White);
    switch(this->state)
    {
        case GameState::MainMenu:
            // vẽ các nút, chữ trên màn hình
            for (auto& button : this->menuButtons)
                button.ShowButton(window);
            for (auto& text   : this->menuTexts)
                text.ShowText(window);
            break;

        case GameState::LevelSelect:
            for (auto& button : this->levelButtons)
                button.ShowButton(window);
            for (auto& text   : this->levelTexts)
                text.ShowText(window);
            break;
    }
    window.display();
}