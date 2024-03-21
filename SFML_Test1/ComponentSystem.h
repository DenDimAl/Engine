#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#define Type(x) std::type_index(typeid(x))
class Component {
public:
	Component() {

	}
	virtual void Update() {

	}
	
protected:
	
};

class SpriteComponent : public Component
{
public:
	SpriteComponent() {

	}
	void Initialize(sf::Shape* s, sf::Texture* t, sf::RenderWindow* w) {
		shape = s;
		window = w;
		(*shape).setTexture(t);
	}
	void Initialize(sf::Shape* s, sf::RenderWindow* w) {
		shape = s;
		window = w;
	}
	void Update() {
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



class Transform : public Component {
public:
	Transform(){
		
	}
	void Initialize() {
		coords.x = 0;
		coords.y = 0;
		(*s).setPosition(0.f, 0.f);
	}
	void Initialize(float a, float b) {
		coords.x = a;
		coords.y = b;
		(*s).setPosition(coords);
	}
	
	void Initialize(SpriteComponent sprite) {
		coords.x = (*sprite.GetShape()).getPosition().x;
		coords.y = (*sprite.GetShape()).getPosition().y;
		s = sprite.GetShape();
		(*s).setOrigin((*s).getGlobalBounds().width / 2, (*s).getGlobalBounds().height / 2);
		
	}
	

	sf::Vector2f GetCoords() {
		return coords;
	}
	void SetCoords(float X, float Y) {
		coords.x = X;
		coords.y = Y;
		(*s).setPosition(coords);
	}
	void Translate(float Tx, float Ty) {
		(*s).move(Tx, -Ty); 
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
	void Update() {
		coords.x = (*s).getPosition().x;
		coords.y = (*s).getPosition().y;
	}
	
private:
	sf::Vector2f coords;
	sf::Shape* s;
};



class GameObject
{
public:
	std::unordered_map<std::type_index, Component*> components;
	GameObject() {
		components = {};
	};
	~GameObject() {};
	GameObject(std::unordered_map<std::type_index, Component*> v) {
		components = v;
		
	}
	template <typename T>
	T* GetComponent() {
		T* c;
		for (auto it = components.begin(); it != components.end(); it++) {
			if (c=dynamic_cast<T*>(it->second)) {
				return c;
			}
		}
		return nullptr;
	}
	void Update() {
		for (auto i = components.begin(); i != components.end(); i++) {
			i->second->Update();
		}
	}
	template <typename T>
	T* AddComponent(T* c) {
		components.insert(std::make_pair(Type(T), c));
		return c;
	}
	
	
private:
	unsigned int ID;
	
};
class PlayerControllerComponent : public Component
{
public:
	PlayerControllerComponent(){}
	void Initialize(GameObject GO,sf::Keyboard::Key Up, sf::Keyboard::Key Left, sf::Keyboard::Key Down, sf::Keyboard::Key Right) {
		MoveUp = Up;
		MoveLeft = Left;
		MoveDown = Down;
		MoveRight = Right;
		tr=GO.GetComponent<Transform>();
	}

	void SetEvent(sf::Event* e) {
		ev = e;
	}
	void Update() {
		
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
	void Update() {
		for (int i = 0; i < objects.size(); i++)
			objects[i].Update();
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
		
	};
	
	void Initialize(Transform t) {
		camera.setCenter(t.GetCoords());
		camera.setSize(800, 600);

	}
	void Initialize(Transform t,float SizeX, float SizeY) {
		camera.setCenter(t.GetCoords());
		camera.setSize(SizeX, SizeY);

	}
	void Initialize(float CenterX,float CenterY,float SizeX, float SizeY) {
		camera.setCenter(CenterX,CenterY);
		camera.setSize(SizeX,SizeY);
	}
	
	void SetCenter(float X, float Y) {
		camera.setCenter(X, Y);
	}
	void SetScale(float sizeX, float sizeY) {
		camera.setSize(sizeX, sizeY);
	}
private:
	sf::View camera;
};


