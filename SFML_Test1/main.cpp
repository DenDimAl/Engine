#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "main.h"
void checkBorder(sf::CircleShape shape) {
    if (shape.getPosition().x > 280.00000) {
        //shape.setPosition(280,shape.getPosition().y);
        shape.move(-20, 0);
    }
    else if (shape.getPosition().x < 0) {
        shape.setPosition(0, shape.getPosition().y);
    }
    if (shape.getPosition().y > 280.00000) {
        shape.setPosition(shape.getPosition().x, 280);
    }
    else if (shape.getPosition().y < 0) {
        shape.setPosition(shape.getPosition().x,0);
    }
}
int main()
{
    
    sf::RenderWindow window(sf::VideoMode(300, 300), "Ultrakill 2");
    window.setKeyRepeatEnabled(false);
    sf::CircleShape shape(10.f);
    sf::Text txt;
    sf::Font fnt;
    fnt.loadFromFile("C:\\Windows\\Fonts\\Tahoma.ttf");
    txt.setFont(fnt); // font is a sf::Font

    txt.setString("Hello world");

    // set the character size
    txt.setCharacterSize(12); // in pixels, not points!

    // set the color
    txt.setFillColor(sf::Color::Red);

    // set the text style
    txt.setStyle(sf::Text::Bold | sf::Text::Underlined);
    sf::String coords;
    
    shape.setFillColor(sf::Color::Red);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                shape.move(0, 10);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                shape.move(0, -10);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                shape.move(10,0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                shape.move(-10, 0);
            }
        }
        window.clear();    
        coords = std::to_string(shape.getPosition().x) + " " + std::to_string(shape.getPosition().y);
        txt.setString(coords);
        txt.setPosition(150, 150);
        window.draw(txt);
        window.draw(shape);
        checkBorder(shape);
        window.display();
    }

    return 0;
}