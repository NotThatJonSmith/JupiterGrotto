#include "GameObjectDef.h"
#include <fstream>
#include "ResourceManager.h"
#include "rapidjson/document.h"

GameObjectDef::GameObjectDef() :
	texture(nullptr),
	vertexCount(0),
	vertices(nullptr),
	origin(sf::Vector2<float>(0, 0)),
	position(sf::Vector2<int>(0, 0)),
	friction(0.0f),
	density(0.0f),
	dynamic(false) {}

GameObjectDef::~GameObjectDef() {
	if (vertices != nullptr)
		delete[] vertices;
}

void GameObjectDef::loadFromFile(std::string fileName) {
	std::ifstream ifs;
	ifs.open(fileName, std::ifstream::in);
	ifs.seekg(0, std::ios_base::end);
	int len = ifs.tellg();
	char * json = new char[len];
	ifs.seekg(0, std::ios_base::beg);
	ifs.get(json, len, '\0');
	ifs.close();
	rapidjson::Document dom;
	dom.Parse(json);
	texture = ResourceManager::get<sf::Texture>(dom["texture"].GetString());
	friction = dom["friction"].GetDouble();
	density = dom["density"].GetDouble();
	dynamic = dom["dynamic"].GetBool();
	origin = sf::Vector2<float>(dom["origin"][0].GetDouble(), dom["origin"][1].GetDouble());
	position = sf::Vector2<int>(dom["position"][0].GetInt(), dom["position"][1].GetInt());
	const rapidjson::Value& verts = dom["vertices"];
	vertices = new sf::Vector2<int>[verts.Size()];
	vertexCount = verts.Size();
	for (rapidjson::SizeType i = 0; i < verts.Size(); i++)
		vertices[i] = sf::Vector2<int>(verts[i][0].GetInt(), verts[i][1].GetInt());
	delete[] json;
}

void GameObjectDef::saveToFile(std::string fileName) {
	return;
}