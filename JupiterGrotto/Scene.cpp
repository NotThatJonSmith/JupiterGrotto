#include "Scene.h"

Scene::Scene() : world(b2Vec2(0.f, 0.f)) {}

Scene::~Scene() {
	while (!objects.empty()) removeObject(*objects.begin());
}

void Scene::update() {
	world.Step(1 / 60.f, 8, 3);
}

void Scene::setGravity(b2Vec2 gravity) {
	world.SetGravity(gravity);
}

std::set<GameObject*>::iterator Scene::objectsBegin() {
	return objects.begin();
}

std::set<GameObject*>::iterator Scene::objectsEnd() {
	return objects.end();
}

void Scene::addObject(std::string baseObjectFileName, sf::Vector2f position) {
	GameObject * addedObject = new GameObject();
	*addedObject = *ResourceManager::get<BaseGameObject>(baseObjectFileName);
	addedObject->startPhysics(world, position);
	objects.insert(addedObject);
}

void Scene::removeObject(GameObject * victim) {
	if (objects.find(victim) == objects.end()) return;
	objects.erase(victim);
	world.DestroyBody(victim->body);
	delete victim;
}

void Scene::loadFromFile(std::string fileName) {
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