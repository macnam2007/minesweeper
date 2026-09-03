#include "Text.hpp"

Text::Text(const std::string& text, sf::Font &font, int size, float x, float y, sf::Color color) : text(font)
{
    this->text.setString(text);
    this->text.setCharacterSize(size);
    this->text.setFillColor(color);

    // tay đổi điểm vẽ (góc trên bên trái -> trung tâm chữ) 
    sf::FloatRect bounds = this->text.getLocalBounds();
    this->text.setOrigin(
        {
            bounds.position.x + bounds.size.x/2.0f,
            bounds.position.y + bounds.size.y/2.0f
        }
    );

    // vị trí trung tâm của chữ
    this->text.setPosition({x,y});
}

void Text::ShowText(sf::RenderWindow& window)
{
    window.draw(this->text);
}