#include <Brick.hpp>

Brick::Brick(float width, float height) : enabled{true} {
	shape.setSize({width, height});
	
	// Give the shape a random color
	shape.setFillColor({static_cast<sf::Uint8>(rand() % 256), static_cast<sf::Uint8>(rand() % 256), static_cast<sf::Uint8>(rand() % 256)});
	
	// Set the origin to the center of the shape
	shape.setOrigin({width/2.0f, height/2.0f}); 
	origin = shape.getOrigin();
	
	// Add the points from the shape to the GameObjects points 
	for (int i = 0; i < shape.getPointCount(); ++i) {
		points.emplace_back(shape.getPoint(i));
	}

	calcNormals();
}

Brick::~Brick() {
}

void Brick::fixedUpdate(Gamemode *gm) {
}

void Brick::update(Gamemode *gm, const float dt) {
}

void Brick::draw(Gamemode *gm) {
	auto& window = gm->getWindow();

	if (enabled) {
		shape.setPosition(position);
		window.draw(shape);
	}
};

void Brick::setEnabled(bool enabled) {
	this->enabled = enabled;
}

bool Brick::getEnabled() const {
	return enabled;
}