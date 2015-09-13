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

std::set<GameObject*>::iterator Model::objectsBegin() {
	return objects.begin();
}

std::set<GameObject*>::iterator Model::objectsEnd() {
	return objects.end();
}

void Model::addObject(std::string baseObjectFileName, sf::Vector2f position) {
	GameObject * addedObject = new GameObject();
	*addedObject = *ResourceManager::get<BaseGameObject>(baseObjectFileName);
	addedObject->startPhysics(world, position);
	objects.insert(addedObject);
}

void Model::removeObject(GameObject * victim) {
	if (objects.find(victim) == objects.end()) return;
	objects.erase(victim);
	world.DestroyBody(victim->body);
	delete victim;
}

void Model::loadFromFile(std::string fileName) {
	rapidjson::Document jsonDom = JGUtils::getJsonDom(fileName);
	
	const rapidjson::Value& domGravity = jsonDom["gravity"];
	b2Vec2 gravity(domGravity[0].GetDouble(), domGravity[1].GetDouble());
	world.SetGravity(gravity);

	const rapidjson::Value& domObjectList = jsonDom["objects"];
	for (unsigned int i = 0; i < domObjectList.Size(); i++) {
		const rapidjson::Value& domObjectPlacementVector = domObjectList[i];
		std::string objectName = domObjectPlacementVector[0].GetString();
		sf::Vector2f objectPosition = sf::Vector2f(domObjectPlacementVector[1][0].GetDouble(), domObjectPlacementVector[1][1].GetDouble());
		addObject(objectName, objectPosition);
	}
}