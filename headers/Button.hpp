#include <SFML/Graphics.hpp>
#include <string>
#include <cassert> // in ra lỗi

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
        Button(
            float x, float y , float w, float h,
            const std::string& text,
            sf::Font& font,
            int size,
            const sf::Color& normalColor,
            const sf::Color& hoverColor,
            const sf::Color& clickColor
        );
        void ShowButton(sf::RenderWindow&);
        sf::Color GetColor();
        void Update(sf::RenderWindow&);
        bool HoverButton(sf::RenderWindow& window);
};