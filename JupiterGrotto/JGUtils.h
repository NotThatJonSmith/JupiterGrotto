#pragma once
#include "rapidjson/document.h"

namespace JGUtils {
	rapidjson::Document getJsonDom(std::string fileName);
}