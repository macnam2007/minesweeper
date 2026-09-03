#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include <string>


class Button
{
    private:
        enum ButtonState{
            normal,
            hover,
            click
        };
        ButtonState state = ButtonState::normal;
        sf::Color listBgColor[3];
        float x,y,w,h;
        sf::RectangleShape box;
        sf::Text textShow;

    public:
        const std::string text;

    public:
        Button(
            float x, float y , float w, float h,
            const std::string& text,
            sf::Font& font,
            int size,
            const sf::Color& normalColor,
            const sf::Color& hoverColor,
            const sf::Color& clickColor
        );
        void ShowButton(sf::RenderWindow& window);
        sf::Color GetColor();
        bool Update(sf::RenderWindow& window);
        bool HoverButton(sf::RenderWindow& window);
};