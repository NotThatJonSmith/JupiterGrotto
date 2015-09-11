#include <SFML\Graphics.hpp>
#include "Model.h"
#include "GameObject.h"
#include "JGUtils.h"

class View {

private:

	sf::Vector2f origin;
	sf::Vector2f dimensions;
	sf::RenderWindow * window;
	std::string title;
	sf::Color bgColor;
	int pixelDepth;
	int fpsLimit;

public:

	View();
	~View();
	void update(Model &model);
	bool isActive();
	sf::Vector2f getMousePosition();
	
};