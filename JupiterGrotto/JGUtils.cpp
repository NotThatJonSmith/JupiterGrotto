
#include "JGUtils.h"
#include <fstream>
namespace JGUtils {

	rapidjson::Document getJsonDom(std::string fileName) {
		std::ifstream jsonFile;
		jsonFile.open(fileName, std::ifstream::in);

		jsonFile.seekg(0, std::ios_base::end);
		int bufferSize = jsonFile.tellg();
		jsonFile.seekg(0, std::ios_base::beg);

		char * jsonBuffer = new char[bufferSize];
		jsonFile.get(jsonBuffer, bufferSize, '\0');
		jsonFile.close();

		rapidjson::Document jsonDom;
		jsonDom.Parse(jsonBuffer);

		delete[] jsonBuffer;
		return jsonDom;
	}

	b2Vec2 sf2Box(sf::Vector2<float> sfVector) {
		return b2Vec2(sfVector.x / SCALE, sfVector.y / SCALE);
	}

	sf::Vector2<float> box2Sf(b2Vec2 boxVector) {
		return sf::Vector2<float>(boxVector.x * SCALE, boxVector.y * SCALE);
	}
}