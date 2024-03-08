#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <typeindex>
#include <typeinfo>


class Component {
public:
	Component() {

	}
	virtual void update() {

	}
	unsigned int Get_Id(){
		return ID;
	}
protected:
	unsigned int ID=0;
};

class SpriteComponent : public Component
{
public:
	SpriteComponent(sf::Shape* s, sf::Texture* t, sf::RenderWindow* w) { 
		shape = s;
		window = w;
		(*shape).setTexture(t);
		ID = 1;
	}
	SpriteComponent(sf::Shape* s, sf::RenderWindow* w) {
		window = w;
		shape = s;
		ID = 1;
	}
	void update() {
		(*window).draw(*shape);
	}
	sf::Shape* GetShape() {
		return shape;
	}
	unsigned int Get_Id() {
		return ID;
	}
private:
	sf::RenderWindow* window;
	sf::Shape* shape;
	sf::Texture tex;
};



class Transform : public Component {
public:
	Transform(){
		coords.x = 0;
		coords.y = 0;
		(*s).setPosition(0.f, 0.f);
		ID = 2;
	}
	Transform(float a, float b) {
		coords.x = a;
		coords.y = b;
		(*s).setPosition(coords);
		ID = 2;
	}
	
	Transform(SpriteComponent sprite) {
		coords.x = (*sprite.GetShape()).getPosition().x;
		coords.y = (*sprite.GetShape()).getPosition().y;
		s = sprite.GetShape();
		(*s).setOrigin((*s).getGlobalBounds().width / 2, (*s).getGlobalBounds().height / 2);
		ID = 2;
	}
	sf::Vector2f Get_coords() {
		return coords;
	}
	void SetCoords(float X, float Y) {
		coords.x = X;
		coords.y = Y;
		(*s).setPosition(coords);
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
		coords.x = (*s).getPosition().x;
		coords.y = (*s).getPosition().y;
	}
	unsigned int Get_Id() {
		return ID;
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
		for (auto it = components.begin(); it != components.end(); it++) {
			if (*it == c) {
				components.erase(it);
			}
		}
	  
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
		ID = 3;
	}
	PlayerControllerComponent(GameObject GO,sf::Keyboard::Key Up, sf::Keyboard::Key Left, sf::Keyboard::Key Down, sf::Keyboard::Key Right) {
		MoveUp = Up;
		MoveLeft = Left;
		MoveDown = Down;
		MoveRight = Right;
		Shoot = sf::Mouse::Left;
		Check = sf::Mouse::Right;
		for (int i = 0; i < GO.components.size(); i++) {
			if (GO.components[i]->Get_Id() == 2) {
				tr = dynamic_cast<Transform*>(GO.components[i]);
				break;
			}
		}
		ID = 3;
	}
	PlayerControllerComponent(GameObject GO) {
		
		for (int i = 0; i < GO.components.size(); i++) {
			Transform* t;
			if (GO.components[i]->Get_Id()==2) {
				tr = dynamic_cast<Transform*>(GO.components[i]);//!
				break;
			}
		}
		ID = 3;
	}
	void SetEvent(sf::Event* e) {
		ev = e;
	}
	void update() {
		
		if ((*ev).type == (*ev).KeyPressed) {
			if ((*ev).key.code == MoveUp) {
				tr->Translate(0.f, 60.f);
			}
			if ((*ev).key.code == MoveDown) {
				tr->Translate(0.f, -60.f);
			}
			if ((*ev).key.code == MoveLeft) {
				tr->Translate(-60.f, 0.f);
			}
			if ((*ev).key.code == MoveRight) {
				tr->Translate(60.f, 0.f);
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
	sf::Keyboard::Key MoveRight = sf::Keyboard::D;
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
class CameraComponent : public Component
{
public:
	CameraComponent() {
		ID = 4;
	};
	CameraComponent(Scene s) {

	}
	CameraComponent(Transform t) {
		camera.setCenter(t.Get_coords());
		camera.setSize(800, 600);

	}
	CameraComponent(Transform t,float SizeX, float SizeY) {
		camera.setCenter(t.Get_coords());
		camera.setSize(SizeX, SizeY);

	}
	CameraComponent(float CenterX,float CenterY,float SizeX, float SizeY) {
		camera.setCenter(CenterX,CenterY);
		camera.setSize(SizeX,SizeY);

	}
	~CameraComponent() {};
	void SetCenter() {

	}
private:
	sf::View camera;
};


