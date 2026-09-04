#include "GameManeger.hpp"

GameManeger::GameManeger() : wScreen(1280), hScreen(720), state(GameState::MainMenu),  Map(font), textTime(font)
{
    assert(this->font.openFromFile("assets/Roboto-Regular.ttf") && "Error: không tải được font chữ !!!\n");
    this->bgEnd.setSize(sf::Vector2f({float(this->wScreen),float(this->hScreen)}));
    this->bgEnd.setFillColor(sf::Color(0,0,0,200));
    this->bgEnd.setPosition({0,0});

    this->textTime.setCharacterSize(30);
    this->textTime.setFillColor(sf::Color::Red);
    this->textTime.setPosition({this->wScreen/2.0f, this->hScreen/2.0f});



    //          MENU
    //Texts
    this->menuTexts.push_back(
        Text("MINESWEEPER",this->font, 40, this->wScreen/2, this->hScreen/5.0f)
    );
    //Buttons
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
            "EXIT", this->font, 30,
            sf::Color(200,200,200),
            sf::Color(180,180,180),
            sf::Color(170,170,170)
        )
    );



    //          SELECT LEVEL
    //Texts
    this->levelTexts.push_back(
        Text("Select Level",this->font, 40, this->wScreen/2, this->hScreen/5.0f)
    );
    //Buttons
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
    this->levelButtons.push_back(
        Button(
            this->wScreen/2.0f-550,this->hScreen/5.0f+500, 100, 50,
            "<- Back", this->font, 30,
            sf::Color(200,200,200),
            sf::Color(180,180,180),
            sf::Color(170,170,170)
        )
    );



    //          GAME OVER
    //Texts
    this->gameOverTexts.push_back(
        Text("Game Over",this->font, 50, this->wScreen/2.0f, this->hScreen/3.0f, sf::Color::White)
    );



    //          WIN
    //Texts
    this->winTexts.push_back(
        Text("Win",this->font, 50, this->wScreen/2.0f, this->hScreen/3.0f, sf::Color::White)
    );



    //          END
    //Buttons
    this->endButtons.push_back(
        Button(
            this->wScreen/2.0f-300,this->hScreen/3.0f+200, 100, 60,
            "Again", this->font, 30,
            sf::Color(200,200,200),
            sf::Color(180,180,180),
            sf::Color(170,170,170)
        )
    );
    this->endButtons.push_back(
        Button(
            this->wScreen/2.0f+200,this->hScreen/3.0f+200, 100, 60,
            "Quit", this->font, 30,
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

        if (this->state == GameState::MainMenu)
        {
            // tương tác tại trang MainMenu
            for (auto& button : menuButtons)
            {
                bool check = button.Update(window);
                if (check)
                {
                    if (button.text == "START GAME")
                        this->state = GameState::LevelSelect;
                    else if (button.text == "EXIT")
                        window.close();
                }
            }
        }
        else if (this->state == GameState::LevelSelect)
        {
            for (auto& button : levelButtons)
            {
                bool check = button.Update(window);
                if (check)
                {
                    if (button.text == "<- Back")
                        this->state = GameState::MainMenu;
                    else
                    {
                        // tạo bảng game tại đây
                        this->state = GameState::Playing;
                        if (button.text == "Easy")
                            this->Map.Create(9,9,9,this->wScreen,this->hScreen);
                        else if (button.text == "Normal")
                            this->Map.Create(16,16,40,this->wScreen,this->hScreen);
                        else if (button.text == "Hard")
                            this->Map.Create(32,16,99,this->wScreen,this->hScreen);
                    }
                }
            }
        }
        else if (this->state == GameState::Playing)
        {
            this->Map.InteractCell(window,this->state);
            if (this->state == GameState::Win)
            {
                this->textTime.setString(Map.GetTextTimeElapsed());
                sf::FloatRect bounds = this->textTime.getLocalBounds();
                this->textTime.setOrigin(
                    {
                        bounds.position.x + bounds.size.x/2.0f,
                        bounds.position.y + bounds.size.y/2.0f
                    }
                );
            }
        }
        else if (this->state == GameState::GameOver || this->state == GameState::Win)
        {
            for (auto& button : this->endButtons)
            {
                bool check = button.Update(window);
                if (check)
                {
                    if (button.text == "Again")
                    {
                        this->state = GameState::LevelSelect;
                    }
                    else if (button.text == "Quit")
                        this->state = GameState::MainMenu;
                }
            }
        }
    }
}

void GameManeger::UI(sf::RenderWindow& window)
{
    window.clear(sf::Color::White);
    if (this->state == GameState::MainMenu)
    {
        // vẽ các nút, chữ trên màn hình
        for (auto& button : this->menuButtons)
            button.ShowButton(window);
        for (auto& text   : this->menuTexts)
            text.ShowText(window);
    }
    else if (this->state == GameState::LevelSelect)    
    {
        for (auto& button : this->levelButtons)
            button.ShowButton(window);
        for (auto& text   : this->levelTexts)
            text.ShowText(window);
    }
    else if (this->state == GameState::Playing || this->state == GameState::GameOver || this->state == GameState::Win)
    {
        this->Map.ShowBoard(window);
        if (this->state == GameState::GameOver)
        {
            window.draw(this->bgEnd);
            for (auto& text : this->gameOverTexts)
                text.ShowText(window);
            for (auto& button : this->endButtons)
                button.ShowButton(window);
        }
        else if (this->state == GameState::Win)
        {
            window.draw(this->bgEnd);
            window.draw(this->textTime);
            for (auto& text : this->winTexts)
                text.ShowText(window);
            for (auto& button : this->endButtons)
                button.ShowButton(window);
            
        }
    }
    window.display();
}