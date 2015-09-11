#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "GameObject.h"
#include "JGUtils.h"

GameObject::GameObject(GameObjectDef &def, b2World &world) {

	origin = def.origin;
	texture = def.texture;

	b2BodyDef BodyDef;
	BodyDef.position = JGUtils::sf2Box(def.position);
	BodyDef.type = def.dynamic ? b2_dynamicBody : b2_staticBody;
	body = world.CreateBody(&BodyDef);

	b2Vec2 * vertices = new b2Vec2[def.vertexCount];
	for (int i = 0; i < def.vertexCount; i++)
		vertices[i] = JGUtils::sf2Box(def.vertices[i]);
	b2PolygonShape polygon;
	polygon.Set(vertices, def.vertexCount);
	delete[] vertices;

	b2FixtureDef FixtureDef;
	FixtureDef.density = def.density;
	FixtureDef.friction = def.friction;
	FixtureDef.shape = &polygon;
	body->CreateFixture(&FixtureDef);
}

sf::Vector2f GameObject::getPosition() {
	return JGUtils::box2Sf(body->GetPosition());
}