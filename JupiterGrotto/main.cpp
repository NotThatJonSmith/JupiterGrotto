#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <cstdlib>
#include <list>
#include "GameObjectDef.h"
#include "GameObject.h"
#include "ResourceManager.h"

int main() {

	// Set up the SFML window, Box2D world, and object list
	sf::RenderWindow Window(sf::VideoMode(1600, 1200, 32), "JupiterGrotto");
	Window.setFramerateLimit(60);
	b2Vec2 Gravity(0.f, 9.8f);
	b2World World(Gravity);
	std::list<GameObject> ObjectList;

	// Load the ground and box object definitions from their files
	GameObjectDef *groundDef = ResourceManager::get<GameObjectDef>("ground.god");
	GameObjectDef *boxDef = ResourceManager::get<GameObjectDef>("box.god");

	// Create a ground object
	GameObject groundObject(*groundDef, World);
	ObjectList.push_back(groundObject);

	// Main game loop
	while (Window.isOpen()) {

		// Listen for the window close event
		sf::Event event;
		while (Window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				Window.close();

		// If the mouse button is down, add more boxes
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			boxDef->position = sf::Vector2<int>(sf::Mouse::getPosition(Window).x, sf::Mouse::getPosition(Window).y);
			ObjectList.push_back(GameObject(*boxDef, World));
		}

		// Step physics and graphics forward
		World.Step(1 / 60.f, 8, 3);
		Window.clear(sf::Color::White);
		for (std::list<GameObject>::iterator it = ObjectList.begin(); it != ObjectList.end(); it++)
			it->draw(Window);
		Window.display();
	}
	return 0;
}
