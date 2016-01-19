#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "View.h"
#include "Scene.h"

int main() {
	
	Scene scene;
	View view;
	scene.loadFromFile("res/testbed.wd");
	view.attachToScene(&scene);
	
	while (view.isActive()) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			scene.addObject("box.god", view.getMousePosition());
		scene.update();
		view.update();
	}

	return 0;
}