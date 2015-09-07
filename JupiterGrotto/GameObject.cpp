#include "GameObject.h"

GameObject::GameObject() : body(nullptr), startTexture(nullptr) {}

GameObject::GameObject(GameObject original) {
	startFriction = original.startFriction;
	startDensity = original.startDensity;
	startDynamic = original.startDynamic;
	startPosition = original.startPosition;
	startTexture = original.startTexture;
	startOrigin = original.startOrigin;
	startShape = original.startShape;
}

void GameObject::loadFromFile(std::string fileName) {

	rapidjson::Document jsonDom = JGUtils::getJsonDom(fileName);
	const rapidjson::Value& domPosition = jsonDom["position"];
	const rapidjson::Value& domOrigin = jsonDom["origin"];
	const rapidjson::Value& domVertices = jsonDom["vertices"];

	startDynamic = jsonDom["dynamic"].GetBool();
	startFriction = jsonDom["friction"].GetDouble();
	startDensity = jsonDom["density"].GetDouble();
	startTexture = ResourceManager::get<sf::Texture>(jsonDom["texture"].GetString());
	startPosition = sf::Vector2f(domPosition[0], domPosition[1]);
	startOrigin = sf::Vector2f(domOrigin[0].GetDouble(), domOrigin[1].GetDouble());

	int vertexCount = domVertices.Size();
	b2Vec2 * vertices = new b2Vec2[vertexCount];
	for (rapidjson::SizeType i = 0; i < vertexCount; i++)
		vertices[i] = JGUtils::sf2Box(sf::Vector2f(domVertices[i][0].GetDouble(), domVertices[i][1].GetDouble()));
	startShape.Set(vertices, vertexCount);
	delete[] vertices;
}

void GameObject::begin(b2World &world) {
	texture = startTexture;
	if (body != nullptr)
		world.DestroyBody(body);
	b2BodyDef BodyDef;
	BodyDef.position = JGUtils::sf2Box(startPosition);
	BodyDef.type = startDynamic ? b2_dynamicBody : b2_staticBody;
	body = world.CreateBody(&BodyDef);
	b2FixtureDef FixtureDef;
	FixtureDef.density = startDensity;
	FixtureDef.friction = startFriction;
	FixtureDef.shape = &startShape;
	body->CreateFixture(&FixtureDef);
}

sf::Vector2f GameObject::getPosition() {
	return JGUtils::box2Sf(body->GetPosition());
}

float getAngle() {
	return body->GetAngle();
}

void GameObject::setPosition(sf::Vector2f newPosition) {
	body->SetTransform(JGUtils::sf2Box(newPosition), body->GetAngle());
}

void GameObject::setAngle(float newAngle) {
	body->SetTransform(body->GetPosition(), newAngle);
}

sf::Texture * GameObject::getTexture() {
	return texture;
}

sf::Vector2f GameObject::getOrigin() {
	return origin;
}

void GameObject::setTexture(sf::Texture * newTexture) {
	texture = newTexture;
}

void GameObject::setOrigin(sf::Vector2f newOrigin) {
	origin = newOrigin;
}
