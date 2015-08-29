#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <cstdlib>
#include <list>
#include "GameObject.h"

int main() {

	// Set up the SFML window
	sf::RenderWindow Window(sf::VideoMode(1600, 1200, 32), "JupiterGrotto");
	Window.setFramerateLimit(60);

	// Set up the Box2D world
	b2Vec2 Gravity(0.f, 9.8f);
	b2World World(Gravity);

	// Load the textures we need
	sf::Texture GroundTexture;
	sf::Texture BoxTexture;
	GroundTexture.loadFromFile("res/ground.png");
	BoxTexture.loadFromFile("res/box.png");

	// Create the global list of game objects
	std::list<GameObject> ObjectList;
	ObjectList.push_back(GameObject(World, 400, 500, 800.f, 16.f, &GroundTexture, false));

	// Main game loop
	while (Window.isOpen()) {

		// Listen for the window close event
		sf::Event event;
		while (Window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				Window.close();

		// If the mouse button is down, add more boxes
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			int MouseX = sf::Mouse::getPosition(Window).x;
			int MouseY = sf::Mouse::getPosition(Window).y;
			ObjectList.push_back(GameObject(World, MouseX, MouseY, 16.f, 16.f, &BoxTexture, true));
		}

		// Step the Box2D physics world forward
		World.Step(1 / 60.f, 8, 3);

		// Draw every game object
		Window.clear(sf::Color::White);
		for (std::list<GameObject>::iterator it = ObjectList.begin(); it != ObjectList.end(); it++)
			it->draw(Window);
		Window.display();
	}
	return 0;
}
