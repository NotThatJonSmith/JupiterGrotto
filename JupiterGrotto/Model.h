#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <cstdlib>
#include <list>
#include "GameObject.h"

class Model {
	friend class View;
public:
	Model();
	~Model();
	void setGravity(b2Vec2 grav);
	void update(); // Step physics and run controller script for each object
	//void loadFromFile(std::string fileName); // will call addObject from a bunch of .god files
	//void saveToFile(std::string fileName);
	void addObject(std::string fileName, sf::Vector2<int> position);
	//void removeObject(GameObject * obj); // need a good ID scheme
private:
	std::list<GameObject> objects;
	b2World world;
};
