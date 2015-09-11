#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <cstdlib>
#include <set>
#include "GameObject.h"
#include "JGUtils.h"

class Model {
	friend class View;
private:
	b2World world;
	std::set<GameObject *> objects;
public:
	Model();
	~Model();
	void setGravity(b2Vec2 grav);
	void update();
	void addObject(std::string fileName, sf::Vector2f position);
	void removeObject(GameObject * victim);
	void loadFromFile(std::string fileName);
};
