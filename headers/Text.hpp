#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Text
{
    private:
        sf::Text text;
    public:
        Text(const std::string& text, sf::Font &font, int size, float x, float y, sf::Color color=sf::Color::Black);
        void ShowText(sf::RenderWindow& window);
};