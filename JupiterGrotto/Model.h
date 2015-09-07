#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <cstdlib>
#include <list>
#include "GameObject.h"
#include "JGUtils.h"

class Model {
	friend class View;
public:
	Model();
	~Model();
	void setGravity(b2Vec2 grav);
	void update();
	void loadFromFile(std::string fileName);
	void addObject(std::string fileName, sf::Vector2f position);
	//void removeObject(GameObject * obj);
private:
	b2World world;
	std::list<GameObject> objects;
};
