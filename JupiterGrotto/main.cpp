#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <cstdlib>
#include <list>
#include "GameObjectDef.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "View.h"

int main() {

	// Construct a default view.
	View view;

	// Model should contain the b2World and object list
	b2Vec2 Gravity(0.f, 9.81f);
	b2World World(Gravity);
	std::list<GameObject> ObjectList;

	// Load the ground and box object definitions from their files
	GameObjectDef *groundDef = ResourceManager::get<GameObjectDef>("ground.god");
	GameObjectDef *boxDef = ResourceManager::get<GameObjectDef>("box.god");

	// Create a ground object
	GameObject groundObject(*groundDef, World);
	ObjectList.push_back(groundObject);
	bool w, a, s, d; w = false; a = false; s = false; d = false;

	// Main game loop
	while (view.isActive()) {

		// If the mouse button is down, add more boxes. Should go in a controller
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			boxDef->position = view.getMousePosition();
			ObjectList.push_back(GameObject(*boxDef, World));
		}

		// Right mouse toggles gravity!
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			World.SetGravity(b2Vec2((World.GetGravity() == b2Vec2(0.f, 9.81f)) ? b2Vec2(0.f, 0.f) : b2Vec2(0.f, 9.81f)));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (!w) {
				w = true;
				view.origin.y -= 10;
			}
		} else w = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (!s) {
				s = true;
				view.origin.y += 10;
			}
		} else s = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (!d) {
				d = true;
				view.origin.x += 10;
			}
		} else d = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			if (!a) {
				a = true;
				view.origin.x -= 10;
			}
		} else a = false;

		// Step physics and graphics forward
		World.Step(1 / 60.f, 8, 3);
		view.update(ObjectList);

		// ULTIMATE GOAL: view.show(model.update(controller));
	}
	return 0;
}
