#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <typeindex>


class Component {
public:
	Component() {

	}
	virtual void update() {

	}
	unsigned int Get_Id(){
		//return ID;
	}
protected:
	//unsigned int ID;
};

class SpriteComponent : public Component
{
public:
	SpriteComponent(sf::Shape* s, sf::Texture* t, sf::RenderWindow* w) { 
		shape = s;
		window = w;
		(*shape).setTexture(t);
		//ID = 1;
	}
	SpriteComponent(sf::Shape* s) {
		
		shape = s;
		//ID = 1;
	}
	void update() {
		(*window).draw(*shape);
	}
	sf::Shape* GetShape() {
		return shape;
	}
	
private:
	sf::RenderWindow* window;
	sf::Shape* shape;
	sf::Texture tex;
};

class WallComponent : Component {
public:

private:

};



class Transform : public Component {
public:
	Transform(){
		coords.x = 0;
		coords.y = 0;
		(*s).setPosition(0.f, 0.f);
		//ID = 2;
	}
	Transform(float a, float b) {
		coords.x = a;
		coords.y = b;
		(*s).setPosition(coords);
	}
	Transform(SpriteComponent sprite) {
		coords.x = (*sprite.GetShape()).getPosition().x;
		coords.y = (*sprite.GetShape()).getPosition().y;
		s = sprite.GetShape();
		(*s).setOrigin((*s).getGlobalBounds().width / 2, (*s).getGlobalBounds().height / 2);
	}
	void Translate(float Tx, float Ty) {
		(*s).move(Tx, -Ty); //функции SFML
	}
	void Rotate(float theta) {
		
		(*s).rotate(theta);
	
	}
	void Scale(float Sx, float Sy) {
		(*s).scale(sf::Vector2f(Sx, Sy));
	}
	void Scale(float S) {
		(*s).scale(sf::Vector2f(S, S));
	}
	void update() {
		
	}
private:
	sf::Vector2f coords;
	sf::Shape* s;
};



class GameObject
{
public:
	std::vector<Component*> components;
	GameObject() {
		ID = 0;
		components = {};
	};
	~GameObject() {};
	GameObject(std::vector <Component*> v, unsigned int id) {
		components = v;
		ID = id;
	}
	void AddComponent(Component* c) {
		components.push_back(c);
	}
	void RemoveComponent(Component* c) {
		
	  
	}
	
	void update() {
		for (int i = 0; i < components.size(); i++) {
			(*components[i]).update();
		}
	}
	
private:
	unsigned int ID;
	
};
class PlayerControllerComponent : public Component
{
public:
	PlayerControllerComponent() {

	}
	PlayerControllerComponent(GameObject GO,sf::Keyboard::Key Up, sf::Keyboard::Key Left, sf::Keyboard::Key Down, sf::Keyboard::Key Right) {
		MoveUp = Up;
		MoveLeft = Left;
		MoveDown = Down;
		MoveRight = Right;
		Shoot = sf::Mouse::Left;
		Check = sf::Mouse::Right;
		for (int i = 0; i < GO.components.size(); i++) {
			if (typeid(GO.components[i]) == typeid(Transform)) {
				tr = dynamic_cast<Transform*>(GO.components[i]);
				break;
			}
		}
	}
	PlayerControllerComponent(GameObject GO) {
		
		for (int i = 0; i < GO.components.size(); i++) {
			if (std::type_index(typeid(GO.components[i])) == std::type_index((typeid(Transform*)))) {
				tr = dynamic_cast<Transform*>(GO.components[i]);//!
				break;
			}
		}
	}
	void SetEvent(sf::Event* e) {
		ev = e;
	}
	void update() {
		
		if ((*ev).type == (*ev).KeyPressed) {
			if ((*ev).key.code == MoveUp) {
				tr->Translate(0.f, 30.f);
			}
			if ((*ev).key.code == MoveDown) {
				tr->Translate(0.f, -30.f);
			}
			if ((*ev).key.code == MoveLeft) {
				tr->Translate(-30.f, 0.f);
			}
			if ((*ev).key.code == MoveRight) {
				tr->Translate(30.f, 0.f);
			}
			if ((*ev).key.code == MoveUp) {
				tr->Translate(30.f, 0.f);
			}
		}
		if ((*ev).type == (*ev).MouseButtonPressed) {
			if ((*ev).mouseButton.button == Shoot) {

			}
			if ((*ev).mouseButton.button == Check) {

			}
		}
	}

private:
	sf::Keyboard::Key MoveUp = sf::Keyboard::W;
	sf::Keyboard::Key MoveDown = sf::Keyboard::S;
	sf::Keyboard::Key MoveLeft = sf::Keyboard::A;
	sf::Keyboard::Key MoveRight = sf::Keyboard::W;
	sf::Mouse::Button Shoot = sf::Mouse::Left;
	sf::Mouse::Button Check = sf::Mouse::Right;
	Transform* tr;
	sf::Event* ev;
};

class Cell {
public:
	Cell() {

	}
	~Cell() {};
	Cell(std::vector <GameObject> o) {
		objects = o;
	}
	void update() {
		for (int i = 0; i < objects.size(); i++)
			objects[i].update();
	}
private:
	std::vector <GameObject> objects;

};

class Scene {

};