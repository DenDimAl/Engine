#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "ComponentSystem.h"



void Resize(sf::RenderWindow& wind, sf::View& v) {
    float aspect = (float(wind.getSize().x) / float(wind.getSize().y));
    v.setSize(wind.getSize().y*aspect, wind.getSize().y);
}


int main()
{
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(1200, 900), "DA");
    sf::CircleShape shape(40.f);
    sf::Font f;
    f.loadFromFile("C:/Windows/Fonts/Tahoma.ttf");
    sf::Texture t;
    t.loadFromFile("textura.png");
    
    shape.setFillColor(sf::Color::Green);
    sf::RectangleShape W(sf::Vector2f(1500, 800));
    W.setFillColor(sf::Color::White);
    sf::View v1(sf::Vector2f(0.f,0.f), sf::Vector2f(800.f,600.f));
   
    v1.setCenter(0.f, 0.f);
    v1.setSize(1800.f, 1500.f);
    SpriteComponent s(&shape, &t,&window);
    GameObject o;
    Transform tra(s);
    o.AddComponent(&s);
    o.AddComponent(&tra);
    PlayerControllerComponent P(o);
    P.SetEvent(&event);
    o.AddComponent(&P);
    while (window.isOpen())
    {
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            P.update();
            if (event.type == event.Resized) {
                Resize(window, v1);
            }
        }

        window.clear();
        window.draw(W);
       
        o.update();
        window.setView(v1);
        window.display();
    }

    return 0;
}