#include "Model.h"

Model::Model() : world(b2Vec2(0.f, 0.f)) {}

Model::~Model() {
	while (!objects.empty()) removeObject(*objects.begin());
}

void Model::update() {
	world.Step(1 / 60.f, 8, 3);
}

void Model::setGravity(b2Vec2 gravity) {
	world.SetGravity(gravity);
}

void Model::addObject(std::string objectPropertiesFileName, sf::Vector2f position) {
	GameObjectProperties * addedObjectProperties = ResourceManager::get<GameObjectProperties>(objectPropertiesFileName);
	GameObject * addedObject = new GameObject(*addedObjectProperties);
	addedObject->startPhysics(world, position);
	objects.insert(addedObject);
}

void Model::removeObject(GameObject * victim) {
	if (objects.find(victim) == objects.end()) return;
	objects.erase(victim);
	world.DestroyBody(victim->body);
	delete victim;
}
/*
void Model::loadFromFile(std::string fileName) {
rapidjson::Document jsonDom = JGUtils::getJsonDom(fileName);
const rapidjson::Value& domGravity = jsonDom["gravity"];
b2Vec2 gravity(domGravity[0].GetDouble(), domGravity[1].GetDouble());
world.SetGravity(gravity);
const rapidjson::Value& domObject
}*/