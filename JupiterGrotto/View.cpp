#include "View.h"

View::View() : title("Jupiter Grotto"),
			   dimensions(sf::Vector2i(1200,1200)),
			   bgColor(sf::Color::White),
			   fpsLimit(60),
			   pixelDepth(32),
			   scene(nullptr)   {
	sf::VideoMode videoMode = sf::VideoMode(dimensions.x, dimensions.y, pixelDepth);
	window = new sf::RenderWindow(videoMode, title);
	window->setFramerateLimit(fpsLimit);

	setOrigin(sf::Vector2i(0, 0));
}

View::~View() {
	delete window;
}

bool View::isActive() {
	return window->isOpen();
}

void View::attachToScene(Scene *targetScene) {
	scene = targetScene;
}

void View::update() {
	scene->update();
	handleEvents();
	draw();
}

void View::setOrigin(sf::Vector2i newOrigin) {
	origin = newOrigin;
	sf::View winView = window->getView();
	winView.setSize(dimensions);
	winView.setCenter(origin.x + dimensions.x / 2, origin.y + dimensions.y / 2);
	window->setView(winView);
}

sf::Vector2i View::getOrigin() {
	return origin;
}

sf::Sprite View::getSpriteFromGameObject(GameObject * object) {
	sf::Sprite sprite;
	sprite.setTexture(*(object->getTexture()));
	sprite.setOrigin(object->getOrigin().x, object->getOrigin().y);
	sprite.setPosition(object->getPosition());
	sprite.setRotation(object->getAngle());
	return sprite;
}

void View::draw() {
	window->clear(bgColor);
	for (std::set<GameObject*>::iterator it = scene->objectsBegin(); it != scene->objectsEnd(); it++) {
		GameObject* object = *it;
		sf::Sprite sprite = getSpriteFromGameObject(object);
		window->draw(sprite);
	}
	window->display();
}

void View::handleEvents() {
	sf::Event event;
	while (window->pollEvent(event))
		if (event.type == sf::Event::Closed)
			window->close();
		else if (event.type == sf::Event::Resized)
			dimensions = sf::Vector2f((float)event.size.width, (float)event.size.height);
}

sf::Vector2f View::getMousePosition() {
	return (sf::Vector2f)sf::Mouse::getPosition(*window) + (sf::Vector2f)origin;
}
