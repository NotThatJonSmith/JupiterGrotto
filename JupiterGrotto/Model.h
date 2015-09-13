#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <cstdlib>
#include <set>
#include "GameObject.h"
#include "JGUtils.h"

class Model {

private:

	b2World world;
	std::set<GameObject *> objects;

public:

	Model();
	~Model();
	void setGravity(b2Vec2 grav);
	void update();
	std::set<GameObject*>::iterator objectsBegin();
	std::set<GameObject*>::iterator objectsEnd();
	void addObject(std::string fileName, sf::Vector2f position);
	void removeObject(GameObject * victim);
	void loadFromFile(std::string fileName);
};
