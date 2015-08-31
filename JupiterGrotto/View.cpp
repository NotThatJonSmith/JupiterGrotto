#include "View.h"

View::View() : title("Jupiter Grotto"),
			   origin(sf::Vector2<int>(0,0)),
			   dimensions(sf::Vector2<int>(1200,1200)),
			   bgColor(sf::Color::White),
			   fpsLimit(60),
			   pixelDepth(32) {
	window = new sf::RenderWindow(sf::VideoMode((int)dimensions.x, (int)dimensions.y, pixelDepth), title);
	window->setFramerateLimit(fpsLimit);
}

View::~View() {
	delete window;
}

bool View::isActive() {
	return window->isOpen();
}

void View::update(Model &model) {

	sf::View winView = window->getView();
	winView.setSize(dimensions);
	winView.setCenter(origin.x + dimensions.x / 2, origin.y + dimensions.y / 2);
	window->setView(winView);

	sf::Event event;
	while (window->pollEvent(event))
		if (event.type == sf::Event::Closed)
			window->close();
		else if (event.type == sf::Event::Resized) {
			dimensions = sf::Vector2<float>((float)event.size.width, (float)event.size.height);
		}


	// Draw the window
	window->clear(bgColor);
	for (std::list<GameObject>::iterator it = model.objects.begin(); it != model.objects.end(); it++) {
		sf::Sprite Sprite;
		Sprite.setTexture(*(it->texture));
		Sprite.setOrigin(it->origin.x, it->origin.y);
		Sprite.setPosition(SCALE * it->body->GetPosition().x, SCALE * it->body->GetPosition().y);
		Sprite.setRotation(it->body->GetAngle() * 180 / b2_pi);
		window->draw(Sprite);
	}
	window->display();
}

sf::Vector2<int> View::getMousePosition() {
	return sf::Vector2<int> (sf::Mouse::getPosition(*window).x + origin.x, sf::Mouse::getPosition(*window).y + origin.y);
}