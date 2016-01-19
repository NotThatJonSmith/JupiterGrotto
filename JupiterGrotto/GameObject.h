#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "ResourceManager.h"
#include "JGUtils.h"

static const float SCALE = 30.f;

class BaseGameObject {

public:
	sf::Sprite sprite;
	b2PolygonShape shape;
	float density;
	float friction;
	bool dynamic;
	void loadFromFile(std::string baseObjectFileName);
	BaseGameObject();
	BaseGameObject(BaseGameObject &other);
	void setTexture(sf::Texture *);

	sf::Vector2f getOrigin();
	void setOrigin(sf::Vector2f newOrigin);
};

class GameObject : protected BaseGameObject {
private:
	b2Body * body;

public:
	GameObject();
	GameObject & operator=(BaseGameObject &other);
	GameObject(BaseGameObject &other);
	
	void update();

	void startPhysics(b2World &world, sf::Vector2f position);
	void stopPhysics(b2World &world);

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);

	float getAngle();
	void setAngle(float angle);

	sf::Sprite getSprite();

	static b2Vec2 GameObject::sf2Box(sf::Vector2f boxVector);
	static sf::Vector2f box2Sf(b2Vec2 sfVector);
};
