#include <SFML\Graphics.hpp>
#include "Scene.h"
#include "GameObject.h"
#include "JGUtils.h"

class View {

private:

	sf::Vector2i origin;
	sf::Vector2f dimensions;
	sf::RenderWindow * window;
	std::string title;
	sf::Color bgColor;
	int pixelDepth;
	int fpsLimit;
	Scene *scene;
	void handleEvents();
	void draw();

public:
	View();
	~View();
	void update();
	void attachToScene(Scene *targetScene);
	bool isActive();
	sf::Vector2f getMousePosition();
	sf::Sprite getSpriteFromGameObject(GameObject * object);
	void setOrigin(sf::Vector2i newOrigin);
	sf::Vector2i getOrigin();
	
};
