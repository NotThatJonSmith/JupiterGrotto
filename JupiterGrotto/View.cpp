#include "View.h"

View::View() : title("Jupiter Grotto"),
			   origin(sf::Vector2<int>(0,0)),
			   dimensions(sf::Vector2<int>(1200,1200)),
			   bgColor(sf::Color::White),
			   fpsLimit(60),
			   pixelDepth(32) {
	window = new sf::RenderWindow(sf::VideoMode(dimensions.x, dimensions.y, pixelDepth), title);
	window->setFramerateLimit(fpsLimit);
}

View::~View() {
	delete window;
}

bool View::isActive() {
	return window->isOpen();
}

void View::update(std::list<GameObject> &objects) {

	// Listen for the window close event
	sf::Event event;
	while (window->pollEvent(event))
		if (event.type == sf::Event::Closed)
			window->close();

	window->clear(bgColor);
	for (std::list<GameObject>::iterator it = objects.begin(); it != objects.end(); it++) {
		sf::Sprite Sprite;
		Sprite.setTexture(*(it->texture));
		Sprite.setOrigin(it->origin.x, it->origin.y);
		Sprite.setPosition(SCALE * it->body->GetPosition().x - origin.x, SCALE * it->body->GetPosition().y - origin.y);
		Sprite.setRotation(it->body->GetAngle() * 180 / b2_pi);
		window->draw(Sprite);
	}

	window->display();
}

sf::Vector2<int> View::getMousePosition() {
	return sf::Vector2<int>(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
}