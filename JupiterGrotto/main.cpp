#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "View.h"
#include "Model.h"

int main() {
	
	Model model;
	View view;
	model.loadFromFile("res/testbed.wd");
	
	while (view.isActive()) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			model.addObject("box.god", view.getMousePosition());
		model.update();
		view.update(model);
	}
	return 0;
}