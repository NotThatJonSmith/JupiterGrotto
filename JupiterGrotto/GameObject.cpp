#include "GameObject.h"

void BaseGameObject::loadFromFile(std::string fileName) {

	rapidjson::Document jsonDom = JGUtils::getJsonDom(fileName);

	setTexture(ResourceManager::get<sf::Texture>(jsonDom["texture"].GetString()));
	setOrigin(sf::Vector2f(jsonDom["origin"][0].GetDouble(), jsonDom["origin"][1].GetDouble()));
	density = jsonDom["density"].GetDouble();
	friction = jsonDom["friction"].GetDouble();
	dynamic = jsonDom["dynamic"].GetBool();

	const rapidjson::Value& domVertices = jsonDom["vertices"];
	int vertexCount = domVertices.Size();
	b2Vec2 * vertices = new b2Vec2[vertexCount];
	for (int i = 0; i < vertexCount; i++)
		vertices[i] = GameObject::sf2Box(sf::Vector2f(domVertices[i][0].GetInt(), domVertices[i][1].GetInt()));
	shape.Set(vertices, vertexCount);
	delete[] vertices;
}

GameObject::GameObject() : body(nullptr) { }

BaseGameObject::BaseGameObject() {}

GameObject& GameObject::operator=(BaseGameObject &other) {
	sprite = other.sprite;
	shape = other.shape;
	density = other.density;
	friction = other.friction;
	dynamic = other.dynamic;
	return *this;
}

GameObject::GameObject(BaseGameObject &other) {
	*this = other;
}

void GameObject::startPhysics(b2World &world, sf::Vector2f position) {

	if (body != nullptr) world.DestroyBody(body); // Could modify to restart physics on a stopped object...
	b2BodyDef BodyDef;
	BodyDef.position = GameObject::sf2Box(position);
	BodyDef.type = dynamic ? b2_dynamicBody : b2_staticBody;
	body = world.CreateBody(&BodyDef);

	b2FixtureDef FixtureDef;
	FixtureDef.density = density;
	FixtureDef.friction = friction;
	FixtureDef.shape = &shape;
	body->CreateFixture(&FixtureDef);
}


void GameObject::stopPhysics(b2World &world) {
	world.DestroyBody(body);
}

sf::Vector2f GameObject::getPosition() {
	return box2Sf(body->GetPosition());
}

void GameObject::setPosition(sf::Vector2f position) {
	body->SetTransform(GameObject::sf2Box(position), body->GetAngle());
}

float GameObject::getAngle() {
	return body->GetAngle() * 180 / b2_pi;
}

void GameObject::setAngle(float angle) {
	body->SetTransform(body->GetPosition(), angle * b2_pi / 180);
}

void BaseGameObject::setTexture(sf::Texture * newTexture) {
	sprite.setTexture(*newTexture);
}

void BaseGameObject::setOrigin(sf::Vector2f newOrigin) {
	sprite.setOrigin(newOrigin);
}

sf::Vector2f BaseGameObject::getOrigin() {
	return sprite.getOrigin();
}

sf::Sprite GameObject::getSprite() {
	sprite.setPosition(getPosition());
	sprite.setRotation(getAngle());
	return sprite;
}

void GameObject::update() {
}

b2Vec2 GameObject::sf2Box(sf::Vector2f sfVector) {
	return b2Vec2(sfVector.x / SCALE, sfVector.y / SCALE);
}

sf::Vector2f GameObject::box2Sf(b2Vec2 boxVector) {
	return sf::Vector2f(boxVector.x * SCALE, boxVector.y * SCALE);
}