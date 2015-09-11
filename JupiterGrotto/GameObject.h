#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "ResourceManager.h"
#include "JGUtils.h"

class GameObjectProperties {

	friend class GameObject;

private:

	sf::Texture * texture;
	sf::Vector2f origin;
	b2PolygonShape shape;
	float density;
	float friction;
	bool dynamic;

public:

	void loadFromFile(std::string fileName);

};

class GameObject {

private:

	GameObjectProperties properties;

public:

	b2Body * body; // Only public so Model can remove it from its world

	GameObject(GameObjectProperties initialProperties);
	void startPhysics(b2World &world, sf::Vector2f position);

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);

	float getAngle();
	void setAngle(float angle);

	sf::Texture * getTexture();
	sf::Vector2f getOrigin();
	
};
