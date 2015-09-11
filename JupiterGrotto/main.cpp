#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "View.h"
#include "Model.h"

int main() {
	
	Model model;
	View view;

	model.setGravity(b2Vec2(0.f, 9.81f));
	model.addObject("ground.god", sf::Vector2<float>(800, 1100));

	while (view.isActive()) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			model.addObject("box.god", view.getMousePosition());

		model.update();
		view.update(model);
	}
	return 0;
}