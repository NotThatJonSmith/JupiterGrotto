
#include "Model.h"

Model::Model() :
world(b2Vec2(0.f, 0.f)) {
}

Model::~Model() {
	//ToDO
}

void Model::update() {
	world.Step(1 / 60.f, 8, 3);
}

void Model::setGravity(b2Vec2 gravity) {
	world.SetGravity(gravity);
}

void Model::addObject(std::string name, sf::Vector2<int> pos) {
	GameObjectDef * def = ResourceManager::get<GameObjectDef>(name);
	def->position = pos;
	objects.push_back(GameObject(*def,world));
}
