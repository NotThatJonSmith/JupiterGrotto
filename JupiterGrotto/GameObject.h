#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "GameObjectDef.h"


class GameObject {
	friend class View;
private:
	b2Body * body;
	sf::Texture * texture;
	sf::Vector2<float> origin;
public:
	GameObject(GameObjectDef &def, b2World &world);
	sf::Vector2f getPosition();
};
