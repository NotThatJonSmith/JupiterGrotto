#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "rapidjson\document.h"
#include "ResourceManager.h"
#include "JGUtils.h"

// TODO copy constructor, error checking, and more gets and sets
// Work on this until addind things like scripts is a trivial task!
// Lua scripts should only ever be able to access these get/set methods

// Copy ctor should only copy the start values...

class GameObject {

private:

	b2PolygonShape startShape;
	float startDensity;
	float startDynamic;
	float startFriction;
	sf::Texture * startTexture;
	sf::Vector2f startOrigin;
	sf::Vector2f startPosition;

	b2Body * body;
	sf::Texture * texture;
	sf::Vector2f origin;

public:

	GameObject();
	GameObject(GameObject original);

	void loadFromFile(std::string fileName);
	void begin(b2World &world);

	void setAngle(sf::Vector2f newAngle);
	void setOrigin(sf::Vector2f newOrigin);
	void setPosition(sf::Vector2f newPosition);
	void setTexture(sf::Texture * newTexture);

	float getAngle();
	sf::Vector2f getOrigin();
	sf::Vector2f getPosition();
	sf::Texture * getTexture();
};
