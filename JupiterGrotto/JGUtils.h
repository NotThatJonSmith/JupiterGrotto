#pragma once
#include "rapidjson/document.h"
#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
static const float SCALE = 30.f;

namespace JGUtils {
	rapidjson::Document getJsonDom(std::string fileName);
	b2Vec2 sf2Box(sf::Vector2f sfVector);
	sf::Vector2f box2Sf(b2Vec2 boxVector);
}