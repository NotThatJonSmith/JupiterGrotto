#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "GameObject.h"

GameObject::GameObject(GameObjectDef &def) {
	origin = def.origin;
	texture = def.texture;

	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(def.position.x / SCALE, def.position.y / SCALE);
	BodyDef.type = def.dynamic ? b2_dynamicBody : b2_staticBody;
	body = def.world->CreateBody(&BodyDef);

	b2FixtureDef FixtureDef;
	FixtureDef.density = def.density;
	FixtureDef.friction = def.friction;
	FixtureDef.shape = def.shape;
	body->CreateFixture(&FixtureDef);
}

void GameObject::draw(sf::RenderWindow &window) {
	sf::Sprite Sprite;
	Sprite.setTexture(texture);
	Sprite.setOrigin(origin.x, origin.y);
	Sprite.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
	Sprite.setRotation(body->GetAngle() * 180 / b2_pi);
	window.draw(Sprite);
}
