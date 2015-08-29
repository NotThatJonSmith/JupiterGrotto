#include "ResourceManager.h"

ResourceManager::ResourceManager() : resDir("res/") {}

ResourceManager::ResourceManager(std::string arg_resDir) {
	resDir = arg_resDir;
}

ResourceManager::~ResourceManager() {
	unloadAllResources();
}

// Type T *must* have loadFromFile
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

void ResourceManager::unloadAllResources() {
	for (std::unordered_map<std::string, void *>::iterator it = resourceCache.begin();
		 it != resourceCache.end(); it++)
		delete it->second;
	resourceCache.clear();
}
