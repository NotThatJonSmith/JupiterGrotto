#include "GameObjectDef.h"
#include "ResourceManager.h"
#include "rapidjson/document.h"
#include "JGUtils.h"

GameObjectDef::GameObjectDef() : texture(nullptr),
								 vertexCount(0),
								 vertices(nullptr),
								 origin(sf::Vector2<float>(0, 0)),
								 position(sf::Vector2<int>(0, 0)),
								 friction(0.0f),
								 density(0.0f),
								 dynamic(false) {}

GameObjectDef::~GameObjectDef() {
	if (vertices != nullptr) delete[] vertices;
}

void GameObjectDef::loadFromFile(std::string fileName) {

	rapidjson::Document jsonDom = JGUtils::getJsonDom(fileName);
	
	texture = ResourceManager::get<sf::Texture>(jsonDom["texture"].GetString());
	friction = jsonDom["friction"].GetDouble();
	density = jsonDom["density"].GetDouble();
	dynamic = jsonDom["dynamic"].GetBool();
	origin = sf::Vector2<float>(jsonDom["origin"][0].GetDouble(), jsonDom["origin"][1].GetDouble());
	position = sf::Vector2<float>(jsonDom["position"][0].GetInt(), jsonDom["position"][1].GetDouble());

	const rapidjson::Value& domVertices = jsonDom["vertices"];
	vertices = new sf::Vector2<float>[domVertices.Size()];
	vertexCount = domVertices.Size();

	for (rapidjson::SizeType i = 0; i < domVertices.Size(); i++)
		vertices[i] = sf::Vector2<float>(domVertices[i][0].GetInt(), domVertices[i][1].GetInt());

}
