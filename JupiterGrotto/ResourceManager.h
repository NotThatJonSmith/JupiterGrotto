#pragma once
#include <cstdlib>
#include <unordered_map>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class ResourceManager {
private:
	static std::string resDir;
	static std::unordered_map<std::string, void *> resourceCache;
public:
	template <typename T>
	static T * get(std::string);
	static void unloadAllResources();
};	