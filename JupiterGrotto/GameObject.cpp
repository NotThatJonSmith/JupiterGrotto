#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "GameObject.h"

GameObject::GameObject(GameObjectDef &def, b2World &world) {

	// Origin and texture are simple data members
	origin = def.origin;
	texture = def.texture;

	// Construct a b2Body using dynamic, position, and world data members
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(def.position.x / SCALE, def.position.y / SCALE);
	BodyDef.type = def.dynamic ? b2_dynamicBody : b2_staticBody;
	body = world.CreateBody(&BodyDef);

	// Convert from sf::Vector2 to b2Vec2 with SCALE to set up the shape
	b2Vec2 * vertices = new b2Vec2[def.vertexCount];
	for (int i = 0; i < def.vertexCount; i++)
		vertices[i].Set(def.vertices[i].x / SCALE, def.vertices[i].y / SCALE);
	b2PolygonShape polygon;
	polygon.Set(vertices, def.vertexCount);

	// Create and apply the fixture using the shape and other data members
	b2FixtureDef FixtureDef;
	FixtureDef.density = def.density;
	FixtureDef.friction = def.friction;
	FixtureDef.shape = &polygon;
	body->CreateFixture(&FixtureDef);
	delete[] vertices;
}

void GameObject::draw(sf::RenderWindow &window) {
	sf::Sprite Sprite;
	Sprite.setTexture(*texture);
	Sprite.setOrigin(origin.x, origin.y);
	Sprite.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
	Sprite.setRotation(body->GetAngle() * 180 / b2_pi);
	window.draw(Sprite);
}
