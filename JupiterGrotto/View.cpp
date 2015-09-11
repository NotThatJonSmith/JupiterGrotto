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

	model.update();
	sf::View winView = window->getView();
	winView.setSize(dimensions);
	winView.setCenter(origin.x + dimensions.x / 2, origin.y + dimensions.y / 2);
	window->setView(winView);

	sf::Event event;
	while (window->pollEvent(event))
		if (event.type == sf::Event::Closed)
			window->close();
		else if (event.type == sf::Event::Resized)
			dimensions = sf::Vector2f((float)event.size.width, (float)event.size.height);

	window->clear(bgColor);
	for (std::set<GameObject*>::iterator it = model.objects.begin(); it != model.objects.end(); it++) {
		sf::Sprite Sprite;
		Sprite.setTexture(*((*it)->getTexture()));
		Sprite.setOrigin((*it)->getOrigin().x, (*it)->getOrigin().y);
		Sprite.setPosition((*it)->getPosition());
		Sprite.setRotation((*it)->getAngle());
		window->draw(Sprite);
	}
	window->display();
}

sf::Vector2f View::getMousePosition() {
	return sf::Vector2f (sf::Mouse::getPosition(*window).x + origin.x, sf::Mouse::getPosition(*window).y + origin.y);
}