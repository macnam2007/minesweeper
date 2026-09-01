#include "Button.hpp"

Button::Button(
    float x, float y, float w, float h,const std::string& text, sf::Font& font, int size,const sf::Color& normalColor,const sf::Color& hoverColor,const sf::Color& clickColor
) : x(x), y(y), w(w), h(h), textShow(font), state(ButtonState::normal)
{
    listBgColor[0] = normalColor;
    listBgColor[1] = hoverColor;
    listBgColor[2] = clickColor;

    this->textShow.setString(text);
    this->textShow.setCharacterSize(size);
    sf::FloatRect bounds = this->textShow.getLocalBounds();
    this->textShow.setOrigin(
    {   bounds.position.x + bounds.size.x/2.0f,
        bounds.position.y  + bounds.size.y/2.0f
    }
    );
    this->textShow.setPosition({x+w/2, y+h/2});

    this->box.setSize(sf::Vector2f(w,h));
    this->box.setFillColor(GetColor());
    this->box.setPosition({x,y});
}

void Button::ShowButton(sf::RenderWindow& window)
{
    window.draw(box);
    window.draw(textShow);
}

sf::Color Button::GetColor()
{
    return listBgColor[this->state];
}

void Button::Update(sf::RenderWindow& window)
{
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);
    if (this->box.getGlobalBounds().contains(mouseWorldPos))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            this->state = ButtonState::click;
            // lệnh tương tác của nút
        }
        else this->state = ButtonState::hover;
    }
    else this->state = ButtonState::normal;

    this->box.setFillColor(GetColor());
}

bool Button::HoverButton(sf::RenderWindow& window) // khi nhả chuột , hàm này ktra có phải nhả chuột trong ô này hay không
{
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);
    return this->box.getGlobalBounds().contains(mouseWorldPos);
}
