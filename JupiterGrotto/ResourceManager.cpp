#include "ResourceManager.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "GameObject.h"

std::string ResourceManager::resDir = "res/";
std::unordered_map<std::string, void *> ResourceManager::resourceCache;

template <typename T>
T * ResourceManager::get(std::string resName) {
	std::unordered_map<std::string, void *>::iterator it = resourceCache.find(resName);
	if (it == resourceCache.end()) {
		T * resource = new T();
		resource->loadFromFile(resDir + resName);
		resourceCache.insert(std::make_pair(resName, resource));
		return resource;
	}
	return (T *)it->second;
}

template sf::Texture * ResourceManager::get(std::string);
template sf::SoundBuffer * ResourceManager::get(std::string);
template BaseGameObject * ResourceManager::get(std::string);

void ResourceManager::unloadAllResources() {
	for (std::unordered_map<std::string, void *>::iterator it = resourceCache.begin();
		 it != resourceCache.end(); it++)
		delete it->second;
	resourceCache.clear();
}