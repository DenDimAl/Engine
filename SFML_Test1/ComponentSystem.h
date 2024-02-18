#pragma once
#include <SFML/Graphics.hpp>
#include <Vector>

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
	unsigned int ID;
};

class SpriteComponent : Component
{
public:
	SpriteComponent(sf::Shape* s, sf::Texture* t) { 
		shape = s;
		(*shape).setTexture(t);
		ID = 1;
	}
	SpriteComponent(sf::Shape* s) {
		shape = s;
		ID = 1;
	}
	void update(sf::RenderWindow& w) {
		w.draw(*shape);
	}
	
private:
	
	sf::Shape* shape;
	sf::Texture tex;
};

class WallComponent : Component {
public:

private:

};

class PlayerComponent : Component
{
public:
	
private:

};

//class Cell {
//public:
//	Cell() {
//
//	}
//	~Cell() {};
//	Cell(std::vector <GameObject> o) {
//		objects = o;
//	}
//	void update() {
//		for (int i = 0; i < objects.size(); i++)
//			objects[i].update();
//	}
//private:
//	std::vector <GameObject> objects;
//
//};

class Scene {

};

//class GameObject
//{
//public:
//	GameObject() {
//		ID = 0;
//		components = {};
//	};
//	~GameObject() {};
//	GameObject(std::vector <Component> v, unsigned int id) {
//		components = v;
//		ID = id;
//	}
//	void AddComponent(Component c) {
//		components.push_back(c);
//	}
//	void RemoveComponent(Component c) {
//		
//	}
//	void update() {
//		for (int i = 0; i < components.size(); i++) {
//			components[i].update();
//		}
//	}
//private:
//	unsigned int ID;
//	std::vector<Component> components;
//};

