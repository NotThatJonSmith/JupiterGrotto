#include <SFML\Graphics.hpp>
#include <cstdlib>
#include <list>
#include "GameObject.h"
class View {
private:
	std::string title;
	sf::Vector2<int> dimensions;
	sf::Color bgColor;
	int pixelDepth;
	int fpsLimit;
public:
	sf::Vector2<int> origin;
	sf::RenderWindow * window;
	View();
	~View();
	void update(std::list<GameObject> &objects);
	bool isActive();
	sf::Vector2<int> getMousePosition();
};