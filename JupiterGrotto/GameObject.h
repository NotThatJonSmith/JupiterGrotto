#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "ResourceManager.h"
#include "JGUtils.h"

class BaseGameObject {

public:
	sf::Texture * texture;
	sf::Vector2f origin;
	b2PolygonShape shape;
	float density;
	float friction;
	bool dynamic;
	void loadFromFile(std::string baseObjectFileName);
	BaseGameObject();
	BaseGameObject(BaseGameObject &other);
	
};

class GameObject : protected BaseGameObject {

public:

	b2Body * body;

	GameObject();
	GameObject & operator=(BaseGameObject &other);
	GameObject(BaseGameObject &other);
	
	void startPhysics(b2World &world, sf::Vector2f position);

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);

	float getAngle();
	void setAngle(float angle);

	sf::Texture * getTexture();
	sf::Vector2f getOrigin();
	sf::Sprite getSprite();
};
