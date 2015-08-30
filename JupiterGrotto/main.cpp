#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <cstdlib>
#include <list>
#include "GameObject.h"
#include "ResourceManager.h"

// Linked to sfml-main.lib so that the main function name is platform-independent
int main() {

	// Set up the SFML window
	sf::RenderWindow Window(sf::VideoMode(1600, 1200, 32), "JupiterGrotto");
	Window.setFramerateLimit(60);

	// Set up the Resource Manager
	ResourceManager manager;

	// Set up the Box2D world
	b2Vec2 Gravity(0.f, 9.8f);
	b2World World(Gravity);

	// Create the global list of game objects
	std::list<GameObject> ObjectList;

	// Specify everything about the ground box. Looks like a form to fill out, right?
	GameObjectDef groundDef;
	groundDef.texture = manager.get<sf::Texture>("ground.png");
	groundDef.dynamic = false;
	groundDef.density = 0.0f;
	groundDef.friction = 0.5f;
	groundDef.world = &World;
	groundDef.origin = sf::Vector2<int>(800, 8);
	groundDef.position = sf::Vector2<int>(800, 800);
	groundDef.vertexCount = 4;
	groundDef.vertices = new sf::Vector2<int>[groundDef.vertexCount];
	groundDef.vertices[0] = sf::Vector2<int>(-800, 8);
	groundDef.vertices[1] = sf::Vector2<int>(-800, -8);
	groundDef.vertices[2] = sf::Vector2<int>(800, -8);
	groundDef.vertices[3] = sf::Vector2<int>(800, 8);

	GameObjectDef boxDef;
	boxDef.texture = manager.get<sf::Texture>("box.png");
	boxDef.dynamic = true;
	boxDef.density = 1.f;
	boxDef.friction = 0.7f;
	boxDef.world = &World;
	boxDef.origin = sf::Vector2<int>(16, 16);
	boxDef.position = sf::Vector2<int>(0, 0);
	boxDef.vertexCount = 4;
	boxDef.vertices = new sf::Vector2<int>[boxDef.vertexCount];
	boxDef.vertices[0] = sf::Vector2<int>(-16, 16);
	boxDef.vertices[1] = sf::Vector2<int>(-16, -16);
	boxDef.vertices[2] = sf::Vector2<int>(16, -16);
	boxDef.vertices[3] = sf::Vector2<int>(16, 16);

	// Actually make the ground object
	GameObject groundObject(groundDef);
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
			int MouseX = sf::Mouse::getPosition(Window).x;
			int MouseY = sf::Mouse::getPosition(Window).y;
			boxDef.position = sf::Vector2<int>(MouseX, MouseY);
			ObjectList.push_back(GameObject(boxDef));
		}

		// Step the Box2D physics world forward
		World.Step(1 / 60.f, 8, 3);

		// Draw every game object
		Window.clear(sf::Color::White);
		for (std::list<GameObject>::iterator it = ObjectList.begin(); it != ObjectList.end(); it++)
			it->draw(Window);
		Window.display();
	}

	delete groundDef.vertices;
	delete boxDef.vertices;

	return 0;
}
