#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

static const float SCALE = 30.f;

struct GameObjectDef {

	sf::Texture * texture;
	b2Shape * shape;
	b2World * world;
	sf::Vector2<int> origin;
	sf::Vector2<int> position;
	float friction;
	float density;
	bool dynamic;

	GameObjectDef() :
		texture(nullptr),
		shape(nullptr),
		world(nullptr),
		origin(sf::Vector2(0, 0)),
		position(sf::Vector2(0, 0)),
		friction(0.0f),
		density(0.0f),
		dynamic(false) {}
};

class GameObject {
private:
	sf::Texture * texture;
	b2Body * body;
	sf::Vector2<int> origin;
public:
	GameObject(GameObjectDef &def);
	void draw(sf::RenderWindow &window);
};
