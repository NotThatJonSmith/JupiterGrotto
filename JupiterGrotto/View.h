#include <SFML\Graphics.hpp>
#include "Model.h"
#include "GameObject.h"
class View {
private:
	sf::RenderWindow * window;
	std::string title;
	sf::Color bgColor;
	int pixelDepth;
	int fpsLimit;
public:
	sf::Vector2<float> origin;
	sf::Vector2<float> dimensions;
	View();
	~View();
	void update(Model &model);
	bool isActive();
	sf::Vector2<int> getMousePosition();
	
};