#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "View.h"
#include "Scene.h"

int main() {
	
	Scene scene;
	scene.loadFromFile("res/testbed.wd");

	View view;
	view.attachToScene(&scene);
	
	while (view.isActive()) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			scene.addObject("box.god", view.getMousePosition());
		view.update();
	}

	return 0;
}