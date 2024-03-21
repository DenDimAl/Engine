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
    sf::RectangleShape wall1(sf::Vector2f(80.f,80.f));
    sf::RectangleShape wall2(sf::Vector2f(80.f, 80.f));
    wall1.setFillColor(sf::Color::Red);
    wall2.setFillColor(sf::Color::Red);
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
    SpriteComponent s;
    Transform tra;
    GameObject o;
    PlayerControllerComponent P;
    o.AddComponent<SpriteComponent>(&s);
    s.Initialize(&shape, &t, &window);
    o.AddComponent<Transform>(&tra);
    tra.Initialize(s);
    o.AddComponent(&P);
    P.Initialize(o, sf::Keyboard::W, sf::Keyboard::A, sf::Keyboard::S, sf::Keyboard::D);
    P.SetEvent(&event);

    GameObject w1;
    GameObject w2;
    SpriteComponent sw1;
    SpriteComponent sw2;
    Transform tw1;
    Transform tw2;
    w1.AddComponent<SpriteComponent>(&sw1);
    w1.AddComponent<Transform>(&tw1);
    w2.AddComponent<SpriteComponent>(&sw2);
    w2.AddComponent<Transform>(&tw2);
    sw1.Initialize(&wall1, &window);
    sw2.Initialize(&wall2, &window);
    tw1.Initialize(sw1);
    tw2.Initialize(sw2);
    tw1.SetCoords(0.f, 150.f);
    tw2.SetCoords(150.f, 150.f);
    
    
   
    
    
    
   
    
    while (window.isOpen())
    {
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            P.Update();
            if (event.type == event.Resized) {
                Resize(window, v1);
            }
        }

        window.clear();
        window.draw(W);
        w1.Update();
        w2.Update();
        o.Update();
        window.setView(v1);
        window.display();
    }

    return 0;
}