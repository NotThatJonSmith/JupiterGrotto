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
		jsonFile.get(jsonBuffer, bufferSize,'\0');
		jsonFile.close();

		rapidjson::Document jsonDom;
		jsonDom.Parse(jsonBuffer);

		delete[] jsonBuffer;
		return jsonDom;
	}
}