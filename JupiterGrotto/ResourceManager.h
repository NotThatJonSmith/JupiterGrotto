#include <cstdlib>
#include <unordered_map>
#include <SFML\Graphics.hpp>

class ResourceManager {
private:
	std::string resDir;
	std::unordered_map<std::string, void *> resourceCache;
public:
	ResourceManager();
	ResourceManager(std::string arg_resDir);
	~ResourceManager();

	template <typename T>
	T * get(std::string);

	void unloadAllResources();
};	