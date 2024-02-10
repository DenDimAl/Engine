#include <SFML/Graphics.hpp>
#include <vector>

void Resize(sf::RenderWindow& wind, sf::View& v) {
    float aspect = (float(wind.getSize().x) / float(wind.getSize().y));
    v.setSize(wind.getSize().y*aspect, wind.getSize().y);
}

class Cell {

};

class Scene {

};

class Player {

};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 900), "SFML works!");
    sf::CircleShape shape(40.f);
    
    sf::Font f;
    f.loadFromFile("C:/Windows/Fonts/Tahoma.ttf");
   
    shape.setFillColor(sf::Color::Green);
    sf::RectangleShape W(sf::Vector2f(1500, 800));
    W.setFillColor(sf::Color::White);
    sf::View v1(sf::Vector2f(0.f,0.f), sf::Vector2f(800.f,600.f));
    v1.setCenter(0.f, 0.f);
    v1.setSize(1800.f, 1500.f);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == event.KeyPressed) {
                if (event.key.code == sf::Keyboard::Right) {
                    v1.move(10.f, 0.f);
                }
                if (event.key.code == sf::Keyboard::Left) {
                    v1.move(-10.f, 0.f);
                }
                if (event.key.code == sf::Keyboard::Up) {
                    v1.move(0.f, -10.f);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    v1.move(0.f, 10.f);
                }
                if (event.key.code == sf::Keyboard::D) {
                    shape.move(60.f, 0.f);
                }
                if (event.key.code == sf::Keyboard::A) {
                    shape.move(-60.f, 0.f);
                }
                if (event.key.code == sf::Keyboard::W) {
                    shape.move(0.f, -60.f);
                }
                if (event.key.code == sf::Keyboard::S) {
                    shape.move(0.f, 60.f);
                }
            }
            if (event.type == event.Resized) {
                Resize(window, v1);
            }
        }

        window.clear();
        window.draw(W);
        window.draw(shape);
        window.setView(v1);
        window.display();
    }

    return 0;
}