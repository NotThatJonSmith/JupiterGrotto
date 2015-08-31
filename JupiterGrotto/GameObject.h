#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "GameObjectDef.h"

static const float SCALE = 30.f;

class GameObject {
	friend class View;
private:
	sf::Texture * texture;
	b2Body * body;
	sf::Vector2<float> origin;
public:
	GameObject(GameObjectDef &def, b2World &world);
};
