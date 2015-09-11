#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "ResourceManager.h"

class GameObjectDef {
public:
	sf::Texture * texture;
	int vertexCount;
	sf::Vector2<float> * vertices;
	b2World * world;
	sf::Vector2<float> origin;
	sf::Vector2<float> position;
	float friction;
	float density;
	bool dynamic;
	GameObjectDef();
	~GameObjectDef();
	void loadFromFile(std::string fileName);
};
